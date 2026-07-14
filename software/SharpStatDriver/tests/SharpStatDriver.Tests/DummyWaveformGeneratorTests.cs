using System.Text.Json.Nodes;
using IoRodeo.SharpStatDriver.Simulation;

namespace IoRodeo.SharpStatDriver.Tests;

public class DummyWaveformGeneratorTests
{
    private static readonly Random Rng = new(1);

    [Fact]
    public void Constant_HoldsValue_ForConfiguredDuration()
    {
        var param = new JsonObject { ["value"] = 0.75, ["duration"] = 1000, ["quietValue"] = 0.0, ["quietTime"] = 200 };

        Assert.Equal(0.0, DummyWaveformGenerator.Evaluate("constant", param, 100, "1000uA", Rng).Volt);
        Assert.Equal(0.75, DummyWaveformGenerator.Evaluate("constant", param, 200, "1000uA", Rng).Volt);
        Assert.Equal(0.75, DummyWaveformGenerator.Evaluate("constant", param, 900, "1000uA", Rng).Volt);
        Assert.Equal(1200.0, DummyWaveformGenerator.GetTotalDurationMs("constant", param));
    }

    [Fact]
    public void LinearSweep_InterpolatesBetweenStartAndFinal()
    {
        var param = new JsonObject
        {
            ["startValue"] = -1.0, ["finalValue"] = 1.0, ["duration"] = 1000, ["quietValue"] = 0.0, ["quietTime"] = 0,
        };

        Assert.Equal(-1.0, DummyWaveformGenerator.Evaluate("linearSweep", param, 0, "1000uA", Rng).Volt, 6);
        Assert.Equal(0.0, DummyWaveformGenerator.Evaluate("linearSweep", param, 500, "1000uA", Rng).Volt, 6);
        Assert.Equal(1.0, DummyWaveformGenerator.Evaluate("linearSweep", param, 1000, "1000uA", Rng).Volt, 6);
    }

    [Fact]
    public void Cyclic_StaysWithinAmplitudeBounds_AndDurationMatchesPeriodTimesCycles()
    {
        var param = new JsonObject
        {
            ["amplitude"] = 0.5, ["offset"] = 0.1, ["period"] = 1000, ["numCycles"] = 3, ["shift"] = 0.0,
            ["quietValue"] = 0.0, ["quietTime"] = 0,
        };

        for (double t = 0; t <= 3000; t += 37)
        {
            double volt = DummyWaveformGenerator.Evaluate("cyclic", param, t, "1000uA", Rng).Volt;
            Assert.InRange(volt, -0.4001, 0.6001);
        }

        Assert.Equal(3000.0, DummyWaveformGenerator.GetTotalDurationMs("cyclic", param));
    }

    [Fact]
    public void Sinusoid_StaysWithinAmplitudeBounds()
    {
        var param = new JsonObject
        {
            ["amplitude"] = 0.3, ["offset"] = 0.0, ["period"] = 500, ["numCycles"] = 2, ["shift"] = 0.25,
            ["quietValue"] = 0.0, ["quietTime"] = 0,
        };

        for (double t = 0; t <= 1000; t += 13)
        {
            double volt = DummyWaveformGenerator.Evaluate("sinusoid", param, t, "1000uA", Rng).Volt;
            Assert.InRange(volt, -0.3001, 0.3001);
        }
    }

    [Fact]
    public void Chronoamp_HoldsEachStepValue_ForItsConfiguredDuration()
    {
        var param = new JsonObject
        {
            ["step"] = new JsonArray(new JsonArray(300, -0.2), new JsonArray(400, 0.6)),
            ["quietValue"] = 0.0,
            ["quietTime"] = 100,
        };

        Assert.Equal(0.0, DummyWaveformGenerator.Evaluate("chronoamp", param, 50, "1000uA", Rng).Volt);
        Assert.Equal(-0.2, DummyWaveformGenerator.Evaluate("chronoamp", param, 200, "1000uA", Rng).Volt);
        Assert.Equal(0.6, DummyWaveformGenerator.Evaluate("chronoamp", param, 450, "1000uA", Rng).Volt);
        Assert.Equal(800.0, DummyWaveformGenerator.GetTotalDurationMs("chronoamp", param));
    }
}
