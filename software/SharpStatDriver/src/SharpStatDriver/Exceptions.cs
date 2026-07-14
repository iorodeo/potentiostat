namespace IoRodeo.SharpStatDriver;

/// <summary>Base type for all errors raised by the Rodeostat driver.</summary>
public class PotentiostatException : Exception
{
    public PotentiostatException(string message) : base(message) { }
    public PotentiostatException(string message, Exception inner) : base(message, inner) { }
}

/// <summary>The device replied with success=false, or the reply was malformed.</summary>
public class CommandFailedException : PotentiostatException
{
    public CommandFailedException(string message) : base(message) { }
}

/// <summary>The command or test name echoed by the device does not match what was sent.</summary>
public class CommandMismatchException : PotentiostatException
{
    public CommandMismatchException(string message) : base(message) { }
}

/// <summary>Too many JSON decode errors while streaming test data.</summary>
public class DataDecodeException : PotentiostatException
{
    public DataDecodeException(string message) : base(message) { }
    public DataDecodeException(string message, Exception inner) : base(message, inner) { }
}

/// <summary>The connected hardware version does not support the requested feature.</summary>
public class HardwareVersionException : PotentiostatException
{
    public HardwareVersionException(string message) : base(message) { }
}
