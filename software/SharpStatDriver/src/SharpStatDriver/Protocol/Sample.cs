namespace IoRodeo.SharpStatDriver.Protocol;

/// <summary>
/// One streamed measurement sample from a running voltammetric test.
/// </summary>
/// <param name="Channel">Mux channel number; 0 when the multiplexer is disabled.</param>
/// <param name="TimeMs">Sample time as reported by the device, milliseconds.</param>
/// <param name="Volt">Output voltage, volts.</param>
/// <param name="Curr">Working electrode current, microamps.</param>
/// <param name="LimitError">True if the device flagged a current limit error on this sample.</param>
public sealed record Sample(int Channel, double TimeMs, double Volt, double Curr, bool LimitError)
{
    /// <summary>Sample time in seconds.</summary>
    public double TimeSeconds => TimeMs * 1.0e-3;
}

/// <summary>Event payload raised for each sample received during <c>RunTestAsync</c>.</summary>
public sealed class SampleEventArgs : EventArgs
{
    public SampleEventArgs(Sample sample) => Sample = sample;
    public Sample Sample { get; }
}

/// <summary>Progress of a running test, both values in seconds.</summary>
public readonly record struct TestProgress(double ElapsedSeconds, double TotalSeconds)
{
    /// <summary>Completed fraction in [0,1], or 0 when the total is unknown.</summary>
    public double Fraction => TotalSeconds > 0 ? Math.Clamp(ElapsedSeconds / TotalSeconds, 0.0, 1.0) : 0.0;
}
