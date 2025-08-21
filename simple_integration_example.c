#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

// Function to integrate: f(x) = x^2
double my_function(double x, void *params) {
    return x * x;
}

int main() {
    // Step 1: Create a GSL function structure
    gsl_function F;
    F.function = &my_function;  // Pointer to your function
    F.params = NULL;            // Parameters (NULL if none)

    // Step 2: Set up integration parameters
    double a = 0.0;             // Lower limit
    double b = 1.0;             // Upper limit
    double epsabs = 1e-10;      // Absolute error tolerance
    double epsrel = 1e-10;      // Relative error tolerance
    size_t limit = 1000;        // Maximum number of subintervals

    // Step 3: Create workspace for adaptive integration
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(limit);

    // Step 4: Perform the integration
    double result, error;
    int status = gsl_integration_qags(&F, a, b, epsabs, epsrel, limit, 
                                     workspace, &result, &error);

    // Step 5: Display results
    printf("Integral of x^2 from 0 to 1:\n");
    printf("Result: %.10f\n", result);
    printf("Error estimate: %.2e\n", error);
    printf("Analytical result: %.10f\n", 1.0/3.0);
    printf("Status: %s\n", gsl_strerror(status));

    // Step 6: Clean up memory
    gsl_integration_workspace_free(workspace);

    return 0;
}

/*
COMPILATION:
gcc -o simple_integration simple_integration_example.c -lgsl -lgslcblas -lm

BASIC USAGE PATTERN:
1. Define your function with signature: double func(double x, void *params)
2. Create gsl_function structure and set function pointer and parameters
3. Choose integration method (qng, qag, qags, qagi, etc.)
4. Create workspace if needed (for adaptive methods)
5. Call integration function
6. Clean up allocated memory

COMMON INTEGRATION FUNCTIONS:
- gsl_integration_qng: Simple non-adaptive (no workspace needed)
- gsl_integration_qag: General adaptive integration
- gsl_integration_qags: Adaptive with singularity handling
- gsl_integration_qagi: Infinite intervals (-∞, ∞)
- gsl_integration_qagiu: Semi-infinite [a, ∞)
- gsl_integration_qagil: Semi-infinite (-∞, b]
*/