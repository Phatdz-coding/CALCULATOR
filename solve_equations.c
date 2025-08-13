#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/sovle_equations.h>
// See new libbraries in se_include folder

int main()
{
    char str_function[] = "x^2-2";
    __INFIX__ I_function = convert_string_to_INFIX(str_function);

    double * roots = NULL;
    short int numof_root = se_solve_equation(I_function, 'x', -2, 3, &roots);

    se_display_root_array(roots, numof_root);



    free(I_function.tokens);
    return 0;
}
