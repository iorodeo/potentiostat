using System.Text.Json.Nodes;
using System.Threading.Channels;
using IoRodeo.SharpStatDriver.Protocol;

namespace IoRodeo.SharpStatDriver.Simulation;

/// <summary>
/// In-process stand-in for the Rodeostat firmware: implements <see cref="ISerialTransport"/>
/// without touching any real hardware, so <see cref="Potentiostat"/> can be driven exactly
/// as it would be over a real serial port. Reports the same identity as the reference
/// hardware (<see cref="HardwareVariant"/>/<see cref="FirmwareVersion"/>/<see cref="HardwareVersion"/>)
/// and answers <c>runTest</c> by streaming samples computed by <see cref="DummyWaveformGenerator"/>
/// from whatever parameters were set via <c>setParam</c>, paced in real time by the configured
/// sample period.
/// </summary>
public sealed class DummyTransport : ISerialTransport
{
    public const string HardwareVariant = "10V_10MilliAmpV0.2";
    public const string FirmwareVersion = "FW0.0.9";
    public const string HardwareVersion = "HW0.2";

    private static readonly string[] TestNames =
        { "constant", "chronoamp", "cyclic", "linearSweep", "sinusoid", "squareWave" };

    private readonly Channel<string> _wire = Channel.CreateUnbounded<string>();
    private readonly Dictionary<string, JsonObject> _params = BuildDefaultParams();
    private readonly Random _rng = new();

    private string _currRange = "1000uA";
    private string _voltRange = "10V";
    private int _samplePeriodMs = 10;
    private CancellationTokenSource? _runCts;

    public bool IsOpen { get; private set; }

    public void Open() => IsOpen = true;

    public void Close() => IsOpen = false;

    public void DiscardInput()
    {
        // Nothing queued that the driver didn't ask for.
    }

    public Task WriteLineAsync(string line, CancellationToken cancellationToken = default)
    {
        var cmd = JsonNode.Parse(line)!.AsObject();
        string command = cmd[JsonKeys.Command]!.GetValue<string>();

        switch (command)
        {
            case Commands.RunTest:
                StartRun(cmd);
                break;
            case Commands.StopTest:
                _runCts?.Cancel();
                break;
            default:
                _wire.Writer.TryWrite(BuildResponse(cmd, command));
                break;
        }

        return Task.CompletedTask;
    }

    public async Task<string> ReadLineAsync(CancellationToken cancellationToken = default)
        => await _wire.Reader.ReadAsync(cancellationToken).ConfigureAwait(false);

    public void Dispose()
    {
        _runCts?.Cancel();
        _wire.Writer.TryComplete();
    }

    // ------------------------------------------------------------------
    // Command handling
    // ------------------------------------------------------------------

    private string BuildResponse(JsonObject cmd, string command)
    {
        var response = new JsonObject { [JsonKeys.Command] = command };
        switch (command)
        {
            case Commands.GetVariant:
                response[JsonKeys.Variant] = HardwareVariant;
                break;
            case Commands.GetVersion:
                response[JsonKeys.Version] = FirmwareVersion;
                break;
            case Commands.GetHardwareVersion:
                response[JsonKeys.Version] = HardwareVersion;
                break;
            case Commands.GetTestNames:
                response[JsonKeys.TestNameArray] = new JsonArray(TestNames.Select(n => (JsonNode)n).ToArray());
                break;
            case Commands.GetMuxEnabled:
                response[JsonKeys.MuxEnabled] = false;
                break;
            case Commands.GetParam:
            {
                string test = cmd[JsonKeys.Test]!.GetValue<string>();
                response[JsonKeys.Test] = test;
                response[JsonKeys.Param] = _params[test].DeepClone();
                break;
            }
            case Commands.SetParam:
            {
                string test = cmd[JsonKeys.Test]!.GetValue<string>();
                _params[test] = cmd[JsonKeys.Param]!.AsObject().DeepClone().AsObject();
                response[JsonKeys.Test] = test;
                response[JsonKeys.Param] = _params[test].DeepClone();
                break;
            }
            case Commands.GetCurrRange:
                response[JsonKeys.CurrRange] = _currRange;
                break;
            case Commands.SetCurrRange:
                _currRange = cmd[JsonKeys.CurrRange]!.GetValue<string>();
                response[JsonKeys.CurrRange] = _currRange;
                break;
            case Commands.GetVoltRange:
                response[JsonKeys.VoltRange] = _voltRange;
                break;
            case Commands.SetVoltRange:
                _voltRange = cmd[JsonKeys.VoltRange]!.GetValue<string>();
                response[JsonKeys.VoltRange] = _voltRange;
                break;
            case Commands.GetSamplePeriod:
                response[JsonKeys.SamplePeriod] = _samplePeriodMs;
                break;
            case Commands.SetSamplePeriod:
                _samplePeriodMs = cmd[JsonKeys.SamplePeriod]!.GetValue<int>();
                response[JsonKeys.SamplePeriod] = _samplePeriodMs;
                break;
            case Commands.GetTestDoneTime:
            {
                string test = cmd[JsonKeys.Test]!.GetValue<string>();
                response[JsonKeys.Test] = test;
                response[JsonKeys.TestDoneTime] = DummyWaveformGenerator.GetTotalDurationMs(test, _params[test]);
                break;
            }
            case Commands.RunTest:
                response[JsonKeys.Test] = cmd[JsonKeys.Test]!.GetValue<string>();
                break;
            default:
                break;
        }
        return new JsonObject { [JsonKeys.Success] = true, [JsonKeys.Response] = response }.ToJsonString();
    }

    private void StartRun(JsonObject cmd)
    {
        string test = cmd[JsonKeys.Test]!.GetValue<string>();
        _wire.Writer.TryWrite(BuildResponse(cmd, Commands.RunTest));

        var param = _params[test].DeepClone().AsObject();
        string currRange = _currRange;
        int samplePeriodMs = Math.Max(1, _samplePeriodMs);
        double totalMs = DummyWaveformGenerator.GetTotalDurationMs(test, param);

        var cts = new CancellationTokenSource();
        _runCts = cts;
        _ = Task.Run(() => StreamAsync(test, param, currRange, samplePeriodMs, totalMs, cts.Token));
    }

    private async Task StreamAsync(
        string test, JsonObject param, string currRange, int samplePeriodMs, double totalMs, CancellationToken ct)
    {
        try
        {
            double elapsedMs = 0.0;
            while (elapsedMs <= totalMs)
            {
                var (volt, curr) = DummyWaveformGenerator.Evaluate(test, param, elapsedMs, currRange, _rng);
                var sample = new JsonObject
                {
                    [JsonKeys.Time] = elapsedMs,
                    [JsonKeys.Volt] = volt,
                    [JsonKeys.Curr] = curr,
                };
                _wire.Writer.TryWrite(sample.ToJsonString());

                elapsedMs += samplePeriodMs;
                await Task.Delay(samplePeriodMs, ct).ConfigureAwait(false);
            }
        }
        catch (OperationCanceledException)
        {
            // stopTest requested; fall through to the terminator below.
        }
        finally
        {
            _wire.Writer.TryWrite("{}");
        }
    }

    private static Dictionary<string, JsonObject> BuildDefaultParams() => new()
    {
        ["constant"] = new JsonObject
        {
            ["value"] = 0.5, ["duration"] = 5000, ["quietValue"] = 0.0, ["quietTime"] = 500,
        },
        ["chronoamp"] = new JsonObject
        {
            ["step"] = new JsonArray(new JsonArray(2000, 0.0), new JsonArray(2000, 0.5)),
            ["quietValue"] = 0.0,
            ["quietTime"] = 500,
        },
        ["cyclic"] = new JsonObject
        {
            ["amplitude"] = 0.5, ["offset"] = 0.0, ["period"] = 1000, ["numCycles"] = 2, ["shift"] = 0.0,
            ["quietValue"] = 0.0, ["quietTime"] = 500,
        },
        ["linearSweep"] = new JsonObject
        {
            ["startValue"] = -0.5, ["finalValue"] = 0.5, ["duration"] = 5000,
            ["quietValue"] = 0.0, ["quietTime"] = 500,
        },
        ["sinusoid"] = new JsonObject
        {
            ["amplitude"] = 0.5, ["offset"] = 0.0, ["period"] = 1000, ["numCycles"] = 2, ["shift"] = 0.0,
            ["quietValue"] = 0.0, ["quietTime"] = 500,
        },
        ["squareWave"] = new JsonObject
        {
            ["amplitude"] = 0.5, ["startValue"] = -0.5, ["finalValue"] = 0.5, ["stepValue"] = 0.05, ["window"] = 100,
            ["quietValue"] = 0.0, ["quietTime"] = 500,
        },
    };
}
