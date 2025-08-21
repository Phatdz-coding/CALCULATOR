#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

// Example function to integrate: f(x) = x^2
double function1(double x, void *params) {
    return x * x;
}

// Example function to integrate: f(x) = sin(x)
double function2(double x, void *params) {
    return sin(x);
}

// Example function to integrate: f(x) = exp(-x^2)
double function3(double x, void *params) {
    return exp(-x * x);
}

// Example function with parameters: f(x) = a * x^2 + b
double function_with_params(double x, void *params) {
    double *p = (double *)params;
    double a = p[0];
    double b = p[1];
    return a * x * x + b;
}

int main() {
    printf("GSL Integration Examples\n");
    printf("========================\n\n");

    // Variables for integration results
    double result, error;
    size_t neval;
    int status;

    // Create GSL function structures
    gsl_function F1, F2, F3, F4;
    
    // Set up function 1: x^2
    F1.function = &function1;
    F1.params = NULL;
    
    // Set up function 2: sin(x)
    F2.function = &function2;
    F2.params = NULL;
    
    // Set up function 3: exp(-x^2)
    F3.function = &function3;
    F3.params = NULL;
    
    // Set up function 4 with parameters: 2*x^2 + 3
    double params[2] = {2.0, 3.0}; // a = 2, b = 3
    F4.function = &function_with_params;
    F4.params = params;

    // 1. Simple non-adaptive integration (QNG)
    printf("1. QNG Integration (Non-adaptive)\n");
    printf("----------------------------------\n");
    
    // Integrate x^2 from 0 to 1 (analytical result = 1/3)
    status = gsl_integration_qng(&F1, 0.0, 1.0, 1e-10, 1e-10, &result, &error, &neval);
    printf("∫₀¹ x² dx = %.10f ± %.2e (analytical: 0.3333333333)\n", result, error);
    printf("Function evaluations: %zu\n", neval);
    printf("Status: %s\n\n", gsl_strerror(status));

    // 2. Adaptive integration (QAG)
    printf("2. QAG Integration (Adaptive)\n");
    printf("-----------------------------\n");
    
    // Create workspace for adaptive integration
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(1000);
    
    // Integrate sin(x) from 0 to π (analytical result = 2)
    status = gsl_integration_qag(&F2, 0.0, M_PI, 1e-10, 1e-10, 1000, 
                                GSL_INTEG_GAUSS61, workspace, &result, &error);
    printf("∫₀^π sin(x) dx = %.10f ± %.2e (analytical: 2.0)\n", result, error);
    printf("Status: %s\n\n", gsl_strerror(status));

    // 3. Integration with singularities (QAGS)
    printf("3. QAGS Integration (Adaptive with singularities)\n");
    printf("------------------------------------------------\n");
    
    // Integrate x^2 from 0 to 2
    status = gsl_integration_qags(&F1, 0.0, 2.0, 1e-10, 1e-10, 1000, 
                                 workspace, &result, &error);
    printf("∫₀² x² dx = %.10f ± %.2e (analytical: 2.6666666667)\n", result, error);
    printf("Status: %s\n\n", gsl_strerror(status));

    // 4. Infinite interval integration (QAGI)
    printf("4. QAGI Integration (Infinite intervals)\n");
    printf("---------------------------------------\n");
    
    // Integrate exp(-x^2) from -∞ to +∞ (analytical result = √π)
    status = gsl_integration_qagi(&F3, 1e-10, 1e-10, 1000, workspace, &result, &error);
    printf("∫₋∞^∞ exp(-x²) dx = %.10f ± %.2e (analytical: %.10f)\n", 
           result, error, sqrt(M_PI));
    printf("Status: %s\n\n", gsl_strerror(status));

    // 5. Semi-infinite interval integration (QAGIU)
    printf("5. QAGIU Integration (Semi-infinite: [a,∞))\n");
    printf("-------------------------------------------\n");
    
    // Integrate exp(-x^2) from 0 to +∞ (analytical result = √π/2)
    status = gsl_integration_qagiu(&F3, 0.0, 1e-10, 1e-10, 1000, workspace, &result, &error);
    printf("∫₀^∞ exp(-x²) dx = %.10f ± %.2e (analytical: %.10f)\n", 
           result, error, sqrt(M_PI)/2.0);
    printf("Status: %s\n\n", gsl_strerror(status));

    // 6. Integration with parameters
    printf("6. Integration with Parameters\n");
    printf("------------------------------\n");
    
    // Integrate 2*x^2 + 3 from 0 to 1 (analytical result = 2/3 + 3 = 11/3)
    status = gsl_integration_qag(&F4, 0.0, 1.0, 1e-10, 1e-10, 1000, 
                                GSL_INTEG_GAUSS61, workspace, &result, &error);
    printf("∫₀¹ (2x² + 3) dx = %.10f ± %.2e (analytical: %.10f)\n", 
           result, error, 11.0/3.0);
    printf("Status: %s\n\n", gsl_strerror(status));

    // 7. Fixed-order Gauss-Legendre integration
    printf("7. Fixed-order Gauss-Legendre Integration\n");
    printf("-----------------------------------------\n");
    
    // Create Gauss-Legendre table with 10 points
    gsl_integration_glfixed_table *gl_table = gsl_integration_glfixed_table_alloc(10);
    
    // Integrate x^2 from 0 to 1
    result = gsl_integration_glfixed(&F1, 0.0, 1.0, gl_table);
    printf("∫₀¹ x² dx = %.10f (10-point Gauss-Legendre)\n", result);
    printf("Analytical result: 0.3333333333\n\n");

    // 8. Romberg integration
    printf("8. Romberg Integration\n");
    printf("---------------------\n");
    
    // Create Romberg workspace
    gsl_integration_romberg_workspace *romberg_ws = gsl_integration_romberg_alloc(20);
    
    // Integrate sin(x) from 0 to π
    status = gsl_integration_romberg(&F2, 0.0, M_PI, 1e-10, 1e-10, &result, &neval, romberg_ws);
    printf("∫₀^π sin(x) dx = %.10f (analytical: 2.0)\n", result);
    printf("Function evaluations: %zu\n", neval);
    printf("Status: %s\n\n", gsl_strerror(status));

    // Clean up memory
    gsl_integration_workspace_free(workspace);
    gsl_integration_glfixed_table_free(gl_table);
    gsl_integration_romberg_free(romberg_ws);

    printf("Integration Examples Complete!\n");
    printf("\nKey Points:\n");
    printf("- QNG: Simple non-adaptive integration\n");
    printf("- QAG: General adaptive integration\n");
    printf("- QAGS: Adaptive integration handling singularities\n");
    printf("- QAGI: Integration over infinite intervals (-∞,∞)\n");
    printf("- QAGIU: Integration over semi-infinite intervals [a,∞)\n");
    printf("- QAGIL: Integration over semi-infinite intervals (-∞,b]\n");
    printf("- Gauss-Legendre: Fixed-order quadrature\n");
    printf("- Romberg: Richardson extrapolation method\n");

    return 0;
}