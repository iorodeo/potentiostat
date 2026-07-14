using System.Text.Json.Nodes;
using IoRodeo.SharpStatDriver.Protocol;

namespace IoRodeo.SharpStatDriver.Tests;

public class PotentiostatTests
{
    private const string Variant = "10V_microAmpV0.2";

    private static string Ok(string command, params (string Key, JsonNode? Value)[] fields)
    {
        var response = new JsonObject { [JsonKeys.Command] = command };
        foreach (var (key, value) in fields)
        {
            response[key] = value;
        }
        return new JsonObject
        {
            [JsonKeys.Success] = true,
            [JsonKeys.Response] = response,
        }.ToJsonString();
    }

    private static string Fail(string message)
        => new JsonObject { [JsonKeys.Success] = false, [JsonKeys.Message] = message }.ToJsonString();

    /// <summary>
    /// Builds a fake device that answers the standard commands. Test-specific
    /// behavior is layered on via <paramref name="overrides"/>, which may
    /// return null to fall through to the defaults.
    /// </summary>
    private static FakeTransport NewDevice(
        string firmware = "0.0.9",
        string hardware = "HW0.2",
        bool muxEnabled = false,
        int[]? muxChannels = null,
        IEnumerable<string>? testStream = null,
        Func<JsonObject, IEnumerable<string>?>? overrides = null)
    {
        var transport = new FakeTransport();
        transport.Responder = cmd =>
        {
            var custom = overrides?.Invoke(cmd);
            if (custom is not null)
            {
                return custom;
            }
            string command = cmd[JsonKeys.Command]!.GetValue<string>();
            return command switch
            {
                Commands.GetVariant => new[] { Ok(command, (JsonKeys.Variant, Variant)) },
                Commands.GetVersion => new[] { Ok(command, (JsonKeys.Version, firmware)) },
                Commands.GetHardwareVersion => new[] { Ok(command, (JsonKeys.Version, hardware)) },
                Commands.GetMuxEnabled => new[] { Ok(command, (JsonKeys.MuxEnabled, muxEnabled)) },
                Commands.GetEnabledMuxChannels => new[]
                {
                    Ok(command, (JsonKeys.MuxChannel, new JsonArray((muxChannels ?? Array.Empty<int>()).Select(c => (JsonNode)c).ToArray()))),
                },
                Commands.GetTestDoneTime => new[]
                {
                    Ok(command, (JsonKeys.Test, cmd[JsonKeys.Test]!.GetValue<string>()), (JsonKeys.TestDoneTime, 2000)),
                },
                Commands.RunTest => new[]
                {
                    Ok(command, (JsonKeys.Test, cmd[JsonKeys.Test]!.GetValue<string>())),
                }.Concat(testStream ?? Array.Empty<string>()),
                Commands.StopTest => new[] { Ok(command) },
                _ => new[] { Ok(command) },
            };
        };
        return transport;
    }

    private static async Task<Potentiostat> ConnectAsync(FakeTransport transport)
    {
        var pstat = new Potentiostat(transport);
        await pstat.ConnectAsync();
        return pstat;
    }

    /// <summary>IProgress implementation that reports synchronously (unlike Progress&lt;T&gt;).</summary>
    private sealed class SyncProgress<T> : IProgress<T>
    {
        public List<T> Reports { get; } = new();
        public void Report(T value) => Reports.Add(value);
    }

    // ------------------------------------------------------------------
    // Command layer
    // ------------------------------------------------------------------

    [Fact]
    public async Task Connect_SendsCompactJson_AndCachesDeviceInfo()
    {
        var transport = NewDevice();
        var pstat = await ConnectAsync(transport);

        Assert.Equal("{\"command\":\"getVariant\"}", transport.Written[0]);
        Assert.Equal("{\"command\":\"getVersion\"}", transport.Written[1]);
        Assert.Equal("{\"command\":\"getHardwareVersion\"}", transport.Written[2]);
        Assert.Equal(Variant, pstat.HardwareVariant);
        Assert.Equal("0.0.9", pstat.FirmwareVersion);
        Assert.Equal("HW0.2", pstat.HardwareVersion);
    }

    [Fact]
    public async Task GetVolt_ReturnsValueFromResponse()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.GetVolt
                ? new[] { Ok(Commands.GetVolt, (JsonKeys.Volt, 1.25)) }
                : null);
        var pstat = await ConnectAsync(transport);

        Assert.Equal(1.25, await pstat.GetVoltAsync());
        Assert.Contains("{\"command\":\"getVolt\"}", transport.Written);
    }

    [Fact]
    public async Task FailureResponse_ThrowsCommandFailed()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.GetVolt
                ? new[] { Fail("bad command") }
                : null);
        var pstat = await ConnectAsync(transport);

        var ex = await Assert.ThrowsAsync<CommandFailedException>(() => pstat.GetVoltAsync());
        Assert.Contains("bad command", ex.Message);
    }

    [Fact]
    public async Task CommandEchoMismatch_ThrowsCommandMismatch()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.GetVolt
                ? new[] { Ok(Commands.GetCurr, (JsonKeys.Curr, 0.0)) }
                : null);
        var pstat = await ConnectAsync(transport);

        await Assert.ThrowsAsync<CommandMismatchException>(() => pstat.GetVoltAsync());
    }

    [Fact]
    public async Task HardwareVersionCommandFailure_FallsBackToDefault()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.GetHardwareVersion
                ? new[] { Fail("unknown command") }
                : null);
        var pstat = await ConnectAsync(transport);

        Assert.Equal(HardwareVersions.Default, pstat.HardwareVersion);
    }

    [Fact]
    public async Task ElectrodeControl_ThrowsOnPreV0p2Hardware()
    {
        var transport = NewDevice(hardware: "HW0.1");
        var pstat = await ConnectAsync(transport);

        await Assert.ThrowsAsync<HardwareVersionException>(() => pstat.SetRefElectConnectedAsync(true));
    }

    [Fact]
    public async Task SetVoltRange_RejectsUnknownRange()
    {
        var pstat = await ConnectAsync(NewDevice());
        await Assert.ThrowsAsync<ArgumentException>(() => pstat.SetVoltRangeAsync("3V"));
    }

    [Fact]
    public async Task SetSampleRate_ConvertsToPeriodAndBack()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.SetSamplePeriod
                ? new[] { Ok(Commands.SetSamplePeriod, (JsonKeys.SamplePeriod, cmd[JsonKeys.SamplePeriod]!.GetValue<int>())) }
                : null);
        var pstat = await ConnectAsync(transport);

        Assert.Equal(10.0, await pstat.SetSampleRateAsync(10.0));
        Assert.Contains("\"samplePeriod\":100", transport.Written.Last());
    }

    // ------------------------------------------------------------------
    // 64-byte USB serial workaround
    // ------------------------------------------------------------------

    [Theory]
    [InlineData(64, true)]
    [InlineData(128, true)]
    [InlineData(63, false)]
    [InlineData(65, false)]
    [InlineData(1, false)]
    public void UsbSerialWorkaround_PadsExactlyMultiplesOf64(int lengthWithTerminator, bool expectPadded)
    {
        string data = new string('x', lengthWithTerminator - 1) + "\n";
        string result = SerialJsonTransport.ApplyUsbSerialWorkaround(data);

        Assert.Equal(expectPadded ? " " + data : data, result);
    }

    // ------------------------------------------------------------------
    // RunTestAsync streaming
    // ------------------------------------------------------------------

    [Fact]
    public async Task RunTest_CollectsDataAndConvertsTimeToSeconds()
    {
        var stream = new[]
        {
            "{\"t\":0,\"v\":0.1,\"i\":1.5}",
            "{\"t\":100,\"v\":0.2,\"i\":2.5}",
            "{\"t\":200,\"v\":0.3,\"i\":3.5}",
            "{}",
        };
        var pstat = await ConnectAsync(NewDevice(testStream: stream));

        var samples = new List<Sample>();
        pstat.SampleReceived += (_, e) => samples.Add(e.Sample);
        var progress = new SyncProgress<TestProgress>();

        var result = await pstat.RunTestAsync("cyclic", progress: progress);

        Assert.False(result.MuxEnabled);
        Assert.False(result.LimitError);
        Assert.Equal(new[] { 0.0, 0.1, 0.2 }, result.Times);
        Assert.Equal(new[] { 0.1, 0.2, 0.3 }, result.Volts);
        Assert.Equal(new[] { 1.5, 2.5, 3.5 }, result.Currents);
        Assert.Equal(3, samples.Count);
        Assert.Equal(3, progress.Reports.Count);
        Assert.Equal(2.0, progress.Reports[0].TotalSeconds);
        Assert.False(pstat.TestRunning);
    }

    [Fact]
    public async Task RunTest_WithMux_GroupsDataByChannel()
    {
        var stream = new[]
        {
            "{\"n\":1,\"t\":0,\"v\":0.1,\"i\":1.0}",
            "{\"n\":2,\"t\":0,\"v\":0.1,\"i\":2.0}",
            "{\"n\":1,\"t\":100,\"v\":0.2,\"i\":1.1}",
            "{\"n\":2,\"t\":100,\"v\":0.2,\"i\":2.1}",
            "{}",
        };
        var pstat = await ConnectAsync(NewDevice(muxEnabled: true, muxChannels: new[] { 1, 2 }, testStream: stream));

        var result = await pstat.RunTestAsync("cyclic");

        Assert.True(result.MuxEnabled);
        Assert.Equal(new[] { 1, 2 }, result.Channels.Keys.OrderBy(k => k));
        Assert.Equal(new[] { 1.0, 1.1 }, result.Channels[1].Currents);
        Assert.Equal(new[] { 2.0, 2.1 }, result.Channels[2].Currents);
        Assert.Equal(new[] { 0.0, 0.1 }, result.Channels[2].Times);
    }

    [Fact]
    public async Task RunTest_DecodeError_ThrowsWhenOverLimit()
    {
        var stream = new[]
        {
            "{\"t\":0,\"v\":0.1,\"i\":1.5}",
            "not valid json",
            "{\"t\":100,\"v\":0.2,\"i\":2.5}",
            "{}",
        };
        var pstat = await ConnectAsync(NewDevice(testStream: stream));

        await Assert.ThrowsAsync<DataDecodeException>(() => pstat.RunTestAsync("cyclic", maxDecodeErrors: 0));
    }

    [Fact]
    public async Task RunTest_DecodeError_ToleratedWithinLimit()
    {
        var stream = new[]
        {
            "{\"t\":0,\"v\":0.1,\"i\":1.5}",
            "not valid json",
            "{\"t\":100,\"v\":0.2,\"i\":2.5}",
            "{}",
        };
        var pstat = await ConnectAsync(NewDevice(testStream: stream));

        var result = await pstat.RunTestAsync("cyclic", maxDecodeErrors: 1);

        Assert.Equal(2, result.Times.Count);
    }

    [Fact]
    public async Task RunTest_DecodeError_UnlimitedWhenNull()
    {
        var stream = new[] { "garbage", "garbage", "garbage", "{}" };
        var pstat = await ConnectAsync(NewDevice(testStream: stream));

        var result = await pstat.RunTestAsync("cyclic", maxDecodeErrors: null);

        Assert.Empty(result.Times);
    }

    [Fact]
    public async Task RunTest_SetsLimitErrorFlag()
    {
        var stream = new[]
        {
            "{\"t\":0,\"v\":0.1,\"i\":1.5}",
            "{\"t\":100,\"v\":0.2,\"i\":2.5,\"le\":1}",
            "{}",
        };
        var pstat = await ConnectAsync(NewDevice(testStream: stream));

        var result = await pstat.RunTestAsync("cyclic");

        Assert.True(result.LimitError);
    }

    [Fact]
    public async Task RunTest_AppliesParamBeforeStarting()
    {
        var transport = NewDevice(
            testStream: new[] { "{}" },
            overrides: cmd =>
                cmd[JsonKeys.Command]!.GetValue<string>() == Commands.SetParam
                    ? new[]
                    {
                        Ok(Commands.SetParam,
                            (JsonKeys.Test, cmd[JsonKeys.Test]!.GetValue<string>()),
                            (JsonKeys.Param, cmd[JsonKeys.Param]!.DeepClone())),
                    }
                    : null);
        var pstat = await ConnectAsync(transport);

        var param = new JsonObject { ["quietTime"] = 1000, ["amplitude"] = 2.0 };
        await pstat.RunTestAsync("cyclic", param: param);

        int setParamIndex = transport.Written.FindIndex(w => w.Contains("\"setParam\""));
        int runTestIndex = transport.Written.FindIndex(w => w.Contains("\"runTest\""));
        Assert.True(setParamIndex >= 0 && setParamIndex < runTestIndex);
        Assert.Contains("\"quietTime\":1000", transport.Written[setParamIndex]);
    }

    [Fact]
    public async Task RunTest_TestNameEchoMismatch_Throws()
    {
        var transport = NewDevice(overrides: cmd =>
            cmd[JsonKeys.Command]!.GetValue<string>() == Commands.RunTest
                ? new[] { Ok(Commands.RunTest, (JsonKeys.Test, "otherTest")) }
                : null);
        var pstat = await ConnectAsync(transport);

        await Assert.ThrowsAsync<CommandMismatchException>(() => pstat.RunTestAsync("cyclic"));
    }
}
