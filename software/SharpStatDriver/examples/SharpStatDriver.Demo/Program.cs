using IoRodeo.SharpStatDriver;
using IoRodeo.SharpStatDriver.Helpers;
using IoRodeo.SharpStatDriver.Protocol;

if (args.Length < 1)
{
    Console.WriteLine("usage: SharpStatDriver.Demo <port> [testName] [output.csv]");
    Console.WriteLine("  e.g. SharpStatDriver.Demo COM3 cyclic data.csv");
    return 1;
}

string port = args[0];
string testName = args.Length > 1 ? args[1] : "cyclic";
string? csvPath = args.Length > 2 ? args[2] : null;

using var cts = new CancellationTokenSource();
Console.CancelKeyPress += (_, e) =>
{
    e.Cancel = true;
    cts.Cancel();
};

await using var pstat = new Potentiostat(port);
await pstat.ConnectAsync(cts.Token);

Console.WriteLine($"port:             {port}");
Console.WriteLine($"hardware variant: {pstat.HardwareVariant}");
Console.WriteLine($"hardware version: {pstat.HardwareVersion}");
Console.WriteLine($"firmware version: {pstat.FirmwareVersion}");
Console.WriteLine($"tests:            {string.Join(", ", await pstat.GetTestNamesAsync(cts.Token))}");
Console.WriteLine();
Console.WriteLine($"running test '{testName}' (Ctrl+C to stop)");

var progress = new Progress<TestProgress>(p =>
{
    const int width = 40;
    int filled = (int)(p.Fraction * width);
    Console.Write($"\r[{new string('#', filled)}{new string('-', width - filled)}] {p.Fraction * 100,5:0.0}%  t={p.ElapsedSeconds:0.00}s");
});

// CsvSampleWriter? csvWriter = null;
// if (csvPath is not null)
// {
//     csvWriter = new CsvSampleWriter(csvPath);
//     pstat.SampleReceived += csvWriter.HandleSample;
// }

pstat.SampleReceived += (s, e) =>
{
    if (csvPath is not null)
    {
        Console.WriteLine($"sample: {e.Sample.Channel} {e.Sample.TimeMs:0.00}ms {e.Sample.Volt:0.000}V {e.Sample.Curr:0.000}uA limit={e.Sample.LimitError}");
    }
};

try
{
    var result = await pstat.RunTestAsync(testName, progress: progress, cancellationToken: cts.Token);
    Console.WriteLine();
    Console.WriteLine($"done: {result.Times.Count} samples, limit error: {result.LimitError}");
    if (csvPath is not null)
    {
        Console.WriteLine($"data written to {csvPath}");
    }
}
catch (OperationCanceledException)
{
    Console.WriteLine();
    Console.WriteLine("test cancelled");
}
finally
{
    // csvWriter?.Dispose();
}
return 0;
