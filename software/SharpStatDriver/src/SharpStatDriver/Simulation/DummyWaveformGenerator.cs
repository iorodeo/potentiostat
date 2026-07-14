using System.Text.Json.Nodes;

namespace IoRodeo.SharpStatDriver.Simulation;

/// <summary>
/// Pure waveform math for <see cref="DummyTransport"/>. Computes the voltage a firmware
/// test would apply at a given elapsed time, plus a synthetic current response, directly
/// from the same firmware-shaped parameter JSON (as produced by
/// Potentiostat.Web's TechniqueCatalog.ToFirmwareParam) the real device would consume.
/// </summary>
public static class DummyWaveformGenerator
{
    private const double CapacitiveTimeConstantMs = 80.0;

    /// <summary>Quiet time plus the technique's active-phase duration, milliseconds.</summary>
    public static double GetTotalDurationMs(string firmwareTestName, JsonObject param)
        => D(param, "quietTime") + ActiveDurationMs(firmwareTestName, param);

    /// <summary>Voltage and synthetic current at <paramref name="elapsedMs"/> since the test started.</summary>
    public static (double Volt, double Curr) Evaluate(
        string firmwareTestName, JsonObject param, double elapsedMs, string currRange, Random rng)
    {
        double quietTime = D(param, "quietTime");
        double quietValue = D(param, "quietValue");

        double volt;
        double drive;
        if (elapsedMs < quietTime)
        {
            volt = quietValue;
            drive = 0.0;
        }
        else
        {
            double t = elapsedMs - quietTime;
            (volt, drive) = firmwareTestName switch
            {
                "constant" => ConstantAt(param, t),
                "chronoamp" => ChronoampAt(param, t),
                "cyclic" => TriangleAt(param, t),
                "sinusoid" => SinusoidAt(param, t),
                "linearSweep" => SweepAt(param, t),
                "squareWave" => SquareWaveAt(param, t),
                _ => (quietValue, 0.0),
            };
        }

        double curr = SyntheticCurrent(firmwareTestName, param, volt, drive, currRange, rng);
        return (volt, curr);
    }

    // ------------------------------------------------------------------
    // Per-technique voltage + normalized capacitive "drive" signal
    // ------------------------------------------------------------------

    private static (double Volt, double Drive) ConstantAt(JsonObject p, double t)
        => (D(p, "value"), Math.Exp(-t / CapacitiveTimeConstantMs));

    private static (double Volt, double Drive) ChronoampAt(JsonObject p, double t)
    {
        var (dur1, val1, dur2, val2) = StepPairs(p);
        if (t < dur1)
        {
            return (val1, Math.Exp(-t / CapacitiveTimeConstantMs));
        }
        double sinceEdge = t - dur1;
        return (val2, Math.Sign(val2 - val1) * Math.Exp(-sinceEdge / CapacitiveTimeConstantMs));
    }

    private static (double Volt, double Drive) TriangleAt(JsonObject p, double t)
    {
        double amplitude = D(p, "amplitude");
        double offset = D(p, "offset");
        double period = Math.Max(D(p, "period"), 1.0);
        double shift = D(p, "shift");
        double phase = Frac(t / period + shift);
        double triangle = phase < 0.5 ? (4.0 * phase - 1.0) : (3.0 - 4.0 * phase);
        double slopeSign = phase < 0.5 ? 1.0 : -1.0;
        return (offset + amplitude * triangle, slopeSign);
    }

    private static (double Volt, double Drive) SinusoidAt(JsonObject p, double t)
    {
        double amplitude = D(p, "amplitude");
        double offset = D(p, "offset");
        double period = Math.Max(D(p, "period"), 1.0);
        double shift = D(p, "shift");
        double angle = 2.0 * Math.PI * (t / period + shift);
        return (offset + amplitude * Math.Sin(angle), Math.Cos(angle));
    }

    private static (double Volt, double Drive) SweepAt(JsonObject p, double t)
    {
        double start = D(p, "startValue");
        double final = D(p, "finalValue");
        double duration = Math.Max(D(p, "duration"), 1.0);
        double frac = Math.Clamp(t / duration, 0.0, 1.0);
        return (start + (final - start) * frac, Math.Sign(final - start));
    }

    private static (double Volt, double Drive) SquareWaveAt(JsonObject p, double t)
    {
        double amplitude = D(p, "amplitude");
        double start = D(p, "startValue");
        double final = D(p, "finalValue");
        double stepValue = Math.Max(Math.Abs(D(p, "stepValue")), 1e-6);
        double window = Math.Max(D(p, "window"), 1.0);

        int stepIndex = (int)(t / window);
        double baseline = start + Math.Sign(final - start) * stepIndex * stepValue;
        baseline = final >= start ? Math.Min(baseline, final) : Math.Max(baseline, final);

        double sinceEdge = t - stepIndex * window;
        bool pulseUp = stepIndex % 2 == 0;
        double volt = baseline + (pulseUp ? amplitude : -amplitude);
        double drive = (pulseUp ? 1.0 : -1.0) * Math.Exp(-sinceEdge / CapacitiveTimeConstantMs);
        return (volt, drive);
    }

    // ------------------------------------------------------------------
    // Synthetic current + active-phase duration
    // ------------------------------------------------------------------

    private static double SyntheticCurrent(
        string test, JsonObject p, double volt, double drive, string currRange, Random rng)
    {
        double scale = CurrRangeMagnitudeUa(currRange);
        double capacitive = 0.08 * scale * drive;

        double faradaic = 0.0;
        if (test is "cyclic" or "sinusoid" or "linearSweep" or "squareWave")
        {
            var (center, span) = PeakCenterAndSpan(test, p);
            double sigma = Math.Max(span, 0.05) * 0.15;
            double gaussian = Math.Exp(-Math.Pow(volt - center, 2) / (2 * sigma * sigma));
            faradaic = 0.5 * scale * gaussian * (drive == 0.0 ? 1.0 : Math.Sign(drive));
        }

        double noise = (rng.NextDouble() - 0.5) * 0.02 * scale;
        return capacitive + faradaic + noise;
    }

    private static (double Center, double Span) PeakCenterAndSpan(string test, JsonObject p) => test switch
    {
        "cyclic" or "sinusoid" => (D(p, "offset"), D(p, "amplitude") * 2.0),
        _ => ((D(p, "startValue") + D(p, "finalValue")) / 2.0, Math.Abs(D(p, "finalValue") - D(p, "startValue"))),
    };

    private static double ActiveDurationMs(string test, JsonObject p) => test switch
    {
        "constant" => D(p, "duration"),
        "chronoamp" => StepPairs(p) is var (dur1, _, dur2, _) ? dur1 + dur2 : 0.0,
        "cyclic" or "sinusoid" => D(p, "period") * D(p, "numCycles"),
        "linearSweep" => D(p, "duration"),
        "squareWave" => SquareWaveStepCount(p) * Math.Max(D(p, "window"), 1.0),
        _ => 0.0,
    };

    private static int SquareWaveStepCount(JsonObject p)
    {
        double start = D(p, "startValue");
        double final = D(p, "finalValue");
        double stepValue = Math.Max(Math.Abs(D(p, "stepValue")), 1e-6);
        return Math.Max(1, (int)Math.Round(Math.Abs(final - start) / stepValue));
    }

    // ------------------------------------------------------------------
    // JSON + misc helpers
    // ------------------------------------------------------------------

    private static (double Dur1, double Val1, double Dur2, double Val2) StepPairs(JsonObject p)
    {
        var steps = p["step"]?.AsArray();
        return (ArrayD(steps, 0, 0), ArrayD(steps, 0, 1), ArrayD(steps, 1, 0), ArrayD(steps, 1, 1));
    }

    private static double ArrayD(JsonArray? array, int i, int j) => AsDouble(array?[i]?[j]);

    private static double D(JsonObject param, string key) =>
        param.TryGetPropertyValue(key, out var node) ? AsDouble(node) : 0.0;

    private static double AsDouble(JsonNode? node) => node switch
    {
        null => 0.0,
        JsonValue value when value.TryGetValue<double>(out var d) => d,
        JsonValue value when value.TryGetValue<int>(out var i) => i,
        JsonValue value when value.TryGetValue<long>(out var l) => l,
        _ => node.GetValue<double>(),
    };

    private static double Frac(double x) => x - Math.Floor(x);

    private static double CurrRangeMagnitudeUa(string currRange)
    {
        if (currRange.EndsWith("nA", StringComparison.Ordinal))
        {
            return double.Parse(currRange[..^2]) / 1000.0;
        }
        if (currRange.EndsWith("uA", StringComparison.Ordinal))
        {
            return double.Parse(currRange[..^2]);
        }
        return 100.0;
    }
}
