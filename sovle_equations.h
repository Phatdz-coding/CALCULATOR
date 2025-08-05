#ifndef SOVLE_EQUATIONS_H
#define SOVLE_EQUATIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_poly.h>

// ====================================================================================================================== //
// ===============================================FUNCTION DECLARATIONS================================================== //
// ====================================================================================================================== //

/**
 * Check if a complex number is real (imaginary part is effectively zero)
 * @param z Complex number to check
 * @return true if the number is real, false otherwise
 */
bool se_is_real(const gsl_complex z);

/**
 * Swap the values of two complex numbers
 * @param z1 Pointer to first complex number
 * @param z2 Pointer to second complex number
 */
void se_swap_2_complex_number(gsl_complex *z1, gsl_complex *z2);

/**
 * Display a complex number in the format: z = real + (imaginary)i
 * @param z Complex number to display
 */
void se_display_complex_number(gsl_complex z);

/**
 * Display the solutions of a quadratic equation
 * @param root1 First root of the quadratic equation
 * @param root2 Second root of the quadratic equation
 */
void se_display_quadratic_solutions(const gsl_complex root1, const gsl_complex root2);

/**
 * Display the solutions of a cubic equation
 * @param root1 First root of the cubic equation
 * @param root2 Second root of the cubic equation
 * @param root3 Third root of the cubic equation
 */
void se_display_cubic_equation_solutions(const gsl_complex root1, const gsl_complex root2, const gsl_complex root3);

/**
 * Display the solutions of a quartic equation
 * @param root1 First root of the quartic equation
 * @param root2 Second root of the quartic equation
 * @param root3 Third root of the quartic equation
 * @param root4 Fourth root of the quartic equation
 */
void se_display_quartic_equation_solutions(const gsl_complex root1, const gsl_complex root2,
                                           const gsl_complex root3, const gsl_complex root4);

/**
 * Solve quadratic equation ax^2 + bx + c = 0 in the complex domain
 * @param a Coefficient of x^2 (must not be zero)
 * @param b Coefficient of x
 * @param c Constant term
 * @param root1 Pointer to store the first root
 * @param root2 Pointer to store the second root
 * @return -1: Invalid inputs, 0: Complex roots, 1: 2 identical real roots, 2: 2 distinct real roots
 */
short int se_sovle_quadratic_equation(const double a, const double b, const double c, 
                                      gsl_complex *root1, gsl_complex *root2);

/**
 * Solve cubic equation ax^3 + bx^2 + cx + d = 0 in the complex domain
 * @param a Coefficient of x^3 (must not be zero)
 * @param b Coefficient of x^2
 * @param c Coefficient of x
 * @param d Constant term
 * @param root1 Pointer to store the first root
 * @param root2 Pointer to store the second root
 * @param root3 Pointer to store the third root
 * @return -1: Invalid inputs, 1: One real root and 2 complex roots, 3: All roots are real and distinct
 */
short int se_solve_cubic_equation(const double a, const double b, const double c, const double d,
                                  gsl_complex *root1, gsl_complex *root2, gsl_complex *root3);

/**
 * Solve quartic equation ax^4 + bx^3 + cx^2 + dx + e = 0 in the complex domain
 * @param a Coefficient of x^4 (must not be zero)
 * @param b Coefficient of x^3
 * @param c Coefficient of x^2
 * @param d Coefficient of x
 * @param e Constant term
 * @param x1 Pointer to store the first root
 * @param x2 Pointer to store the second root
 * @param x3 Pointer to store the third root
 * @param x4 Pointer to store the fourth root
 * @return -1: Invalid inputs, 0: All roots are complex, 2: 2 distinct real roots and 2 complex roots,
 *         3: 3 distinct real roots, 4: 4 distinct real roots
 */
short int se_solve_quartic_equation(const double a, const double b, const double c, const double d, const double e,
                                    gsl_complex *x1, gsl_complex *x2, gsl_complex *x3, gsl_complex *x4);

#endif // SOVLE_EQUATIONS_H