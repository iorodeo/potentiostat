namespace IoRodeo.SharpStatDriver.Protocol;

/// <summary>Command names understood by the Rodeostat firmware.</summary>
public static class Commands
{
    public const string RunTest = "runTest";
    public const string StopTest = "stopTest";
    public const string GetVolt = "getVolt";
    public const string SetVolt = "setVolt";
    public const string GetCurr = "getCurr";
    public const string GetRefVolt = "getRefVolt";
    public const string GetParam = "getParam";
    public const string SetParam = "setParam";
    public const string GetVoltRange = "getVoltRange";
    public const string SetVoltRange = "setVoltRange";
    public const string GetCurrRange = "getCurrRange";
    public const string SetCurrRange = "setCurrRange";
    public const string GetDeviceId = "getDeviceId";
    public const string SetDeviceId = "setDeviceId";
    public const string GetSamplePeriod = "getSamplePeriod";
    public const string SetSamplePeriod = "setSamplePeriod";
    public const string GetTestDoneTime = "getTestDoneTime";
    public const string GetTestNames = "getTestNames";
    public const string GetVersion = "getVersion";
    public const string GetVariant = "getVariant";

    public const string SetMuxEnabled = "setMuxEnabled";
    public const string GetMuxEnabled = "getMuxEnabled";
    public const string SetEnabledMuxChannels = "setEnabledMuxChannels";
    public const string GetEnabledMuxChannels = "getEnabledMuxChannels";
    public const string GetMuxTestNames = "getMuxTestNames";
    public const string SetMuxRefElectConnected = "setMuxRefElectConnected";
    public const string GetMuxRefElectConnected = "getMuxRefElectConnected";
    public const string SetMuxCtrElectConnected = "setMuxCtrElectConnected";
    public const string GetMuxCtrElectConnected = "getMuxCtrElectConnected";
    public const string SetMuxWrkElectConnected = "setMuxWrkElectConnected";
    public const string GetMuxWrkElectConnected = "getMuxWrkElectConnected";
    public const string DisconnectAllMuxElect = "disconnectAllMuxElect";

    public const string SetRefElectConnected = "setRefElectConnected";
    public const string GetRefElectConnected = "getRefElectConnected";
    public const string SetCtrElectConnected = "setCtrElectConnected";
    public const string GetCtrElectConnected = "getCtrElectConnected";
    public const string SetWrkElectConnected = "setWrkElectConnected";
    public const string GetWrkElectConnected = "getWrkElectConnected";
    public const string SetAllElectConnected = "setAllElectConnected";
    public const string GetAllElectConnected = "getAllElectConnected";
    public const string SetElectAutoConnect = "setElectAutoConnect";
    public const string GetElectAutoConnect = "getElectAutoConnect";
    public const string SetRefElectVoltRange = "setRefElectVoltRange";
    public const string GetRefElectVoltRange = "getRefElectVoltRange";
    public const string GetHardwareVersion = "getHardwareVersion";
}
