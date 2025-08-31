#ifndef EXTRA_MATH_FUNCTION_H
#define EXTRA_MATH_FUNCTION_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //

bool is_integer(double x);

bool is_zero(const double);

double logarithm(const double base, const double expression);

double permutations(int, int);

double combinations(int, int);

double coth(double x);

double arccoth(double x);

double arcsec(double x);

double arcsech(double x);

double csch(double x);

double arccsc(double x);

double arccsch(double x);

double lambertw_real(double z);

int gcd(int a, int b);

int lcm(int a, int b);

int hcf(int a, int b);

double gamma_function(double n);

unsigned long long factorial(int n);

int generate_nth_prime(int n);

int fibonacci(int n);

bool prime_checker(const int number);

double sigmoid(const double x);

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //

double sigmoid(const double x)
{
    return 1.0 / (1.0 + pow(2.718281828459045, -x));
}

// Function to check if a number is a prime
bool prime_checker(const int number)
{
    if (number < 2)
        return false;
    for (int i = 2; i * i <= number; i++)
        if (number % i == 0)
            return false;
    return true;
}

// generate the nth fibonachi number
int fibonacci(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }

    int a = 0, b = 1, fib = 0;
    for (int i = 2; i <= n; i++)
    {
        fib = a + b;
        a = b;
        b = fib;
    }
    return fib;
}

// Function to generate the nth prime number | Fast prime generator
int generate_nth_prime(int n)
{
    if (n < 1)
        return -1; // Invalid input

    int upper_bound = estimate_upper_bound(n);
    bool *is_prime = (bool *)malloc((upper_bound + 1) * sizeof(bool));
    for (int i = 0; i <= upper_bound; i++)
    {
        is_prime[i] = true;
    }

    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= upper_bound; p++)
    {
        if (is_prime[p])
        {
            for (int degreeltiple = p * p; degreeltiple <= upper_bound; degreeltiple += p)
            {
                is_prime[degreeltiple] = false;
            }
        }
    }

    int count = 0;
    int nth_prime_number = -1;
    for (int i = 2; i <= upper_bound; i++)
    {
        if (is_prime[i])
        {
            count++;
            if (count == n)
            {
                nth_prime_number = i;
                break;
            }
        }
    }

    free(is_prime);
    return nth_prime_number;
}

/*
  compute the factorial of an integer
  the term unsigned long long is used to handle enormous numbers
*/
unsigned long long factorial(int n)
{
    if (n < 0)
        return 0; // Factorial is not defined for negative numbers

    unsigned long long result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

// Compute the factorial of a real number using the Gamma function
double gamma_function(double n)
{
    if (n < 0)
    {
        return NAN; // Factorial is not defined for negative numbers
    }
    return tgamma(n + 1);
}

// find the greatest common divisor of 2 integers
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// find the least common degreeltiplier of 2 integers
int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    return abs(a * b) / gcd(a, b);
}

// find the highest common factor of 2 integers
int hcf(int a, int b)
{
    return gcd(a, b);
}

double lambertw_real(double z)
{
    // Check if z is in the domain of the real-valued Lambert W function
    if (z < -1.0 / 2.718281828459045)
    {
        return NAN; // Or handle the error as appropriate for your application
    }

    // Initial guess:  A simple approximation.  Can be improved.
    double w = 0.0;
    if (z > 0)
    {
        w = log(z + 1); // crude approximation, good for positive z
    }

    // Newton-Raphson iteration
    for (int i = 0; i < 100; ++i)
    {
        double ew = exp(w);
        double f = w * ew - z;
        double df = ew * (w + 1);

        // Avoid division by zero o near-zero
        if (fabs(df) < 1e-15)
        {
            return w; // or NAN, depending on desired behavior
        }

        double delta = f / df;
        w -= delta;

        if (fabs(delta) < 1e-15)
        {
            break; // Convergence
        }
    }

    return w; // Return the approximate value
}

/**
 * Calculates the hyperbolic cotangent of x.
 * coth(x) = 1 / tanh(x)
 * Returns HUGE_VAL for x == 0 (division by zero).
 */
double coth(double x)
{
    if (x == 0.0)
    {
        errno = EDOM; // Domain error
        return HUGE_VAL;
    }
    return 1.0 / tanh(x);
}

/**
 * Calculates the inverse hyperbolic cotangent of x.
 * arccoth(x) = 0.5 * ln((x + 1) / (x - 1)), |x| > 1
 * Returns NAN for |x| <= 1 (undefined).
 */
double arccoth(double x)
{
    if (fabs(x) <= 1.0)
    {
        errno = EDOM; // Domain error
        return NAN;
    }
    return 0.5 * log((x + 1.0) / (x - 1.0));
}

double arcsec(double x)
{
    if (fabs(x) < 1.0)
    {
        errno = EDOM; // Domain error
        return NAN;
    }
    return acos(1.0 / x);
}

double arcsech(double x)
{
    if (x <= 0.0 || x > 1.0)
    {
        errno = EDOM; // Domain error
        return NAN;
    }
    return log((1.0 + sqrt(1.0 - x * x)) / x);
}

/**
 * Calculates the hyperbolic cosecant of x.
 * csch(x) = 1 / sinh(x)
 * Returns HUGE_VAL for x == 0 (division by zero).
 */
double csch(double x)
{
    if (x == 0.0)
    {
        errno = EDOM; // Domain error
        return HUGE_VAL;
    }
    return 1.0 / sinh(x);
}

/**
 * Calculates the inverse cosecant of x.
 * arccsc(x) = arcsin(1/x), |x| >= 1
 * Returns NAN for |x| < 1 (undefined).
 */
double arccsc(double x)
{
    if (fabs(x) < 1.0)
    {
        errno = EDOM; // Domain error
        return NAN;
    }
    return asin(1.0 / x);
}

/**
 * Calculates the inverse hyperbolic cosecant of x.
 * arccsch(x) = ln(1/x + sqrt(1/x^2 + 1)), x != 0
 * Returns NAN for x == 0 (undefined).
 */
double arccsch(double x)
{
    if (x == 0.0)
    {
        errno = EDOM; // Domain error
        return NAN;
    }
    return log(1.0 / x + sqrt(1.0 / (x * x) + 1.0));
}

// probalbilistic
double permutations(int n, int r)
{
    // Input validation
    if (n < 0 || r < 0)
        return 0.0;

    if (r > n)
        return 0.0;

    // Special cases
    if (r == 0)
        return 1.0;

    if (r == n)
        return factorial(n); // Use real factorial for consistency

    // Calculate P(n,r) = n! / (n-r)!
    // More efficient: P(n,r) = n * (n-1) * (n-2) * ... * (n-r+1)
    double result = 1.0;
    for (int i = 0; i < r; i++)
    {
        result *= (double)(n - i);

        // Check for overflow/infinity
        if (isinf(result))
        {
            return INFINITY; // Return infinity if overflow occurs
        }
    }

    return result;
}

// probalbilistic
double combinations(int n, int r)
{
    // Input validation
    if (n < 0 || r < 0)
        return 0.0;

    if (r > n)
        return 0.0;

    // Special cases
    if (r == 0 || r == n)
        return 1.0;

    // Optimization: C(n,r) = C(n,n-r), use smaller r for efficiency
    if (r > n - r)
        r = n - r;

    // Calculate C(n,r) = n! / (r! * (n-r)!)
    // More efficient: C(n,r) = (n * (n-1) * ... * (n-r+1)) / (r * (r-1) * ... * 1)
    double result = 1.0;

    for (int i = 0; i < r; i++)
    {
        result *= (double)(n - i);
        result /= (double)(i + 1);

        // Check for overflow/infinity
        if (isinf(result))
        {
            return INFINITY; // Return infinity if overflow occurs
        }

        // Check for underflow (result becoming too small)
        if (result == 0.0 && (n - i) > 0)
        {
            return 0.0; // Underflow occurred
        }
    }

    return result;
}

double logarithm(const double base, const double expression)
{
    // Validate base - must be positive and not equal to 1
    if (base <= 0 || base == 1 || isnan(base) || isinf(base))
    {
        return NAN; // Invalid base
    }

    // Check if expression is in the domain of logarithm
    if (isnan(expression) || isinf(expression))
    {
        return expression; // Propagate NaN or infinity
    }

    if (expression < 0)
    {
        return NAN; // log(negative) = undefined
    }

    if (expression == 0)
    {
        return -INFINITY; // log(0) = -infinity
    }

    if (expression == 1)
    {
        return 0.0; // log_base(1) = 0 for any valid base
    }

    // Calculate logarithm using change of base formula: log_base(x) = ln(x) / ln(base)
    double log_result = log(expression) / log(base);

    // Handle potential numerical issues
    if (isnan(log_result) || isinf(log_result))
    {
        return log_result;
    }

    // Check for very small results that should be zero
    if (fabs(log_result) < 1e-15)
    {
        return 0.0;
    }

    return log_result;
}

bool is_zero(const double x)
{
    if (fabs(x) <= __DBL_EPSILON__)
        return true;
    return false;
}

// Checks if a double value is an integer.
bool is_integer(double x)
{
    // NaN and infinity are not integers
    if (!isfinite(x))
        return false;
    return floor(x) == x;
}

#endif