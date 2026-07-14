using System.Text.Json;
using System.Text.Json.Nodes;
using IoRodeo.SharpStatDriver.Protocol;

namespace IoRodeo.SharpStatDriver;

/// <summary>
/// High level async interface for serial communications with the IO Rodeo
/// Rodeostat open source potentiostat. C# port of the Python driver
/// (potentiostat.py); the wire protocol is newline-delimited JSON at 115200 baud.
/// </summary>
public class Potentiostat : IDisposable, IAsyncDisposable
{
    public const int BaudRate = 115200;
    public const string MinimumFirmwareVersionForMux = "0.0.5";
    public static readonly TimeSpan DefaultTimeout = TimeSpan.FromSeconds(2.0);

    private readonly ISerialTransport _transport;
    private bool _disposed;

    /// <summary>Creates a driver for the device on the given serial port (e.g. "COM3", "/dev/ttyACM0").</summary>
    public Potentiostat(string portName, TimeSpan? timeout = null)
        : this(new SerialJsonTransport(portName, BaudRate, timeout ?? DefaultTimeout))
    {
    }

    /// <summary>Creates a driver over a custom transport (used for testing).</summary>
    public Potentiostat(ISerialTransport transport)
    {
        _transport = transport;
    }

    /// <summary>True while a voltammetric test is streaming data.</summary>
    public bool TestRunning { get; private set; }

    /// <summary>Hardware variant string, e.g. "10V_microAmpV0.2". Populated by <see cref="ConnectAsync"/>.</summary>
    public string HardwareVariant { get; private set; } = string.Empty;

    /// <summary>Firmware version string. Populated by <see cref="ConnectAsync"/>.</summary>
    public string FirmwareVersion { get; private set; } = string.Empty;

    /// <summary>Hardware version string, e.g. "HW0.2". Populated by <see cref="ConnectAsync"/>.</summary>
    public string HardwareVersion { get; private set; } = string.Empty;

    /// <summary>Raised for every sample received while a test is running.</summary>
    public event EventHandler<SampleEventArgs>? SampleReceived;

    /// <summary>
    /// Opens the serial port, flushes any stale input and caches the device's
    /// hardware variant, firmware version and hardware version.
    /// </summary>
    public async Task ConnectAsync(CancellationToken cancellationToken = default)
    {
        if (!_transport.IsOpen)
        {
            _transport.Open();
        }
        _transport.DiscardInput();
        HardwareVariant = await GetHardwareVariantAsync(cancellationToken).ConfigureAwait(false);
        FirmwareVersion = await GetFirmwareVersionAsync(cancellationToken).ConfigureAwait(false);
        HardwareVersion = await GetHardwareVersionAsync(cancellationToken).ConfigureAwait(false);
    }

    // ------------------------------------------------------------------
    // Basic getters/setters
    // ------------------------------------------------------------------

    /// <summary>Returns the hardware variant string, e.g. "10V_microAmpV0.2".</summary>
    public async Task<string> GetHardwareVariantAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetVariant), ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.Variant);
    }

    /// <summary>Stops any currently running test.</summary>
    public Task StopTestAsync(bool expectResponse = true, CancellationToken ct = default)
        => SendCommandAsync(NewCommand(Commands.StopTest), expectResponse, ct);

    /// <summary>Gets the output voltage setting (potential between working and reference electrode), volts.</summary>
    public async Task<double> GetVoltAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetVolt), ct: ct).ConfigureAwait(false);
        return GetDouble(rsp, JsonKeys.Volt);
    }

    /// <summary>Sets the output voltage setting, volts. Returns the value echoed by the device.</summary>
    public async Task<double> SetVoltAsync(double volt, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetVolt);
        cmd[JsonKeys.Volt] = volt;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetDouble(rsp, JsonKeys.Volt);
    }

    /// <summary>Gets an immediate measurement of the working electrode current, microamps.</summary>
    public async Task<double> GetCurrAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetCurr), ct: ct).ConfigureAwait(false);
        return GetDouble(rsp, JsonKeys.Curr);
    }

    /// <summary>Gets an immediate measurement of the working-to-reference electrode potential, volts.</summary>
    public async Task<double> GetRefVoltAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetRefVolt), ct: ct).ConfigureAwait(false);
        return GetDouble(rsp, JsonKeys.RefVolt);
    }

    /// <summary>Returns the current parameter values for the given voltammetric test, e.g. "cyclic".</summary>
    public async Task<JsonObject> GetParamAsync(string testName, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.GetParam);
        cmd[JsonKeys.Test] = testName;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return rsp[JsonKeys.Param]!.AsObject().DeepClone().AsObject();
    }

    /// <summary>Sets the parameters for the given voltammetric test. Returns the values echoed by the device.</summary>
    public async Task<JsonObject> SetParamAsync(string testName, JsonNode param, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetParam);
        cmd[JsonKeys.Test] = testName;
        cmd[JsonKeys.Param] = param.DeepClone();
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return rsp[JsonKeys.Param]!.AsObject().DeepClone().AsObject();
    }

    /// <summary>Sets the output voltage range, e.g. "1V". Returns the range echoed by the device.</summary>
    public async Task<string> SetVoltRangeAsync(string voltRange, CancellationToken ct = default)
    {
        if (!GetAllVoltRanges().Contains(voltRange))
        {
            throw new ArgumentException($"unknown voltage range '{voltRange}'", nameof(voltRange));
        }
        var cmd = NewCommand(Commands.SetVoltRange);
        cmd[JsonKeys.VoltRange] = voltRange;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.VoltRange);
    }

    /// <summary>Gets the current output voltage range, e.g. "1V".</summary>
    public async Task<string> GetVoltRangeAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetVoltRange), ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.VoltRange);
    }

    /// <summary>Voltage ranges supported by the connected hardware variant.</summary>
    public IReadOnlyList<string> GetAllVoltRanges()
        => HardwareVariants.VoltRangesByVariant[HardwareVariant];

    /// <summary>Sets the working electrode current range, e.g. "10uA". Returns the range echoed by the device.</summary>
    public async Task<string> SetCurrRangeAsync(string currRange, CancellationToken ct = default)
    {
        if (!GetAllCurrRanges().Contains(currRange))
        {
            throw new ArgumentException($"unknown current range '{currRange}'", nameof(currRange));
        }
        var cmd = NewCommand(Commands.SetCurrRange);
        cmd[JsonKeys.CurrRange] = currRange;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.CurrRange);
    }

    /// <summary>Gets the working electrode current range, e.g. "10uA".</summary>
    public async Task<string> GetCurrRangeAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetCurrRange), ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.CurrRange);
    }

    /// <summary>Current ranges supported by the connected hardware variant.</summary>
    public IReadOnlyList<string> GetAllCurrRanges()
        => HardwareVariants.CurrRangesByVariant[HardwareVariant];

    /// <summary>Gets the device identification number.</summary>
    public async Task<int> GetDeviceIdAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetDeviceId), ct: ct).ConfigureAwait(false);
        return GetInt(rsp, JsonKeys.DeviceId);
    }

    /// <summary>Sets the device identification number. Returns the value echoed by the device.</summary>
    public async Task<int> SetDeviceIdAsync(int deviceId, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetDeviceId);
        cmd[JsonKeys.DeviceId] = deviceId;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetInt(rsp, JsonKeys.DeviceId);
    }

    /// <summary>Sets the sample period (time between samples), milliseconds.</summary>
    public async Task<int> SetSamplePeriodAsync(int samplePeriodMs, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetSamplePeriod);
        cmd[JsonKeys.SamplePeriod] = samplePeriodMs;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetInt(rsp, JsonKeys.SamplePeriod);
    }

    /// <summary>Gets the sample period (time between samples), milliseconds.</summary>
    public async Task<int> GetSamplePeriodAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetSamplePeriod), ct: ct).ConfigureAwait(false);
        return GetInt(rsp, JsonKeys.SamplePeriod);
    }

    /// <summary>Sets the sample rate in Hz (alternative to setting the sample period).</summary>
    public async Task<double> SetSampleRateAsync(double sampleRateHz, CancellationToken ct = default)
    {
        int samplePeriod = (int)(1.0e3 / sampleRateHz);
        int actualPeriod = await SetSamplePeriodAsync(samplePeriod, ct).ConfigureAwait(false);
        return 1.0e3 / actualPeriod;
    }

    /// <summary>Gets the sample rate in Hz (1000 / sample period in ms).</summary>
    public async Task<double> GetSampleRateAsync(CancellationToken ct = default)
    {
        int samplePeriod = await GetSamplePeriodAsync(ct).ConfigureAwait(false);
        return 1.0e3 / samplePeriod;
    }

    /// <summary>Time required to complete the given test including quiet time, seconds.</summary>
    public async Task<double> GetTestDoneTimeAsync(string testName, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.GetTestDoneTime);
        cmd[JsonKeys.Test] = testName;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetDouble(rsp, JsonKeys.TestDoneTime) * 1.0e-3;
    }

    /// <summary>Names of all tests supported by the device firmware.</summary>
    public async Task<IReadOnlyList<string>> GetTestNamesAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetTestNames), ct: ct).ConfigureAwait(false);
        return GetStringList(rsp, JsonKeys.TestNameArray);
    }

    /// <summary>Firmware version string reported by the device.</summary>
    public async Task<string> GetFirmwareVersionAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetVersion), ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.Version);
    }

    /// <summary>
    /// Hardware version string, e.g. "HW0.2". Firmware that predates this
    /// command fails the request, in which case "HW0.1 (default)" is returned.
    /// </summary>
    public async Task<string> GetHardwareVersionAsync(CancellationToken ct = default)
    {
        try
        {
            var rsp = await SendCommandAsync(NewCommand(Commands.GetHardwareVersion), ct: ct).ConfigureAwait(false);
            return GetString(rsp, JsonKeys.Version);
        }
        catch (Exception ex) when (ex is PotentiostatException or TimeoutException)
        {
            return HardwareVersions.Default;
        }
    }

    // ------------------------------------------------------------------
    // Electrode connection control (requires hardware >= HW0.2)
    // ------------------------------------------------------------------

    /// <summary>Sets the connected state of the reference electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> SetRefElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetRefElectConnected, value, requireHw0p2: true, ct);

    /// <summary>Gets the connected state of the reference electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> GetRefElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetRefElectConnected, requireHw0p2: true, ct);

    /// <summary>Sets the connected state of the counter electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> SetCtrElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetCtrElectConnected, value, requireHw0p2: true, ct);

    /// <summary>Gets the connected state of the counter electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> GetCtrElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetCtrElectConnected, requireHw0p2: true, ct);

    /// <summary>Sets the connected state of the working electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> SetWrkElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetWrkElectConnected, value, requireHw0p2: true, ct);

    /// <summary>Gets the connected state of the working electrode. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> GetWrkElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetWrkElectConnected, requireHw0p2: true, ct);

    /// <summary>Sets the connected state of all electrodes. Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> SetAllElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetAllElectConnected, value, requireHw0p2: true, ct);

    /// <summary>Gets the connected state of all electrodes (true only if all connected). Requires hardware &gt;= HW0.2.</summary>
    public Task<bool> GetAllElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetAllElectConnected, requireHw0p2: true, ct);

    /// <summary>
    /// Enables/disables auto-connect: electrodes are connected at the start of
    /// each test and disconnected at the end. Requires hardware &gt;= HW0.2.
    /// </summary>
    public async Task<bool> SetAutoConnectAsync(bool value, CancellationToken ct = default)
    {
        CheckHardwareVersion(HardwareVersions.V0p2);
        var cmd = NewCommand(Commands.SetElectAutoConnect);
        cmd[JsonKeys.AutoConnect] = value;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.AutoConnect);
    }

    /// <summary>Gets the auto-connect setting. Requires hardware &gt;= HW0.2.</summary>
    public async Task<bool> GetAutoConnectAsync(CancellationToken ct = default)
    {
        CheckHardwareVersion(HardwareVersions.V0p2);
        var rsp = await SendCommandAsync(NewCommand(Commands.GetElectAutoConnect), ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.AutoConnect);
    }

    /// <summary>Sets the voltage range for the reference electrode analog input. Requires hardware &gt;= HW0.2.</summary>
    public async Task<string> SetRefElectVoltRangeAsync(string voltRange, CancellationToken ct = default)
    {
        CheckHardwareVersion(HardwareVersions.V0p2);
        if (!GetAllVoltRanges().Contains(voltRange))
        {
            throw new ArgumentException($"unknown voltage range '{voltRange}'", nameof(voltRange));
        }
        var cmd = NewCommand(Commands.SetRefElectVoltRange);
        cmd[JsonKeys.VoltRange] = voltRange;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.VoltRange);
    }

    /// <summary>Gets the voltage range for the reference electrode analog input. Requires hardware &gt;= HW0.2.</summary>
    public async Task<string> GetRefElectVoltRangeAsync(CancellationToken ct = default)
    {
        CheckHardwareVersion(HardwareVersions.V0p2);
        var rsp = await SendCommandAsync(NewCommand(Commands.GetRefElectVoltRange), ct: ct).ConfigureAwait(false);
        return GetString(rsp, JsonKeys.VoltRange);
    }

    // ------------------------------------------------------------------
    // Multiplexer expansion hardware
    // ------------------------------------------------------------------

    /// <summary>Enables/disables the multiplexer expansion hardware.</summary>
    public async Task<bool> SetMuxEnabledAsync(bool value, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetMuxEnabled);
        cmd[JsonKeys.MuxEnabled] = value;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.MuxEnabled);
    }

    /// <summary>Gets the multiplexer enabled state.</summary>
    public async Task<bool> GetMuxEnabledAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetMuxEnabled), ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.MuxEnabled);
    }

    /// <summary>Enables the given subset of mux working electrode channels, e.g. [1,2,5].</summary>
    public async Task<IReadOnlyList<int>> SetEnabledMuxChannelsAsync(IEnumerable<int> channels, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetEnabledMuxChannels);
        var array = new JsonArray();
        foreach (int chan in channels)
        {
            array.Add(chan);
        }
        cmd[JsonKeys.MuxChannel] = array;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetIntList(rsp, JsonKeys.MuxChannel);
    }

    /// <summary>Gets the list of enabled mux working electrode channels.</summary>
    public async Task<IReadOnlyList<int>> GetEnabledMuxChannelsAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetEnabledMuxChannels), ct: ct).ConfigureAwait(false);
        return GetIntList(rsp, JsonKeys.MuxChannel);
    }

    /// <summary>Names of tests compatible with the multiplexer expansion hardware.</summary>
    public async Task<IReadOnlyList<string>> GetMuxTestNamesAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetMuxTestNames), ct: ct).ConfigureAwait(false);
        return GetStringList(rsp, JsonKeys.TestNameArray);
    }

    /// <summary>Sets the connected state of the reference electrode when using the multiplexer.</summary>
    public Task<bool> SetMuxRefElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetMuxRefElectConnected, value, requireHw0p2: false, ct);

    /// <summary>Gets the connected state of the reference electrode when using the multiplexer.</summary>
    public Task<bool> GetMuxRefElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetMuxRefElectConnected, requireHw0p2: false, ct);

    /// <summary>Sets the connected state of the counter electrode when using the multiplexer.</summary>
    public Task<bool> SetMuxCtrElectConnectedAsync(bool value, CancellationToken ct = default)
        => SetConnectedAsync(Commands.SetMuxCtrElectConnected, value, requireHw0p2: false, ct);

    /// <summary>Gets the connected state of the counter electrode when using the multiplexer.</summary>
    public Task<bool> GetMuxCtrElectConnectedAsync(CancellationToken ct = default)
        => GetConnectedAsync(Commands.GetMuxCtrElectConnected, requireHw0p2: false, ct);

    /// <summary>
    /// Connects the mux working electrode to the given channel (1-7), or
    /// disconnects it when <paramref name="channel"/> is null. Returns the
    /// connected channel, or null when disconnected.
    /// </summary>
    public async Task<int?> SetMuxWrkElectConnectedAsync(int? channel, CancellationToken ct = default)
    {
        var cmd = NewCommand(Commands.SetMuxWrkElectConnected);
        cmd[JsonKeys.Connected] = channel is int c ? JsonValue.Create(c) : JsonValue.Create(false);
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetMuxWrkConnection(rsp);
    }

    /// <summary>Gets the mux working electrode channel (1-7), or null when disconnected.</summary>
    public async Task<int?> GetMuxWrkElectConnectedAsync(CancellationToken ct = default)
    {
        var rsp = await SendCommandAsync(NewCommand(Commands.GetMuxWrkElectConnected), ct: ct).ConfigureAwait(false);
        return GetMuxWrkConnection(rsp);
    }

    /// <summary>Disconnects all electrodes when using the multiplexer expansion hardware.</summary>
    public Task DisconnectAllMuxElectAsync(CancellationToken ct = default)
        => SendCommandAsync(NewCommand(Commands.DisconnectAllMuxElect), ct: ct);

    // ------------------------------------------------------------------
    // Test streaming
    // ------------------------------------------------------------------

    /// <summary>
    /// Runs the named voltammetric test (e.g. "cyclic", "constant",
    /// "linearSweep") and collects the streamed data. Subscribe to
    /// <see cref="SampleReceived"/> for live samples; pass
    /// <paramref name="progress"/> to drive a progress bar. Cancelling the
    /// token stops the test on the device and throws
    /// <see cref="OperationCanceledException"/>.
    /// </summary>
    /// <param name="testName">Name of the test to run.</param>
    /// <param name="param">Optional test parameters; when null the device's current values are used.</param>
    /// <param name="progress">Optional progress sink, reported once per sample.</param>
    /// <param name="maxDecodeErrors">
    /// Maximum number of malformed streamed lines tolerated before
    /// <see cref="DataDecodeException"/> is thrown; null means unlimited.
    /// </param>
    public async Task<TestResult> RunTestAsync(
        string testName,
        JsonNode? param = null,
        IProgress<TestProgress>? progress = null,
        int? maxDecodeErrors = 0,
        CancellationToken cancellationToken = default)
    {
        bool muxEnabled = false;
        IReadOnlyList<int> channelList = new[] { 0 };
        if (string.Compare(FirmwareVersion, MinimumFirmwareVersionForMux, StringComparison.Ordinal) >= 0)
        {
            muxEnabled = await GetMuxEnabledAsync(cancellationToken).ConfigureAwait(false);
            if (muxEnabled)
            {
                channelList = await GetEnabledMuxChannelsAsync(cancellationToken).ConfigureAwait(false);
            }
        }

        if (param is not null)
        {
            await SetParamAsync(testName, param, cancellationToken).ConfigureAwait(false);
        }

        double testDoneSeconds = 0.0;
        if (progress is not null)
        {
            testDoneSeconds = await GetTestDoneTimeAsync(testName, cancellationToken).ConfigureAwait(false);
        }

        var data = channelList.ToDictionary(chan => chan, _ => new ChannelDataBuilder());

        var runCmd = NewCommand(Commands.RunTest);
        runCmd[JsonKeys.Test] = testName;
        await SendCommandAsync(runCmd, ct: cancellationToken).ConfigureAwait(false);
        TestRunning = true;

        bool limitError = false;
        int decodeErrors = 0;
        bool cancelRequested = false;
        try
        {
            while (true)
            {
                if (cancellationToken.IsCancellationRequested && !cancelRequested)
                {
                    // Ask the device to stop, then keep reading until it sends
                    // the end-of-test terminator so no stale data is left in
                    // the serial buffer for the next command.
                    cancelRequested = true;
                    await StopTestAsync(expectResponse: false, CancellationToken.None).ConfigureAwait(false);
                }

                string line = await _transport.ReadLineAsync(CancellationToken.None).ConfigureAwait(false);

                JsonObject sampleObj;
                try
                {
                    sampleObj = JsonNode.Parse(line)?.AsObject()
                        ?? throw new JsonException("not a JSON object");
                }
                catch (JsonException ex)
                {
                    decodeErrors++;
                    if (maxDecodeErrors is int max && decodeErrors > max)
                    {
                        throw new DataDecodeException(
                            $"number of decode errors ({decodeErrors}) > maxDecodeErrors ({max})", ex);
                    }
                    continue;
                }

                // A line without the t/v/i keys is the end-of-test terminator.
                if (!sampleObj.ContainsKey(JsonKeys.Time) ||
                    !sampleObj.ContainsKey(JsonKeys.Volt) ||
                    !sampleObj.ContainsKey(JsonKeys.Curr))
                {
                    break;
                }

                double timeMs = sampleObj[JsonKeys.Time]!.GetValue<double>();
                double volt = sampleObj[JsonKeys.Volt]!.GetValue<double>();
                double curr = sampleObj[JsonKeys.Curr]!.GetValue<double>();
                bool sampleLimitErr = sampleObj.ContainsKey(JsonKeys.LimitErr);
                limitError |= sampleLimitErr;

                int chan = muxEnabled ? sampleObj[JsonKeys.Chan]!.GetValue<int>() : 0;
                if (!data.TryGetValue(chan, out var builder))
                {
                    builder = new ChannelDataBuilder();
                    data[chan] = builder;
                }
                double timeSeconds = timeMs * 1.0e-3;
                builder.Times.Add(timeSeconds);
                builder.Volts.Add(volt);
                builder.Currents.Add(curr);

                var sample = new Sample(chan, timeMs, volt, curr, sampleLimitErr);
                SampleReceived?.Invoke(this, new SampleEventArgs(sample));
                progress?.Report(new TestProgress(timeSeconds, testDoneSeconds));
            }
        }
        finally
        {
            TestRunning = false;
        }

        if (cancelRequested)
        {
            throw new OperationCanceledException("test stopped by cancellation", cancellationToken);
        }

        return new TestResult(
            muxEnabled,
            limitError,
            data.ToDictionary(kv => kv.Key, kv => kv.Value.Build()));
    }

    // ------------------------------------------------------------------
    // Low-level command handling
    // ------------------------------------------------------------------

    /// <summary>
    /// Sends a raw command object and returns the device's "response" element
    /// after validating success and command echo. Low-level escape hatch;
    /// prefer the typed methods.
    /// </summary>
    public async Task<JsonObject> SendCommandAsync(JsonObject cmd, bool expectResponse = true, CancellationToken ct = default)
    {
        await _transport.WriteLineAsync(cmd.ToJsonString(), ct).ConfigureAwait(false);
        if (!expectResponse)
        {
            return new JsonObject();
        }

        string line = await _transport.ReadLineAsync(ct).ConfigureAwait(false);
        JsonObject msg;
        try
        {
            msg = JsonNode.Parse(line)?.AsObject() ?? throw new JsonException("not a JSON object");
        }
        catch (JsonException ex)
        {
            throw new DataDecodeException($"invalid JSON response: '{line}'", ex);
        }
        CheckCommandMessage(cmd, msg);
        return msg[JsonKeys.Response]!.AsObject();
    }

    private static void CheckCommandMessage(JsonObject cmd, JsonObject msg)
    {
        if (msg[JsonKeys.Success] is not JsonValue successValue || !successValue.TryGetValue(out bool success))
        {
            throw new CommandFailedException($"json key '{JsonKeys.Success}' missing from response: {msg.ToJsonString()}");
        }
        if (!success)
        {
            string message = msg[JsonKeys.Message]?.GetValue<string>() ?? "(no message)";
            throw new CommandFailedException($"{message}, {msg.ToJsonString()}");
        }
        if (msg[JsonKeys.Response] is not JsonObject response)
        {
            throw new CommandFailedException($"json key '{JsonKeys.Response}' missing from response: {msg.ToJsonString()}");
        }

        string cmdSent = cmd[JsonKeys.Command]!.GetValue<string>();
        string? cmdRecv = response[JsonKeys.Command]?.GetValue<string>();
        if (cmdRecv != cmdSent)
        {
            throw new CommandMismatchException($"command sent, '{cmdSent}', not same as received, '{cmdRecv}'");
        }

        if (cmd[JsonKeys.Test] is JsonNode testNode)
        {
            string testSent = testNode.GetValue<string>();
            string? testRecv = response[JsonKeys.Test]?.GetValue<string>();
            if (testRecv != testSent)
            {
                throw new CommandMismatchException($"testname sent, '{testSent}', not same as received, '{testRecv}'");
            }
        }
    }

    private void CheckHardwareVersion(string requiredVersion)
    {
        // Ordinal string comparison, matching the Python driver's behavior.
        if (string.Compare(HardwareVersion, requiredVersion, StringComparison.Ordinal) < 0)
        {
            throw new HardwareVersionException($"requires hardware version >= {requiredVersion}");
        }
    }

    private async Task<bool> SetConnectedAsync(string command, bool value, bool requireHw0p2, CancellationToken ct)
    {
        if (requireHw0p2)
        {
            CheckHardwareVersion(HardwareVersions.V0p2);
        }
        var cmd = NewCommand(command);
        cmd[JsonKeys.Connected] = value;
        var rsp = await SendCommandAsync(cmd, ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.Connected);
    }

    private async Task<bool> GetConnectedAsync(string command, bool requireHw0p2, CancellationToken ct)
    {
        if (requireHw0p2)
        {
            CheckHardwareVersion(HardwareVersions.V0p2);
        }
        var rsp = await SendCommandAsync(NewCommand(command), ct: ct).ConfigureAwait(false);
        return GetBool(rsp, JsonKeys.Connected);
    }

    private static JsonObject NewCommand(string command) => new() { [JsonKeys.Command] = command };

    private static string GetString(JsonObject rsp, string key) => rsp[key]!.GetValue<string>();

    private static double GetDouble(JsonObject rsp, string key) => rsp[key]!.GetValue<double>();

    private static int GetInt(JsonObject rsp, string key) => rsp[key]!.GetValue<int>();

    private static bool GetBool(JsonObject rsp, string key)
    {
        var value = rsp[key]!.AsValue();
        // Firmware sometimes encodes booleans as 0/1.
        return value.TryGetValue(out bool b) ? b : value.GetValue<int>() != 0;
    }

    private static IReadOnlyList<string> GetStringList(JsonObject rsp, string key)
        => rsp[key]!.AsArray().Select(node => node!.GetValue<string>()).ToList();

    private static IReadOnlyList<int> GetIntList(JsonObject rsp, string key)
        => rsp[key]!.AsArray().Select(node => node!.GetValue<int>()).ToList();

    private static int? GetMuxWrkConnection(JsonObject rsp)
    {
        var value = rsp[JsonKeys.Connected]!.AsValue();
        if (value.TryGetValue(out bool b))
        {
            return b ? throw new DataDecodeException("unexpected boolean 'true' for mux working electrode") : null;
        }
        return value.GetValue<int>();
    }

    // ------------------------------------------------------------------
    // Cleanup
    // ------------------------------------------------------------------

    public async ValueTask DisposeAsync()
    {
        if (_disposed)
        {
            return;
        }
        _disposed = true;
        if (TestRunning && _transport.IsOpen)
        {
            try
            {
                await StopTestAsync(expectResponse: false).ConfigureAwait(false);
            }
            catch
            {
                // Best-effort stop during teardown; the port is closing anyway.
            }
        }
        _transport.Dispose();
        GC.SuppressFinalize(this);
    }

    public void Dispose()
    {
        if (_disposed)
        {
            return;
        }
        _disposed = true;
        if (TestRunning && _transport.IsOpen)
        {
            try
            {
                StopTestAsync(expectResponse: false).GetAwaiter().GetResult();
            }
            catch
            {
                // Best-effort stop during teardown; the port is closing anyway.
            }
        }
        _transport.Dispose();
        GC.SuppressFinalize(this);
    }
}
