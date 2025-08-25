#include <MY_LIB/numerical_integration.h>

double * f___(int n, double x[])
{
    double *result = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        result[i] = sin(1000.0 * x[i]); // f(x) = sin(1000x)
    }
    return result;
}

int main()
{
    char str_function[] = "cos(1000x)";
    __INFIX__ I_function = convert_string_to_INFIX(str_function);

    double a = 0.0;
    double b = 5.0;

    double result = NAN;
    double error = 0;

    // short int status = ni_integral_GauussianQuadrature(I_function, 'x', a, b, &result, 3);

    // ni_integral_aq(I_function, 'x', a, b, &result, 1e-15);

    // short int status = ni_integral_GauussianQuadrature1000(I_function, 'x', a, b, &result);

    // result = ni_integral_GaussianQuadrature500(I_function, 'x', a, b);

    // result = integral_definite_infix(I_function, 'x', a, b);


        printf("Result = %.15g | Status = %d\n", result, 0);

    if (I_function.tokens != NULL)
        free(I_function.tokens);
    return 0;
}