#include <MY_LIB/sovle_equations.h>

int main()
{
    gsl_complex x1, x2, x3, x4;
    se_solve_quartic_equation(3, 0.0, 4, 0.0, -4.1, &x1, &x2, &x3, &x4);
    se_display_quartic_equation_solutions(x1, x2, x3, x4);

    return 0;
}