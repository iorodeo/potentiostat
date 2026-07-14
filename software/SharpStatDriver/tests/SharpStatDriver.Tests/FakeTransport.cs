using System.Text.Json.Nodes;

namespace IoRodeo.SharpStatDriver.Tests;

/// <summary>
/// In-memory transport: records written lines and serves queued response
/// lines. An optional <see cref="Responder"/> inspects each written command
/// and enqueues one or more reply lines (responses plus streamed samples).
/// </summary>
public sealed class FakeTransport : ISerialTransport
{
    public List<string> Written { get; } = new();
    public Queue<string> Lines { get; } = new();

    /// <summary>Maps a written command object to the lines the device sends back.</summary>
    public Func<JsonObject, IEnumerable<string>>? Responder { get; set; }

    public bool IsOpen { get; private set; }

    public void Open() => IsOpen = true;

    public void Close() => IsOpen = false;

    public void DiscardInput() { }

    public Task WriteLineAsync(string line, CancellationToken cancellationToken = default)
    {
        Written.Add(line);
        if (Responder is not null)
        {
            var cmd = JsonNode.Parse(line)!.AsObject();
            foreach (var response in Responder(cmd))
            {
                Lines.Enqueue(response);
            }
        }
        return Task.CompletedTask;
    }

    public Task<string> ReadLineAsync(CancellationToken cancellationToken = default)
    {
        cancellationToken.ThrowIfCancellationRequested();
        if (Lines.Count == 0)
        {
            throw new TimeoutException("fake transport has no queued lines");
        }
        return Task.FromResult(Lines.Dequeue());
    }

    public void Dispose() => Close();
}
