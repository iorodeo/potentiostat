namespace IoRodeo.SharpStatDriver;

/// <summary>Hardware version strings reported by the device.</summary>
public static class HardwareVersions
{
    public const string Default = "HW0.1 (default)";
    public const string V0p1 = "HW0.1";
    public const string V0p2 = "HW0.2";
}

/// <summary>Output voltage range settings.</summary>
public static class VoltRanges
{
    public const string Range1V = "1V";
    public const string Range2V = "2V";
    public const string Range4V = "4V";
    public const string Range5V = "5V";
    public const string Range8V = "8V";
    public const string Range10V = "10V";

    public static readonly IReadOnlyList<string> List8V =
        new[] { Range1V, Range2V, Range4V, Range8V };

    public static readonly IReadOnlyList<string> List10V =
        new[] { Range1V, Range2V, Range5V, Range10V };
}

/// <summary>Working electrode current range settings.</summary>
public static class CurrRanges
{
    public const string Range60nA = "60nA";
    public const string Range100nA = "100nA";
    public const string Range1uA = "1uA";
    public const string Range10uA = "10uA";
    public const string Range100uA = "100uA";
    public const string Range1000uA = "1000uA";
    public const string Range10000uA = "10000uA";
    public const string Range12000uA = "12000uA";
    public const string Range24000uA = "24000uA";

    public static readonly IReadOnlyList<string> ListNanoAmp =
        new[] { Range1uA, Range10uA, Range100nA, Range60nA };

    public static readonly IReadOnlyList<string> ListMicroAmp =
        new[] { Range1uA, Range10uA, Range100uA, Range1000uA };

    public static readonly IReadOnlyList<string> List10MilliAmp =
        new[] { Range10uA, Range100uA, Range1000uA, Range10000uA };

    public static readonly IReadOnlyList<string> List24MilliAmp =
        new[] { Range100uA, Range1000uA, Range12000uA, Range24000uA };
}

/// <summary>Lookup tables mapping hardware variant strings to supported ranges.</summary>
public static class HardwareVariants
{
    public static readonly IReadOnlyDictionary<string, IReadOnlyList<string>> VoltRangesByVariant =
        new Dictionary<string, IReadOnlyList<string>>
        {
            ["nanoAmpV0.1"] = VoltRanges.List10V,
            ["microAmpV0.1"] = VoltRanges.List10V,
            ["milliAmpV0.1"] = VoltRanges.List10V,
            ["AD8250_nanoAmpV0.1"] = VoltRanges.List10V,
            ["AD8250_microAmpV0.1"] = VoltRanges.List10V,
            ["AD8250_milliAmpV0.1"] = VoltRanges.List10V,
            ["AD8251_nanoAmpV0.1"] = VoltRanges.List8V,
            ["AD8251_microAmpV0.1"] = VoltRanges.List8V,
            ["AD8251_milliAmpV0.1"] = VoltRanges.List8V,
            ["10V_nanoAmpV0.2"] = VoltRanges.List10V,
            ["10V_microAmpV0.2"] = VoltRanges.List10V,
            ["10V_milliAmpV0.2"] = VoltRanges.List10V,
            ["10V_10MilliAmpV0.2"] = VoltRanges.List10V,
            ["10V_24MilliAmpV0.2"] = VoltRanges.List10V,
        };

    public static readonly IReadOnlyDictionary<string, IReadOnlyList<string>> CurrRangesByVariant =
        new Dictionary<string, IReadOnlyList<string>>
        {
            ["nanoAmpV0.1"] = CurrRanges.ListNanoAmp,
            ["microAmpV0.1"] = CurrRanges.ListMicroAmp,
            ["milliAmpV0.1"] = CurrRanges.List24MilliAmp,
            ["AD8250_nanoAmpV0.1"] = CurrRanges.ListNanoAmp,
            ["AD8250_microAmpV0.1"] = CurrRanges.ListMicroAmp,
            ["AD8250_milliAmpV0.1"] = CurrRanges.List24MilliAmp,
            ["AD8251_nanoAmpV0.1"] = CurrRanges.ListNanoAmp,
            ["AD8251_microAmpV0.1"] = CurrRanges.ListMicroAmp,
            ["AD8251_milliAmpV0.1"] = CurrRanges.List24MilliAmp,
            ["10V_nanoAmpV0.2"] = CurrRanges.ListNanoAmp,
            ["10V_microAmpV0.2"] = CurrRanges.ListMicroAmp,
            ["10V_milliAmpV0.2"] = CurrRanges.List24MilliAmp,
            ["10V_10MilliAmpV0.2"] = CurrRanges.List10MilliAmp,
            ["10V_24MilliAmpV0.2"] = CurrRanges.List24MilliAmp,
        };
}
