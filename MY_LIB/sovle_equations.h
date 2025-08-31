#ifndef SOLVE_EQUATIONS_H
#define SOLVE_EQUATIONS_H

#include <MY_LIB/lexer_and_format.h>
#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/complex/math.c>
#include <gsl/poly/solve_cubic.c>
#include <gsl/poly/zsolve_cubic.c>
#include <gsl/sys/minmax.c>
#include <gsl/poly/zsolve_init.c>
#include <gsl/poly/zsolve.c>

// determine the minimum value of a number or expression that is likely to be zero
#define SE_EPSILON 1e-12

// determine the maximum iteration for refining root
#define SE_MAX_ITERATION 150
#define SE_MAX_RETRIES 5
#define SE_MAX_VARIABLES 100



// ====================================================================================================================== //
// ===============================================FUNCTION DECLARATIONS================================================== //
// ====================================================================================================================== //

bool se_is_real(const gsl_complex z);

void se_swap_2_complex_number(gsl_complex *z1, gsl_complex *z2);

void se_display_complex_number(gsl_complex z);

void se_display_quadratic_solutions(const gsl_complex root1, const gsl_complex root2);

void se_display_cubic_equation_solutions(const gsl_complex root1, const gsl_complex root2, const gsl_complex root3);

void se_display_quartic_equation_solutions(const gsl_complex root1, const gsl_complex root2,
                                           const gsl_complex root3, const gsl_complex root4);

short int se_sovle_quadratic_equation(const double a, const double b, const double c,
                                      gsl_complex *root1, gsl_complex *root2);

short int se_solve_cubic_equation(const double a, const double b, const double c, const double d,
                                  gsl_complex *root1, gsl_complex *root2, gsl_complex *root3);

short int se_solve_quartic_equation(const double a, const double b, const double c, const double d, const double e,
                                    gsl_complex *x1, gsl_complex *x2, gsl_complex *x3, gsl_complex *x4);

gsl_complex *se_convert__complex_packed_ptr__to__gsl_complex(gsl_complex_packed_ptr, const short int);

void se_free_complex_array(gsl_complex *array);

short int se_solve_polynomial_equation(const double *coefficients, const unsigned short int degree, gsl_complex **results);

double *se_solve_system_equation(int num_of_sol, double **coefficients);

double **se_malloc_coefficients_of_system_equation(const unsigned short int num_of_variable);

void se_free_coefficients_of_system_equation(double ***coefficients, const unsigned short int num_of_variable);

void se_subsitude_var(_POSTFIX__ *P_equation, const char var, const double value);

double se_eval_P_expression(const _POSTFIX__ P_expression, const char var, const double value);

double se_find_root_regula_falsi(const _POSTFIX__ P_equation, const char var, const double init_a, const double init_b, const double init_fa, const double init_fb);

double se_find_root_newton(const __INFIX__ I_equation, const char var, const double x0);

void se_verify_roots(const _POSTFIX__ P_equation, const char var, double **roots, unsigned short int *num_of_root);

short int se_solve_equation(const __INFIX__ equation, const char var, double lower_bound, double upper_bound, double **roots);

void se_display_root_array(const double *, const char var, const unsigned short int);

__INFIX__ *se_alloc_F_x_for_systemof_nonlinear_equation(const unsigned short int num_of_sol);

void se_free_F_x_for_systemof_nonlinear_equation(__INFIX__ **F_x, const unsigned short int num_of_sol);

double se_eval_P_function(const _POSTFIX__ P_F_x_originnal, const char *var_set, const unsigned short int num_of_sol, const double *valueof_var_set);

static void se_cleanup_nonlinear_resources(
    double **F_x_k,
    _POSTFIX__ **P_F_x,
    __INFIX__ ***J_x,
    _POSTFIX__ ***P_J_x,
    double ***J_x_k,
    const unsigned short int num_of_sol);

short int se_solve_system_of_nonlinear_equation(
    const __INFIX__ *F_x,
    const char *var_set,
    const unsigned short int num_of_sol,
    double **solutions,
    double l_bound,
    double u_bound);

char **se_alloc_string_array(const unsigned short int num_of_string);
void se_free_string_array(char ***ptr_string_array, const unsigned short int n);

// ====================================================================================================================== //
// ===============================================FUNCTION DEFINITIONS=================================================== //
// ====================================================================================================================== //

void se_display_root_array(const double *roots, const char var, const unsigned short int num_of_root)
{
    if (roots == NULL)
    {
        return;
    }

    for (unsigned short int i = 0; i < num_of_root; i++)
    {
        printf("%c = ", var);
        display_number(roots[i]);
        putchar('\n');
    }
}

void se_free_complex_array(gsl_complex *array)
{
    if (array != NULL)
    {
        free(array);
    }
}

/**
 * Converts a GSL complex packed pointer to an array of gsl_complex structures
 *
 * @param packed_ptr Pointer to packed complex data (alternating real, imaginary values)
 * @param num_complex Number of complex numbers in the packed array
 * @return Pointer to newly allocated array of gsl_complex, or NULL on failure
 *
 * Note: Caller is responsible for freeing the returned memory
 */
gsl_complex *se_convert__complex_packed_ptr__to__gsl_complex(gsl_complex_packed_ptr packed_ptr,
                                                             const short int num_complex)
{
    // Input validation
    if (packed_ptr == NULL || num_complex <= 0)
    {
        return NULL;
    }

    // Allocate memory for the gsl_complex array
    gsl_complex *complex_array = (gsl_complex *)calloc(num_complex, sizeof(gsl_complex));
    if (complex_array == NULL)
    {
        return NULL;
    }

    // Convert packed format to gsl_complex array
    // packed_ptr contains: [real0, imag0, real1, imag1, real2, imag2, ...]
    for (short int i = 0; i < num_complex; i++)
    {
        double real_part = packed_ptr[2 * i];
        double imag_part = packed_ptr[2 * i + 1];
        GSL_SET_COMPLEX(&(complex_array[i]), real_part, imag_part);
    }

    return complex_array;
}

bool se_is_real(const gsl_complex z)
{
    if (fabs(GSL_IMAG(z)) <= __DBL_EPSILON__)
        return true;
    return false;
}

// swap value of z2 --> z1
void se_swap_2_complex_number(gsl_complex *z1, gsl_complex *z2)
{
    gsl_complex swap;
    GSL_SET_COMPLEX(&swap, GSL_COMPLEX_P_REAL(z1), GSL_COMPLEX_P_IMAG(z1));
    GSL_SET_COMPLEX(z1, GSL_COMPLEX_P_REAL(z2), GSL_COMPLEX_P_IMAG(z2));
    GSL_SET_COMPLEX(z2, GSL_REAL(swap), GSL_IMAG(swap));
}

void se_display_complex_number(gsl_complex z)
{
    if (se_is_real(z))
        printf("z = %.17lf\n", GSL_REAL(z));

    else if (is_zero(GSL_REAL(z)))
        printf("%.17lfi\n", GSL_IMAG(z));

    else
    {
        if (GSL_IMAG(z) < 0.0)
            printf("z = %.17lf %.17lfi\n", GSL_REAL(z), GSL_IMAG(z));
        else
            printf("z = %.17lf + %.17lfi\n", GSL_REAL(z), GSL_IMAG(z));
    }
}

void se_display_complex_number_2(const gsl_complex z)
{
    if (se_is_real(z))
    {
        display_number(GSL_REAL(z));
    }

    else if (is_zero(GSL_REAL(z)))
    {
        display_number(GSL_IMAG(z));
        putchar('i');
    }

    else
    {
        if (GSL_IMAG(z) < 0.0)
        // printf("%.17lf - %.17lfi", GSL_REAL(z), -GSL_IMAG(z));
        {
            display_number(GSL_REAL(z));
            putchar(' ');
            putchar('-');
            putchar(' ');
            display_number(-GSL_IMAG(z));
            putchar('i');
        }
        else
        // printf("%.17lf + %.17lfi", GSL_REAL(z), GSL_IMAG(z));
        {
            display_number(GSL_REAL(z));
            putchar(' ');
            putchar('+');
            putchar(' ');
            display_number(GSL_IMAG(z));
            putchar('i');
        }
    }
}

void se_display_quadratic_solutions(const gsl_complex root1, const gsl_complex root2)
{
    // real solutions
    if (GSL_IMAG(root1) == 0.0)
    {
        if (fabs(GSL_REAL(root1) - GSL_REAL(root2)) <= __DBL_EPSILON__)
        {
            printf("\nx₁ = x₂ = ");
            display_number(GSL_REAL(root1));
        }

        else
        {
            printf("\nx₁ = ");
            display_number(GSL_REAL(root1));
            printf("\nx₂ = ");
            display_number(GSL_REAL(root2));
        }
    }

    // complex solutions
    else
    {
        printf("x₁ = ");
        se_display_complex_number_2(root1);
        putchar('\n');
        printf("x₂ = ");
        se_display_complex_number_2(root2);
        putchar('\n');
    }
}

void se_display_cubic_equation_solutions(const gsl_complex root1, const gsl_complex root2, const gsl_complex root3)
{
    // All real solutions
    if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0 && GSL_IMAG(root3) == 0.0)
    {
        // Check for triple root
        if (fabs(GSL_REAL(root1) - GSL_REAL(root2)) <= __DBL_EPSILON__ &&
            fabs(GSL_REAL(root2) - GSL_REAL(root3)) <= __DBL_EPSILON__)
        {
            printf("\nx₁ = x₂ = x₃ = ");
            display_number(GSL_REAL(root1));
        }
        // All distinct real roots
        else
        {
            printf("\nx₁ = ");
            display_number(GSL_REAL(root1));
            printf("\nx₂ = ");
            display_number(GSL_REAL(root2));
            printf("\nx₃ = ");
            display_number(GSL_REAL(root3));
        }
    }
    // One real and two complex conjugate roots
    else
    {
        // Find which root is real
        if (GSL_IMAG(root1) == 0.0)
        {
            printf("\nx₁ = ");
            display_number(GSL_REAL(root1));
            printf("\nx₂ = ");
            se_display_complex_number_2(root2);
            putchar('\n');
            printf("x₃ = ");
            se_display_complex_number_2(root3);
            putchar('\n');
        }
        else if (GSL_IMAG(root2) == 0.0)
        {
            printf("\nx₁ = ");
            se_display_complex_number_2(root1);
            putchar('\n');
            printf("x₂ = ");
            display_number(GSL_REAL(root2));
            printf("\nx₃ = ");
            se_display_complex_number_2(root3);
            putchar('\n');
        }
        else
        {
            printf("\nx₁ = ");
            se_display_complex_number_2(root1);
            putchar('\n');
            printf("x₂ = ");
            se_display_complex_number_2(root2);
            putchar('\n');
            printf("x₃ = ");
            display_number(GSL_REAL(root3));
        }
    }
}

void se_display_quartic_equation_solutions(const gsl_complex root1, const gsl_complex root2,
                                           const gsl_complex root3, const gsl_complex root4)
{
    // All real solutions
    if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0 &&
        GSL_IMAG(root3) == 0.0 && GSL_IMAG(root4) == 0.0)
    {
        // Check for quadruple root
        if (fabs(GSL_REAL(root1) - GSL_REAL(root2)) <= __DBL_EPSILON__ &&
            fabs(GSL_REAL(root2) - GSL_REAL(root3)) <= __DBL_EPSILON__ &&
            fabs(GSL_REAL(root3) - GSL_REAL(root4)) <= __DBL_EPSILON__)
        {
            printf("\nx₁ = x₂ = x₃ = x₄ = ");
            display_number(GSL_REAL(root1));
        }
        // All distinct real roots
        else
        {
            printf("\nx₁ = ");
            display_number(GSL_REAL(root1));
            printf("\nx₂ = ");
            display_number(GSL_REAL(root2));
            printf("\nx₃ = ");
            display_number(GSL_REAL(root3));
            printf("\nx₄ = ");
            display_number(GSL_REAL(root4));
        }
    }
    // Two real and two complex conjugate solutions
    else if ((GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0) ||
             (GSL_IMAG(root3) == 0.0 && GSL_IMAG(root4) == 0.0))
    {
        if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0)
        {
            printf("\nx₁ = ");
            display_number(GSL_REAL(root1));
            printf("\nx₂ = ");
            display_number(GSL_REAL(root2));
            printf("\nx₃ = ");
            se_display_complex_number_2(root3);
            putchar('\n');
            printf("x₄ = ");
            se_display_complex_number_2(root4);
            putchar('\n');
        }
        else
        {
            printf("\nx₁ = ");
            se_display_complex_number_2(root1);
            putchar('\n');
            printf("x₂ = ");
            se_display_complex_number_2(root2);
            putchar('\n');
            printf("x₃ = ");
            display_number(GSL_REAL(root3));
            printf("\nx₄ = ");
            display_number(GSL_REAL(root4));
        }
    }
    // All complex solutions (two pairs of complex conjugates)
    else
    {
        printf("\nx₁ = ");
        se_display_complex_number_2(root1);
        putchar('\n');
        printf("x₂ = ");
        se_display_complex_number_2(root2);
        putchar('\n');
        printf("x₃ = ");
        se_display_complex_number_2(root3);
        putchar('\n');
        printf("x₄ = ");
        se_display_complex_number_2(root4);
        putchar('\n');
    }
}

/* This module solve for quadratic equation on complex domain
Returns:
-1:  Invalid inputs
0:   Complex roots
1:   2 indentical real roots
2:   2 distinct real roots
 */
short int se_sovle_quadratic_equation(const double a, const double b, const double c, gsl_complex *root1, gsl_complex *root2)
{
    if (fabs(a) <= __DBL_EPSILON__)
        return -1;
    // init root1 & root2
    GSL_SET_COMPLEX(root1, NAN, NAN);
    GSL_SET_COMPLEX(root2, NAN, NAN);

    // calculate delta
    double delta = b * b - 4 * a * c;

    if (!isfinite(delta))
        return -1;

    // case 1: delta < 0
    if (delta < 0)
    {
        GSL_SET_COMPLEX(root1, (-b) / (2 * a), (-sqrt(-delta)) / (2 * a));
        GSL_SET_COMPLEX(root2, (-b) / (2 * a), (sqrt(-delta)) / (2 * a));
        return 0;
    }

    // case 2: delta = 0
    if (delta == 0.0 || fabs(delta) <= __DBL_EPSILON__)
    {
        double root = -(b / (2 * a));
        GSL_SET_COMPLEX(root1, root, 0.0);
        GSL_SET_COMPLEX(root2, root, 0.0);
        return 1;
    }

    // case 3: delta > 0
    GSL_SET_COMPLEX(root1, (-b - sqrt(delta)) / (2 * a), 0.0);
    GSL_SET_COMPLEX(root2, (-b + sqrt(delta)) / (2 * a), 0.0);
    return 2;
}

/* This module solve for cubic equation on complex domain
Returns:
-1:     Invalid inputs
1:      One real root and 2 complex roots
3:      All roots are real and distinct
 */
short int se_solve_cubic_equation(const double a, const double b, const double c, const double d,
                                  gsl_complex *root1, gsl_complex *root2, gsl_complex *root3)
{
    if (fabs(a) <= __DBL_EPSILON__)
        return 0;

    // Initialize roots
    GSL_SET_COMPLEX(root1, NAN, NAN);
    GSL_SET_COMPLEX(root2, NAN, NAN);
    GSL_SET_COMPLEX(root3, NAN, NAN);

    // Convert to standard form x^3 + px^2 + qx + r = 0
    double p = b / a;
    double q = c / a;
    double r = d / a;

    // Get real roots using gsl function
    double x0, x1, x2;
    int num_real_roots = gsl_poly_solve_cubic(p, q, r, &x0, &x1, &x2);

    // Case 1: Three real roots
    if (num_real_roots == 3)
    {
        GSL_SET_COMPLEX(root1, x0, 0.0);
        GSL_SET_COMPLEX(root2, x1, 0.0);
        GSL_SET_COMPLEX(root3, x2, 0.0);

        return 3;
    }
    // Case 2: One real root and two complex conjugate roots
    else if (num_real_roots == 1)
    {
        gsl_poly_complex_solve_cubic(p, q, r, root1, root2, root3);
        return 1;
    }

    return 0;
}

/* This module find all roots of a quartic equation on complex domain
Returns:
-1:     Invalid inputs
0:      All roots are complex
2:      2 distinct real roots and 2 complex roots
3:      3 distinct real roots
4:      4 distinct real roots

Reference:
How to solve quartic equation and the general formula: https://www.curtisbright.com/quartic/quartic-derivation.html
 */
short int se_solve_quartic_equation(const double a, const double b, const double c, const double d, const double e,
                                    gsl_complex *x1, gsl_complex *x2, gsl_complex *x3, gsl_complex *x4)
{
    if (fabs(a) <= __DBL_EPSILON__)
        return 0;

    // handle biquadratic equation
    if (fabs(b) <= __DBL_EPSILON__ && fabs(d) <= __DBL_EPSILON__)
    {
        double biquadratic_a = a;
        double biquadratic_b = c;
        double biquadratic_c = e;

        gsl_complex t1, t2;
        se_sovle_quadratic_equation(biquadratic_a, biquadratic_b, biquadratic_c, &t1, &t2);

        (*x1) = gsl_complex_sqrt(t1);
        (*x2) = gsl_complex_mul_real(*x1, -1.0);
        (*x3) = gsl_complex_sqrt(t2);
        (*x4) = gsl_complex_mul_real(*x3, -1.0);

        return 2;
    }

    // coefficients of cubic equation
    double cubic_b = -(3 * b * b - 8 * a * c);
    double cubic_c = 3 * b * b * b * b + 16 * a * a * c * c + 16 * a * a * b * d - 16 * a * b * b * c - 64 * a * a * a * e;
    double cubic_d = -((-b * b * b + 4 * a * b * c - 8 * a * a * d) * (-b * b * b + 4 * a * b * c - 8 * a * a * d));

    // roots of the cubic equation
    gsl_complex yy1, yy2, yy3;

    // solve for side cubic equation
    short int numofsol = se_solve_cubic_equation(1.0, cubic_b, cubic_c, cubic_d, &yy1, &yy2, &yy3);

    double check = -b * b * b + 4 * a * b * c - 8 * a * a * d;
    double s = 1; // sign
    double cubic_delta = cubic_b * cubic_b * cubic_c * cubic_c - 4 * cubic_c * cubic_c * cubic_c - 4 * cubic_b * cubic_b * cubic_b * cubic_d - 27 * cubic_d * cubic_d + 18 * cubic_b * cubic_c * cubic_d;

    // take the sqrt of yyi
    gsl_complex y1, y2, y3;
    y1 = gsl_complex_sqrt(yy1);
    y2 = gsl_complex_sqrt(yy2);
    y3 = gsl_complex_sqrt(yy3);

    // choose correct sign for the term: s*y3
    s = GSL_SIGN((GSL_SIGN(check) - 0.5) * (GSL_SIGN(gsl_max(-27 * cubic_delta, gsl_min(-cubic_b, cubic_c))) - 0.5));

    // compute the roots
    double fourimtes_a = 4 * a;
    (*x1) = gsl_complex_div_real(gsl_complex_add(gsl_complex_add_real(y1, -b), gsl_complex_add(y2, gsl_complex_mul_real(y3, s))), fourimtes_a);
    (*x2) = gsl_complex_div_real(gsl_complex_sub(gsl_complex_add_real(y1, -b), gsl_complex_add(y2, gsl_complex_mul_real(y3, s))), fourimtes_a);
    (*x3) = gsl_complex_div_real(gsl_complex_add(gsl_complex_add_real(gsl_complex_negative(y1), -b), gsl_complex_sub(y2, gsl_complex_mul_real(y3, s))), fourimtes_a);
    (*x4) = gsl_complex_div_real(gsl_complex_add(gsl_complex_add_real(gsl_complex_negative(y1), -b), gsl_complex_sub(gsl_complex_mul_real(y3, s), y2)), fourimtes_a);

    // count for real solutions
    short int numofrealsol = 0;
    if (se_is_real(*x1))
        numofrealsol++;
    if (se_is_real(*x2))
        numofrealsol++;
    if (se_is_real(*x3))
        numofrealsol++;
    if (se_is_real(*x4))
        numofrealsol++;

    return numofrealsol;
}

/* This module solves for complex roots of any polynomial equations with degree higher than 4: quintic equation, 6th-degree equation . . .
Returns:
-1:     Encounter error while processing
>= 0:   Number of distinct real roots

Method: Converts the polynomial into a companion matrix,
        balances it for numerical stability and
        applies the QR algorithm to find the eigenvalues which correspond to the polynomial roots.
 */
short int se_solve_polynomial_equation(const double *coefficients, const unsigned short int degree, gsl_complex **results)
{

    if (coefficients == NULL || degree <= 4 || is_zero(coefficients[0]))
        return -1;

    // init
    gsl_complex *roots = NULL;

    // flip the coefficient array
    double *reversed_coefficients = (double *)calloc(degree + 1, sizeof(double));
    if (reversed_coefficients == NULL)
        return -1;

    for (short int i = degree, k = 0; i >= 0 && k <= degree; i--, k++)
    {
        reversed_coefficients[k] = coefficients[i];
    }

    // prepare for solving
    gsl_complex_packed_ptr se_roots = malloc(2 * degree * sizeof(double));
    if (se_roots == NULL)
    {
        free(reversed_coefficients);
        return -1;
    }

    gsl_poly_complex_workspace *poly_workspace = gsl_poly_complex_workspace_alloc(degree + 1);
    if (poly_workspace == NULL)
    {
        free(reversed_coefficients);
        free(se_roots);
        return -1;
    }

    // solve the equation
    int status = gsl_poly_complex_solve(reversed_coefficients, degree + 1, poly_workspace, se_roots);

    free(reversed_coefficients);
    gsl_poly_complex_workspace_free(poly_workspace);

    if (status != 0)
    {
        free(se_roots);
        return -1;
    }

    roots = se_convert__complex_packed_ptr__to__gsl_complex(se_roots, 2 * degree);

    // count real root
    short int numof_real_root = 0;
    for (short int i = 0; i < degree; i++)
    {
        if (se_is_real((roots)[i]))
            numof_real_root++;
    }

    (*results) = roots;

    return numof_real_root;
}

double **se_malloc_coefficients_of_system_equation(const unsigned short int num_of_variable)
{
    if (num_of_variable <= 1)
        return NULL;

    double **coefficients = (double **)malloc(num_of_variable * sizeof(double *));
    if (coefficients == NULL)
    {
        return NULL;
    }

    for (short int i = 0; i < num_of_variable; i++)
    {
        coefficients[i] = (double *)calloc(num_of_variable + 1, sizeof(double));
        if (coefficients[i] == NULL)
        {
            free(coefficients);
            return NULL;
        }
    }

    return coefficients;
}

void se_free_coefficients_of_system_equation(double ***coefficients, const unsigned short int num_of_variable)
{
    if (coefficients == NULL || (*coefficients) == NULL)
        return;
    for (short int i = 0; i < num_of_variable; i++)
    {
        free((*coefficients)[i]);
        (*coefficients)[i] = NULL;
    }
    free(*coefficients);
    *coefficients = NULL;
}

/*
This module is used to solve any linear system equations
#Equation form:
a[1]x_1 + a[2]x_2 + a[3]x_3 + . . . + a[n]x_n = a[n + 1]
b[1]x_1 + b[2]x_2 + b[3]x_3 + . . . + b[n]x_n = b[n + 1]
.
.
.

#Example usage:

double ** coefficients = se_malloc_coefficients_of_system_equation(2);

//get coefficients
for(int row = 0; row < 2; row++){
    for(int col = 0; col < 3; col++) scanf("%lf", &coefficients[row][col]);
}
//

double *solutions = solve_system_equation(2, coefficients);

// display results here

free(solutions);
se_free_coefficients_of_system_equation(&coefficients, 2);
*/
double *se_solve_system_equation(int num_of_sol, double **coefficients)
{
    if (coefficients == NULL || num_of_sol < 2)
        return NULL;

    double *solutions = (double *)malloc(num_of_sol * sizeof(double));

    // if the first ever coefficient = 0, then swap the first row with the second row
    if (coefficients[0][0] == 0)
    {
        double swap;
        for (int col = 0; col <= num_of_sol; col++)
        {
            swap = coefficients[0][col];
            coefficients[0][col] = coefficients[1][col];
            coefficients[1][col] = swap;
        }
    }

    // implement Gauss Elimination method
    double g = 1;
    for (int loops = 0; loops < num_of_sol - 1; loops++)
    {
        for (int row = loops + 1; row < num_of_sol; row++)
        {
            g = coefficients[row][loops] / coefficients[loops][loops];
            for (int col = 0; col <= num_of_sol; col++)
            {
                coefficients[row][col] = coefficients[row][col] - (g * coefficients[loops][col]);
            }
        }
    }

    // sovle for solutions
    int so_thu_tu_nghiem = 0, s;
    double leftover = 0, right = 0;
    for (int row = num_of_sol - 1; row >= 0; row--)
    {
        s = 0;
        right = coefficients[row][num_of_sol];
        leftover = 0;
        for (int col = num_of_sol - 1; col > row; col--)
        {
            leftover += coefficients[row][col] * solutions[s++];
        }

        // if any solutions isn't solved, then the equation has no solutions, return NAN
        if (coefficients[row][row] == 0)
        {
            for (int i = 0; i < num_of_sol; i++)
                solutions[i] = NAN;
            return solutions;
        }

        solutions[so_thu_tu_nghiem++] = (right - leftover) / coefficients[row][row];
    }

    // rearrange the solutions
    for (int i = 0; 2 * i < num_of_sol; i++)
    {
        double swap;
        swap = solutions[i];
        solutions[i] = solutions[num_of_sol - i - 1];
        solutions[num_of_sol - i - 1] = swap;
    }

    return solutions;
}

void se_subsitude_var(_POSTFIX__ *P_equation, const char var, const double value)
{
    for (short int i = 0; i < P_equation->size; i++)
    {
        if (P_equation->tokens[i].variable == var)
        {
            P_equation->tokens[i].num = value;
            P_equation->tokens[i].variable = '\0';
        }
    }
}

double se_eval_P_expression(const _POSTFIX__ P_expression, const char var, const double value)
{
    // Make a copy of P_expression
    _POSTFIX__ cloned_exp = copy_postfix_expression(P_expression);
    se_subsitude_var(&cloned_exp, var, value);

    while (cloned_exp.size > 1)
    {
        int i;
        char OP = '\0';
        for (i = 0; i < cloned_exp.size; i++)
        {
            if (cloned_exp.tokens[i].operator== '\0')
                continue;

            OP = cloned_exp.tokens[i].operator;

            switch (OP)
            {
            case '+': // addition
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num + cloned_exp.tokens[i - 1].num;
                break;
            case '-': // substraction
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num - cloned_exp.tokens[i - 1].num;
                break;
            case '*': // multiplication
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num * cloned_exp.tokens[i - 1].num;
                break;
            case '/': // division
            {
                if (cloned_exp.tokens[i - 1].num == 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num / cloned_exp.tokens[i - 1].num;
                break;
            }
            case '%': // remainder modulo
            {
                if (!is_integer(cloned_exp.tokens[i - 2].num) || !is_integer(cloned_exp.tokens[i - 1].num))
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 2].num = (double)(((int)cloned_exp.tokens[i - 2].num) % ((int)cloned_exp.tokens[i - 1].num));
                break;
            }
            case '^': // exponential
                cloned_exp.tokens[i - 2].num = pow(cloned_exp.tokens[i - 2].num, cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SIN: // sin
                cloned_exp.tokens[i - 1].num = sin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SINH: // sinh
                cloned_exp.tokens[i - 1].num = sinh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SEC: // sec
                cloned_exp.tokens[i - 1].num = 1 / cos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SECH: // sech
                cloned_exp.tokens[i - 1].num = 1 / cosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSEC: // arcsec
                cloned_exp.tokens[i - 1].num = arcsec(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSECH: // arcsech
                cloned_exp.tokens[i - 1].num = arcsech(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COS: // cos
                cloned_exp.tokens[i - 1].num = cos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COSH: // cosh
                cloned_exp.tokens[i - 1].num = cosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSC: // csc
                cloned_exp.tokens[i - 1].num = 1 / sin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSCH: // csch
                cloned_exp.tokens[i - 1].num = csch(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSC: // arccsc
                cloned_exp.tokens[i - 1].num = arccsc(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSCH: // arccsch
                cloned_exp.tokens[i - 1].num = arccsch(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TAN: // tan
                cloned_exp.tokens[i - 1].num = tan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TANH: // tanh
                cloned_exp.tokens[i - 1].num = tanh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COT: // cot
                cloned_exp.tokens[i - 1].num = 1 / tan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COTH: // coth
                cloned_exp.tokens[i - 1].num = coth(cloned_exp.tokens[i - 1].num);
                break;
            case '!': // factorial
            {
                // Check if it's an integer or not
                if (!is_integer(cloned_exp.tokens[i - 1].num) || cloned_exp.tokens[i - 1].num < 0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                double fac = 1.0;
                double n = cloned_exp.tokens[i - 1].num;
                for (double f = 1.0; f <= n; f++)
                    fac *= f;
                if (fac > __DBL_MAX__)
                    cloned_exp.tokens[i - 1].num = NAN;
                else
                    cloned_exp.tokens[i - 1].num = (double)fac;
                break;
            }
            case SPECIFIER_OF_ARCSIN: // arcsin
                cloned_exp.tokens[i - 1].num = asin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSINH: // arcsinh
                cloned_exp.tokens[i - 1].num = asinh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOS: // arccos
                cloned_exp.tokens[i - 1].num = acos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOSH: // arccosh
                cloned_exp.tokens[i - 1].num = acosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTAN: // arctan
                cloned_exp.tokens[i - 1].num = atan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTANH: // arctanh
                cloned_exp.tokens[i - 1].num = atanh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOT: // arccot
            {
                if (cloned_exp.tokens[i - 1].num > 0.0)
                    cloned_exp.tokens[i - 1].num = atan(1.0 / (cloned_exp.tokens[i - 1].num));
                else
                    cloned_exp.tokens[i - 1].num = atan(1.0 / (cloned_exp.tokens[i - 1].num)) + PI;
                break;
            }
            case SPECIFIER_OF_ARCCOTH: // arccoth
                cloned_exp.tokens[i - 1].num = arccoth(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LN: // ln
            {
                if (cloned_exp.tokens[i - 1].num <= 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = log(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_LG: // log10
            {
                if (cloned_exp.tokens[i - 1].num <= 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = log10(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_SQRT: // sqrt
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = sqrt(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_ABS: // abs
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                    cloned_exp.tokens[i - 1].num = -cloned_exp.tokens[i - 1].num;
                break;
            }
            case SPECIFIER_OF_CBRT: // cuberoot
                cloned_exp.tokens[i - 1].num = cbrt(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_GAMMA: // gamma function
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = gamma_function(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_CEIL: // ceiling function
                cloned_exp.tokens[i - 1].num = ceil(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_FLOOR: // floor function
                cloned_exp.tokens[i - 1].num = floor(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LAMBERTW: // lambert W function
            {
                if (cloned_exp.tokens[i - 1].num < -1.0 / EULER_NUMBER)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = lambertw_real(cloned_exp.tokens[i - 1].num);
                break;
            }
            default:
            {
                free(cloned_exp.tokens);
                return NAN;
            }
            }

            break;
        }

        if ((OP == '-' || OP == '+' || OP == '*' || OP == '/' || OP == '^' || OP == '^' || OP == '%') && !isfinite(cloned_exp.tokens[i - 2].num))
        {
            // puts("-NAN-\n");
            free(cloned_exp.tokens);
            return NAN;
        }
        else if (!isfinite(cloned_exp.tokens[i - 1].num))
        {
            // puts("-NAN-\n");
            free(cloned_exp.tokens);
            return NAN;
        }

        // After completing 1 calculation
        {
            // Re-allocate memories for stack
            if (cloned_exp.tokens[i].operator== '-' || cloned_exp.tokens[i].operator== '+' || cloned_exp.tokens[i].operator== '*' || cloned_exp.tokens[i].operator== '/' || cloned_exp.tokens[i].operator== '^' || cloned_exp.tokens[i].operator== '%')
            {
                // rearrange the stack
                for (int k = i - 1; k < cloned_exp.size - 2; k++)
                {
                    cloned_exp.tokens[k].num = cloned_exp.tokens[k + 2].num;
                    cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 2].operator;
                    cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 2].variable;
                }

                // re-allocate the stack's memories
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_exp.tokens, (cloned_exp.size - 2) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens = temp_ptr;
                cloned_exp.size -= 2;
            }
            else if (cloned_exp.tokens[i].operator!= '\0')
            {
                // rearrange the stack
                for (int k = i; k < cloned_exp.size - 1; k++)
                {
                    cloned_exp.tokens[k].num = cloned_exp.tokens[k + 1].num;
                    cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 1].operator;
                    cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 1].variable;
                }

                // re-allocate the stack's memories
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_exp.tokens, (cloned_exp.size - 1) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens = temp_ptr;
                cloned_exp.size--;
            }
        }
    }

    double result = cloned_exp.tokens[0].num;
    free(cloned_exp.tokens);

    return result;
}

double se_find_root_regula_falsi(const _POSTFIX__ P_equation, const char var, const double init_a, const double init_b, const double init_fa, const double init_fb)
{
    double a = init_a;
    double b = init_b;
    double fa = init_fa;
    double fb = init_fb;
    double c;

    unsigned short int i;
    if (init_fa < init_fb)
    {
        for (i = 1; i <= SE_MAX_ITERATION; i++)
        {
            c = a - (fa * (b - a)) / (fb - fa);
            b = c;
            fb = se_eval_P_expression(P_equation, var, b);

            if (fabs(fb) <= SE_EPSILON)
                break;
        }
    }
    else
    {
        for (i = 1; i <= SE_MAX_ITERATION; i++)
        {
            c = a - (fa * (b - a)) / (fb - fa);
            a = c;
            fa = se_eval_P_expression(P_equation, var, a);

            if (fabs(fa) <= SE_EPSILON)
                break;
        }
    }

    // printf("RF-Loops : %d | RF-Root: %.9lf\n", i, c);

    if (i >= SE_MAX_ITERATION)
        return NAN;

    return c;
}

double se_find_root_newton(const __INFIX__ I_equation, const char var, const double x0)
{
    __INFIX__ derivative = differentiate_I_exp(I_equation, var);
    reformat_I_exp(&derivative);
    optimize_I_exp(&derivative);
    _POSTFIX__ P_f = submodule_Parse(I_equation);
    _POSTFIX__ P_df = submodule_Parse(derivative);
    free(derivative.tokens);

    double x1 = x0;
    unsigned short int i;
    for (i = 1; i <= SE_MAX_ITERATION; i++)
    {
        double f = se_eval_P_expression(P_f, var, x1);
        double df = se_eval_P_expression(P_df, var, x1);

        if (fabs(f) <= SE_EPSILON)
        {
            break;
        }
        else if (!isfinite(f) || !isfinite(df) || fabs(df) <= SE_EPSILON)
        {
            continue;
        }

        x1 = x1 - f / df;
    }

    free(P_f.tokens);
    free(P_df.tokens);

    // printf("Newton-Loops: %d | Newton-Root: %.9lf\n", i, x1);

    if (i >= SE_MAX_ITERATION)
        return NAN;

    return x1;
}

void se_verify_roots(const _POSTFIX__ P_equation, const char var, double **roots, unsigned short int *num_of_root)
{
    // verify roots
    for (unsigned short int i = 0; i < *num_of_root; i++)
    {
        double fi = se_eval_P_expression(P_equation, var, (*roots)[i]);

        // remove incorrect root
        if (!isfinite((*roots)[i]) || !isfinite(fi) || fabs(fi) > SE_EPSILON)
        {
            for (unsigned short int k = i; k < *num_of_root - 1; k++)
            {
                (*roots)[k] = (*roots)[k + 1];
            }

            double *temp = (double *)realloc(*roots, (*num_of_root - 1) * sizeof(double));
            if (temp == NULL)
            {
                return;
            }
            (*roots) = temp;
            (*num_of_root)--;
            i = -1;
        }
    }

    // remove repeated roots
    unsigned short int new_numof_root = 0;
    double *new_roots_array = (double *)calloc(*num_of_root, sizeof(double));
    if (new_roots_array == NULL)
        return;
    for (unsigned short int i = 0; i < *num_of_root; i++)
    {
        double current_root = (*roots)[i];

        bool is_repeated = false;
        for (unsigned short int k = 0; k < new_numof_root; k++)
        {
            if (fabs(current_root - new_roots_array[k]) <= SE_EPSILON)
            {
                is_repeated = true;
                break;
            }
        }

        if (!is_repeated)
        {
            new_roots_array[new_numof_root++] = current_root;
        }
    }

    // sort root array in ascending order
    sort_double_array(new_roots_array, new_numof_root);

    free(*roots);
    (*roots) = new_roots_array;
    *num_of_root = new_numof_root;
}

short int se_solve_equation(const __INFIX__ equation, const char var, double lower_bound, double upper_bound, double **roots)
{
    if (equation.tokens == NULL || upper_bound <= lower_bound || equation.size < 1)
        return -1;

    // make a copy
    __INFIX__ copyof_equation = copy_infix_expression(equation);
    if (copyof_equation.size == 0 || copyof_equation.tokens == NULL)
        return -1;

    // enhance expressions for faster computation
    reformat_I_exp(&copyof_equation);
    optimize_I_exp(&copyof_equation);

    _POSTFIX__ P_equation = submodule_Parse(copyof_equation);

    // alloc storage for roots
    unsigned short int num_of_root = 0;
    unsigned short int max_numof_root = 50;
    double *se_roots = (double *)calloc(max_numof_root, sizeof(double));
    if (se_roots == NULL)
    {
        free(copyof_equation.tokens);
        free(P_equation.tokens);
        return -1;
    }

    // ==================================================================================================================== //
    // Find roots

    // apply newton method to find min and max root in the given interval
    double min_root = se_find_root_newton(copyof_equation, var, lower_bound);
    double max_root = se_find_root_newton(copyof_equation, var, upper_bound);
    if (min_root <= lower_bound)
        min_root = NAN;
    if (max_root >= upper_bound)
        max_root = NAN;

    // printf("min root = %.9lf | max root = %.9lf\n", min_root, max_root);

    if (isfinite(min_root) && isfinite(max_root))
    {
        // min = max
        if (fabs(min_root - max_root) <= SE_EPSILON)
        {
            se_roots[num_of_root++] = min_root;
        }

        // min # max
        else
        {
            se_roots[num_of_root++] = min_root;
            se_roots[num_of_root++] = max_root;

            lower_bound = min_root;
            upper_bound = max_root;
        }
    }
    else if (isfinite(min_root))
    {
        se_roots[num_of_root++] = min_root;
        lower_bound = min_root;
    }

    else if (isfinite(max_root))
    {
        se_roots[num_of_root++] = max_root;
        upper_bound = max_root;
    }

    // printf("l-bound = %.9lf | u_bound = %.9lf\n", lower_bound, upper_bound);

    // apply regula falsi method
    unsigned short int sub_interval = 500; // Number of subinterval. Increase this will improve the chance of detecting new roots, but take more time to interate
    double init_step = (upper_bound - lower_bound) / ((double)sub_interval);
    double modified_step;
    for (double t = lower_bound; t < upper_bound; t += modified_step)
    {
        // compute fa & fb
        double fa = se_eval_P_expression(P_equation, var, t);
        double fc = se_eval_P_expression(P_equation, var, t + init_step);

        // calculate next step
        modified_step = fabs(init_step / ((fc - fa) / init_step));
        if (modified_step <= 1e-5)
            modified_step = 1e-5;
        else if (modified_step >= init_step || !isfinite(modified_step))
            modified_step = init_step;

        double fb = se_eval_P_expression(P_equation, var, t + modified_step);

        // check if found a root in [t, t + (modified_step / 2)]
        if (fa * fb > 0.0 || !isfinite(fa) || !isfinite(fb))
            continue;

        // printf("t = %.3lf | t2 = %.3lf | fa = %.5lf | fb = %.5lf\n", t, t + init_step, fa, fb);

        // refine root if found
        // case 1: fa <= 0
        if (fa <= __DBL_EPSILON__)
        {
            if (fabs(fa) <= SE_EPSILON)
                se_roots[num_of_root++] = t;
            else
            {
                se_roots[num_of_root++] = se_find_root_regula_falsi(P_equation, var, t, t + modified_step, fa, fb);
            }
        }

        // case 2: fb <= 0
        else if (fb <= __DBL_EPSILON__)
        {
            if (fabs(fb) <= SE_EPSILON)
                se_roots[num_of_root++] = t + modified_step;
            else
            {
                se_roots[num_of_root++] = se_find_root_regula_falsi(P_equation, var, t, t + modified_step, fa, fb);
            }
        }
    }

    // ==================================================================================================================== //

    se_verify_roots(P_equation, var, &se_roots, &num_of_root);

    free(P_equation.tokens);
    free(copyof_equation.tokens);

    // puts("after solve");
    // se_display_root_array(se_roots, num_of_root);

    (*roots) = se_roots;

    return num_of_root;
}

// ====== //

__INFIX__ *se_alloc_F_x_for_systemof_nonlinear_equation(const unsigned short int num_of_sol)
{
    __INFIX__ *F_x = (__INFIX__ *)calloc(num_of_sol, sizeof(__INFIX__));
    if (F_x == NULL)
    {
        perror("se_alloc_F_x_for_systemof_nonlinear_equation: Failed to calloc F_x");
        return NULL;
    }
    return F_x;
}

void se_free_F_x_for_systemof_nonlinear_equation(__INFIX__ **F_x, const unsigned short int num_of_sol)
{
    if (*F_x == NULL)
        return;
    for (unsigned short int i = 0; i < num_of_sol; i++)
    {
        if ((*F_x)[i].tokens != NULL)
        {
            free((*F_x)[i].tokens);
            (*F_x)[i].tokens = NULL;
        }
    }
    free(*F_x);
    *F_x = NULL;
}

double se_eval_P_function(const _POSTFIX__ P_F_x_originnal, const char *var_set, const unsigned short int num_of_sol, const double *valueof_var_set)
{
    _POSTFIX__ P_F_x = copy_postfix_expression(P_F_x_originnal);

    for (unsigned short int i = 0; i < P_F_x.size; i++)
    {
        if (P_F_x.tokens[i].variable != '\0')
        {
            for (unsigned short int k = 0; k < num_of_sol; k++)
            {
                if (P_F_x.tokens[i].variable == var_set[k])
                {
                    P_F_x.tokens[i].variable = '\0';
                    P_F_x.tokens[i].num = valueof_var_set[k];

                    // check
                    // printf("substitue: %c = %.3lf\n", var_set[k], valueof_var_set[k]);
                }
            }
        }
    }

    double result = Compute_P_expression(P_F_x);

    free(P_F_x.tokens);

    return result;
}

// Helper function to safely clean up resources
static void se_cleanup_nonlinear_resources(
    double **F_x_k,
    _POSTFIX__ **P_F_x,
    __INFIX__ ***J_x,
    _POSTFIX__ ***P_J_x,
    double ***J_x_k,
    const unsigned short int num_of_sol)
{
    // Clean F_x_k
    if (F_x_k && *F_x_k)
    {
        free(*F_x_k);
        *F_x_k = NULL;
    }

    // Clean P_F_x
    if (P_F_x && *P_F_x)
    {
        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            if ((*P_F_x)[i].tokens != NULL)
            {
                free((*P_F_x)[i].tokens);
            }
        }
        free(*P_F_x);
        *P_F_x = NULL;
    }

    // Clean P_J_x
    if (P_J_x && *P_J_x)
    {
        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            if ((*P_J_x)[i] != NULL)
            {
                for (unsigned short int k = 0; k < num_of_sol; k++)
                {
                    if ((*P_J_x)[i][k].tokens != NULL)
                    {
                        free((*P_J_x)[i][k].tokens);
                    }
                }
                free((*P_J_x)[i]);
            }
        }
        free(*P_J_x);
        *P_J_x = NULL;
    }

    // Clean J_x
    if (J_x && *J_x)
    {
        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            if ((*J_x)[i] != NULL)
            {
                for (unsigned short int k = 0; k < num_of_sol; k++)
                {
                    if ((*J_x)[i][k].tokens != NULL)
                    {
                        free((*J_x)[i][k].tokens);
                    }
                }
                free((*J_x)[i]);
            }
        }
        free(*J_x);
        *J_x = NULL;
    }

    // Clean J_x_k
    if (J_x_k && *J_x_k)
    {
        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            if ((*J_x_k)[i] != NULL)
            {
                free((*J_x_k)[i]);
            }
        }
        free(*J_x_k);
        *J_x_k = NULL;
    }
}

// stable version
/* Module Description:  Attempts to find n real solutions (x₁, x₂, …, xₙ) of a square system of n nonlinear equations
 F₁(x₁,…,xₙ)=0, F₂(x₁,…,xₙ)=0, …, Fₙ(x₁,…,xₙ)=0
 using a multidimensional Newton–Raphson iteration with automatic Jacobian construction and a bounded‐retry strategy.

Signature:  short int se_solve_system_of_nonlinear_equation(
  const INFIX *F_x,  // Array of n infix expressions for F₁…Fₙ
  const char *var_set, // String of n variable names, e.g. "xyz"
  unsigned short num_of_sol,// Number of equations/variables n
  double **solutions,// OUT: pointer to newly allocated array of n solution values
  double l_bound, // Lower bound for random initial guesses
  double u_bound // Upper bound for random initial guesses
 );

Inputs: • F_x[]: each INFIX holds one equation’s expression (left side = 0).
• var_set: must list exactly n distinct single‐character variable names.
• num_of_sol: dimensionality of the system (n).
• l_bound, u_bound: range in which random starting points are drawn.

Outputs:
• On success returns 0 and *solutions points to an array of length n containing the solution vector.
• On failure, returns:
    -1          : Failed to allocate memories
    -2          : Failed to solve the equation. The solutions are not converged or not found
    -3, -4, -5  : Invalid F_x, var_set or solutions pointer
    -6          : The number of variable in var_set is not matched with num_of_sol
    -7          : Invalid value of num_of_sol

Reference:
    Numerical Methods for Solving Systems of Nonlinear Equations
    Link: https://www.lakeheadu.ca/sites/default/files/uploads/77/docs/RemaniFinal.pdf
 */
short int se_solve_system_of_nonlinear_equation(
    const __INFIX__ *F_x,
    const char *var_set,
    const unsigned short int num_of_sol,
    double **solutions,
    double l_bound,
    double u_bound)
{
    // input validation
    {
        if (F_x == NULL)
            return -3;

        if (var_set == NULL)
            return -4;
        if (solutions == NULL)
            return -5;
        if (strlen(var_set) != num_of_sol)
            return -6;
        if (num_of_sol <= 1 || num_of_sol > SE_MAX_VARIABLES)
            return -7;
        if (!isfinite(l_bound) || !isfinite(u_bound))
            return -8;
    }

    int return_code = -2;
    unsigned short int retry_count = 0;

    // Declare all resources
    double *se_solutions = NULL;
    double *F_x_k = NULL;
    _POSTFIX__ *P_F_x = NULL;
    __INFIX__ **J_x = NULL;
    _POSTFIX__ **P_J_x = NULL;
    double **J_x_k = NULL;

    // Seed randomness once
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    // Main retry loop
    while (retry_count < SE_MAX_RETRIES)
    {
        // Clean up from previous iteration
        se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);

        // Allocate solution array
        se_solutions = (double *)calloc(num_of_sol, sizeof(double));
        if (se_solutions == NULL)
        {
            return -1;
        }

        // Allocate F_x_k
        F_x_k = (double *)calloc(num_of_sol, sizeof(double));
        if (F_x_k == NULL)
        {
            free(se_solutions);
            return -1;
        }

        // Allocate and parse P_F_x
        P_F_x = (_POSTFIX__ *)calloc(num_of_sol, sizeof(_POSTFIX__));
        if (P_F_x == NULL)
        {
            free(se_solutions);
            free(F_x_k);
            return -1;
        }

        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            P_F_x[i] = submodule_Parse(F_x[i]);
            if (P_F_x[i].tokens == NULL)
            {
                // Clean up partial allocation
                for (unsigned short int j = 0; j < i; j++)
                {
                    if (P_F_x[j].tokens)
                        free(P_F_x[j].tokens);
                }
                free(P_F_x);
                free(F_x_k);
                free(se_solutions);
                return -1;
            }
        }

        // Allocate Jacobian matrices
        J_x = (__INFIX__ **)calloc(num_of_sol, sizeof(__INFIX__ *));
        if (J_x == NULL)
        {
            se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
            free(se_solutions);
            return -1;
        }

        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            J_x[i] = (__INFIX__ *)calloc(num_of_sol, sizeof(__INFIX__));
            if (J_x[i] == NULL)
            {
                se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
                free(se_solutions);
                return -1;
            }
        }

        P_J_x = (_POSTFIX__ **)calloc(num_of_sol, sizeof(_POSTFIX__ *));
        if (P_J_x == NULL)
        {
            se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
            free(se_solutions);
            return -1;
        }

        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            P_J_x[i] = (_POSTFIX__ *)calloc(num_of_sol, sizeof(_POSTFIX__));
            if (P_J_x[i] == NULL)
            {
                se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
                free(se_solutions);
                return -1;
            }
        }

        J_x_k = (double **)calloc(num_of_sol, sizeof(double *));
        if (J_x_k == NULL)
        {
            se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
            free(se_solutions);
            return -1;
        }

        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            J_x_k[i] = (double *)calloc(num_of_sol, sizeof(double));
            if (J_x_k[i] == NULL)
            {
                se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
                free(se_solutions);
                return -1;
            }
        }

        // Compute Jacobian matrix
        for (unsigned short int row = 0; row < num_of_sol; row++)
        {
            for (unsigned short int col = 0; col < num_of_sol; col++)
            {
                J_x[row][col] = differentiate_I_exp(F_x[row], var_set[col]);
                reformat_I_exp(&(J_x[row][col]));
                optimize_I_exp(&(J_x[row][col]));
                P_J_x[row][col] = submodule_Parse(J_x[row][col]);
            }
        }

        // Initialize solutions with random values
        for (unsigned short int i = 0; i < num_of_sol; i++)
        {
            se_solutions[i] = random_in_range_double(l_bound, u_bound);
        }

        // Newton-Raphson iteration
        unsigned short int iteration = 0;
        double norm = INFINITY;

        while (iteration < SE_MAX_ITERATION && norm > SE_EPSILON)
        {
            // Compute F(x_k)
            for (unsigned short int i = 0; i < num_of_sol; i++)
            {
                F_x_k[i] = se_eval_P_function(P_F_x[i], var_set, num_of_sol, se_solutions);
                if (!isfinite(F_x_k[i]))
                {
                    break; // Try different initial guess
                }
            }

            // Compute J(x_k)
            for (unsigned short int row = 0; row < num_of_sol; row++)
            {
                for (unsigned short int col = 0; col < num_of_sol; col++)
                {
                    J_x_k[row][col] = se_eval_P_function(P_J_x[row][col], var_set, num_of_sol, se_solutions);
                    if (!isfinite(J_x_k[row][col]))
                    {
                        goto next_retry; // Try different initial guess
                    }
                }
            }

            // Solve J(x_k) * y = -F(x_k)
            double **coef = se_malloc_coefficients_of_system_equation(num_of_sol);
            if (coef == NULL)
            {
                se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);
                free(se_solutions);
                return -1;
            }

            for (unsigned short int row = 0; row < num_of_sol; row++)
            {
                for (unsigned short int col = 0; col < num_of_sol; col++)
                {
                    coef[row][col] = J_x_k[row][col];
                }
                coef[row][num_of_sol] = -F_x_k[row];
            }

            double *y = se_solve_system_equation(num_of_sol, coef);
            se_free_coefficients_of_system_equation(&coef, num_of_sol);

            if (y == NULL)
            {
                goto next_retry; // Singular matrix, try different initial guess
            }

            // Check for NaN solutions
            bool has_nan = false;
            for (unsigned short int i = 0; i < num_of_sol; i++)
            {
                if (!isfinite(y[i]))
                {
                    has_nan = true;
                    break;
                }
            }

            if (has_nan)
            {
                free(y);
                goto next_retry;
            }

            // Calculate norm
            norm = 0.0;
            for (unsigned short int i = 0; i < num_of_sol; i++)
            {
                norm += y[i] * y[i];
            }
            norm = sqrt(norm);

            // Update solution
            for (unsigned short int i = 0; i < num_of_sol; i++)
            {
                se_solutions[i] += y[i];
            }

            free(y);
            iteration++;

            if (!isfinite(norm))
            {
                goto next_retry;
            }
        }

        // Check convergence
        if (norm <= SE_EPSILON)
        {
            // Verify final solution
            double max_residual = 0.0;
            for (unsigned short int i = 0; i < num_of_sol; i++)
            {
                double residual = fabs(se_eval_P_function(P_F_x[i], var_set, num_of_sol, se_solutions));
                if (residual > max_residual)
                {
                    max_residual = residual;
                }
            }

            if (max_residual <= SE_EPSILON)
            {
                return_code = 0; // Success
                break;
            }
        }

    next_retry:
        retry_count++;
        // Expand search bounds for next retry
        l_bound -= 2.0;
        u_bound += 2.0;
    }

    // Cleanup
    se_cleanup_nonlinear_resources(&F_x_k, &P_F_x, &J_x, &P_J_x, &J_x_k, num_of_sol);

    if (return_code == 0)
    {
        *solutions = se_solutions;
    }
    else
    {
        if (se_solutions)
            free(se_solutions);
    }

    return return_code;
}

char **se_alloc_string_array(const unsigned short int num_of_string)
{
    if (num_of_string == 0)
    {
        return NULL;
    }

    // Allocate memory for an array of char pointers and initialize to NULL
    char **string_array = (char **)calloc(num_of_string, sizeof(char *));

    if (string_array == NULL)
    {
        return NULL;
    }

    return string_array;
}

void se_free_string_array(char ***ptr_string_array, const unsigned short int n)
{
    // Check if the pointer to the array pointer is NULL
    if (ptr_string_array == NULL || *ptr_string_array == NULL)
    {
        return;
    }

    // Free each individual string in the array
    for (unsigned short int i = 0; i < n; i++)
    {
        if ((*ptr_string_array)[i] != NULL)
        {
            free((*ptr_string_array)[i]);
            (*ptr_string_array)[i] = NULL;
        }
    }

    // Free the array of pointers
    free(*ptr_string_array);

    // Set the original pointer to NULL
    *ptr_string_array = NULL;
}

#endif