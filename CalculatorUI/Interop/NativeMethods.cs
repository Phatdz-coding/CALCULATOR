using System.Runtime.InteropServices;

namespace CalculatorUI.Interop;

internal static class NativeMethods
{
    private const string DllName = "CalculatorCore.dll";

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "evaluate_expression")]
    internal static extern long EvaluateExpression(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string expression);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "evaluate_expression_double")]
    internal static extern double EvaluateExpressionDouble(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string expression);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "solve_equation_roots")]
    internal static extern int SolveEquationRoots(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string equation,
        byte variable,
        double lowerBound,
        double upperBound,
        [Out] double[] roots,
        int maxRoots);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "calculator_get_state")]
    internal static extern int GetState(out CalculatorState state);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "calculator_set_state")]
    internal static extern int SetState(in CalculatorState state);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "calculator_clear_state")]
    internal static extern int ClearState();
}

[StructLayout(LayoutKind.Sequential)]
internal struct CalculatorVariable
{
    public byte Name;

    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
    public byte[] Reserved0;

    public double Value;
    public int IsSet;
    public int Reserved1;
}

[StructLayout(LayoutKind.Sequential)]
internal struct CalculatorState
{
    public int AngleMode;
    public int LastError;
    public int VariableCount;
    public double LastResult;

    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 49)]
    public CalculatorVariable[] Variables;
}
