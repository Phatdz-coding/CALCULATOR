/* =======================================


THIS FILE IS USED TO DEBUG


======================================= */



#include "MY_LIB/inputsDisplays.h"
#include "MY_LIB/my_calculator.h"

int main()
{
    char * str_exp = input_String("");

    __INFIX__ I_exp = convert_string_to_INFIX(str_exp);

    puts("[INPUT]\n\n");
    display_infix_exp(I_exp);

    printf("\n\nFinal result = %.17lf\n", evaluate_I_exp(I_exp));

    free(I_exp.tokens);
    free(str_exp);
    return 0;
}
