namespace IoRodeo.SharpStatDriver.Protocol;

/// <summary>JSON message keys used by the Rodeostat firmware protocol.</summary>
public static class JsonKeys
{
    public const string Command = "command";
    public const string Response = "response";
    public const string Message = "message";
    public const string Success = "success";
    public const string Test = "test";
    public const string Param = "param";
    public const string Time = "t";
    public const string Volt = "v";
    public const string Curr = "i";
    public const string Chan = "n";
    public const string LimitErr = "le";
    public const string RefVolt = "r";
    public const string VoltRange = "voltRange";
    public const string CurrRange = "currRange";
    public const string DeviceId = "deviceId";
    public const string SamplePeriod = "samplePeriod";
    public const string TestDoneTime = "testDoneTime";
    public const string StepArray = "step";
    public const string TestNameArray = "testNames";
    public const string Version = "version";
    public const string Variant = "variant";
    public const string MuxEnabled = "muxEnabled";
    public const string MuxChannel = "muxChannel";
    public const string Connected = "connected";
    public const string AutoConnect = "autoConnect";
}
