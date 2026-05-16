#define _CRT_SECURE_NO_WARNINGS

#include "calculator_api.h"

#if defined(_MSC_VER)
#include <float.h>
#include <string.h>
#define __DBL_EPSILON__ DBL_EPSILON
#define __DBL_MAX__ DBL_MAX
#define strncasecmp _strnicmp
#endif

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <MY_LIB/my_calculator.h>

static CalculatorState g_state = {0};

static int copy_expression(char *destination, size_t destination_size, const char *source)
{
    if (destination == 0 || destination_size == 0 || source == 0 || source[0] == '\0')
        return 0;

#if defined(_MSC_VER)
    strncpy_s(destination, destination_size, source, _TRUNCATE);
#else
    strncpy(destination, source, destination_size - 1);
    destination[destination_size - 1] = '\0';
#endif

    return 1;
}

static int build_zero_equation(char *destination, size_t destination_size, const char *source)
{
    const char *equals = strchr(source, '=');
    if (equals == 0)
        return copy_expression(destination, destination_size, source);

    size_t left_length = (size_t)(equals - source);
    const char *right = equals + 1;

    if (left_length == 0 || right[0] == '\0')
        return 0;

#if defined(_MSC_VER)
    int written = _snprintf_s(
        destination,
        destination_size,
        _TRUNCATE,
        "%.*s-(%s)",
        (int)left_length,
        source,
        right);
    return written > 0;
#else
    int written = snprintf(destination, destination_size, "%.*s-(%s)", (int)left_length, source, right);
    return written > 0 && (size_t)written < destination_size;
#endif
}

double CALC_CALL evaluate_expression_double(const char *expression)
{
    char buffer[4096];

    if (!copy_expression(buffer, sizeof(buffer), expression))
    {
        g_state.last_error = 1;
        return NAN;
    }

    double result = evaluate(buffer);
    if (isnan(result) || isinf(result))
    {
        g_state.last_error = 2;
        return result;
    }

    g_state.last_error = 0;
    g_state.last_result = result;
    return result;
}

long long int CALC_CALL evaluate_expression(const char *expression)
{
    double result = evaluate_expression_double(expression);

    if (isnan(result) || isinf(result))
        return 0;

    return (long long int)llround(result);
}

int CALC_CALL solve_equation_roots(
    const char *equation,
    char variable,
    double lower_bound,
    double upper_bound,
    double *roots,
    int32_t max_roots)
{
    char buffer[4096];

    if (roots == 0 || max_roots <= 0 || variable == '\0' || !isfinite(lower_bound) || !isfinite(upper_bound))
    {
        g_state.last_error = 1;
        return -1;
    }

    if (!copy_expression(buffer, sizeof(buffer), equation))
    {
        g_state.last_error = 1;
        return -1;
    }

    if (!build_zero_equation(buffer, sizeof(buffer), equation))
    {
        g_state.last_error = 1;
        return -1;
    }

    __INFIX__ infix = convert_string_to_INFIX(buffer);
    if (infix.tokens == 0 || infix.size <= 0)
    {
        g_state.last_error = 2;
        return -2;
    }

    int variable_found = 0;
    for (int i = 0; i < infix.size; i++)
    {
        if (infix.tokens[i].variable == variable)
        {
            variable_found = 1;
            break;
        }
    }

    if (!variable_found)
    {
        free(infix.tokens);
        g_state.last_error = 3;
        return 0;
    }

    reformat_I_exp(&infix);
    optimize_I_exp(&infix);

    int copied_count = 0;
    const int intervals = 2000;
    const double step = (upper_bound - lower_bound) / intervals;
    const double epsilon = 1e-7;

    double previous_x = lower_bound;
    double previous_y = evaluate_I_1_var_function(infix, variable, previous_x);

    for (int i = 1; i <= intervals && copied_count < max_roots; i++)
    {
        double current_x = i == intervals ? upper_bound : lower_bound + (step * i);
        double current_y = evaluate_I_1_var_function(infix, variable, current_x);

        if (!isfinite(previous_y))
        {
            previous_x = current_x;
            previous_y = current_y;
            continue;
        }

        if (isfinite(current_y) && fabs(current_y) <= epsilon)
        {
            int duplicate = 0;
            for (int r = 0; r < copied_count; r++)
            {
                if (fabs(roots[r] - current_x) <= 1e-5)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate)
                roots[copied_count++] = current_x;
        }
        else if (isfinite(current_y) && previous_y * current_y < 0.0)
        {
            double left = previous_x;
            double right = current_x;
            double left_y = previous_y;

            for (int iteration = 0; iteration < 100; iteration++)
            {
                double mid = (left + right) / 2.0;
                double mid_y = evaluate_I_1_var_function(infix, variable, mid);

                if (!isfinite(mid_y))
                    break;

                if (fabs(mid_y) <= epsilon)
                {
                    left = mid;
                    right = mid;
                    break;
                }

                if (left_y * mid_y <= 0.0)
                {
                    right = mid;
                }
                else
                {
                    left = mid;
                    left_y = mid_y;
                }
            }

            double root = (left + right) / 2.0;
            int duplicate = 0;
            for (int r = 0; r < copied_count; r++)
            {
                if (fabs(roots[r] - root) <= 1e-5)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate)
                roots[copied_count++] = root;
        }

        previous_x = current_x;
        previous_y = current_y;
    }

    free(infix.tokens);

    g_state.last_error = 0;
    return copied_count;
}

int CALC_CALL calculator_get_state(CalculatorState *out_state)
{
    if (out_state == 0)
        return 0;

    *out_state = g_state;
    return 1;
}

int CALC_CALL calculator_set_state(const CalculatorState *state)
{
    if (state == 0)
        return 0;

    g_state = *state;
    return 1;
}

int CALC_CALL calculator_clear_state(void)
{
    memset(&g_state, 0, sizeof(g_state));
    return 1;
}
