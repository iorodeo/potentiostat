# IoRodeo.SharpStatDriver

Async C# driver for the [IO Rodeo Rodeostat](https://iorodeo.com/) open source
potentiostat — a C# port of the Python driver in `../../python/potentiostat`.
Targets .NET 8, communicates over newline-delimited JSON at 115200 baud via
`System.IO.Ports`, and has no UI dependencies (safe to reference from a
console app, ASP.NET Core app, or WPF/Avalonia app alike).

## Install / reference

Not published as a NuGet package; reference the project directly:

```
dotnet add reference ../SharpStatDriver/SharpStatDriver.csproj
```

## Quick start

```csharp
using IoRodeo.SharpStatDriver;
using System.Text.Json.Nodes;

await using var pstat = new Potentiostat("COM3");
await pstat.ConnectAsync();

Console.WriteLine(pstat.HardwareVariant);   // e.g. 10V_microAmpV0.2
await pstat.SetCurrRangeAsync(CurrRanges.Range100uA);

var param = new JsonObject
{
    ["quietValue"] = 0.0,
    ["quietTime"] = 1000,
    ["amplitude"] = 1.0,
    ["offset"] = 0.0,
    ["period"] = 2000,
    ["numCycles"] = 3,
    ["shift"] = 0.0,
};

pstat.SampleReceived += (_, e) =>
    Console.WriteLine($"{e.Sample.TimeSeconds:0.000} s  {e.Sample.Volt:0.0000} V  {e.Sample.Curr:0.0000} uA");

var result = await pstat.RunTestAsync("cyclic", param);
// result.Times (s), result.Volts (V), result.Currents (uA)
```

`Potentiostat` implements `IDisposable`/`IAsyncDisposable`; disposing while a
test is running best-effort sends `stopTest` before closing the port.

## Layout

- `Potentiostat.cs` — main device class: connection lifecycle, get/set
  commands, electrode/mux control, and the `RunTestAsync` streaming loop
- `SerialJsonTransport.cs` — real serial transport (115200 baud, DTR/RTS
  asserted, line-delimited JSON), including the 64-byte write workaround
- `ISerialTransport.cs` — transport interface; lets the driver run against
  something other than a real port
- `Simulation/` — `DummyTransport` + `DummyWaveformGenerator`, an in-process
  fake device (no hardware) that streams synthetic waveforms for `runTest`,
  used by the demo app and available for UI development without a Rodeostat
- `Protocol/` — wire-format constants (`Commands`, `JsonKeys`) and DTOs
  (`Sample`, `SampleEventArgs`, `TestProgress`)
- `Ranges.cs` — `VoltRanges`/`CurrRanges` constants and the
  `HardwareVariants` lookup tables used to validate range settings
  against the connected hardware
- `TestResult.cs` — `TestResult`/`ChannelData`, the acquired time/volt/current
  series returned by `RunTestAsync` (per mux channel, or flattened via
  `Times`/`Volts`/`Currents` when the mux is disabled)
- `Exceptions.cs` — `PotentiostatException` hierarchy
  (`CommandFailedException`, `CommandMismatchException`,
  `DataDecodeException`, `HardwareVersionException`)
- `Helpers/CsvSampleWriter.cs` — opt-in CSV writer you can wire up to
  `SampleReceived`; not used internally by the library

## API overview

- **Connect**: `ConnectAsync()` opens the port, discards stale input, and
  caches `HardwareVariant`/`FirmwareVersion`/`HardwareVersion`.
- **Immediate get/set**: `GetVoltAsync`/`SetVoltAsync`, `GetCurrAsync`,
  `GetRefVoltAsync`, `GetVoltRangeAsync`/`SetVoltRangeAsync`,
  `GetCurrRangeAsync`/`SetCurrRangeAsync`, `GetSamplePeriodAsync`/
  `SetSamplePeriodAsync` (and the Hz-based `GetSampleRateAsync`/
  `SetSampleRateAsync` wrappers), `GetDeviceIdAsync`/`SetDeviceIdAsync`.
- **Test parameters**: `GetParamAsync`/`SetParamAsync` take/return
  `JsonObject` — parameters are firmware-defined and deliberately untyped.
  `GetTestNamesAsync` and `GetTestDoneTimeAsync` describe what a test
  supports and how long it will take.
- **Electrode connection control** (requires hardware ≥ `HW0.2`):
  `Get/SetRefElectConnectedAsync`, `Get/SetCtrElectConnectedAsync`,
  `Get/SetWrkElectConnectedAsync`, `Get/SetAllElectConnectedAsync`,
  `Get/SetAutoConnectAsync`, `Get/SetRefElectVoltRangeAsync`.
- **Multiplexer expansion hardware**: `Get/SetMuxEnabledAsync`,
  `Get/SetEnabledMuxChannelsAsync`, `GetMuxTestNamesAsync`,
  `Get/SetMuxRefElectConnectedAsync`, `Get/SetMuxCtrElectConnectedAsync`,
  `Get/SetMuxWrkElectConnectedAsync`, `DisconnectAllMuxElectAsync`.
- **Running a test**: `RunTestAsync(testName, param?, progress?, maxDecodeErrors?, cancellationToken)`
  sets parameters (if given), starts the test, and streams samples until the
  device sends its end-of-test terminator. Subscribe to `SampleReceived` for
  live samples or pass an `IProgress<TestProgress>` for a progress bar.
  Cancelling the token sends `stopTest`, drains the stream, then throws
  `OperationCanceledException`. Malformed streamed lines count against
  `maxDecodeErrors` (default `0`; pass `null` for unlimited) before a
  `DataDecodeException` is thrown.
- **Escape hatch**: `SendCommandAsync(JsonObject cmd, ...)` sends a raw
  command and validates/unwraps the response — prefer the typed methods
  above unless you're calling something not yet wrapped.

## Wire protocol

Newline-delimited JSON. Command: `{"command":"getVolt"}\n`. Response:
`{"success":true,"response":{"command":"getVolt","v":1.25}}`. While a test
runs, the device streams one sample per line
(`{"t":ms,"v":volts,"i":uA}`, plus `"n"` for the mux channel and `"le"` for a
current limit error); a line **without** the `t`/`v`/`i` keys is the
end-of-test terminator.

## Notable behavior

- Firmware/hardware version gates (`>= "0.0.5"` for mux, `>= "HW0.2"` for
  electrode control) use **ordinal** string comparison, matching the Python
  driver — real devices report values (`FW0.0.9`, `V0.2`) that only compare
  correctly this way.
- `GetHardwareVersionAsync` fails gracefully on pre-`HW0.2` firmware,
  returning `"HW0.1 (default)"` instead of throwing.
- Times are always exposed in seconds (`Sample.TimeSeconds`); `Sample.TimeMs`
  keeps the raw device value.

## Testing

`tests/SharpStatDriver.Tests` exercises this library against `FakeTransport`
(scripted via a `Responder` callback) — no hardware required:

```
dotnet test
```
