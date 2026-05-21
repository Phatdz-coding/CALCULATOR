using System.Runtime.InteropServices;

namespace CalculatorUI.Interop;

internal static class NativeMethods
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct GslComplex
    {
        public double Real;
        public double Imag;
    }

    private const string DllName = "CalculatorCore.dll";

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "evaluate_expression")]
    internal static extern long EvaluateExpression(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string expression);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "differentiate")]
    private static extern IntPtr differentiate_support(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string function, char variable);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "integral")]
    internal static extern double Integral(
        [MarshalAs(UnmanagedType.LPUTF8Str)] string function, char variable, string l_bound, string u_bound, int method);

    internal static string Differentiate(string function, char variable)
    {
        IntPtr resultPtr = differentiate_support(function, variable);
        try
        {
            return resultPtr == IntPtr.Zero
                ? string.Empty
                : Marshal.PtrToStringUTF8(resultPtr) ?? string.Empty;
        }
        finally
        {
            if (resultPtr != IntPtr.Zero)
                FreeString(resultPtr);
        }
    }


    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "free_string")]
    private static extern void FreeString(IntPtr text);

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

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "free_solutions")]
    private static extern void free_solutions(IntPtr solutions);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "solve_polynomial")]
    private static extern IntPtr solve_polynomial(double[] coef, int degree);

    internal static GslComplex[] SolvePolynomial(double[] coef)
    {
        if (coef == null || coef.Length < 2)
            return Array.Empty<GslComplex>();

        int degree = coef.Length - 1;
        IntPtr ptr = solve_polynomial(coef, degree);
        if (ptr == IntPtr.Zero)
            return Array.Empty<GslComplex>();

        try
        {
            int count = degree;
            var result = new GslComplex[count];
            int size = Marshal.SizeOf<GslComplex>();
            for (int i = 0; i < count; i++)
            {
                IntPtr itemPtr = IntPtr.Add(ptr, i * size);
                result[i] = Marshal.PtrToStructure<GslComplex>(itemPtr);
            }
            return result;
        }
        finally
        {
            free_solutions(ptr);
        }
    }

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
