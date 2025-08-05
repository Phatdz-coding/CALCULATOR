#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/complex/math.c>
#include <gsl/poly/solve_cubic.c>
#include <gsl/poly/zsolve_cubic.c>
#include <gsl/sys/minmax.c>

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

// ====================================================================================================================== //
// ===============================================FUNCTION DEFINITIONS=================================================== //
// ====================================================================================================================== //
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
    printf("\nz = %.17lf + (%.17lf)i\n", GSL_REAL(z), GSL_IMAG(z));
}

void se_display_quadratic_solutions(const gsl_complex root1, const gsl_complex root2)
{
    // real solutions
    if (GSL_IMAG(root1) == 0.0)
    {
        if (fabs(GSL_REAL(root1) - GSL_REAL(root2)) <= __DBL_EPSILON__)
        {
            printf("\nRoot 1 = Root 2 = %.17lf\n", GSL_REAL(root1));
        }

        else
        {
            printf("\nRoot 1 = %.17lf | Root 2 = %.17lf\n", GSL_REAL(root1), GSL_REAL(root2));
        }
    }

    // complex solutions
    else
    {
        printf("\nRoot 1 = %.17lf + (%.17lf)i | Root 2 = %.17lf + (%.17lf)i\n", GSL_REAL(root1), GSL_IMAG(root1), GSL_REAL(root2), GSL_IMAG(root2));
    }
}

void se_display_cubic_equation_solutions(const gsl_complex root1, const gsl_complex root2, const gsl_complex root3)
{
    // 3 real sol
    if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0 && GSL_IMAG(root3) == 0.0)
    {
        printf("\nRoot 1 = %.17lf | Root 2 = %.17lf | Root 3 = %.17lf\n", GSL_REAL(root1), GSL_REAL(root2), GSL_REAL(root3));
    }
    // 1 real & 2 complex
    else
    {
        if (GSL_IMAG(root1) == 0.0)
            printf("\nRoot 1 = %.17lf | Root 2 = %.17lf + (%.17lf)i | Root 3 = %.17lf + (%.17lf)i\n", GSL_REAL(root1), GSL_REAL(root2), GSL_IMAG(root2), GSL_REAL(root3), GSL_IMAG(root3));

        else if (GSL_IMAG(root2) == 0.0)
            printf("\nRoot 2 = %.17lf | Root 1 = %.17lf + (%.17lf)i | Root 3 = %.17lf + (%.17lf)i\n", GSL_REAL(root2), GSL_REAL(root1), GSL_IMAG(root1), GSL_REAL(root3), GSL_IMAG(root3));

        else if (GSL_IMAG(root3) == 0.0)
            printf("\nRoot 3 = %.17lf | Root 2 = %.17lf + (%.17lf)i | Root 1 = %.17lf + (%.17lf)i\n", GSL_REAL(root3), GSL_REAL(root2), GSL_IMAG(root2), GSL_REAL(root1), GSL_IMAG(root1));
    }
}

void se_display_quartic_equation_solutions(const gsl_complex root1, const gsl_complex root2,
                                           const gsl_complex root3, const gsl_complex root4)
{
    // All real solutions
    if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0 &&
        GSL_IMAG(root3) == 0.0 && GSL_IMAG(root4) == 0.0)
    {
        printf("\nRoot 1 = %.17lf | Root 2 = %.17lf | Root 3 = %.17lf | Root 4 = %.17lf\n",
               GSL_REAL(root1), GSL_REAL(root2), GSL_REAL(root3), GSL_REAL(root4));
    }
    // Two real and two complex conjugate solutions
    else if ((GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0) ||
             (GSL_IMAG(root2) == 0.0 && GSL_IMAG(root3) == 0.0) ||
             (GSL_IMAG(root3) == 0.0 && GSL_IMAG(root4) == 0.0) ||
             (GSL_IMAG(root4) == 0.0 && GSL_IMAG(root1) == 0.0))
    {
        // Find the real roots and complex conjugate pair
        if (GSL_IMAG(root1) == 0.0 && GSL_IMAG(root2) == 0.0)
        {
            printf("\nRoot 1 = %.17lf | Root 2 = %.17lf\n", GSL_REAL(root1), GSL_REAL(root2));
            printf("Root 3 = %.17lf + (%.17lf)i | Root 4 = %.17lf + (%.17lf)i\n",
                   GSL_REAL(root3), GSL_IMAG(root3), GSL_REAL(root4), GSL_IMAG(root4));
        }
        else if (GSL_IMAG(root2) == 0.0 && GSL_IMAG(root3) == 0.0)
        {
            printf("\nRoot 2 = %.17lf | Root 3 = %.17lf\n", GSL_REAL(root2), GSL_REAL(root3));
            printf("Root 1 = %.17lf + (%.17lf)i | Root 4 = %.17lf + (%.17lf)i\n",
                   GSL_REAL(root1), GSL_IMAG(root1), GSL_REAL(root4), GSL_IMAG(root4));
        }
        else if (GSL_IMAG(root3) == 0.0 && GSL_IMAG(root4) == 0.0)
        {
            printf("\nRoot 3 = %.17lf | Root 4 = %.17lf\n", GSL_REAL(root3), GSL_REAL(root4));
            printf("Root 1 = %.17lf + (%.17lf)i | Root 2 = %.17lf + (%.17lf)i\n",
                   GSL_REAL(root1), GSL_IMAG(root1), GSL_REAL(root2), GSL_IMAG(root2));
        }
    }
    // Two pairs of complex conjugate solutions
    else
    {
        printf("\nRoot 1 = %.17lf + (%.17lf)i | Root 2 = %.17lf + (%.17lf)i\n",
               GSL_REAL(root1), GSL_IMAG(root1), GSL_REAL(root2), GSL_IMAG(root2));
        printf("Root 3 = %.17lf + (%.17lf)i | Root 4 = %.17lf + (%.17lf)i\n",
               GSL_REAL(root3), GSL_IMAG(root3), GSL_REAL(root4), GSL_IMAG(root4));
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
