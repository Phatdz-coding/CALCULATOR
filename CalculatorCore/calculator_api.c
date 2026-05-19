/*
▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄

to export this file to .dll
use the following command:
gcc -shared -o x64/Debug/CalculatorCore.dll calculator_api.c

▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄
*/

#include <MY_LIB/types_and_specifiers.h>
#include <MY_LIB/extra_math_function.h>
#include <MY_LIB/lexer_and_format.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/numerical_integration.h>
#include <MY_LIB/sovle_equations.h>

typedef struct CalculatorVariable
{
    unsigned char Name;
    unsigned char Reserved0[7];
    double Value;
    int IsSet;
    int Reserved1;
} CalculatorVariable;

typedef struct CalculatorState
{
    int AngleMode;
    int LastError;
    int VariableCount;
    double LastResult;
    CalculatorVariable Variables[49];
} CalculatorState;

static CalculatorState g_state;
static int g_state_initialized = 0;

static void calculator_init_state(void)
{
    if (g_state_initialized)
        return;

    memset(&g_state, 0, sizeof(g_state));
    g_state.VariableCount = 49;

    static const unsigned char kVariableNames[49] = {
        'a', 'b', 'd', 'f', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
        'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
        'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int i = 0; i < 49; i++)
    {
        g_state.Variables[i].Name = kVariableNames[i];
        g_state.Variables[i].Value = 0.0;
        g_state.Variables[i].IsSet = 0;
        g_state.Variables[i].Reserved1 = 0;
        memset(g_state.Variables[i].Reserved0, 0, sizeof(g_state.Variables[i].Reserved0));
    }

    g_state_initialized = 1;
}

static char *calculator_strdup(const char *text)
{
    if (!text)
        return NULL;

    size_t len = strlen(text);
    char *copy = (char *)malloc(len + 1);
    if (!copy)
        return NULL;

    memcpy(copy, text, len + 1);
    return copy;
}

static char *calculator_build_equation_function(const char *equation)
{
    const char *equals = strchr(equation, '=');
    if (!equals)
        return calculator_strdup(equation);

    size_t left_len = (size_t)(equals - equation);
    const char *right = equals + 1;
    size_t right_len = strlen(right);
    size_t out_len = left_len + 3 + right_len + 1;

    char *out = (char *)malloc(out_len + 1);
    if (!out)
        return NULL;

    memcpy(out, equation, left_len);
    out[left_len] = '\0';
    strcat(out, "-(");
    strcat(out, right);
    strcat(out, ")");
    return out;
}

long long evaluate_expression(const char *expression)
{
    // temp:
    // disable this feature
    return 0;
}

double evaluate_expression_double(const char *expression)
{
    calculator_init_state();
    if (!expression)
    {
        g_state.LastError = 1;
        return NAN;
    }

    char *mutable_expression = calculator_strdup(expression);
    if (!mutable_expression)
    {
        g_state.LastError = 1;
        return NAN;
    }

    double result = evaluate(mutable_expression);
    free(mutable_expression);

    g_state.LastResult = result;
    g_state.LastError = isfinite(result) ? 0 : 1;
    return result;
}

int solve_equation_roots(const char *equation,
                         unsigned char variable,
                         double lower_bound,
                         double upper_bound,
                         double *roots,
                         int maxRoots)
{
    calculator_init_state();
    if (!equation || !roots || maxRoots <= 0)
    {
        g_state.LastError = 1;
        return -1;
    }

    char *function_text = calculator_build_equation_function(equation);
    if (!function_text)
    {
        g_state.LastError = 1;
        return -1;
    }

    INFIX infix_function = convert_string_to_INFIX(function_text);
    free(function_text);

    if (!infix_function.tokens || infix_function.size <= 0)
    {
        g_state.LastError = 1;
        return -1;
    }

    bool var_found = false;
    for (int i = 0; i < infix_function.size; i++)
    {
        if (infix_function.tokens[i].variable == (char)variable)
        {
            var_found = true;
            break;
        }
    }

    if (!var_found)
    {
        free(infix_function.tokens);
        g_state.LastError = 2;
        return -2;
    }

    double *solver_roots = NULL;
    short int root_count = se_solve_equation(infix_function, (char)variable, lower_bound, upper_bound, &solver_roots);
    free(infix_function.tokens);

    if (!solver_roots || root_count < 0)
    {
        if (solver_roots)
            free(solver_roots);
        g_state.LastError = 3;
        return -1;
    }

    int write_count = root_count < maxRoots ? root_count : maxRoots;
    for (int i = 0; i < write_count; i++)
    {
        roots[i] = solver_roots[i];
    }

    free(solver_roots);
    g_state.LastError = 0;
    return write_count;
}

int calculator_get_state(CalculatorState *state)
{
    calculator_init_state();
    if (!state)
        return -1;

    *state = g_state;
    return 0;
}

int calculator_set_state(const CalculatorState *state)
{
    calculator_init_state();
    if (!state)
        return -1;

    g_state = *state;
    g_state_initialized = 1;
    return 0;
}

int calculator_clear_state(void)
{
    calculator_init_state();
    g_state.LastError = 0;
    g_state.LastResult = 0.0;
    g_state.AngleMode = 0;

    for (int i = 0; i < g_state.VariableCount && i < 49; i++)
    {
        g_state.Variables[i].Value = 0.0;
        g_state.Variables[i].IsSet = 0;
    }

    return 0;
}

char * differentiate(char * function, char variable){
    INFIX I_function = convert_string_to_INFIX(function);
    INFIX I_result = differentiate_I_exp(I_function, variable);
    string_ result = convert_INFIX_to_string(I_result);
    free(I_function.tokens);
    free(I_result.tokens);
    return result.Content;
}

int main()
{
    // main function to test api
    printf("%g", evaluate("infinity"));
    return 0;
}