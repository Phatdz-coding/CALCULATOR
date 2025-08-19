#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/sovle_equations.h>

int main()
{
    turn_on_advanced_character_mode();
    char f1[] = "x*x + y*y - 7";
    char f2[] = "x*x - y*y - ln2";

    const char var_set[] = "xy";

    __INFIX__ *F_x = se_alloc_F_x_for_systemof_nonlinear_equation(2);

    F_x[0] = convert_string_to_INFIX(f1);
    F_x[1] = convert_string_to_INFIX(f2);
    // F_x[2] = convert_string_to_INFIX(f3);

    double *solutions = NULL;
    short int status = se_solve_system_of_nonlinear_equation(F_x, var_set, 2, &solutions, -2.0, 0.0);

    puts("Solutions");
    se_display_root_array(solutions, 's', 2);

    se_free_F_x_for_systemof_nonlinear_equation(&F_x, 2);
    if (solutions != NULL)
        free(solutions);
    return 0;
}
