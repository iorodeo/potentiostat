namespace IoRodeo.SharpStatDriver;

/// <summary>Time, voltage and current series acquired on one channel.</summary>
public sealed class ChannelData
{
    internal ChannelData(IReadOnlyList<double> times, IReadOnlyList<double> volts, IReadOnlyList<double> currents)
    {
        Times = times;
        Volts = volts;
        Currents = currents;
    }

    /// <summary>Sample times, seconds.</summary>
    public IReadOnlyList<double> Times { get; }

    /// <summary>Output voltages, volts.</summary>
    public IReadOnlyList<double> Volts { get; }

    /// <summary>Working electrode currents, microamps.</summary>
    public IReadOnlyList<double> Currents { get; }
}

/// <summary>
/// Data acquired during a voltammetric test. When the multiplexer is disabled
/// all data is on channel 0 and the <see cref="Times"/>/<see cref="Volts"/>/<see cref="Currents"/>
/// shortcuts can be used directly; when enabled use <see cref="Channels"/> keyed
/// by mux channel number.
/// </summary>
public sealed class TestResult
{
    internal TestResult(bool muxEnabled, bool limitError, IReadOnlyDictionary<int, ChannelData> channels)
    {
        MuxEnabled = muxEnabled;
        LimitError = limitError;
        Channels = channels;
    }

    public bool MuxEnabled { get; }

    /// <summary>True if any sample was flagged with a current limit error.</summary>
    public bool LimitError { get; }

    public IReadOnlyDictionary<int, ChannelData> Channels { get; }

    private ChannelData First => Channels.OrderBy(kv => kv.Key).First().Value;

    /// <summary>Sample times (s) of the first channel (channel 0 when mux is disabled).</summary>
    public IReadOnlyList<double> Times => First.Times;

    /// <summary>Voltages (V) of the first channel (channel 0 when mux is disabled).</summary>
    public IReadOnlyList<double> Volts => First.Volts;

    /// <summary>Currents (uA) of the first channel (channel 0 when mux is disabled).</summary>
    public IReadOnlyList<double> Currents => First.Currents;
}

internal sealed class ChannelDataBuilder
{
    public List<double> Times { get; } = new();
    public List<double> Volts { get; } = new();
    public List<double> Currents { get; } = new();

    public ChannelData Build() => new(Times, Volts, Currents);
}
