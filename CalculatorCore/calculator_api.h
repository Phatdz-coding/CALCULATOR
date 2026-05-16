#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CALCULATORCORE_EXPORTS
#define CALC_API __declspec(dllexport)
#else
#define CALC_API __declspec(dllimport)
#endif

#define CALC_CALL __cdecl
#define CALC_MAX_VARIABLES 49

typedef struct CalculatorVariable
{
    char name;
    char reserved0[7];
    double value;
    int32_t is_set;
    int32_t reserved1;
} CalculatorVariable;

typedef struct CalculatorState
{
    int32_t angle_mode;
    int32_t last_error;
    int32_t variable_count;
    double last_result;
    CalculatorVariable variables[CALC_MAX_VARIABLES];
} CalculatorState;

CALC_API long long int CALC_CALL evaluate_expression(const char *expression);
CALC_API double CALC_CALL evaluate_expression_double(const char *expression);
CALC_API int CALC_CALL solve_equation_roots(
    const char *equation,
    char variable,
    double lower_bound,
    double upper_bound,
    double *roots,
    int32_t max_roots);

CALC_API int CALC_CALL calculator_get_state(CalculatorState *out_state);
CALC_API int CALC_CALL calculator_set_state(const CalculatorState *state);
CALC_API int CALC_CALL calculator_clear_state(void);

#ifdef __cplusplus
}
#endif
