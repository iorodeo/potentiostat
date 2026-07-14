using System.Text.Json.Nodes;
using IoRodeo.SharpStatDriver.Simulation;

namespace IoRodeo.SharpStatDriver.Tests;

public class DummyTransportTests
{
    private static async Task<Potentiostat> ConnectAsync()
    {
        var pstat = new Potentiostat(new DummyTransport());
        await pstat.ConnectAsync();
        return pstat;
    }

    [Fact]
    public async Task Connect_ReportsSimulatedIdentity()
    {
        var pstat = await ConnectAsync();

        Assert.Equal(DummyTransport.HardwareVariant, pstat.HardwareVariant);
        Assert.Equal(DummyTransport.FirmwareVersion, pstat.FirmwareVersion);
        Assert.Equal(DummyTransport.HardwareVersion, pstat.HardwareVersion);
    }

    [Fact]
    public async Task GetTestNames_ReturnsAllSixTechniques()
    {
        var pstat = await ConnectAsync();
        var names = await pstat.GetTestNamesAsync();

        Assert.Equal(
            new[] { "constant", "chronoamp", "cyclic", "linearSweep", "sinusoid", "squareWave" },
            names);
    }

    [Fact]
    public async Task RunTest_StreamsSamplesRespectingQuietValueAndConfiguredParam()
    {
        var pstat = await ConnectAsync();
        await pstat.SetSampleRateAsync(1000.0); // 1 ms sample period keeps the test fast.

        var param = new JsonObject { ["value"] = 0.42, ["duration"] = 40, ["quietValue"] = -0.1, ["quietTime"] = 20 };
        var result = await pstat.RunTestAsync("constant", param);

        Assert.NotEmpty(result.Times);
        foreach (var (timeSeconds, volt) in result.Times.Zip(result.Volts))
        {
            double expected = timeSeconds * 1000.0 < 20 ? -0.1 : 0.42;
            Assert.Equal(expected, volt);
        }
    }

    [Fact]
    public async Task RunTest_TotalElapsedTime_MatchesGetTestDoneTime()
    {
        var pstat = await ConnectAsync();
        await pstat.SetSampleRateAsync(1000.0);

        var param = new JsonObject
        {
            ["amplitude"] = 0.2, ["offset"] = 0.0, ["period"] = 20, ["numCycles"] = 2, ["shift"] = 0.0,
            ["quietValue"] = 0.0, ["quietTime"] = 0,
        };
        await pstat.SetParamAsync("cyclic", param);
        double expectedSeconds = await pstat.GetTestDoneTimeAsync("cyclic");

        var result = await pstat.RunTestAsync("cyclic");

        Assert.Equal(expectedSeconds, result.Times.Last(), 2);
    }

    [Fact]
    public async Task StopTest_CancelsPromptly_WithCleanTerminator()
    {
        var pstat = await ConnectAsync();
        await pstat.SetSampleRateAsync(200.0); // 5 ms sample period.

        var param = new JsonObject { ["value"] = 0.1, ["duration"] = 5000, ["quietValue"] = 0.0, ["quietTime"] = 0 };

        using var cts = new CancellationTokenSource();
        var runTask = pstat.RunTestAsync("constant", param, cancellationToken: cts.Token);

        await Task.Delay(30);
        cts.Cancel();

        await Assert.ThrowsAsync<OperationCanceledException>(() => runTask);
        Assert.False(pstat.TestRunning);
    }
}
