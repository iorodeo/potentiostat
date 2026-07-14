using System.Globalization;
using IoRodeo.SharpStatDriver.Protocol;

namespace IoRodeo.SharpStatDriver.Helpers;

/// <summary>
/// Writes streamed samples to a text file in the same format as the Python
/// driver: "t, v, i" per line (seconds, volts, microamps), prefixed with the
/// channel number when the multiplexer is in use. Subscribe
/// <see cref="HandleSample"/> to <see cref="Potentiostat.SampleReceived"/>.
/// </summary>
public sealed class CsvSampleWriter : IDisposable
{
    private readonly StreamWriter _writer;

    public CsvSampleWriter(string path)
    {
        _writer = new StreamWriter(path);
    }

    public void HandleSample(object? sender, SampleEventArgs e) => Write(e.Sample);

    public void Write(Sample sample)
    {
        if (sample.Channel == 0)
        {
            _writer.WriteLine(string.Format(CultureInfo.InvariantCulture,
                "{0:0.000}, {1:0.0000}, {2:0.0000}", sample.TimeSeconds, sample.Volt, sample.Curr));
        }
        else
        {
            _writer.WriteLine(string.Format(CultureInfo.InvariantCulture,
                "{0}, {1:0.000}, {2:0.0000}, {3:0.0000}", sample.Channel, sample.TimeSeconds, sample.Volt, sample.Curr));
        }
    }

    public void Dispose() => _writer.Dispose();
}
