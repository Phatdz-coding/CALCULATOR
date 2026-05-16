using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Text;
using CalculatorUI.Interop;

namespace CalculatorUI;

public partial class MainWindow : Window
{
    private bool _replaceDisplay = true;

    public MainWindow()
    {
        InitializeComponent();
    }

    private void Input_Click(object sender, RoutedEventArgs e)
    {
        if (sender is not Button button)
            return;

        AppendInput(button.Content?.ToString() ?? string.Empty);
    }

    private void AppendInput(string input)
    {
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
        DisplayTextBox.Text = "0";
        _replaceDisplay = true;
    }

    private void Backspace_Click(object sender, RoutedEventArgs e)
    {
        DeleteLastInput();
    }

    private void DeleteLastInput()
    {
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
        int rootCount = NativeMethods.SolveEquationRoots(equation, variable, -1_000_000.0, 1_000_000.0, roots, maxRoots);

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
        NativeMethods.ClearState();
        DisplayTextBox.Text = "0";
        _replaceDisplay = true;
    }

    private void Window_PreviewTextInput(object sender, TextCompositionEventArgs e)
    {
        string text = e.Text;
        if (text.Length == 1 && IsAllowedTypedInput(text[0]))
        {
            AppendInput(text);
            e.Handled = true;
        }
    }

    private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
    {
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
