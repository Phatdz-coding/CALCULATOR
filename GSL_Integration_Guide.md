# GSL Integration Functions Usage Guide

## Overview
The GNU Scientific Library (GSL) provides various numerical integration routines for computing definite integrals. Here's how to use them effectively.

## Basic Setup

### 1. Include Headers
```c
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>
```

### 2. Define Your Function
Your function must have this signature:
```c
double your_function(double x, void *params) {
    // Your function implementation
    return some_expression_of_x;
}
```

### 3. Create GSL Function Structure
```c
gsl_function F;
F.function = &your_function;
F.params = parameters;  // NULL if no parameters
```

## Integration Methods

### 1. QNG - Simple Non-Adaptive Integration
**Best for:** Smooth functions, quick results
```c
double result, error;
size_t neval;
int status = gsl_integration_qng(&F, a, b, epsabs, epsrel, 
                                &result, &error, &neval);
```

### 2. QAG - General Adaptive Integration
**Best for:** Most general-purpose integration
```c
gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int status = gsl_integration_qag(&F, a, b, epsabs, epsrel, 1000,
                                GSL_INTEG_GAUSS61, w, &result, &error);
gsl_integration_workspace_free(w);
```

### 3. QAGS - Adaptive with Singularities
**Best for:** Functions with singularities or discontinuities
```c
gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int status = gsl_integration_qags(&F, a, b, epsabs, epsrel, 1000,
                                 w, &result, &error);
gsl_integration_workspace_free(w);
```

### 4. QAGI - Infinite Intervals (-∞, ∞)
**Best for:** Functions that decay to zero at infinity
```c
gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int status = gsl_integration_qagi(&F, epsabs, epsrel, 1000,
                                 w, &result, &error);
gsl_integration_workspace_free(w);
```

### 5. QAGIU - Semi-Infinite [a, ∞)
**Best for:** Integration from finite point to infinity
```c
gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int status = gsl_integration_qagiu(&F, a, epsabs, epsrel, 1000,
                                  w, &result, &error);
gsl_integration_workspace_free(w);
```

### 6. QAGIL - Semi-Infinite (-���, b]
**Best for:** Integration from negative infinity to finite point
```c
gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int status = gsl_integration_qagil(&F, b, epsabs, epsrel, 1000,
                                  w, &result, &error);
gsl_integration_workspace_free(w);
```

## Parameters Explanation

- **a, b**: Integration limits
- **epsabs**: Absolute error tolerance (e.g., 1e-10)
- **epsrel**: Relative error tolerance (e.g., 1e-10)
- **limit**: Maximum number of subintervals (e.g., 1000)
- **key**: Integration rule for QAG:
  - `GSL_INTEG_GAUSS15`: 15-point Gauss-Kronrod
  - `GSL_INTEG_GAUSS21`: 21-point Gauss-Kronrod
  - `GSL_INTEG_GAUSS31`: 31-point Gauss-Kronrod
  - `GSL_INTEG_GAUSS41`: 41-point Gauss-Kronrod
  - `GSL_INTEG_GAUSS51`: 51-point Gauss-Kronrod
  - `GSL_INTEG_GAUSS61`: 61-point Gauss-Kronrod (most accurate)

## Error Handling

Check the return status:
```c
if (status != GSL_SUCCESS) {
    printf("Integration failed: %s\n", gsl_strerror(status));
}
```

Common status codes:
- `GSL_SUCCESS`: Integration successful
- `GSL_EMAXITER`: Maximum iterations exceeded
- `GSL_EROUND`: Roundoff error detected
- `GSL_ESING`: Singularity detected
- `GSL_EDIVERGE`: Integral diverges

## Function with Parameters Example

```c
double parametric_function(double x, void *params) {
    double *p = (double *)params;
    double a = p[0];
    double b = p[1];
    return a * x * x + b * x;
}

int main() {
    double params[2] = {2.0, 3.0};  // a=2, b=3
    gsl_function F;
    F.function = &parametric_function;
    F.params = params;
    
    // Now integrate 2x² + 3x
    // ... rest of integration code
}
```

## Compilation

To compile your program with GSL:
```bash
gcc -o myprogram myprogram.c -lgsl -lgslcblas -lm
```

## Quick Reference

| Method | Use Case | Workspace Needed |
|--------|----------|------------------|
| QNG | Simple, smooth functions | No |
| QAG | General purpose | Yes |
| QAGS | Functions with singularities | Yes |
| QAGI | Infinite intervals (-∞,∞) | Yes |
| QAGIU | Semi-infinite [a,∞) | Yes |
| QAGIL | Semi-infinite (-∞,b] | Yes |

## Tips

1. Start with `qng` for simple functions
2. Use `qags` for most real-world problems
3. Set reasonable error tolerances (1e-8 to 1e-12)
4. Always check the return status
5. Free allocated workspaces to prevent memory leaks
6. For oscillatory functions, consider specialized methods like QAWO