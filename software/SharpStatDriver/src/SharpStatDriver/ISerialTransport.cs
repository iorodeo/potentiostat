namespace IoRodeo.SharpStatDriver;

/// <summary>
/// Line-oriented transport used by <see cref="Potentiostat"/>. Extracted as an
/// interface so the protocol layer can be tested without hardware.
/// </summary>
public interface ISerialTransport : IDisposable
{
    bool IsOpen { get; }

    void Open();

    void Close();

    /// <summary>Discards any bytes already received but not yet read.</summary>
    void DiscardInput();

    /// <summary>Writes one line (terminator added by the transport).</summary>
    Task WriteLineAsync(string line, CancellationToken cancellationToken = default);

    /// <summary>Reads one newline-terminated line, returned without the terminator.</summary>
    Task<string> ReadLineAsync(CancellationToken cancellationToken = default);
}
