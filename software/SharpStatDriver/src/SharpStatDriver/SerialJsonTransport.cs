using System.IO.Ports;
using System.Text;

namespace IoRodeo.SharpStatDriver;

/// <summary>
/// Newline-delimited line transport over <see cref="SerialPort"/> (115200 8N1 by default).
/// </summary>
public sealed class SerialJsonTransport : ISerialTransport
{
    private readonly SerialPort _port;
    private readonly TimeSpan _readTimeout;
    private readonly byte[] _readBuffer = new byte[4096];
    private readonly List<byte> _pending = new();

    public SerialJsonTransport(string portName, int baudRate, TimeSpan readTimeout)
    {
        _readTimeout = readTimeout;
        // DTR/RTS asserted to match pyserial defaults; the Rodeostat's USB CDC
        // serial will not transmit until DTR is set.
        _port = new SerialPort(portName, baudRate)
        {
            DtrEnable = true,
            RtsEnable = true,
        };
    }

    public bool IsOpen => _port.IsOpen;

    public void Open() => _port.Open();

    public void Close()
    {
        if (_port.IsOpen)
        {
            _port.Close();
        }
    }

    public void DiscardInput()
    {
        _pending.Clear();
        if (_port.IsOpen)
        {
            _port.DiscardInBuffer();
        }
    }

    public async Task WriteLineAsync(string line, CancellationToken cancellationToken = default)
    {
        var data = ApplyUsbSerialWorkaround(line + "\n");
        var bytes = Encoding.UTF8.GetBytes(data);
        await _port.BaseStream.WriteAsync(bytes, cancellationToken).ConfigureAwait(false);
        await _port.BaseStream.FlushAsync(cancellationToken).ConfigureAwait(false);
    }

    /// <summary>
    /// Works around a bug in Adafruit's ArduinoCore-samd USB serial where
    /// Serial.available() returns 0 for messages whose length (terminator
    /// included) is a multiple of 64 bytes. Prepending a space to such
    /// messages avoids the pathological length; the firmware's JSON parser
    /// ignores the leading whitespace.
    /// </summary>
    public static string ApplyUsbSerialWorkaround(string dataWithTerminator)
    {
        return Encoding.UTF8.GetByteCount(dataWithTerminator) % 64 == 0
            ? " " + dataWithTerminator
            : dataWithTerminator;
    }

    public async Task<string> ReadLineAsync(CancellationToken cancellationToken = default)
    {
        while (true)
        {
            int newlineIndex = _pending.IndexOf((byte)'\n');
            if (newlineIndex >= 0)
            {
                var line = Encoding.UTF8.GetString(_pending.GetRange(0, newlineIndex).ToArray());
                _pending.RemoveRange(0, newlineIndex + 1);
                return line.TrimEnd('\r');
            }

            using var timeoutCts = CancellationTokenSource.CreateLinkedTokenSource(cancellationToken);
            timeoutCts.CancelAfter(_readTimeout);
            int bytesRead;
            try
            {
                bytesRead = await _port.BaseStream
                    .ReadAsync(_readBuffer.AsMemory(), timeoutCts.Token)
                    .ConfigureAwait(false);
            }
            catch (OperationCanceledException) when (!cancellationToken.IsCancellationRequested)
            {
                throw new TimeoutException($"no response from device within {_readTimeout.TotalSeconds:0.##} s");
            }

            if (bytesRead == 0)
            {
                throw new IOException("serial port returned end of stream");
            }
            _pending.AddRange(new ArraySegment<byte>(_readBuffer, 0, bytesRead));
        }
    }

    public void Dispose()
    {
        Close();
        _port.Dispose();
    }
}
