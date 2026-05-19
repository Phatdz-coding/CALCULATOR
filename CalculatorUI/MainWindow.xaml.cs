using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Text;
using System.Globalization;
using System.Numerics;
using CalculatorUI.Interop;

namespace CalculatorUI;

public partial class MainWindow : Window
{
    private bool _replaceDisplay = true;
    private int _polynomialDegree;
    private int _coefficientIndex;
    private double[] _coefficients = [];
    private string _coefficientInput = string.Empty;

    public MainWindow()
    {
        InitializeComponent();
    }

    private void Input_Click(object sender, RoutedEventArgs e)
    {
        if (sender is not Button button)
            return;

        AppendInput(button.Tag?.ToString() ?? button.Content?.ToString() ?? string.Empty);
    }

    private void Mode_Click(object sender, RoutedEventArgs e)
    {
        if (sender is not FrameworkElement item)
            return;

        string mode = item.Tag?.ToString() ?? "Scientific";
        Title = $"{mode} - Calculator";
        ModeTitleTextBlock.Text = mode;
        ModeToggleButton.IsChecked = false;

        SetDerivativeMode(mode == "Derivative Calculator");

        if (mode is "Solve Quadratic Equation" or "Solve Cubic Equation" or "Solve Quartic Equation")
        {
            StartPolynomialMode(mode);
            return;
        }

        ClearPolynomialMode();
        DisplayTextBox.Text = mode switch
        {
            "Scientific" => "0",
            "Derivative Calculator" => "0",
            "Integral Calculator" => "integral(",
            "Solve Any Equation" => "x=",
            _ => mode
        };

        _replaceDisplay = mode is not "Derivative Calculator" and not "Integral Calculator" and not "Solve Any Equation";
        DisplayTextBox.CaretIndex = DisplayTextBox.Text.Length;
    }

    private void SetDerivativeMode(bool isEnabled)
    {
        if (DerivativePanel is null || KeypadGrid is null)
            return;

        DerivativePanel.Visibility = isEnabled ? Visibility.Visible : Visibility.Collapsed;
        KeypadGrid.Visibility = isEnabled ? Visibility.Collapsed : Visibility.Visible;

        if (isEnabled)
        {
            DerivativeFunctionTextBox.Text = string.Empty;
            DerivativeVariableTextBox.Text = "x";
            DerivativeFunctionTextBox.Focus();
        }
    }

    private void ApplyDerivative_Click(object sender, RoutedEventArgs e)
    {
        string function = DerivativeFunctionTextBox.Text.Trim();
        string variableText = DerivativeVariableTextBox.Text.Trim();

        if (string.IsNullOrWhiteSpace(function))
        {
            DisplayTextBox.Text = "Enter a function for differentiation";
            _replaceDisplay = true;
            return;
        }

        if (variableText.Length != 1 || !char.IsLetter(variableText[0]))
        {
            DisplayTextBox.Text = "Variable must be a single letter";
            _replaceDisplay = true;
            return;
        }

        char variable = variableText.First();

        DisplayTextBox.Text = NativeMethods.differentiate(function, variable);
        _replaceDisplay = true;
        DisplayTextBox.CaretIndex = DisplayTextBox.Text.Length;
    }

    private void AppendInput(string input)
    {
        if (_polynomialDegree > 0)
        {
            AppendPolynomialInput(input);
            return;
        }

        if (_replaceDisplay || DisplayTextBox.Text == "0")
        {
            DisplayTextBox.Text = input;
            _replaceDisplay = false;
        }
        else
        {
            DisplayTextBox.Text += input;
        }

        DisplayTextBox.CaretIndex = DisplayTextBox.Text.Length;
    }

    private void Clear_Click(object sender, RoutedEventArgs e)
    {
        ClearDisplay();
    }

    private void ClearDisplay()
    {
        if (_polynomialDegree > 0)
        {
            _coefficientInput = string.Empty;
            UpdatePolynomialDisplay();
            return;
        }

        DisplayTextBox.Text = "0";
        _replaceDisplay = true;
    }

    private void Backspace_Click(object sender, RoutedEventArgs e)
    {
        DeleteLastInput();
    }

    private void DeleteLastInput()
    {
        if (_polynomialDegree > 0)
        {
            if (_coefficientInput.Length > 0)
                _coefficientInput = _coefficientInput[..^1];

            UpdatePolynomialDisplay();
            return;
        }

        if (_replaceDisplay || DisplayTextBox.Text.Length <= 1)
        {
            DisplayTextBox.Text = "0";
            _replaceDisplay = true;
            return;
        }

        DisplayTextBox.Text = DisplayTextBox.Text[..^1];

        if (DisplayTextBox.Text.Length == 0)
        {
            DisplayTextBox.Text = "0";
            _replaceDisplay = true;
        }
    }

    private void Equals_Click(object sender, RoutedEventArgs e)
    {
        if (_polynomialDegree > 0)
        {
            ConfirmPolynomialCoefficient();
            return;
        }

        EvaluateCurrentExpression();
    }

    private void EvaluateCurrentExpression()
    {
        string expression = DisplayTextBox.Text.Trim();

        if (string.IsNullOrWhiteSpace(expression) || expression == "0")
            return;

        try
        {
            if (expression.Contains('='))
            {
                DisplayTextBox.Text = SolveEquation(expression);
            }
            else
            {
                double result = NativeMethods.EvaluateExpressionDouble(expression);
                DisplayTextBox.Text = double.IsFinite(result) ? result.ToString("G15") : "Calculation error";
            }
            _replaceDisplay = true;
        }
        catch (DllNotFoundException)
        {
            DisplayTextBox.Text = "CalculatorCore.dll not found";
            _replaceDisplay = true;
        }
        catch (EntryPointNotFoundException)
        {
            DisplayTextBox.Text = "Native function not exported";
            _replaceDisplay = true;
        }
        catch (Exception ex)
        {
            DisplayTextBox.Text = ex.Message;
            _replaceDisplay = true;
        }
    }

    private static string SolveEquation(string equation)
    {
        const int maxRoots = 50;
        double[] roots = new double[maxRoots];
        byte variable = (byte)FindSolveVariable(equation);
        int rootCount = NativeMethods.SolveEquationRoots(equation, variable, -100.0, 100.0, roots, maxRoots);

        if (rootCount < 0)
            return "Failed to solve equation";

        if (rootCount == 0)
            return $"No solution found for {(char)variable}";

        var result = new StringBuilder();
        for (int i = 0; i < rootCount; i++)
        {
            if (i > 0)
                result.Append(", ");

            result.Append((char)variable);
            result.Append(" = ");
            result.Append(roots[i].ToString("G15"));
        }

        return result.ToString();
    }

    private static char FindSolveVariable(string equation)
    {
        if (equation.Contains('x'))
            return 'x';

        foreach (char character in equation)
        {
            if (char.IsAsciiLetter(character) && character is not 'c' and not 'e' and not 'g')
                return character;
        }

        return 'x';
    }

    private void Equation_Click(object sender, RoutedEventArgs e)
    {
        DisplayTextBox.Text = "solve(";
        _replaceDisplay = false;
    }

    private void ClearState_Click(object sender, RoutedEventArgs e)
    {
        ClearPolynomialMode();
        NativeMethods.ClearState();
        DisplayTextBox.Text = "0";
        _replaceDisplay = true;
    }

    private void Window_PreviewTextInput(object sender, TextCompositionEventArgs e)
    {
        if (IsDerivativeModeActive())
            return;

        string text = e.Text;
        if (text.Length == 1 && IsAllowedTypedInput(text[0]))
        {
            AppendInput(text);
            e.Handled = true;
        }
    }

    private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
    {
        if (IsDerivativeModeActive())
            return;

        string? input = KeyToCalculatorInput(e.Key);
        if (input is not null)
        {
            AppendInput(input);
            e.Handled = true;
            return;
        }

        switch (e.Key)
        {
            case Key.Enter:
                EvaluateCurrentExpression();
                e.Handled = true;
                break;
            case Key.Back:
                DeleteLastInput();
                e.Handled = true;
                break;
            case Key.Delete:
            case Key.Escape:
                ClearDisplay();
                e.Handled = true;
                break;
        }
    }

    private bool IsDerivativeModeActive()
    {
        return DerivativePanel is not null && DerivativePanel.Visibility == Visibility.Visible;
    }

    private void StartPolynomialMode(string mode)
    {
        _polynomialDegree = mode switch
        {
            "Solve Quadratic Equation" => 2,
            "Solve Cubic Equation" => 3,
            "Solve Quartic Equation" => 4,
            _ => 0
        };

        _coefficients = new double[_polynomialDegree + 1];
        _coefficientIndex = 0;
        _coefficientInput = string.Empty;
        _replaceDisplay = false;
        UpdatePolynomialDisplay();
    }

    private void ClearPolynomialMode()
    {
        _polynomialDegree = 0;
        _coefficientIndex = 0;
        _coefficients = [];
        _coefficientInput = string.Empty;
    }

    private void AppendPolynomialInput(string input)
    {
        if (input.Length != 1)
            return;

        char character = input[0];
        if (char.IsDigit(character) || character is '.' or '-')
        {
            if (character == '-' && _coefficientInput.Length > 0)
                return;

            if (character == '.' && _coefficientInput.Contains('.'))
                return;

            _coefficientInput += input;
            UpdatePolynomialDisplay();
        }
    }

    private void ConfirmPolynomialCoefficient()
    {
        if (!double.TryParse(_coefficientInput, NumberStyles.Float, CultureInfo.InvariantCulture, out double coefficient))
        {
            DisplayTextBox.Text = $"{GetPolynomialEquationForm()}\n{GetCurrentCoefficientName()}? invalid";
            _coefficientInput = string.Empty;
            return;
        }

        if (_coefficientIndex == 0 && Math.Abs(coefficient) <= 1e-12)
        {
            DisplayTextBox.Text = $"{GetPolynomialEquationForm()}\na cannot be 0";
            _coefficientInput = string.Empty;
            return;
        }

        _coefficients[_coefficientIndex] = coefficient;
        _coefficientInput = string.Empty;
        _coefficientIndex++;

        if (_coefficientIndex < _coefficients.Length)
        {
            UpdatePolynomialDisplay();
            return;
        }

        DisplayTextBox.Text = SolvePolynomial();
        _replaceDisplay = true;
        ClearPolynomialMode();
    }

    private void UpdatePolynomialDisplay()
    {
        var display = new StringBuilder();
        display.AppendLine(GetPolynomialEquationForm());

        for (int i = 0; i < _coefficientIndex; i++)
        {
            if (i > 0)
                display.Append("  ");

            display.Append(GetCoefficientName(i));
            display.Append('=');
            display.Append(_coefficients[i].ToString("G15", CultureInfo.InvariantCulture));
        }

        if (_coefficientIndex > 0)
            display.AppendLine();

        display.Append(GetCurrentCoefficientName());
        display.Append("? ");
        display.Append(_coefficientInput.Length == 0 ? "_" : _coefficientInput);

        DisplayTextBox.Text = display.ToString();
        DisplayTextBox.CaretIndex = DisplayTextBox.Text.Length;
    }

    private string GetPolynomialEquationForm()
    {
        return _polynomialDegree switch
        {
            2 => "ax^2 + bx + c = 0",
            3 => "ax^3 + bx^2 + cx + d = 0",
            4 => "ax^4 + bx^3 + cx^2 + dx + e = 0",
            _ => string.Empty
        };
    }

    private string GetCurrentCoefficientName()
    {
        return GetCoefficientName(_coefficientIndex);
    }

    private static string GetCoefficientName(int index)
    {
        return ((char)('a' + index)).ToString();
    }

    private string SolvePolynomial()
    {
        Complex[] roots = SolvePolynomialRoots(_coefficients);
        var result = new StringBuilder();
        result.AppendLine(GetPolynomialEquationForm());

        for (int i = 0; i < roots.Length; i++)
        {
            result.Append('x');
            result.Append(i + 1);
            result.Append(" = ");
            result.Append(FormatComplex(roots[i]));

            if (i < roots.Length - 1)
                result.AppendLine();
        }

        return result.ToString();
    }

    private static Complex[] SolvePolynomialRoots(double[] coefficients)
    {
        int degree = coefficients.Length - 1;
        Complex[] roots = new Complex[degree];
        double radius = 1.0;

        for (int i = 1; i < coefficients.Length; i++)
            radius = Math.Max(radius, Math.Abs(coefficients[i] / coefficients[0]) + 1.0);

        for (int i = 0; i < degree; i++)
        {
            double angle = 2.0 * Math.PI * i / degree;
            roots[i] = Complex.FromPolarCoordinates(radius, angle);
        }

        for (int iteration = 0; iteration < 200; iteration++)
        {
            double maxChange = 0.0;

            for (int i = 0; i < degree; i++)
            {
                Complex denominator = Complex.One;
                for (int j = 0; j < degree; j++)
                {
                    if (i != j)
                        denominator *= roots[i] - roots[j];
                }

                if (denominator.Magnitude <= 1e-18)
                    denominator = new Complex(1e-18, 0.0);

                Complex change = EvaluatePolynomial(coefficients, roots[i]) / denominator;
                roots[i] -= change;
                maxChange = Math.Max(maxChange, change.Magnitude);
            }

            if (maxChange <= 1e-12)
                break;
        }

        return roots.OrderBy(root => Math.Abs(root.Imaginary) <= 1e-9 ? 0 : 1)
            .ThenBy(root => root.Real)
            .ThenBy(root => root.Imaginary)
            .ToArray();
    }

    private static Complex EvaluatePolynomial(double[] coefficients, Complex x)
    {
        Complex result = Complex.Zero;
        foreach (double coefficient in coefficients)
            result = result * x + coefficient;

        return result;
    }

    private static string FormatComplex(Complex value)
    {
        double real = Math.Abs(value.Real) <= 1e-10 ? 0.0 : value.Real;
        double imaginary = Math.Abs(value.Imaginary) <= 1e-10 ? 0.0 : value.Imaginary;

        if (imaginary == 0.0)
            return real.ToString("G12", CultureInfo.InvariantCulture);

        if (real == 0.0)
            return $"{imaginary.ToString("G12", CultureInfo.InvariantCulture)}i";

        string sign = imaginary < 0.0 ? " - " : " + ";
        return $"{real.ToString("G12", CultureInfo.InvariantCulture)}{sign}{Math.Abs(imaginary).ToString("G12", CultureInfo.InvariantCulture)}i";
    }

    private static bool IsAllowedTypedInput(char input)
    {
        return char.IsLetterOrDigit(input)
            || input is '+' or '-' or '*' or '/' or '^' or '(' or ')' or '.' or ',' or '!' or '=';
    }

    private static string? KeyToCalculatorInput(Key key)
    {
        return key switch
        {
            Key.Add => "+",
            Key.Subtract => "-",
            Key.Multiply => "*",
            Key.Divide => "/",
            Key.Decimal => ".",
            Key.OemPlus when Keyboard.Modifiers.HasFlag(ModifierKeys.Shift) => "+",
            Key.OemPlus => "=",
            Key.OemMinus => "-",
            Key.OemComma => ",",
            Key.OemPeriod => ".",
            Key.D9 when Keyboard.Modifiers.HasFlag(ModifierKeys.Shift) => "(",
            Key.D0 when Keyboard.Modifiers.HasFlag(ModifierKeys.Shift) => ")",
            Key.D6 when Keyboard.Modifiers.HasFlag(ModifierKeys.Shift) => "^",
            Key.D1 when Keyboard.Modifiers.HasFlag(ModifierKeys.Shift) => "!",
            _ => null
        };
    }
}
