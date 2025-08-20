#ifndef MY_CALCULATOR_H
#define MY_CALCULATOR_H

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
#include <MY_LIB/inputsDisplays.h>

//=================================================================================================================//
//                                                   MACROES                                                       //
//=================================================================================================================//

#define PI 3.14159265358979323846
#define EULER_NUMBER 2.718281828459045
#define VARIABLE -INFINITY
#define _EMPTY_ INFINITY
#define SQRT_2 1.41421356237309504880
#define SQRT_2_2 0.707106781186547524
#define SQRT_3 1.73205080756887729353
#define LN_2 0.69314718055994530942
#define _G_ 9.80665
#define _C_ 299792458
#define _MAX_INT_VALUE_ 2147483647
// Function specifiers
// --- 1-parameter function --- //
#define SPECIFIER_OF_SIN 's'
#define SPECIFIER_OF_SINH 'n'
#define SPECIFIER_OF_ARCSIN 'Q'
#define SPECIFIER_OF_ARCSINH 'N'
#define SPECIFIER_OF_COS '<'
#define SPECIFIER_OF_COSH 'm'
#define SPECIFIER_OF_ARCCOS 'W'
#define SPECIFIER_OF_ARCCOSH 'M'
#define SPECIFIER_OF_TAN 't'
#define SPECIFIER_OF_TANH 'p'
#define SPECIFIER_OF_ARCTAN 'U'
#define SPECIFIER_OF_ARCTANH 'P'
#define SPECIFIER_OF_COT 'T'
#define SPECIFIER_OF_COTH 'j'
#define SPECIFIER_OF_ARCCOT 'O'
#define SPECIFIER_OF_ARCCOTH 'J'
#define SPECIFIER_OF_SEC 'S'
#define SPECIFIER_OF_SECH 'g'
#define SPECIFIER_OF_ARCSEC 'a'
#define SPECIFIER_OF_ARCSECH 'A'
#define SPECIFIER_OF_CSC '>'
#define SPECIFIER_OF_CSCH 'v'
#define SPECIFIER_OF_ARCCSC 'b'
#define SPECIFIER_OF_ARCCSCH 'B'
#define SPECIFIER_OF_SQRT 'r'
#define SPECIFIER_OF_CBRT 'R'
#define SPECIFIER_OF_ABS 'V'
#define SPECIFIER_OF_LN 'L'
#define SPECIFIER_OF_LG 'l'
#define SPECIFIER_OF_GAMMA 'G'
#define SPECIFIER_OF_CEIL 'C'
#define SPECIFIER_OF_FLOOR 'F'
#define SPECIFIER_OF_LAMBERTW 'w'
// --- many-parameters functions --- //
#define SPECIFIER_OF_DIF 'd' // derivative
#define SPECIFIER_OF_INTEGRAL 'I'
#define SPECIFIER_OF_SIGMA_SUM 'k'
#define SPECIFIER_OF_PRODUCT_OF_SEQUENCE 'K'
#define SPECIFIER_OF_PERMUTATIONS 'z' // probalbilstic
#define SPECIFIER_OF_COMBINATIONS 'Z' // probalbilstic
#define SPECIFIER_OF_GCD 'y'          // Greatest Common Divisor
#define SPECIFIER_OF_LCM 'Y'          // Least Common Multiplier
#define SPECIFIER_OF_LOG 'x'          // Logarithm
typedef enum
{
    d,
    f,
    lf,
    ld,
    lld,
    lu,
    llu
} NumType;

typedef struct
{
    double num;
    char operator;
} _postfix_;

typedef struct P_tokens_data
{
    double num;
    char operator;
    char variable;
} _TOKENS_DATA_;

typedef struct P_tokens_array
{
    _TOKENS_DATA_ *tokens;
    int size;
} _POSTFIX__;

typedef struct tokens_data
{
    double num;
    char operator;
    char variable;
} _infix_;

typedef struct tokens_array
{
    int size;
    _infix_ *tokens;
} __INFIX__;

//=================================================================================================================//
//                                            FUNCTIONS DECLARATION                                                //
//=================================================================================================================//

int count_digit_of(const int integer);
int Sovle_Quadratic_Equation(double a, double b, double c, double *x1, double *x2);
int Sovle_Cubic_Polinomial_Equation(double a, double b, double c, double d, double *x1, double *x2, double *x3);
double P_Circle(double radius);
double S_Circle(double radius);
double S_Surface_Sphere(double radius);
double V_Sphere(double radius);
double S_Triangle_3_sides(double a, double b, double c);
double S_Triangle_height_base(double height, double base);
double S_Triangle_3_coord(double x1, double y1, double x2, double y2, double x3, double y3);
int fibonacci(int n);
int estimate_upper_bound(int n);
bool prime_checker(const int number);
int generate_nth_prime(int n);
int gcd(int a, int b);
int lcm(int a, int b);
int hcf(int a, int b);
unsigned long long factorial(int n);
double gamma_function(double n);
int *find_prime_factors(int n, int *num_of_fac);
double sum(double start, double end, double step);
int random_in_range(int a, int b);
char *convert_int_base10_to_base2_string(int number);
char *convert_int_base10_to_base8_string(int number);
char *convert_int_base10_to_base16_string(int number);
int convert_int_base16_to_base10(char *hex);
int convert_binary_to_decimal(const char *binary);
int convert_octal_to_decimal(const char *octal);
char *num_to_string(void *num, NumType type);
int *separate_digits(int num_to_seperate);
int precedent_of(char op);
void _increase_(int *token, char op);
void Least_Operator(char *expression, char *L_O, int *pos_of_op);
double evaluate(char *expression);
char _operator__(char *expression, int token);
double lambertw_real(double z);
int strlen_of_(char *string);
double limit_left(char *function, const char _varriable_, const double _x_);
double limit_right(char *function, const char _varriable_, const double _x_);
double limit(char *function, const char _varriable_, const double _x_);
void re_format(char **expression);
double coth(double x);
double arccoth(double x);
double arcsec(double x);
double arcsech(double x);
double csch(double x);
double arccsc(double x);
double arccsch(double x);
void brackets_check(char **function);
double integral_definite(char *function, const char, const double lower_bound, const double upper_bound);
// double *solve(char *equation, const double, const double);
void sort_int_array(int *arr, int size);
int compare_ints(const void *a, const void *b);
int compare_doubles(const void *a, const void *b);
void sort_double_array(double *arr, int size);
// double average_slope(_postfix_ *P_function, const int output_index, const double a, const double b);
// void bisection_v2();
bool is_integer(double x);
double Compute_P_expression(const _POSTFIX__ P_expression);
_POSTFIX__ Parse(char *expression);
double Compute_P_function(_POSTFIX__ function, char *_variables_, ...);
double evaluate_function(char *_function_, const char *_variables_, ...);
__INFIX__ convert_string_to_INFIX(char *expression);
_POSTFIX__ submodule_Parse(__INFIX__ specified_expression);
__INFIX__ differentiate_I_exp(__INFIX__, const char);
void display_infix_exp(const __INFIX__ expression);
void check_for_valid_braket(__INFIX__ *copyof_input);
void add_many_tokens(__INFIX__ *destination, const __INFIX__ source);
void add_single_token(__INFIX__ *destination, const double num, const char variable, const char operator);
void find_LPO(__INFIX__ specified_expression, char *LPO, int *LPO_pos);
double evaluate_I_exp(__INFIX__ I_exp);
void substitude_result(__INFIX__ *I_exp_tobe_replaced, const __INFIX__ replacement, const int index_start, const int index_end);
void copy_sub_I_exp(__INFIX__ *destination, __INFIX__ source, const short int index_start, const short int index_end);
bool handle_special_functions_(__INFIX__ *I_exp);
double integral_definite_infix(__INFIX__ infix_function, const char var, const double lower_bound, const double upper_bound);
void display_postfix_exp(_POSTFIX__);
void optimize_P_exp(_POSTFIX__ *);
void optimize_I_exp(__INFIX__ *I_exp);
double permutations(int, int);
double combinations(int, int);
double sum_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step);
double product_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step);
double logarithm(const double base, const double expression);
void merge_2_num(__INFIX__ *I_exp, const short int index);
void merge_num_and_bracket(__INFIX__ *I_exp, const short int index);
void merge_multiplier_of_one(__INFIX__ *I_exp, const short int index);
void merge_multiplier_of_zero(__INFIX__ *I_exp, const short int index, const bool zero_first);
bool merge_unused_bracket(__INFIX__ *I_exp, const short int index);
void merge_pow_of_one(__INFIX__ *I_exp, const short int index);
void merge_pow_of_zero(__INFIX__ *I_exp, const short int index);
void reformat_I_exp(__INFIX__ *I_exp);
bool is_zero(const double);
__INFIX__ copy_infix_expression(const __INFIX__ source);
_POSTFIX__ copy_postfix_expression(const _POSTFIX__ source);
double random_in_range_double(const double a, const double b);

//=================================================================================================================//
//                                            FUNCTIONS DEFINITION                                                //
//=================================================================================================================//

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

// Comparison function for qsort (increasing order for doubles)
int compare_doubles(const void *a, const void *b)
{
    double arg1 = *(const double *)a;
    double arg2 = *(const double *)b;
    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

/*
 * Sorts an array of doubles in increasing order.
 * @param arr Pointer to the array of doubles.
 * @param size Number of elements in the array.
 */
void sort_double_array(double *arr, int size)
{
    qsort(arr, size, sizeof(double), compare_doubles);
}

int strlen_of_(char *string)
{
    int _strlen_ = 0;
    while (string[_strlen_] != '\0')
    {
        _strlen_++;
    }
    return _strlen_;
}

/*
Counter the digits of an integer
#Example usage:
int number = 89712;
int numlen = count_digit_of(number);
//numlen = 5
*/
int count_digit_of(const int integer)
{
    return (int)log10(abs(integer)) + 1;
}

/*
  This function return the solutions of the quadratic equation
  The function return -1 if a = 0
  The function return 0 if there's no real solutions
  The function return 1 if the equation has real root
*/
int Sovle_Quadratic_Equation(double a, double b, double c, double *x1, double *x2)
{
    double delta = b * b - 4 * a * c;
    if (a == 0)
    {
        x1 = 0;
        x2 = 0;
        return -1;
    }

    if (delta < 0)
    {
        x1 = 0;
        x2 = 0;
        return 0;
    }

    (*x1) = (-b - sqrt(delta)) / (2 * a);
    (*x2) = (-b + sqrt(delta)) / (2 * a);
    return 1;
}

/*
  This function is used to sovle all real solutions of a cubic equation
  The function return value:
                0 --> a = 0, not a cubic equation
                1 --> the equation has 1 real solution (x1 only)
                2 --> the equation has 1 solution and 1 double solution (x1 = x2 & x3)
                3 --> the equation has 3 solutions (x1 # x2 # x3)
*/
int Sovle_Cubic_Polinomial_Equation(double a, double b, double c, double d, double *x1, double *x2, double *x3)
{
    if (a == 0)
        return 0;

    double delta = b * b - 3 * a * c;

    if (delta == 0)
    {
        if (b * b * b - 27 * a * a * d == 0)
        {
            (*x1) = -b / (3 * a);
            (*x2) = (*x1);
            (*x3) = 0;
            return 2;
        }
        else
        {
            (*x1) = (-b + cbrt(b * b * b - 27 * a * a * d)) / (3 * a);
            return 1;
        }
    }

    double k = (9 * a * b * c - 2 * b * b * b - 27 * a * a * d) / (2 * sqrt(fabs(delta * delta * delta)));

    if (delta > 0)
    {
        if (fabs(k) <= 1)
        {
            (*x1) = (2 * sqrt(delta) * cos(acos(k) / 3) - b) / (3 * a);
            (*x2) = (2 * sqrt(delta) * cos((acos(k) / 3) - 2 * PI / 3) - b) / (3 * a);
            (*x3) = (2 * sqrt(delta) * cos((acos(k) / 3) + 2 * PI / 3) - b) / (3 * a);
            return 3;
        }
        else
        {
            (*x1) = ((sqrt(delta) * fabs(k)) / (3 * a * k)) * (cbrt(fabs(k) + sqrt(k * k - 1)) + cbrt(fabs(k) - sqrt(k * k - 1))) - (b / (3 * a));
            return 1;
        }
    }
    else if (delta < 0)
    {
        (*x1) = (sqrt(delta) / (3 * a)) * (cbrt(k + sqrt(k * k - 1)) + cbrt(k - sqrt(k * k + 1))) - (b / (3 * a));
        return 1;
    }
}

// compute the perimeter of a circle based on its radius
double P_Circle(double radius)
{
    return 2 * PI * radius;
}

// compute the square of a circle based on its radius
double S_Circle(double radius)
{
    return PI * radius * radius;
}

// compute the square of the sphere's surface
double S_Surface_Sphere(double radius)
{
    return 4 * PI * radius * radius;
}

// compute the volume of a sphere
double V_Sphere(double radius)
{
    return (4 * PI * radius * radius * radius) / 3;
}

// compute the square of a triangle based 3 known sides
double S_Triangle_3_sides(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// compute the square of a triangle based on its height and base
double S_Triangle_height_base(double height, double base)
{
    return 0.5 * height * base;
}

// compute the square of a triangle based on its peak's coordinates
double S_Triangle_3_coord(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return 0.5 * fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
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

// Function to estimate the upper bound for the nth prime
int estimate_upper_bound(int n)
{
    if (n < 6)
        return 15;
    return (int)(n * (log(n) + log(log(n))));
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

/*
Function to find all prime factors of an integer

#Example usage:
int num;
int num_of_fac;
int *factors = find_prime_factors(num, &num_of_fact);
//factors now contains all the prime factors of num
*/
int *find_prime_factors(int n, int *num_of_fac)
{
    int *factors = (int *)malloc(count_digit_of(n) * sizeof(int) + 4);

    if (n <= 1)
    {
        *num_of_fac = 0;
        return NULL;
    }

    *num_of_fac = 0; // Initialize *num_of_fac of prime factors

    // Store the number of 2s that divide n
    while (n % 2 == 0)
    {
        factors[(*num_of_fac)++] = 2;
        n /= 2;
    }

    // n degreest be odd at this point, so a skip of 2 is possible
    for (int i = 3; i * i <= n; i += 2)
    {
        // While i divides n, store i and divide n
        while (n % i == 0)
        {
            factors[(*num_of_fac)++] = i;
            n /= i;
        }
    }

    // This condition is to check if n is a prime number greater than 2
    if (n > 2)
    {
        factors[(*num_of_fac)++] = n;
    }

    return factors;
}

// find the sum of a given range with any step
double sum(double start, double end, double step)
{
    double sum = 0;
    if (step == 0)
        return 0;
    if (start < end)
        for (double i = start; i <= end; i += step)
            sum += i;
    else if (end < start)
        for (double i = start; i >= end; i -= step)
            sum += i;
    return sum;
}

// generate random integer between a & b where a < b
int random_in_range(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

// generate a random (double type) value in between a & b where a < b
double random_in_range_double(const double a, const double b)
{
    double lo = a, hi = b;
    if (lo > hi)
    {
        double t = lo;
        lo = hi;
        hi = t;
    }
    if (lo == hi)
        return lo;

    // Uniform u in [0, 1], inclusive of endpoints when rand() == 0 or RAND_MAX
    double u = (double)rand() / (double)RAND_MAX;

    return lo + u * (hi - lo);
}

//===============================================================//

//===============================================================//

char *convert_int_base10_to_base2_string(int number)
{
    char *binary = (char *)malloc(33 * sizeof(char)); // 32 bits + 1 for null terminator
    binary[32] = '\0';                                // Null-terminate the string

    unsigned int mask = 1U << 31; // Mask to extract each bit, starting from the most significant bit
    for (int i = 0; i < 32; i++)
    {
        binary[i] = (number & mask) ? '1' : '0';
        mask >>= 1;
    }

    // find the first '1' to remove leading zeros
    int first_one_index = 0;
    while (binary[first_one_index] == '0' && first_one_index < 31)
    {
        first_one_index++;
    }

    // create memory for refined_binary string
    char *refined_binary = (char *)malloc((33 - first_one_index) * sizeof(char));

    // Copy the refined binary string
    strcpy(refined_binary, &binary[first_one_index]);

    // handle the case if the number is zero
    if (refined_binary[0] == '\0')
        strcpy(refined_binary, "0");

    free(binary);
    return refined_binary;
}

// Function to convert an integer from base 10 to an octal (base 8) string
char *convert_int_base10_to_base8_string(int number)
{
    char *octal = (char *)malloc(12 * sizeof(char)); // Enough to hold octal representation of a 32-bit integer
    if (octal == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Handle negative numbers
    unsigned int abs_number = (number < 0) ? -number : number;

    int index = 11;        // Start from the end of the buffer
    octal[index--] = '\0'; // Null-terminate the string

    do
    {
        octal[index--] = '0' + (abs_number % 8);
        abs_number /= 8;
    } while (abs_number > 0);

    if (number < 0)
    {
        octal[index--] = '-';
    }

    return &octal[index + 1];
}

// Function to convert an integer from base 10 to a hexadecimal string
char *convert_int_base10_to_base16_string(int number)
{
    char *hex = (char *)malloc(11 * sizeof(char)); // Enough to hold hex representation of a 32-bit integer
    if (hex == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Handle negative numbers
    unsigned int abs_number = (number < 0) ? -number : number;

    int index = 10;      // Start from the end of the buffer
    hex[index--] = '\0'; // Null-terminate the string

    const char *hex_digits = "0123456789ABCDEF";
    do
    {
        hex[index--] = hex_digits[abs_number % 16];
        abs_number /= 16;
    } while (abs_number > 0);

    if (number < 0)
    {
        hex[index--] = '-';
    }

    return &hex[index + 1];
}

// Function to convert a hexadecimal string to a decimal integer
int convert_int_base16_to_base10(char *hex)
{
    if (hex == NULL)
        return 0;

    int length = strlen(hex);
    int base = 1; // Base value for hexadecimal (16^0)
    int decimal = 0;
    int start_index = 0;

    // Check for negative sign
    if (hex[0] == '-')
    {
        start_index = 1;
    }

    // Process each character from right to leftover
    for (int i = length - 1; i >= start_index; i--)
    {
        char current_char = toupper(hex[i]);

        if (current_char >= '0' && current_char <= '9')
        {
            decimal += (current_char - '0') * base;
        }
        else if (current_char >= 'A' && current_char <= 'f')
        {
            decimal += (current_char - 'A' + 10) * base;
        }
        else
            return 0;

        base *= 16;
    }

    // If the number is negative, convert the result to negative
    if (start_index == 1)
    {
        decimal = -decimal;
    }

    return decimal;
}

// Function to convert a binary string to a decimal integer
int convert_binary_to_decimal(const char *binary)
{
    if (binary == NULL)
        return 0;

    int length = strlen(binary);
    int base = 1; // Base value for binary (2^0)
    int decimal = 0;
    int start_index = 0;

    // Check for negative sign
    if (binary[0] == '-')
    {
        start_index = 1;
    }

    // Process each character from right to leftover
    for (int i = length - 1; i >= start_index; i--)
    {
        char current_char = binary[i];

        if (current_char == '1')
        {
            decimal += base;
        }
        else if (current_char != '0')
            return 0;

        base *= 2;
    }

    // If the number is negative, convert the result to negative
    if (start_index == 1)
    {
        decimal = -decimal;
    }

    return decimal;
}

// Function to convert an octal string to a decimal integer
int convert_octal_to_decimal(const char *octal)
{
    if (octal == NULL)
        return 0;

    int length = strlen(octal);
    int base = 1; // Base value for octal (8^0)
    int decimal = 0;
    int start_index = 0;

    // Check for negative sign
    if (octal[0] == '-')
    {
        start_index = 1;
    }

    // Process each character from right to leftover
    for (int i = length - 1; i >= start_index; i--)
    {
        char current_char = octal[i];

        if (current_char >= '0' && current_char <= '7')
        {
            decimal += (current_char - '0') * base;
        }
        else
            return 0;

        base *= 8;
    }

    // If the number is negative, convert the result to negative
    if (start_index == 1)
    {
        decimal = -decimal;
    }

    return decimal;
}

/*
#number types:
d
f
lf
ld
lld
lu
llu

#Example usage:

char *num = num_to_string(75, d);

//num now contain: "75"
*/
char *num_to_string(void *num, NumType type)
{
    char *numasstring = (char *)malloc(150 * sizeof(char));

    switch (type)
    {
    case d:
        sprintf(numasstring, "%d", *(int *)num);
        return numasstring;
    case f:
        sprintf(numasstring, "%f", *(float *)num);
        return numasstring;
    case lf:
        sprintf(numasstring, "%lf", *(double *)num);
        return numasstring;
    case ld:
        sprintf(numasstring, "%ld", *(long *)num);
        return numasstring;
    case lld:
        sprintf(numasstring, "%lld", *(long long *)num);
        return numasstring;
    case lu:
        sprintf(numasstring, "%lu", *(unsigned long *)num);
        return numasstring;
    case llu:
        sprintf(numasstring, "%llu", *(unsigned long long *)num);
        return numasstring;
    default:
        return NULL;
    }
}

/*
Function to seperate a number into its digits
32767 --> 3, 2, 7, 6, 7

#Example usage:
int *storage = separate_digits(32767);

//storage now contains: {3, 2, 7, 6, 7}
*/
int *separate_digits(int num_to_seperate)
{
    if (num_to_seperate < 0)
        return NULL;
    int *digits_storage = (int *)malloc(30 * sizeof(int));

    int numlen = log10(num_to_seperate) + 1;

    int d, k = numlen - 1;
    for (int i = 0; i < numlen; i++)
    {
        d = num_to_seperate % 10;
        digits_storage[k--] = d;

        num_to_seperate /= 10;
    }

    return digits_storage;
}

double lambertw_real(double z)
{
    // Check if z is in the domain of the real-valued Lambert W function
    if (z < -1.0 / EULER_NUMBER)
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

// Comparison function for qsort (increasing order)
int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2); // returns 1, 0, or -1
}

// Sorts an array of integers in increasing order
void sort_int_array(int *arr, int size)
{
    qsort(arr, size, sizeof(int), compare_ints);
}

//==========================================================//
//====================Evaluating Modules====================//
//==========================================================//

int precedent_of(char op)
{
    switch (op)
    {
    case '^':
    case '!':
    case SPECIFIER_OF_SIN:
    case SPECIFIER_OF_SINH:
    case SPECIFIER_OF_ARCSIN:
    case SPECIFIER_OF_ARCSINH:
    case SPECIFIER_OF_COS:
    case SPECIFIER_OF_COSH:
    case SPECIFIER_OF_ARCCOS:
    case SPECIFIER_OF_ARCCOSH:
    case SPECIFIER_OF_TAN:
    case SPECIFIER_OF_TANH:
    case SPECIFIER_OF_ARCTAN:
    case SPECIFIER_OF_ARCTANH:
    case SPECIFIER_OF_COT:
    case SPECIFIER_OF_COTH:
    case SPECIFIER_OF_ARCCOT:
    case SPECIFIER_OF_ARCCOTH:
    case SPECIFIER_OF_SEC:
    case SPECIFIER_OF_SECH:
    case SPECIFIER_OF_ARCSEC:
    case SPECIFIER_OF_ARCSECH:
    case SPECIFIER_OF_CSC:
    case SPECIFIER_OF_CSCH:
    case SPECIFIER_OF_ARCCSC:
    case SPECIFIER_OF_ARCCSCH:
    case SPECIFIER_OF_SQRT:
    case SPECIFIER_OF_CBRT:
    case SPECIFIER_OF_ABS:
    case SPECIFIER_OF_LN:
    case SPECIFIER_OF_LG:
    case SPECIFIER_OF_GAMMA:
    case SPECIFIER_OF_CEIL:
    case SPECIFIER_OF_FLOOR:
    case SPECIFIER_OF_LAMBERTW:
        return 3;
    case '/':
    case '*':
    case '%':
        return 2;
    case '-':
    case '+':
        return 1;
    default:
        return 0;
    }
}

void _increase_(int *token, char op)
{
    switch (op)
    {
    case SPECIFIER_OF_LN:
    case SPECIFIER_OF_LG:
    case '%':
        (*token) += 1;
        return;

    case SPECIFIER_OF_SIN:
    case SPECIFIER_OF_SEC:
    case SPECIFIER_OF_COS:
    case SPECIFIER_OF_CSC:
    case SPECIFIER_OF_TAN:
    case SPECIFIER_OF_COT:
    case SPECIFIER_OF_ABS:
    case SPECIFIER_OF_DIF:
    case SPECIFIER_OF_GCD:
    case SPECIFIER_OF_LCM:
    case SPECIFIER_OF_LOG:
        (*token) += 2;
        return;

    case SPECIFIER_OF_SQRT:
    case SPECIFIER_OF_CBRT:
    case SPECIFIER_OF_CEIL:
    case SPECIFIER_OF_SINH:
    case SPECIFIER_OF_COSH:
    case SPECIFIER_OF_TANH:
    case SPECIFIER_OF_COTH:
    case SPECIFIER_OF_SECH:
    case SPECIFIER_OF_CSCH:
        (*token) += 3;
        return;

    case SPECIFIER_OF_FLOOR:
    case SPECIFIER_OF_GAMMA:
        (*token) += 4;
        return;

    case SPECIFIER_OF_ARCSIN:
    case SPECIFIER_OF_ARCCOS:
    case SPECIFIER_OF_ARCTAN:
    case SPECIFIER_OF_ARCCOT:
    case SPECIFIER_OF_ARCSEC:
    case SPECIFIER_OF_ARCCSC:
        (*token) += 5;
        return;

    case SPECIFIER_OF_ARCSINH:
    case SPECIFIER_OF_ARCCOSH:
    case SPECIFIER_OF_ARCTANH:
    case SPECIFIER_OF_ARCCOTH:
    case SPECIFIER_OF_ARCSECH:
    case SPECIFIER_OF_ARCCSCH:
        (*token) += 6;
        return;

    case SPECIFIER_OF_LAMBERTW:
    case SPECIFIER_OF_INTEGRAL:
        (*token) += 7;
        return;
    case SPECIFIER_OF_SIGMA_SUM:
        (*token) += 10;
        return;
    case SPECIFIER_OF_PERMUTATIONS:
    case SPECIFIER_OF_COMBINATIONS:
        (*token) += 11;
        return;
    case SPECIFIER_OF_PRODUCT_OF_SEQUENCE:
        (*token) += 14;
        return;
    default:
        return;
    }
}

// Convert operators & functions to specifiers
char _operator__(char *expression, int token)
{
    if (expression[token] == '+')
        return '+';
    if (expression[token] == '-')
        return '-';
    if (expression[token] == '/')
        return '/';
    if (expression[token] == '*')
        return '*';
    if (expression[token] == '(')
        return '(';
    if (expression[token] == ')')
        return ')';
    if (expression[token] == '^')
        return '^';
    if (expression[token] == '%' && expression[token + 1] == '%')
        return '%';
    if (expression[token] == '!')
        return '!';
    if (expression[token] == ',')
        return ',';
    if (expression[token] == '=')
        return '=';
    if (!strncmp(expression + token, "sin(", 4))
        return SPECIFIER_OF_SIN;
    if (!strncmp(expression + token, "cos(", 4))
        return SPECIFIER_OF_COS;
    if (!strncmp(expression + token, "tan(", 4))
        return SPECIFIER_OF_TAN;
    if (!strncmp(expression + token, "cot(", 4))
        return SPECIFIER_OF_COT;
    if (!strncmp(expression + token, "sec(", 4))
        return SPECIFIER_OF_SEC;
    if (!strncmp(expression + token, "sech(", 5))
        return SPECIFIER_OF_SECH;
    if (!strncmp(expression + token, "arcsec(", 7))
        return SPECIFIER_OF_ARCSEC;
    if (!strncmp(expression + token, "arcsech(", 8))
        return SPECIFIER_OF_ARCSECH;
    if (!strncmp(expression + token, "csc(", 4))
        return SPECIFIER_OF_CSC;
    if (!strncmp(expression + token, "csch(", 5))
        return SPECIFIER_OF_CSCH;
    if (!strncmp(expression + token, "arccsc(", 7))
        return SPECIFIER_OF_ARCCSC;
    if (!strncmp(expression + token, "arccsch(", 8))
        return SPECIFIER_OF_ARCCSCH;
    if (!strncmp(expression + token, "arcsin(", 7))
        return SPECIFIER_OF_ARCSIN;
    if (!strncmp(expression + token, "arccos(", 7))
        return SPECIFIER_OF_ARCCOS;
    if (!strncmp(expression + token, "arctan(", 7))
        return SPECIFIER_OF_ARCTAN;
    if (!strncmp(expression + token, "arccot(", 7))
        return SPECIFIER_OF_ARCCOT;
    if (!strncmp(expression + token, "sqrt(", 5))
        return SPECIFIER_OF_SQRT;
    if (!strncmp(expression + token, "ln(", 3))
        return SPECIFIER_OF_LN;
    if (!strncmp(expression + token, "abs(", 4))
        return SPECIFIER_OF_ABS;
    if (!strncmp(expression + token, "cbrt(", 5))
        return SPECIFIER_OF_CBRT;
    if (!strncmp(expression + token, "gamma(", 6))
        return SPECIFIER_OF_GAMMA;
    if (!strncmp(expression + token, "ceil(", 5))
        return SPECIFIER_OF_CEIL;
    if (!strncmp(expression + token, "floor(", 6))
        return SPECIFIER_OF_FLOOR;
    if (!strncmp(expression + token, "lambertw(", 9))
        return SPECIFIER_OF_LAMBERTW;
    if (!strncmp(expression + token, "lg(", 3))
        return SPECIFIER_OF_LG;
    if (!strncmp(expression + token, "log(", 4))
        return SPECIFIER_OF_LOG;
    if (!strncmp(expression + token, "sinh(", 5))
        return SPECIFIER_OF_SINH;
    if (!strncmp(expression + token, "arcsinh(", 8))
        return SPECIFIER_OF_ARCSINH;
    if (!strncmp(expression + token, "cosh(", 5))
        return SPECIFIER_OF_COSH;
    if (!strncmp(expression + token, "arccosh(", 8))
        return SPECIFIER_OF_ARCCOSH;
    if (!strncmp(expression + token, "tanh(", 5))
        return SPECIFIER_OF_TANH;
    if (!strncmp(expression + token, "arctanh(", 8))
        return SPECIFIER_OF_ARCTANH;
    if (!strncmp(expression + token, "coth(", 5))
        return SPECIFIER_OF_COTH;
    if (!strncmp(expression + token, "arccoth(", 8))
        return SPECIFIER_OF_ARCCOTH;
    if (!strncmp(expression + token, "dif(", 4))
        return SPECIFIER_OF_DIF;
    if (!strncmp(expression + token, "integral(", 9))
        return SPECIFIER_OF_INTEGRAL;
    if (!strncmp(expression + token, "sumsequence(", 12))
        return SPECIFIER_OF_SIGMA_SUM;
    if (!strncmp(expression + token, "productsequence(", 16))
        return SPECIFIER_OF_PRODUCT_OF_SEQUENCE;
    if (!strncmp(expression + token, "permutations(", 13))
        return SPECIFIER_OF_PERMUTATIONS;
    if (!strncmp(expression + token, "combinations(", 13))
        return SPECIFIER_OF_COMBINATIONS;
    if (!strncmp(expression + token, "GCD(", 4))
        return SPECIFIER_OF_GCD;
    if (!strncmp(expression + token, "LCM(", 4))
        return SPECIFIER_OF_LCM;
    return '\0';
}

/*---Parsing Module 1---
Convert math expression from INFIX type to POSTFIX type using Shunting Yard Algorithm

#To add new function:
Step 1: add to macroes
Step 2: add to _operator
Step 3: add to _increase
Step 4: add to precedent_of
Step 5: add to Compute_POSTFIX_expression
Step 6: add to Compute_P_function
*/
_POSTFIX__ Parse(char *expression)
{
    _POSTFIX__ parsed_expression;
    parsed_expression.size = 0;
    parsed_expression.tokens = NULL;

    if (expression == NULL || strlen(expression) < 1)
        return parsed_expression;

    /* --------------------Pre-processing--------------------
    1/ Make a copy of original expression
    2/ Errors format handling
    3/ Clear blanks in expression
    4/ Allocate memories
    5/ Specify expression
    6/ Re-format infix expression
    */

    // 1. Create a copy
    int len = strlen(expression);
    char *copy_expression = (char *)calloc(len + 1, sizeof(char));
    if (copy_expression == NULL)
    {
        perror("Failed to make a copy of expression");
        return parsed_expression;
    }
    strcpy(copy_expression, expression);

    // 2. Clear blanks
    {
        for (int i = 0; i < len; i++)
        {
            if (copy_expression[i] == ' ')
            {
                for (int k = i; k < len - 1; k++)
                {
                    copy_expression[k] = copy_expression[k + 1];
                }
                --len;
                --i; // Stay at the same index to check the new character at this position
            }
        }

        char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
        if (temp == NULL)
        {
            perror("Clear blanks");
            free(copy_expression);
            return parsed_expression;
        }
        copy_expression = temp;
        copy_expression[len] = '\0';
    }

    // 3. Errors subtraction, addition, floating point number & parenthesis handling
    {
        // Defensive: check for non-empty string before accessing [0]
        if (len > 0 && (copy_expression[0] == '-' || copy_expression[0] == '+'))
        {
            char *temp = (char *)realloc(copy_expression, (len + 2) * sizeof(char));
            if (temp == NULL)
            {
                perror("Subtraction errors handling 1");
                free(copy_expression);
                return parsed_expression;
            }
            copy_expression = temp;

            for (int k = len; k >= 1; k--)
                copy_expression[k] = copy_expression[k - 1];
            copy_expression[0] = '0';
            len++;
            copy_expression[len] = '\0';
        }

        // if the '-' OR '+' stays next to '('   E.g:  2^(-3.5)
        for (int i = 1; i < len; i++) // start from 1 to avoid out-of-bounds
        {
            if ((copy_expression[i] == '-' || copy_expression[i] == '+') && copy_expression[i - 1] == '(')
            {
                char *temp = (char *)realloc(copy_expression, (len + 2) * sizeof(char));
                if (temp == NULL)
                {
                    perror("Subtraction errors handling 2");
                    free(copy_expression);
                    return parsed_expression;
                }
                copy_expression = temp;

                for (int k = len; k >= i + 1; k--)
                    copy_expression[k] = copy_expression[k - 1];
                copy_expression[i] = '0';
                len++;
                copy_expression[len] = '\0';
            }
        }

        // Special cases of floating point number: .5  or .093
        for (int i = 0; i < len; i++)
        {
            if (i < len - 1 && !isdigit(copy_expression[i + 1]) && copy_expression[i] == '.')
            {
                free(copy_expression);
                return parsed_expression;
            }

            else if (copy_expression[i] == '.' && (i == 0 || !isdigit(copy_expression[i - 1])) && copy_expression[i - 1] != 't')
            {
                len++;
                char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
                if (temp == NULL)
                {
                    perror("Floating point number failed");
                    free(copy_expression);
                    return parsed_expression;
                }
                copy_expression = temp;
                copy_expression[len] = '\0';

                for (int k = len - 1; k > i; k--)
                    copy_expression[k] = copy_expression[k - 1];

                copy_expression[i] = '0';
                i++;
            }
        }

        // Special cases of parenthesis
        int open = 0, close = 0;
        for (int i = 0; i < len; i++)
        {
            if (copy_expression[i] == '(')
                open++;
            else if (copy_expression[i] == ')')
                close++;
        }

        if (close < open)
        {
            len += open - close;
            char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
            if (temp == NULL)
            {
                perror("Failed to handle parenthesis");
                free(copy_expression);
                return parsed_expression;
            }
            copy_expression = temp;

            copy_expression[len] = '\0';
            for (int i = 0; i < open - close; i++)
                copy_expression[len - 1 - i] = ')';
        }
        else if (open < close)
        {
            free(copy_expression);
            return parsed_expression;
        }
    }

    // Test
    // printf("Re-format: %s | Len = %d\n", copy_expression, len);

    // 4. Allocate memories

    _infix_ *infix_exp = (_infix_ *)malloc(len * sizeof(_infix_));
    if (infix_exp == NULL)
    {
        perror("Failed to allocate infix copy_expression");
        free(copy_expression);
        return parsed_expression;
    }
    for (int i = 0; i < len; i++)
    {
        infix_exp[i].num = NAN;
        infix_exp[i].operator= '\0';
        infix_exp[i].variable = '\0';
    }

    // 5. Specify copy_expression
    int infix_len = 0;
    char _op_;
    for (int i = 0; i < len; i++)
    {
        _op_ = _operator__(copy_expression, i);

        // If it's a number or constant or variable
        if (_op_ == '\0')
        {
            // --Number--
            if (isdigit(copy_expression[i]))
            {
                char *str_num = (char *)calloc(26, sizeof(char)); // Max num len = 26
                if (str_num == NULL)
                {
                    perror("Failed to allocate str_num");
                    free(copy_expression);
                    free(infix_exp);
                    return parsed_expression;
                }

                int j = 0;
                // separate to another array
                while ((isdigit(copy_expression[i]) || copy_expression[i] == '.') && j < 26)
                    str_num[j++] = copy_expression[i++];

                // convert to double and store to output queue
                (infix_exp[infix_len++]).num = atof(str_num);

                // reset str_num
                free(str_num);

                --i;
                continue;
            }

            //--Place down constants--
            else if (copy_expression[i] == 'e')
            {
                infix_exp[infix_len++].num = EULER_NUMBER;
                continue;
            }

            else if (copy_expression[i] == 'p' && copy_expression[i + 1] == 'i')
            {
                infix_exp[infix_len++].num = PI;
                i++;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt2", 5))
            {
                infix_exp[infix_len++].num = SQRT_2;
                i += 4;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt.5", 6))
            {
                infix_exp[infix_len++].num = SQRT_2_2;
                i += 5;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt3", 5))
            {
                infix_exp[infix_len++].num = SQRT_3;
                i += 4;
                continue;
            }

            else if (copy_expression[i] == 'g' && copy_expression[i + 1] != 'a')
            {
                infix_exp[infix_len++].num = _G_;
                continue;
            }

            else if (copy_expression[i] == 'l' && copy_expression[i + 1] == 'n' && copy_expression[i + 2] == '2')
            {
                infix_exp[infix_len++].num = LN_2;
                i += 2;
                continue;
            }

            else if (copy_expression[i] == 'c' && copy_expression[i - 1] != 'e' && copy_expression[i - 1] != 's' && copy_expression[i + 1] != 'o' && copy_expression[i + 1] != 's')
            {
                infix_exp[infix_len++].num = _C_;
                continue;
            }

            //-Replace variable with specifier-
            else
            {
                infix_exp[infix_len++].variable = copy_expression[i];
                continue;
            }
        }

        // If it's an operator or available function
        else
        {
            infix_exp[infix_len++].operator= _op_;
            _increase_(&i, _op_);
        }
    }

    // Re-size infix_exp
    _infix_ *temp_ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
    if (temp_ == NULL)
    {
        perror("Failed to shrink infix_exp");
        free(infix_exp);
        free(copy_expression);
        return parsed_expression;
    }
    infix_exp = temp_;

    free(copy_expression);

    // Test infix
    /* printf("RAW INFIX EXPRESSION:\n\n");
    for (int i = 0; i < infix_len; i++)
    {
        if (!isnan(infix_exp[i].num))
            printf("NUM = %.9lf", infix_exp[i].num);
        if (infix_exp[i].operator != '\0')
            printf("OP = %c", infix_exp[i].operator);
        if (infix_exp[i].variable != '\0')
            printf("VAR = %c", infix_exp[i].variable);
        printf("\n");
    }
    printf("Token len = %d\n", infix_len); */

    // 6. Re-format infix_exp to handle errors and missing tokens

    // Left-side of tokens
    {
        for (int i = 1; i < infix_len; i++)
        {
            // Num or var
            if ((!isnan(infix_exp[i].num) || infix_exp[i].variable != '\0') &&
                (!isnan(infix_exp[i - 1].num)         //!= NAN
                 || infix_exp[i - 1].variable != '\0' // ís variable
                 || infix_exp[i - 1].operator== ')'))
            {
                infix_len++;
                _infix_ *temp__ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
                if (temp__ == NULL)
                {
                    perror("Failed to realloc infix_exp");
                    free(infix_exp);
                    return parsed_expression;
                }
                infix_exp = temp__;

                for (int k = infix_len - 1; k > i; k--)
                {
                    infix_exp[k].num = infix_exp[k - 1].num;
                    infix_exp[k].variable = infix_exp[k - 1].variable;
                    infix_exp[k].operator= infix_exp[k - 1].operator;
                }
                infix_exp[i].num = NAN;
                infix_exp[i].variable = '\0';
                infix_exp[i].operator= '*';
            }

            // Special cases of operator
            else if ((infix_exp[i].operator== '+' ||
                      infix_exp[i]
                          .operator== '-' ||
                      infix_exp[i]
                          .operator== '*' ||
                      infix_exp[i]
                          .operator== '/' ||
                      infix_exp[i]
                          .operator== '^' ||
                      infix_exp[i]
                          .operator== '%' ||
                      infix_exp[i]
                          .operator== '!') &&
                     infix_exp[i - 1].operator!= '\0' &&
                     infix_exp[i - 1]
                         .operator!= ')')
            {
                free(infix_exp);
                return parsed_expression;
            }
        }

        // Right-side of tokens
        for (int i = 1; i < infix_len - 1; i++)
        {
            // Num of var
            if ((!isnan(infix_exp[i].num) || infix_exp[i].variable != '\0') &&
                (infix_exp[i + 1].operator!= '+' &&
                 infix_exp[i + 1]
                     .operator!= '-' &&
                 infix_exp[i + 1]
                     .operator!= '*' &&
                 infix_exp[i + 1]
                     .operator!= '/' &&
                 infix_exp[i + 1]
                     .operator!= '^' &&
                 infix_exp[i + 1]
                     .operator!= '%' &&
                 infix_exp[i + 1]
                     .operator!= '!' &&
                 infix_exp[i + 1]
                     .operator!= ')' &&
                 infix_exp[i + 1]
                     .operator!= '\0'))
            {
                i++;
                infix_len++;
                _infix_ *temp__ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
                if (temp__ == NULL)
                {
                    perror("Failed to realloc infix_exp");
                    free(infix_exp);
                    return parsed_expression;
                }
                infix_exp = temp__;

                for (int k = infix_len - 1; k > i; k--)
                {
                    infix_exp[k].num = infix_exp[k - 1].num;
                    infix_exp[k].variable = infix_exp[k - 1].variable;
                    infix_exp[k].operator= infix_exp[k - 1].operator;
                }
                infix_exp[i].num = NAN;
                infix_exp[i].variable = '\0';
                infix_exp[i].operator= '*';
            }

            // Special case of parenthesis
            else if (infix_exp[i].operator== '(' && infix_exp[i + 1].operator== ')' && isnan(infix_exp[i + 1].num))
            {
                free(infix_exp);
                return parsed_expression;
            }

            // Special cases of the left-side of close bracket
            else if (isnan(infix_exp[i].num) && infix_exp[i].variable == '\0' && infix_exp[i].operator!= ')' && infix_exp[i + 1].operator== ')')
            {
                free(infix_exp);
                return parsed_expression;
            }
        }

        // Special cases at the beginning of the expression
        if (infix_exp[0].operator== '+' ||
            infix_exp[0]
                .operator== '-' ||
            infix_exp[0]
                .operator== '*' ||
            infix_exp[0]
                .operator== '/' ||
            infix_exp[0]
                .operator== '^' ||
            infix_exp[0]
                .operator== '!' ||
            infix_exp[0]
                .operator== '%' ||
            infix_exp[0]
                .operator== ')')
        {
            free(infix_exp);
            return parsed_expression;
        }

        // Special cases at the end of the expression
        if (infix_exp[infix_len - 1].operator== '+' ||
            infix_exp[infix_len - 1]
                .operator== '-' ||
            infix_exp[infix_len - 1]
                .operator== '*' ||
            infix_exp[infix_len - 1]
                .operator== '/' ||
            infix_exp[infix_len - 1]
                .operator== '^' ||
            infix_exp[infix_len - 1]
                .operator== '(')
        {
            free(infix_exp);
            return parsed_expression;
        }
    }

    // After pre-processing
    /* printf("AFTER PRE-PROCESSING INFIX EXPRESSION:\n\n");
    for (int i = 0; i < infix_len; i++)
    {
        if (!isnan(infix_exp[i].num))
            printf("NUM = %.9lf", infix_exp[i].num);
        if (infix_exp[i].operator != '\0')
            printf("OP = %c", infix_exp[i].operator);
        if (infix_exp[i].variable != '\0')
            printf("VAR = %c", infix_exp[i].variable);
        printf("\n");
    }
    printf("Token len = %d\n", infix_len); */

    /* --------------------Parsing processor-------------------- */
    // Create memories for parsing
    _TOKENS_DATA_ *P_expression = (_TOKENS_DATA_ *)malloc(infix_len * sizeof(_TOKENS_DATA_));
    if (P_expression == NULL)
    {
        perror("Failed to create P_expression");
        free(infix_exp);
        return parsed_expression;
    }
    // Initialize P_expression with "empty" values
    for (int i = 0; i < infix_len; i++)
    {
        P_expression[i].num = NAN;
        P_expression[i].operator= '\0';
        P_expression[i].variable = '\0';
    }

    char *ope_stack = (char *)calloc(infix_len + 1, sizeof(char));
    if (ope_stack == NULL)
    {
        perror("Failed to create ope_stack");
        free(infix_exp);
        free(P_expression);
        return parsed_expression;
    }

    // Processor
    int P_index = 0;
    int ope_index = 0;
    for (int i = 0; i < infix_len; i++)
    {
        double _num_ = infix_exp[i].num;
        char _op_ = infix_exp[i].operator;
        char _var_ = infix_exp[i].variable;

        // If the current token is a number or variable --> store to output stack
        if (!isnan(_num_))
        {
            P_expression[P_index++].num = _num_;
        }

        else if (_var_ != '\0')
        {
            P_expression[P_index++].variable = _var_;
        }

        // Else, if it's an operator
        else
        {
            // If it's the first op
            if (ope_index == 0 && ope_stack[0] == '\0')
            {
                ope_stack[ope_index++] = _op_;
            }

            // If the current op has a greater precedence than the last op in the stack OR it's an open bracket
            else if (precedent_of(ope_stack[ope_index - 1]) < precedent_of(_op_) || _op_ == '(')
            {
                ope_stack[ope_index++] = _op_;
            }

            // If the current op has a lower precedence than the last op in the stack
            else if (_op_ != ')')
            {
                while (precedent_of(_op_) <= precedent_of(ope_stack[ope_index - 1]) && ope_index > 0)
                {
                    P_expression[P_index++].operator= ope_stack[ope_index - 1];
                    ope_stack[--ope_index] = '\0';
                }
                ope_stack[ope_index++] = _op_;
            }

            // If it's a close bracket
            else if (_op_ == ')')
            {
                while (ope_stack[ope_index - 1] != '(' && ope_index > 0)
                {
                    P_expression[P_index++].operator= ope_stack[ope_index - 1];
                    ope_stack[--ope_index] = '\0';
                }
                ope_stack[--ope_index] = '\0';
            }
        }
    }

    // Push all the remaining op in the ope_stack to output stack
    while (ope_index > 0)
    {
        P_expression[P_index++].operator= ope_stack[--ope_index];
    }

    /* ----------After parsing---------- */
    /* printf("\nAFTER PARSING\n");
    for (int i = 0; i < P_index; i++)
    {
        double _num_ = P_expression[i].num;
        char _var_ = P_expression[i].variable;
        char _op_ = P_expression[i].operator;

        if(!isnan(_num_)) printf("Num = %.9lf\n", _num_);
        if(_var_ != '\0') printf("Var = %c\n", _var_);
        if(_op_ != '\0') printf("OP = %c\n", _op_);
    }
    printf("P_index = %d\n", P_index); */

    // Return final results
    parsed_expression.size = P_index;
    parsed_expression.tokens = P_expression;

    free(infix_exp);
    free(ope_stack);
    return parsed_expression;
}

double evaluate_I_exp(__INFIX__ I_exp)
{
    if (I_exp.tokens == NULL || I_exp.size < 1)
        return NAN;
    // safety: make a copy
    __INFIX__ copyof_I_exp;
    copyof_I_exp.size = I_exp.size;
    copyof_I_exp.tokens = (_infix_ *)calloc(I_exp.size, sizeof(_infix_));
    if (!copyof_I_exp.tokens)
        return NAN;
    for (int i = 0; i < I_exp.size; i++)
    {
        copyof_I_exp.tokens[i].num = I_exp.tokens[i].num;
        copyof_I_exp.tokens[i].operator= I_exp.tokens[i].operator;
        copyof_I_exp.tokens[i].variable = I_exp.tokens[i].variable;
    }

    if (!handle_special_functions_(&copyof_I_exp))
    {
        free(copyof_I_exp.tokens);
        return NAN;
    }

    _POSTFIX__ P_exp = submodule_Parse(copyof_I_exp);
    double result = Compute_P_expression(P_exp);

    free(copyof_I_exp.tokens);
    free(P_exp.tokens);

    return result;
}

/*
This module compute the value of a math expression in term of a string
#Supporting:
--Arithmetic operators: + - * / % ^ ! ( )
--Trig functions: sin() cos() tan() cot() sec() csc() arcsin() arccos() arctan() arccot()
--Hyperbolic functions: sinh() cosh() tanh() coth() arcsinh() arccosh() arctanh() arccoth()
--Logarithmic function: ln() & log(). If you want to calculate log(3,10), try using ln(10)/ln(3) instead
--Square & cube root function: sqrt() & cbrt()
--Absolute value function: abs()
--Other functions: gamma() ceil() floor() lambertw()

#NO supported variables
#If you want to calculate the n-th root of x (for n > 3), use exponentiation like x^(1/n) instead
#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double value = evaluate("1 - 2 * 3^(-4.5)");
//value is now containing 0.9857444378

double result = evaluate("arctan(tan(e^(-lambertw(pi))))");
//result is now equal to  0.3417560178
*/
double evaluate(char *expression)
{
    if (expression == NULL || expression[0] == '\0')
        return NAN;

    __INFIX__ I_exp = convert_string_to_INFIX(expression);

    double result = evaluate_I_exp(I_exp);

    free(I_exp.tokens);
    return result;
}

//==========================================================//
//==========================================================//
//==========================================================//

/*
This module compute the left-sided limit of a function when x tends to x0 in term of a string
#Supporting:
--Arithmetic operators: + - * / % ^ ! ( )
--Trig functions: sin() cos() tan() cot() sec() csc() arcsin() arccos() arctan() arccot()
--Hyperbolic functions: sinh() cosh() tanh() coth() arcsinh() arccosh() arctanh() arccoth()
--Logarithmic function: ln() & log(). If you want to calculate log(3,10), try using ln(10)/ln(3) instead
--Square & cube root function: sqrt() & cbrt()
--Absolute value function: abs()
--Other functions: gamma() ceil() floor() lambertw()

#If you want to calculate the n-th root of x (for n > 3), use exponentiation like x^(1/n) instead
#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double L = limit_left("cos(x)/x", 0)
//output: L = -infinity
*/
double limit_left(char *function, const char _varriable_, const double _x_)
{
    _POSTFIX__ P_expression = Parse(function);

    if (P_expression.size == 0 || P_expression.tokens == NULL)
        return NAN;

    for (int i = 0; i < P_expression.size; i++)
    {
        if (P_expression.tokens[i].variable == _varriable_)
        {
            P_expression.tokens[i].num = _x_ - 1e-12;
            P_expression.tokens[i].variable = '\0';
        }
    }

    double result = Compute_P_expression(P_expression);
    free(P_expression.tokens);

    return result;
}

/*
This module compute the right-sided limit of a function when x tends to x0 in term of a string
#Supporting:
--Arithmetic operators: + - * / % ^ ! ( )
--Trig functions: sin() cos() tan() cot() sec() csc() arcsin() arccos() arctan() arccot()
--Hyperbolic functions: sinh() cosh() tanh() coth() arcsinh() arccosh() arctanh() arccoth()
--Logarithmic function: ln() & log(). If you want to calculate log(3,10), try using ln(10)/ln(3) instead
--Square & cube root function: sqrt() & cbrt()
--Absolute value function: abs()
--Other functions: gamma() ceil() floor() lambertw()

#If you want to calculate the n-th root of x (for n > 3), use exponentiation like x^(1/n) instead
#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double L = limit_right("cos(x/e)/x", 0);
//output: L = infinity
*/
double limit_right(char *function, const char _varriable_, const double _x_)
{
    _POSTFIX__ P_expression = Parse(function);

    if (P_expression.size == 0 || P_expression.tokens == NULL)
        return NAN;

    for (int i = 0; i < P_expression.size; i++)
    {
        if (P_expression.tokens[i].variable == _varriable_)
        {
            P_expression.tokens[i].num = _x_ + 1e-12;
            P_expression.tokens[i].variable = '\0';
        }
    }

    double result = Compute_P_expression(P_expression);
    free(P_expression.tokens);

    return result;
}

/*
This module compute the limit of a function when x tends to x0 in term of a string
#Supporting:
--Arithmetic operators: + - * / % ^ ! ( )
--Trig functions: sin() cos() tan() cot() sec() csc() arcsin() arccos() arctan() arccot()
--Hyperbolic functions: sinh() cosh() tanh() coth() arcsinh() arccosh() arctanh() arccoth()
--Logarithmic function: ln() & log(). If you want to calculate log(3,10), try using ln(10)/ln(3) instead
--Square & cube root function: sqrt() & cbrt()
--Absolute value function: abs()
--Other functions: gamma() ceil() floor() lambertw()

#If you want to calculate the n-th root of x (for n > 3), use exponentiation like x^(1/n) instead
#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double L = limit("sin(x)/x");
//output: L = 1
*/
double limit(char *function, const char _variable_, const double _x_)
{
    _POSTFIX__ P_expression = Parse(function);

    if (P_expression.size == 0 || P_expression.tokens == NULL)
        return NAN;

    for (int i = 0; i < P_expression.size; i++)
    {
        if (P_expression.tokens[i].variable == _variable_)
        {
            P_expression.tokens[i].num = _x_ - 1e-12;
        }
    }

    double left = Compute_P_expression(P_expression);

    for (int i = 0; i < P_expression.size; i++)
    {
        if (P_expression.tokens[i].variable == _variable_)
        {
            P_expression.tokens[i].num = _x_ + 1e-12;
            P_expression.tokens[i].variable = '\0';
        }
    }

    double right = Compute_P_expression(P_expression);

    free(P_expression.tokens);

    if (fabs(left - right) < 1e-5)
    {
        return (left + right) / 2;
    }

    return NAN;
}

//==========================================================//
//=================Differentiation Modules==================//
//==========================================================//

void Least_Operator(char *expression, char *L_O, int *pos_of_op)
{
    /*==================================================
    Pre-processing:
    1/ Calculate the length of the expression
    2/ Create stacks and output storages
    ==================================================*/

    // calculate the expression's length
    int exp_len = 0;
    while (expression[exp_len] != '\0')
        exp_len++;

    // test
    //  printf("refined string: %s | strlen = %d\n", expression, exp_len);

    // create stack for parsing
    typedef struct
    {
        char _op_;
        int pos;
    } _Op_Pos_;

    _Op_Pos_ *output_queue = (_Op_Pos_ *)malloc(exp_len * sizeof(_Op_Pos_));
    if (output_queue == NULL)
    {
        perror("Error");
        return;
    }
    for (int i = 0; i < exp_len; i++)
    {
        output_queue[i]._op_ = '\0';
        output_queue[i].pos = -1;
    }

    _Op_Pos_ *ope_stack = (_Op_Pos_ *)malloc(exp_len * sizeof(_Op_Pos_));
    if (ope_stack == NULL)
    {
        perror("Error");
        return;
    }
    for (int i = 0; i < exp_len; i++)
    {
        ope_stack[i]._op_ = '\0';
        ope_stack[i].pos = -1;
    }

    /*----------------------------------------------------
    Parsing processor
    Turn the expression from INFIX type into POSTFIX type
    ----------------------------------------------------*/
    int output_index = 0;
    int ope_index = 0;
    for (int token = 0; token < exp_len; token++)
    {
        //--------Skip for constants & variables--------//
        if (expression[token] == 'p' && expression[token + 1] == 'i')
        {
            token++;
            continue;
        }

        if (!strncmp(expression + token, "sqrt2", 5))
        {
            token += 4;
            continue;
        }

        if (!strncasecmp(expression + token, "sqrt.5", 6))
        {
            token += 5;
            continue;
        }

        if (!strncmp(expression + token, "sqrt3", 5))
        {
            token += 4;
            continue;
        }

        if (expression[token] == 'g' && expression[token + 1] != 'a')
            continue;

        if (expression[token] == 'l' && expression[token + 1] == 'n' && expression[token + 2] == '2')
        {
            token += 2;
            continue;
        }

        if (isdigit(expression[token]) || expression[token] == '.' || expression[token] == 'x' || expression[token] == ' ' || expression[token] == 'e')
            continue;
        //----------------------------------------------//

        // sorting operators
        while (1)
        {
            if (ope_stack[0]._op_ == '\0')
            {
                ope_stack[ope_index]._op_ = _operator__(expression, token);
                _increase_(&token, ope_stack[ope_index]._op_);
                ope_stack[ope_index++].pos = token;
                // printf("%s\n", ope_stack->_op_);
                break;
            }
            else if (precedent_of(ope_stack[ope_index - 1]._op_) < precedent_of(_operator__(expression, token)) || expression[token] == '(')
            {
                ope_stack[ope_index]._op_ = _operator__(expression, token);
                _increase_(&token, ope_stack[ope_index]._op_);
                ope_stack[ope_index++].pos = token;
                // printf("%s\n", ope_stack->_op_);
                break;
            }
            else if (expression[token] == ')' && ope_stack[ope_index - 1]._op_ == '(')
            {
                ope_stack[ope_index - 1]._op_ = '\0';
                ope_stack[--ope_index].pos = -1;
                // printf("%s\n", ope_stack->_op_);
                break;
            }
            else
            {
                output_queue[output_index]._op_ = ope_stack[ope_index - 1]._op_;
                output_queue[output_index++].pos = ope_stack[ope_index - 1].pos;
                ope_stack[ope_index - 1]._op_ = '\0';
                ope_stack[--ope_index].pos = -1;
                // printf("%s\n", ope_stack->_op_);
            }
        }
    }

    // push the all remaining operators to output_queue
    while (ope_index > 0)
    {
        output_queue[output_index]._op_ = ope_stack[ope_index - 1]._op_;
        output_queue[output_index++].pos = ope_stack[--ope_index].pos;
    }

    // results
    if (output_index > 0)
    {
        output_queue = (_Op_Pos_ *)realloc(output_queue, output_index * sizeof(_Op_Pos_));
        (*L_O) = output_queue[output_index - 1]._op_;      // return the least operator
        (*pos_of_op) = output_queue[output_index - 1].pos; // return the position of the least operator
    }
    // constant & variable only
    else
    {
        (*L_O) = '|';     // empty
        (*pos_of_op) = 0; // return the first index
    }

    free(ope_stack);
    free(output_queue);
}

void re_format(char **expression)
{
    if (expression == NULL || *expression == NULL)
    {
        fprintf(stderr, "Null pointer passed to re_format\n");
        return;
    }

    // clear all blanks in the string
    int len = strlen_of_((*expression));
    {
        int blank = 0;
        for (int i = 0; i < len; i++)
        {
            if ((*expression)[i] == ' ')
            {
                for (int k = i; k < len - 1; k++)
                {
                    (*expression)[k] = (*expression)[k + 1];
                }
                --len;
                --i; // Stay at the same index to check the new character at this position
            }
        }

        (*expression) = (char *)realloc((*expression), (len + 1) * sizeof(char));
        if ((*expression) == NULL)
        {
            perror("Clear blanks");
            return;
        }
        (*expression)[len] = '\0';
    }

    // subtraction errors handling
    {
        // Defensive: check for non-empty string before accessing [0]
        if (len > 0 && (*expression)[0] == '-')
        {
            (*expression) = (char *)realloc((*expression), (len + 2) * sizeof(char));
            if ((*expression) == NULL)
            {
                perror("Subtraction errors handling 1");
                return;
            }

            for (int k = len; k >= 1; k--)
                (*expression)[k] = (*expression)[k - 1];
            (*expression)[0] = '0';
            len++;
            (*expression)[len] = '\0';
        }

        // if the '-' stays next to '('   E.g:  2^(-3.5)
        for (int i = 1; i < len; i++) // start from 1 to avoid out-of-bounds
        {
            if ((*expression)[i] == '-' && (*expression)[i - 1] == '(')
            {
                (*expression) = (char *)realloc((*expression), (len + 2) * sizeof(char));
                if ((*expression) == NULL)
                {
                    perror("Subtraction errors handling 2");
                    return;
                }
                for (int k = len; k >= i + 1; k--)
                    (*expression)[k] = (*expression)[k - 1];
                (*expression)[i] = '0';
                len++;
                (*expression)[len] = '\0';
            }
        }
    }

    // multiplication errors handling
    {
        for (int i = 0; i < len; i++)
        {
            if ((*expression)[i] == 'x')
            {
                // Left-side of x
                if (i > 0 &&
                    (*expression)[i - 1] != '=' &&
                    (*expression)[i - 1] != '-' &&
                    (*expression)[i - 1] != '+' &&
                    (*expression)[i - 1] != '/' &&
                    (*expression)[i - 1] != '*' &&
                    (*expression)[i - 1] != '^' &&
                    (*expression)[i - 1] != '(')
                {
                    ++len;
                    (*expression) = (char *)realloc((*expression), (len + 1) * sizeof(char));
                    if ((*expression) == NULL)
                    {
                        perror("Multiply case 2");
                        return;
                    }
                    (*expression)[len] = '\0';
                    for (int k = len - 1; k > i; k--)
                        (*expression)[k] = (*expression)[k - 1];
                    (*expression)[i] = '*';
                    // ++i;
                }
                // Right-side of x
                else if (i < len - 1 &&
                         (*expression)[i + 1] != ')' &&
                         (*expression)[i + 1] != '-' &&
                         (*expression)[i + 1] != '+' &&
                         (*expression)[i + 1] != '*' &&
                         (*expression)[i + 1] != '/' &&
                         (*expression)[i + 1] != '^' &&
                         (*expression)[i + 1] != '=')
                {
                    ++i;
                    ++len;
                    (*expression) = (char *)realloc((*expression), (len + 1) * sizeof(char));
                    if ((*expression) == NULL)
                    {
                        perror("Multiply case 2");
                        return;
                    }
                    (*expression)[len] = '\0';
                    for (int k = len - 1; k > i; k--)
                        (*expression)[k] = (*expression)[k - 1];
                    (*expression)[i] = '*';
                }
            }
        }
    }
}

void brackets_check(char **function)
{
    int len = strlen(*function);

    int open = 0;
    int close = 0;
    for (int i = 0; i < len; i++)
    {
        if ((*function)[i] == '(')
            open++;
        if ((*function)[i] == ')')
            close++;
    }

    if (open > close)
    {
        int leftover = open - close;
        for (int i = 0; i < len; i++)
            (*function)[i] = (*function)[i + leftover];
        len -= leftover;
        (*function) = (char *)realloc((*function), (len + 1) * sizeof(char));
        if ((*function) == NULL)
        {
            perror("Open > Close");
            return;
        }
        (*function)[len] = '\0';
        return;
    }
    if (open < close)
    {
        len -= close - open;
        (*function) = (char *)realloc((*function), (len + 1) * sizeof(char));
        if ((*function) == NULL)
        {
            perror("Close > Open");
            return;
        }
        (*function)[len] = '\0';
        return;
    }
}

//==========================================================//
//==========================================================//
//==========================================================//

/*This module will approximate the value of a finite integral using Simpson's rule
#UNSUPPORTED functions: ceil() floor()

#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double result = integral("e^x", 1, 2);
// output: result = 4.670774270471628
*/
double integral_definite(char *function, const char var, const double lower_bound, const double upper_bound)
{
    double result;
    _POSTFIX__ P_function = Parse(function);

    if (P_function.size == 0 || P_function.tokens == NULL)
        return NAN;

    double n = 1000; // Number of subintervals - Larger n --> More accurate
    double a, b, h;
    char str_var[2] = {var, '\0'};

    if (lower_bound != -INFINITY && lower_bound != INFINITY && upper_bound != INFINITY && upper_bound != -INFINITY)
    {
        a = lower_bound;
        b = upper_bound;
        h = (b - a) / n;
    }

    // Beta version; may return wrong values
    else
    {
        a = (double)((lower_bound == -INFINITY) ? -100000 : 100000);
        b = (double)((upper_bound == INFINITY) ? 100000 : -100000);
        // printf("a = %lf | b = %lf\n", a, b);
        h = (b - a) / (1000 * n);
    }

    // apply simpson's rule
    result = Compute_P_function(P_function, str_var, a) + Compute_P_function(P_function, str_var, b);
    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        double coefficient;
        if ((int)i % 2 == 0)
            coefficient = 2;
        else
            coefficient = 4;

        result += coefficient * Compute_P_function(P_function, str_var, x);
    }

    result *= (h / 3);

    free(P_function.tokens);
    return result;
}

/* // Beta version
double Newton_Raphson(_postfix_ *P_f, const int output_index, _postfix_ *P_df, const int output_index_d, double x0)
{
    double x1, f, df;
    for (int i = 0; i < 500; i++)
    {
        f = Compute_P_function(P_f, output_index, x0);
        df = Compute_P_function(P_df, output_index_d, x0);
        if (f == -INFINITY || f == INFINITY || isnan(f) || df == -INFINITY || df == INFINITY || isnan(df))
        {
            // printf("Undefined at x0 = %lf\n", x0);
            if (x0 <= 0)
                x0 += 1;
            else
                x0 -= 1;
            continue;
        }

        x1 = x0 - f / df;
        x0 = x1;
        if (fabs(f) < 1e-15 && i <= 100)
            break;
    }
    if (fabs(x0) < 1e-5)
        return 0;
    else if (fabs(f) < 1e-10)
        return x0;
    else
        return NAN;
} */

/*
===BETA VERSION===
This module solves any equations with respect to 'x'

#UNSUPPORTED functions: ceil() floor()

#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2

#Example usage:
double *solutions = sovle("x^(-x) = 13 / 10", 0, 2);
// OUTPUT: solutions = {0.12727398275335775, 0.67981475533093128, NAN}

double *solutions = sovle("x^(-x) = 1.3", 0.5, 2);
// OUTPUT: solutions = {0.67981475533093128, NAN}

#There's always a NAN value at the end of the solutions array
#Remember to free the array after using
#This module does not always find all the solutions. Try to find other solutions by switching the interval
*/
/* double *solve(char *equation, const double lower_bound, const double upper_bound)
{
    // Re-format the equation
    int len = strlen(equation);
    char *copyof_equation = (char *)malloc((len + 1) * sizeof(char));
    {
        if (copyof_equation == NULL)
        {
            perror("Copy equation");
            return NULL;
        }
        copyof_equation[len] = '\0';
        for (int i = 0; i < len; i++)
            copyof_equation[i] = equation[i];

        // Clear blanks & handle subtraction errors
        re_format(&copyof_equation);
        len = strlen(copyof_equation);

        // Handle special equation without '=' sign and without right hand-side
        int mid = strcspn(copyof_equation, "=");
        if (mid == len)
        {
            len += 2;
            copyof_equation = (char *)realloc(copyof_equation, (len + 1) * sizeof(char));
            if (copyof_equation == NULL)
            {
                perror("Missing '='");
                return NULL;
            }

            copyof_equation[len] = '\0';
            copyof_equation[len - 1] = '0';
            copyof_equation[len - 2] = '=';
        }
        else if (mid == len - 1)
        {
            len++;
            copyof_equation = (char *)realloc(copyof_equation, (len + 1) * sizeof(char));
            if (copyof_equation == NULL)
            {
                perror("Missing right hand side");
                return NULL;
            }

            copyof_equation[len] = '\0';
            copyof_equation[len - 1] = '0';
        }

        // Move right-handside equation to the left
        mid = strcspn(copyof_equation, "=");
        len += 2;
        copyof_equation = (char *)realloc(copyof_equation, (len + 1) * sizeof(char));
        if (equation == NULL)
        {
            perror("Reformat equation");
            return NULL;
        }
        copyof_equation[len] = '\0';
        copyof_equation[len - 1] = ')';

        for (int i = len - 2; i > mid + 1; i--)
            copyof_equation[i] = copyof_equation[i - 1];
        copyof_equation[mid + 1] = '(';
        copyof_equation[mid] = '-';
    }

    // Find the derivative of the equation
    char *d_equation = differentiate(copyof_equation);

    // Turn the equations to Postfix type
    int output_index, output_index_d;
    _postfix_ *P_equation = Parse_math_expression(copyof_equation, &output_index);
    _postfix_ *P_d_equation = Parse_math_expression(d_equation, &output_index_d);

    // Create a set of solutions
    int max_sol = 10;
    int sol_index = 0;
    double *solutions = (double *)malloc(max_sol * sizeof(double));
    if (solutions == NULL)
    {
        perror("Create set of solutions");
        return NULL;
    }

    // printf("F = %s\n DF = %s\n", copyof_equation, d_equation);

    free(d_equation);
    free(copyof_equation);

    // Root solving engine
    {
        // trig function detector
        bool trig = false;
        for (int i = 0; i < output_index; i++)
        {
            if (P_equation[i].operator!= '+' &&
                P_equation[i]
                    .operator!= '-' &&
                P_equation[i]
                    .operator!= '*' &&
                P_equation[i]
                    .operator!= '/' &&
                P_equation[i]
                    .operator!= '^' &&
                P_equation[i]
                    .operator!= SPECIFIER_OF_ABS &&
                P_equation[i]
                    .operator!= SPECIFIER_OF_SQRT &&
                P_equation[i]
                    .operator!= SPECIFIER_OF_CBRT &&
                P_equation[i]
                    .operator!= SPECIFIER_OF_LN &&
                P_equation[i]
                    .operator!= SPECIFIER_OF_LG &&
                P_equation[i]
                    .operator!= '\0')
            {
                trig = true;
                break;
            }
        }

        // =====Stage 1: Using Newton-Raphson method===== //
        if (!trig)
        {
            // Find the smallest root
            double left = Newton_Raphson(P_equation, output_index, P_d_equation, output_index_d, lower_bound);
            // Find the greatest root
            double right = Newton_Raphson(P_equation, output_index, P_d_equation, output_index_d, upper_bound);

            // Store solutions
            if (!isnan(left))
                solutions[sol_index++] = left;
            if (!isnan(right))
                solutions[sol_index++] = right;

            // printf("Left = %.9lf | Right = %.9lf\n", left, right);
        }

        // =====Stage 2: Using bisection method===== //
        int So_large = 1000000000; // 10^9
        // double step, aver_slope = fabs(average_slope(P_equation, output_index, lower_bound, upper_bound));
        double step = (upper_bound - lower_bound) / 1000;
        // if (aver_slope > 6)
        //     aver_slope = 6; // Maximum step
        for (double t = lower_bound; t <= upper_bound; t += step)
        {
            // f(t)
            double f0 = Compute_P_function(P_equation, output_index, t);
            if (isnan(f0) || f0 == -INFINITY || f0 == INFINITY || f0 > So_large || f0 < -So_large)
                continue;
            // f(dt)
            double f1 = Compute_P_function(P_equation, output_index, t + step);
            if (isnan(f1) || f1 == -INFINITY || f1 == INFINITY || f1 > So_large || f1 < -So_large)
                continue;

            // If there exists a solution in range: [t, t + step]
            if (f0 * f1 <= 0 || fabs(f0) < 1e-4)
            {
                double start = t;
                double end = t + step;
                double new_step = (end - start) / 200;
                while (fabs(f0) > 1e-12 && start < end)
                {
                    f0 = Compute_P_function(P_equation, output_index, start);
                    if (isnan(f0) || f0 == -INFINITY || f0 == INFINITY || f0 > So_large || f0 < -So_large)
                    {
                        start += new_step;
                        continue;
                    }
                    f1 = Compute_P_function(P_equation, output_index, start + new_step);
                    if (isnan(f1) || f1 == -INFINITY || f1 == INFINITY || f1 > So_large || f1 < -So_large)
                    {
                        start += new_step;
                        continue;
                    }

                    if (f0 * f1 <= 0)
                    {
                        end = start + new_step;
                        new_step = (end - start) / 200;
                    }
                    else
                        start += new_step;

                    // printf("start = %lf | f0 = %lf | f1 = %lf\n", start, f0, f1);
                }

                if (sol_index >= max_sol)
                {
                    max_sol++;
                    solutions = (double *)realloc(solutions, max_sol * sizeof(double));
                    if (solutions == NULL)
                    {
                        perror("Create more solutions");
                        return NULL;
                    }

                    solutions[sol_index++] = start;
                }
                else
                    solutions[sol_index++] = start;
            }

            // step = fabs(1 / (10 * Compute_P_function(P_d_equation, output_index_d, t)));

            // if (step > aver_slope / 2)
            //     step = aver_slope / 2;
            // else if (step < 1e-3)
            //     step = 1e-3;
        }
    }

    // -----Refine solutions-----//
    // Remove duplicated solutions
    double epsilon = 1e-6; // Tolerance for considering two roots as equal
    int unique_count = 0;
    for (int i = 0; i < sol_index; i++)
    {
        bool is_duplicate = false;
        for (int j = 0; j < unique_count; j++)
        {
            if (fabs(solutions[i] - solutions[j]) < epsilon)
            {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate)
        {
            solutions[unique_count++] = solutions[i];
        }
    }
    sol_index = unique_count;

    // Remove the solutions where it makes the equation undefined
    for (int i = 0; i < sol_index; i++)
    {
        double f = Compute_P_function(P_equation, output_index, solutions[i]);
        if (f == INFINITY || f == -INFINITY || isnan(f) || f > 1000000000 || f < -1000000000 || fabs(f) > epsilon)
        {
            for (int k = i; k < sol_index; k++)
                solutions[k] = solutions[k + 1];
            --sol_index;
        }
    }

    // test
    // printf("Solutions found (in function):\n");
    // for (int i = 0; i < sol_index; i++)
    //     printf("%.9lf  ", solutions[i]);

    // shrink the array & put NAN value at the end
    solutions = (double *)realloc(solutions, (++sol_index) * sizeof(double));
    if (solutions == NULL && sol_index > 0)
    {
        perror("Shrink solutions array");
        return NULL;
    }
    solutions[sol_index - 1] = NAN;

    free(P_equation);
    free(P_d_equation);
    return solutions;
}
 */

/* Function to calculate the average slope of a function in a closed interval [a,b]
double average_slope(_postfix_ *P_function, const int output_index, const double a, const double b)
{
   if (a == b)
   {
       // The interval is a single point; slope is undefined (could return NAN or 0)
       return NAN;
   }
   return (Compute_P_function(P_function, output_index, b) - Compute_P_function(P_function, output_index, a)) / (b - a); // aver slope = (fb - fa) / (b - a)
} */

/* void bisection_v2()
{
    char *function = NULL; // temp
    return;
    char *diff = differentiate(function);
    char *copyof_diff = (char *)malloc((strlen(diff) + 1) * sizeof(char));
    if (copyof_diff == NULL)
    {
        perror("Copyof diff");
        return;
    }
    copyof_diff = strdup(diff);
    copyof_diff[strlen(diff)] = '\0';

    int output_index, output_index_d;
    _postfix_ *P_function = Parse_math_expression(function, &output_index);
    _postfix_ *P_d_function = Parse_math_expression(diff, &output_index_d);
    free(function);
    free(diff);

    double a = -10;
    double b = 10;
    double step;
    double aver_slope = fabs(average_slope(P_function, output_index, a, b));

    for (double t = a; t <= b; t += step)
    {
        step = fabs(1 / (10 * Compute_P_function(P_d_function, output_index_d, t)));

        if (step > aver_slope / 2)
            step = aver_slope / 2;

        // printf("x = %.9lf | Aver_slope = %.9lf | Step = %.9lf\n", t, aver_slope, step);
        printf("x = %.9lf\n", t);
    }
} */

double Compute_P_expression(const _POSTFIX__ P_expression)
{
    if (P_expression.tokens == NULL || P_expression.size == 0)
        return NAN;
    // Make a copy of P_expression
    _POSTFIX__ cloned_exp;
    _TOKENS_DATA_ *new_ptr = (_TOKENS_DATA_ *)malloc(P_expression.size * sizeof(_TOKENS_DATA_));
    if (new_ptr == NULL)
    {
        perror("Failed to create new_ptr");
        return NAN;
    }
    for (int i = 0; i < P_expression.size; i++)
    {
        new_ptr[i].num = P_expression.tokens[i].num;
        new_ptr[i].operator= P_expression.tokens[i].operator;
        new_ptr[i].variable = P_expression.tokens[i].variable;

        // Variable without value
        if (P_expression.tokens[i].variable != '\0' && isnan(new_ptr[i].num))
        {
            new_ptr[i].num = 0;
            new_ptr[i].variable = '\0';
        }
    }
    cloned_exp.tokens = new_ptr;
    cloned_exp.size = P_expression.size;

    while (cloned_exp.size > 1)
    {
        int i;
        char OP = '\0';
        for (i = 0; i < cloned_exp.size; i++)
        {
            if (cloned_exp.tokens[i].operator== '\0')
                continue;

            OP = cloned_exp.tokens[i].operator;

            switch (OP)
            {
            case '+': // addition
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num + cloned_exp.tokens[i - 1].num;
                break;
            case '-': // substraction
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num - cloned_exp.tokens[i - 1].num;
                break;
            case '*': // multiplication
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num * cloned_exp.tokens[i - 1].num;
                break;
            case '/': // division
            {
                if (cloned_exp.tokens[i - 1].num == 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num / cloned_exp.tokens[i - 1].num;
                break;
            }
            case '%': // remainder modulo
            {
                if (!is_integer(cloned_exp.tokens[i - 2].num) || !is_integer(cloned_exp.tokens[i - 1].num))
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 2].num = (double)(((int)cloned_exp.tokens[i - 2].num) % ((int)cloned_exp.tokens[i - 1].num));
                break;
            }
            case '^': // exponential
                cloned_exp.tokens[i - 2].num = pow(cloned_exp.tokens[i - 2].num, cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SIN: // sin
                cloned_exp.tokens[i - 1].num = sin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SINH: // sinh
                cloned_exp.tokens[i - 1].num = sinh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SEC: // sec
                cloned_exp.tokens[i - 1].num = 1 / cos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SECH: // sech
                cloned_exp.tokens[i - 1].num = 1 / cosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSEC: // arcsec
                cloned_exp.tokens[i - 1].num = arcsec(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSECH: // arcsech
                cloned_exp.tokens[i - 1].num = arcsech(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COS: // cos
                cloned_exp.tokens[i - 1].num = cos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COSH: // cosh
                cloned_exp.tokens[i - 1].num = cosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSC: // csc
                cloned_exp.tokens[i - 1].num = 1 / sin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSCH: // csch
                cloned_exp.tokens[i - 1].num = csch(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSC: // arccsc
                cloned_exp.tokens[i - 1].num = arccsc(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSCH: // arccsch
                cloned_exp.tokens[i - 1].num = arccsch(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TAN: // tan
                cloned_exp.tokens[i - 1].num = tan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TANH: // tanh
                cloned_exp.tokens[i - 1].num = tanh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COT: // cot
                cloned_exp.tokens[i - 1].num = 1 / tan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COTH: // coth
                cloned_exp.tokens[i - 1].num = coth(cloned_exp.tokens[i - 1].num);
                break;
            case '!': // factorial
            {
                // Check if it's an integer or not
                if (!is_integer(cloned_exp.tokens[i - 1].num) || cloned_exp.tokens[i - 1].num < 0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                double fac = 1.0;
                double n = cloned_exp.tokens[i - 1].num;
                for (double f = 1.0; f <= n; f++)
                    fac *= f;
                if (fac > __DBL_MAX__)
                    cloned_exp.tokens[i - 1].num = NAN;
                else
                    cloned_exp.tokens[i - 1].num = (double)fac;
                break;
            }
            case SPECIFIER_OF_ARCSIN: // arcsin
                cloned_exp.tokens[i - 1].num = asin(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSINH: // arcsinh
                cloned_exp.tokens[i - 1].num = asinh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOS: // arccos
                cloned_exp.tokens[i - 1].num = acos(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOSH: // arccosh
                cloned_exp.tokens[i - 1].num = acosh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTAN: // arctan
                cloned_exp.tokens[i - 1].num = atan(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTANH: // arctanh
                cloned_exp.tokens[i - 1].num = atanh(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOT: // arccot
            {
                if (cloned_exp.tokens[i - 1].num > 0.0)
                    cloned_exp.tokens[i - 1].num = atan(1.0 / (cloned_exp.tokens[i - 1].num));
                else
                    cloned_exp.tokens[i - 1].num = atan(1.0 / (cloned_exp.tokens[i - 1].num)) + PI;
                break;
            }
            case SPECIFIER_OF_ARCCOTH: // arccoth
                cloned_exp.tokens[i - 1].num = arccoth(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LN: // ln
            {
                if (cloned_exp.tokens[i - 1].num <= 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = log(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_LG: // log10
            {
                if (cloned_exp.tokens[i - 1].num <= 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = log10(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_SQRT: // sqrt
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = sqrt(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_ABS: // abs
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                    cloned_exp.tokens[i - 1].num = -cloned_exp.tokens[i - 1].num;
                break;
            }
            case SPECIFIER_OF_CBRT: // cuberoot
                cloned_exp.tokens[i - 1].num = cbrt(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_GAMMA: // gamma function
            {
                if (cloned_exp.tokens[i - 1].num < 0.0)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = gamma_function(cloned_exp.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_CEIL: // ceiling function
                cloned_exp.tokens[i - 1].num = ceil(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_FLOOR: // floor function
                cloned_exp.tokens[i - 1].num = floor(cloned_exp.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LAMBERTW: // lambert W function
            {
                if (cloned_exp.tokens[i - 1].num < -1.0 / EULER_NUMBER)
                {
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens[i - 1].num = lambertw_real(cloned_exp.tokens[i - 1].num);
                break;
            }
            default:
            {
                free(cloned_exp.tokens);
                return NAN;
            }
            }

            break;
        }

        if ((OP == '-' || OP == '+' || OP == '*' || OP == '/' || OP == '^' || OP == '^' || OP == '%') && !isfinite(cloned_exp.tokens[i - 2].num))
        {
            // puts("-NAN-\n");
            free(cloned_exp.tokens);
            return NAN;
        }
        else if (!isfinite(cloned_exp.tokens[i - 1].num))
        {
            // puts("-NAN-\n");
            free(cloned_exp.tokens);
            return NAN;
        }

        // After completing 1 calculation
        {
            // Re-allocate memories for stack
            if (cloned_exp.tokens[i].operator== '-' || cloned_exp.tokens[i].operator== '+' || cloned_exp.tokens[i].operator== '*' || cloned_exp.tokens[i].operator== '/' || cloned_exp.tokens[i].operator== '^' || cloned_exp.tokens[i].operator== '%')
            {
                // rearrange the stack
                for (int k = i - 1; k < cloned_exp.size - 2; k++)
                {
                    cloned_exp.tokens[k].num = cloned_exp.tokens[k + 2].num;
                    cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 2].operator;
                    cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 2].variable;
                }

                // re-allocate the stack's memories
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_exp.tokens, (cloned_exp.size - 2) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens = temp_ptr;
                cloned_exp.size -= 2;
            }
            else if (cloned_exp.tokens[i].operator!= '\0')
            {
                // rearrange the stack
                for (int k = i; k < cloned_exp.size - 1; k++)
                {
                    cloned_exp.tokens[k].num = cloned_exp.tokens[k + 1].num;
                    cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 1].operator;
                    cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 1].variable;
                }

                // re-allocate the stack's memories
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_exp.tokens, (cloned_exp.size - 1) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_exp.tokens);
                    return NAN;
                }
                cloned_exp.tokens = temp_ptr;
                cloned_exp.size--;
            }
        }
    }

    double result = cloned_exp.tokens[0].num;
    free(cloned_exp.tokens);

    return result;
}

double Compute_P_function(_POSTFIX__ function, char *_variables_, ...)
{
    // Make a copy
    _POSTFIX__ cloned_function;
    _TOKENS_DATA_ *new_ptr = (_TOKENS_DATA_ *)malloc(function.size * sizeof(_TOKENS_DATA_));
    if (new_ptr == NULL)
    {
        perror("Failed to create new_ptr");
        return NAN;
    }
    for (int i = 0; i < function.size; i++)
    {
        new_ptr[i].num = function.tokens[i].num;
        new_ptr[i].operator= function.tokens[i].operator;
        new_ptr[i].variable = function.tokens[i].variable;

        // Variable without value
        if (function.tokens[i].variable != '\0')
        {
            new_ptr[i].num = 0;
        }
    }
    cloned_function.tokens = new_ptr;
    cloned_function.size = function.size;

    va_list args;
    va_start(args, _variables_);

    for (int i = 0; _variables_[i] != '\0'; i++)
    {
        double value = va_arg(args, double);

        for (int k = 0; k < cloned_function.size; k++)
        {
            if (cloned_function.tokens[k].variable == _variables_[i])
            {
                cloned_function.tokens[k].num = value;
                cloned_function.tokens[k].variable = '\0';
            }
        }
    }

    va_end(args);

    // Test
    /* printf("After substitute:\n");
    for (int i = 0; i < function.size; i++)
    {
        char _var_ = cloned_function.tokens[i].variable;
        char _op_ = cloned_function.tokens[i].operator;
        double _num_ = cloned_function.tokens[i].num;

        if (!isnan(_num_))
            printf("Num = %.9lf\n", _num_);
        else if (_var_ != '\0')
            printf("Var = %c\n", _var_);
        else if (_op_ != '\0')
            printf("Op = %c\n", _op_);
    } */

    while (cloned_function.size > 1)
    {
        int i;
        for (i = 0; i < cloned_function.size; i++)
        {
            if (cloned_function.tokens[i].operator== '\0')
                continue;

            switch (cloned_function.tokens[i].operator)
            {
            case '+': // addition
                cloned_function.tokens[i - 2].num = cloned_function.tokens[i - 2].num + cloned_function.tokens[i - 1].num;
                break;
            case '-': // substraction
                cloned_function.tokens[i - 2].num = cloned_function.tokens[i - 2].num - cloned_function.tokens[i - 1].num;
                break;
            case '*': // multiplication
                cloned_function.tokens[i - 2].num = cloned_function.tokens[i - 2].num * cloned_function.tokens[i - 1].num;
                break;
            case '/': // division
            {
                if (cloned_function.tokens[i - 1].num == 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 2].num = cloned_function.tokens[i - 2].num / cloned_function.tokens[i - 1].num;
                break;
            }
            case '%': // remainder modulo
            {
                if (!is_integer(cloned_function.tokens[i - 2].num) || !is_integer(cloned_function.tokens[i - 1].num))
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 2].num = (double)(((int)cloned_function.tokens[i - 2].num) % ((int)cloned_function.tokens[i - 1].num));
                break;
            }
            case '^': // exponential
                cloned_function.tokens[i - 2].num = pow(cloned_function.tokens[i - 2].num, cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SIN: // sin
                cloned_function.tokens[i - 1].num = sin(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SINH: // sinh
                cloned_function.tokens[i - 1].num = sinh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SEC: // sec
                cloned_function.tokens[i - 1].num = 1 / cos(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SECH: // sech
                cloned_function.tokens[i - 1].num = 1 / cosh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSEC: // arcsec
                cloned_function.tokens[i - 1].num = arcsec(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSECH: // arcsech
                cloned_function.tokens[i - 1].num = arcsech(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COS: // cos
                cloned_function.tokens[i - 1].num = cos(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COSH: // cosh
                cloned_function.tokens[i - 1].num = cosh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSC: // csc
                cloned_function.tokens[i - 1].num = 1 / sin(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSCH: // csch
                cloned_function.tokens[i - 1].num = csch(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSC: // arccsc
                cloned_function.tokens[i - 1].num = arccsc(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSCH: // arccsch
                cloned_function.tokens[i - 1].num = arccsch(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TAN: // tan
                cloned_function.tokens[i - 1].num = tan(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TANH: // tanh
                cloned_function.tokens[i - 1].num = tanh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COT: // cot
                cloned_function.tokens[i - 1].num = 1 / tan(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COTH: // coth
                cloned_function.tokens[i - 1].num = coth(cloned_function.tokens[i - 1].num);
                break;
            case '!': // factorial
            {
                // Check if it's an integer or not
                if (!is_integer(cloned_function.tokens[i - 1].num) || cloned_function.tokens[i - 1].num < 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                int fac = 1;
                int n = (int)cloned_function.tokens[i - 1].num;
                for (int f = 1; f <= n; f++)
                    fac *= f;
                cloned_function.tokens[i - 1].num = (double)fac;
                break;
            }
            case SPECIFIER_OF_ARCSIN: // arcsin
                cloned_function.tokens[i - 1].num = asin(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSINH: // arcsinh
                cloned_function.tokens[i - 1].num = asinh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOS: // arccos
                cloned_function.tokens[i - 1].num = acos(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOSH: // arccosh
                cloned_function.tokens[i - 1].num = acosh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTAN: // arctan
                cloned_function.tokens[i - 1].num = atan(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTANH: // arctanh
                cloned_function.tokens[i - 1].num = atanh(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOT: // arccot
            {
                if (cloned_function.tokens[i - 1].num > 0)
                    cloned_function.tokens[i - 1].num = atan(1 / (cloned_function.tokens[i - 1].num));
                else
                    cloned_function.tokens[i - 1].num = atan(1 / (cloned_function.tokens[i - 1].num)) + PI;
                break;
            }
            case SPECIFIER_OF_ARCCOTH: // arccoth
                cloned_function.tokens[i - 1].num = arccoth(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LN: // ln
            {
                if (cloned_function.tokens[i - 1].num <= 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 1].num = log(cloned_function.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_LG: // log10
            {
                if (cloned_function.tokens[i - 1].num <= 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 1].num = log10(cloned_function.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_SQRT: // sqrt
            {
                if (cloned_function.tokens[i - 1].num < 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 1].num = sqrt(cloned_function.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_ABS: // abs
            {
                if (cloned_function.tokens[i - 1].num < 0)
                    cloned_function.tokens[i - 1].num = -cloned_function.tokens[i - 1].num;
                break;
            }
            case SPECIFIER_OF_CBRT: // cuberoot
                cloned_function.tokens[i - 1].num = cbrt(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_GAMMA: // gamma function
            {
                if (cloned_function.tokens[i - 1].num < 0)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 1].num = gamma_function(cloned_function.tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_CEIL: // ceiling function
                cloned_function.tokens[i - 1].num = ceil(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_FLOOR: // floor function
                cloned_function.tokens[i - 1].num = floor(cloned_function.tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LAMBERTW: // lambert W function
            {
                if (cloned_function.tokens[i - 1].num < -1 / EULER_NUMBER)
                {
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens[i - 1].num = lambertw_real(cloned_function.tokens[i - 1].num);
                break;
            }
            default:
                break;
            }

            break;
        }

        // After completing 1 calculation
        {
            // Re-allocate memories for stack
            if (cloned_function.tokens[i].operator== '-' || cloned_function.tokens[i].operator== '+' || cloned_function.tokens[i].operator== '*' || cloned_function.tokens[i].operator== '/' || cloned_function.tokens[i].operator== '^')
            {
                // rearrange the stack
                for (int k = i - 1; k < cloned_function.size - 2; k++)
                {
                    cloned_function.tokens[k].num = cloned_function.tokens[k + 2].num;
                    cloned_function.tokens[k].operator= cloned_function.tokens[k + 2].operator;
                    cloned_function.tokens[k].variable = cloned_function.tokens[k + 2].variable;
                }

                // re-allocate the stack's memories
                --cloned_function.size;
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_function.tokens, (--cloned_function.size) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens = temp_ptr;
            }
            else if (cloned_function.tokens[i].operator!= '\0')
            {
                // rearrange the stack
                for (int k = i; k < cloned_function.size - 1; k++)
                {
                    cloned_function.tokens[k].num = cloned_function.tokens[k + 1].num;
                    cloned_function.tokens[k].operator= cloned_function.tokens[k + 1].operator;
                    cloned_function.tokens[k].variable = cloned_function.tokens[k + 1].variable;
                }

                // re-allocate the stack's memories
                _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(cloned_function.tokens, (--cloned_function.size) * sizeof(_TOKENS_DATA_));
                if (temp_ptr == NULL)
                {
                    perror("Failed to re-allocate the stack's memories");
                    free(cloned_function.tokens);
                    return NAN;
                }
                cloned_function.tokens = temp_ptr;
            }
        }
    }

    double result = cloned_function.tokens[0].num;
    free(cloned_function.tokens);

    return result;
}

double evaluate_function(char *_function_, const char *_variables_, ...)
{
    _POSTFIX__ function = Parse(_function_);

    if (function.size == 0 || function.tokens == NULL)
        return NAN;

    va_list args;
    va_start(args, _variables_);

    for (int i = 0; _variables_[i] != '\0'; i++)
    {
        double value = va_arg(args, double);

        for (int k = 0; k < function.size; k++)
        {
            if (function.tokens[k].variable == _variables_[i])
            {
                function.tokens[k].num = value;
                function.tokens[k].variable = '\0';
            }
        }
    }

    va_end(args);

    double result = Compute_P_expression(function);

    free(function.tokens);

    return result;
}

/* To add new functions:
1/ add to macro
2/ add to _operator_
3/ add to _increase
 */
__INFIX__ convert_string_to_INFIX(char *expression)
{
    __INFIX__ specified_exp;
    specified_exp.size = 0;
    specified_exp.tokens = NULL;

    if (expression == NULL || strlen(expression) < 1)
        return specified_exp;

    /* --------------------Pre-processing--------------------
    1/ Make a copy of original expression
    2/ Errors format handling
    3/ Clear blanks in expression
    4/ Allocate memories
    5/ Specify expression
    6/ Re-format infix expression
    */

    // 1. Create a copy
    int len = strlen(expression);
    char *copy_expression = (char *)calloc(len + 1, sizeof(char));
    if (copy_expression == NULL)
    {
        perror("Failed to make a copy of expression");
        return specified_exp;
    }
    for (int i = 0; i < len; i++)
        copy_expression[i] = expression[i];

    // 2. Clear blanks
    {
        for (int i = 0; i < len; i++)
        {
            if (copy_expression[i] == ' ')
            {
                for (int k = i; k < len - 1; k++)
                {
                    copy_expression[k] = copy_expression[k + 1];
                }
                --len;
                --i; // Stay at the same index to check the new character at this position
            }
        }

        char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
        if (temp == NULL)
        {
            perror("Clear blanks");
            free(copy_expression);
            return specified_exp;
        }
        copy_expression = temp;
        copy_expression[len] = '\0';
    }

    // 3. Errors subtraction, addition, floating point number & parenthesis handling
    {
        // Defensive: check for non-empty string before accessing [0]
        if (len > 0 && (copy_expression[0] == '-' || copy_expression[0] == '+'))
        {
            char *temp = (char *)realloc(copy_expression, (len + 2) * sizeof(char));
            if (temp == NULL)
            {
                perror("Subtraction errors handling 1");
                free(copy_expression);
                return specified_exp;
            }
            copy_expression = temp;

            for (int k = len; k >= 1; k--)
                copy_expression[k] = copy_expression[k - 1];
            copy_expression[0] = '0';
            len++;
            copy_expression[len] = '\0';
        }

        // if the '-' OR '+' stays next to '('   E.g:  2^(-3.5) || ,- || =,
        for (int i = 1; i < len; i++) // start from 1 to avoid out-of-bounds
        {
            if ((copy_expression[i] == '-' || copy_expression[i] == '+') && (copy_expression[i - 1] == '(' || copy_expression[i - 1] == '=' || copy_expression[i - 1] == ','))
            {
                char *temp = (char *)realloc(copy_expression, (len + 2) * sizeof(char));
                if (temp == NULL)
                {
                    perror("Subtraction errors handling 2");
                    free(copy_expression);
                    return specified_exp;
                }
                copy_expression = temp;

                for (int k = len; k >= i + 1; k--)
                    copy_expression[k] = copy_expression[k - 1];
                copy_expression[i] = '0';
                len++;
                copy_expression[len] = '\0';
            }
        }

        // Special cases of floating point number: .5  or .093
        for (int i = 0; i < len; i++)
        {
            if (i < len - 1 && !isdigit(copy_expression[i + 1]) && copy_expression[i] == '.')
            {
                free(copy_expression);
                return specified_exp;
            }

            else if (copy_expression[i] == '.' && (i == 0 || !isdigit(copy_expression[i - 1])) && copy_expression[i - 1] != 't')
            {
                len++;
                char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
                if (temp == NULL)
                {
                    perror("Floating point number failed");
                    free(copy_expression);
                    return specified_exp;
                }
                copy_expression = temp;
                copy_expression[len] = '\0';

                for (int k = len - 1; k > i; k--)
                    copy_expression[k] = copy_expression[k - 1];

                copy_expression[i] = '0';
                i++;
            }
        }

        // Special cases of parenthesis
        int open = 0, close = 0;
        for (int i = 0; i < len; i++)
        {
            if (copy_expression[i] == '(')
                open++;
            else if (copy_expression[i] == ')')
                close++;
        }

        if (close < open)
        {
            len += open - close;
            char *temp = (char *)realloc(copy_expression, (len + 1) * sizeof(char));
            if (temp == NULL)
            {
                perror("Failed to handle parenthesis");
                free(copy_expression);
                return specified_exp;
            }
            copy_expression = temp;

            copy_expression[len] = '\0';
            for (int i = 0; i < open - close; i++)
                copy_expression[len - 1 - i] = ')';
        }
        else if (open < close)
        {
            free(copy_expression);
            return specified_exp;
        }
    }

    // Test
    // printf("Re-format: %s | Len = %d\n", copy_expression, len);

    // 4. Allocate memories

    _infix_ *infix_exp = (_infix_ *)malloc(len * sizeof(_infix_));
    if (infix_exp == NULL)
    {
        perror("Failed to allocate infix copy_expression");
        free(copy_expression);
        return specified_exp;
    }
    for (int i = 0; i < len; i++)
    {
        infix_exp[i].num = NAN;
        infix_exp[i].operator= '\0';
        infix_exp[i].variable = '\0';
    }

    // 5. Specify copy_expression -- Lexer
    int infix_len = 0;
    char _op_;
    for (int i = 0; i < len; i++)
    {
        _op_ = _operator__(copy_expression, i);

        // If it's a number or constant or variable
        if (_op_ == '\0')
        {
            // --Number--
            if (isdigit(copy_expression[i]))
            {
                char *str_num = (char *)calloc(26, sizeof(char)); // Max num len = 26
                if (str_num == NULL)
                {
                    perror("Failed to allocate str_num");
                    free(copy_expression);
                    free(infix_exp);
                    return specified_exp;
                }

                int j = 0;
                // separate to another array
                while ((isdigit(copy_expression[i]) || copy_expression[i] == '.') && j < 26)
                    str_num[j++] = copy_expression[i++];

                // convert to double and store
                (infix_exp[infix_len++]).num = atof(str_num);

                // reset str_num
                free(str_num);

                --i;
                continue;
            }

            //--Place down constants--
            else if (copy_expression[i] == 'e')
            {
                infix_exp[infix_len++].num = EULER_NUMBER;
                continue;
            }

            else if (copy_expression[i] == 'p' && copy_expression[i + 1] == 'i')
            {
                infix_exp[infix_len++].num = PI;
                i++;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt2", 5))
            {
                infix_exp[infix_len++].num = SQRT_2;
                i += 4;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt.5", 6))
            {
                infix_exp[infix_len++].num = SQRT_2_2;
                i += 5;
                continue;
            }

            else if (!strncmp(copy_expression + i, "sqrt3", 5))
            {
                infix_exp[infix_len++].num = SQRT_3;
                i += 4;
                continue;
            }

            else if (copy_expression[i] == 'g' && copy_expression[i + 1] != 'a')
            {
                infix_exp[infix_len++].num = _G_;
                continue;
            }

            else if (copy_expression[i] == 'l' && copy_expression[i + 1] == 'n' && copy_expression[i + 2] == '2')
            {
                infix_exp[infix_len++].num = LN_2;
                i += 2;
                continue;
            }

            else if (copy_expression[i] == 'c' && copy_expression[i - 1] != 'e' && copy_expression[i - 1] != 's' && copy_expression[i + 1] != 'o' && copy_expression[i + 1] != 's')
            {
                infix_exp[infix_len++].num = _C_;
                continue;
            }

            // special: percentage
            else if (copy_expression[i] == '%' && copy_expression[i + 1] != '%' && copy_expression[i - 1] != '%')
            {
                infix_exp[infix_len++].num = 1.0 / 100.0;
                continue;
            }

            //-Replace variable with specifier-
            else
            {
                infix_exp[infix_len++].variable = copy_expression[i];
                continue;
            }
        }

        // If it's an operator or available function
        else
        {
            infix_exp[infix_len++].operator= _op_;
            _increase_(&i, _op_);
        }
    }

    // Re-size infix_exp
    _infix_ *temp_ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
    if (temp_ == NULL)
    {
        perror("Failed to shrink infix_exp");
        free(infix_exp);
        free(copy_expression);
        return specified_exp;
    }
    infix_exp = temp_;

    free(copy_expression);

    // Test infix
    /* printf("RAW INFIX EXPRESSION:\n\n");
    for (int i = 0; i < infix_len; i++)
    {
        if (!isnan(infix_exp[i].num))
            printf("NUM = %.9lf", infix_exp[i].num);
        if (infix_exp[i].operator != '\0')
            printf("OP = %c", infix_exp[i].operator);
        if (infix_exp[i].variable != '\0')
            printf("VAR = %c", infix_exp[i].variable);
        printf("\n");
    }
    printf("Token len = %d\n", infix_len); */

    // 6. Re-format infix_exp to handle errors and missing tokens

    // Left-side of tokens
    {
        for (int i = 1; i < infix_len; i++)
        {
            // Num or var
            if ((!isnan(infix_exp[i].num) || infix_exp[i].variable != '\0') &&
                (!isnan(infix_exp[i - 1].num)         //!= NAN
                 || infix_exp[i - 1].variable != '\0' // ís variable
                 || infix_exp[i - 1].operator== ')' || infix_exp[i - 1].operator== '!'))
            {
                infix_len++;
                _infix_ *temp__ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
                if (temp__ == NULL)
                {
                    perror("Failed to realloc infix_exp");
                    free(infix_exp);
                    return specified_exp;
                }
                infix_exp = temp__;

                for (int k = infix_len - 1; k > i; k--)
                {
                    infix_exp[k].num = infix_exp[k - 1].num;
                    infix_exp[k].variable = infix_exp[k - 1].variable;
                    infix_exp[k].operator= infix_exp[k - 1].operator;
                }
                infix_exp[i].num = NAN;
                infix_exp[i].variable = '\0';
                infix_exp[i].operator= '*';
            }

            // Special cases of operator
            else if ((infix_exp[i].operator== '+' ||
                      infix_exp[i]
                          .operator== '-' ||
                      infix_exp[i]
                          .operator== '*' ||
                      infix_exp[i]
                          .operator== '/' ||
                      infix_exp[i]
                          .operator== '^' ||
                      infix_exp[i]
                          .operator== '%' ||
                      infix_exp[i]
                          .operator== '!') &&
                     (infix_exp[i - 1].operator!= '\0' && infix_exp[i - 1].operator!= '!') &&
                     infix_exp[i - 1]
                         .operator!= ')')
            {
                free(infix_exp);
                return specified_exp;
            }
        }

        // Right-side of tokens
        for (int i = 0; i < infix_len - 1; i++)
        {
            // Num or var
            if ((!isnan(infix_exp[i].num) || infix_exp[i].variable != '\0') &&
                (infix_exp[i + 1].operator!= '+' &&
                 infix_exp[i + 1]
                     .operator!= '-' &&
                 infix_exp[i + 1]
                     .operator!= '*' &&
                 infix_exp[i + 1]
                     .operator!= '/' &&
                 infix_exp[i + 1]
                     .operator!= '^' &&
                 infix_exp[i + 1]
                     .operator!= '%' &&
                 infix_exp[i + 1]
                     .operator!= '!' &&
                 infix_exp[i + 1]
                     .operator!= ')' &&
                 infix_exp[i + 1]
                     .operator!= ',' &&
                 infix_exp[i + 1]
                     .operator!= '=' &&
                 infix_exp[i + 1]
                     .operator!= '\0'))
            {
                i++;
                infix_len++;
                _infix_ *temp__ = (_infix_ *)realloc(infix_exp, infix_len * sizeof(_infix_));
                if (temp__ == NULL)
                {
                    perror("Failed to realloc infix_exp");
                    free(infix_exp);
                    return specified_exp;
                }
                infix_exp = temp__;

                for (int k = infix_len - 1; k > i; k--)
                {
                    infix_exp[k].num = infix_exp[k - 1].num;
                    infix_exp[k].variable = infix_exp[k - 1].variable;
                    infix_exp[k].operator= infix_exp[k - 1].operator;
                }
                infix_exp[i].num = NAN;
                infix_exp[i].variable = '\0';
                infix_exp[i].operator= '*';
            }

            // Special case of parenthesis
            else if (infix_exp[i].operator== '(' && infix_exp[i + 1].operator== ')' && isnan(infix_exp[i + 1].num))
            {
                free(infix_exp);
                return specified_exp;
            }

            // Special cases of the left-side of close bracket
            else if (isnan(infix_exp[i].num) && infix_exp[i].variable == '\0' && infix_exp[i].operator!= ')' && infix_exp[i].operator!= '!' && infix_exp[i + 1].operator== ')')
            {
                free(infix_exp);
                return specified_exp;
            }

            else if (infix_exp[i].operator== ')' && infix_exp[i + 1].operator!= ')' && infix_exp[i + 1].operator!= '+' && infix_exp[i + 1].operator!= '-' && infix_exp[i + 1].operator!= '*' && infix_exp[i + 1].operator!= '/' && infix_exp[i + 1].operator!= '^' && infix_exp[i + 1].operator!= '%' && infix_exp[i + 1].operator!= '!' && infix_exp[i + 1].operator!= ',')
            {
                _infix_ *tmp = (_infix_ *)realloc(infix_exp, (infix_len + 1) * sizeof(_infix_));
                if (tmp == NULL)
                {
                    free(infix_exp);
                    return specified_exp;
                }
                infix_exp = tmp;
                infix_len++;

                for (int k = infix_len - 1; k > i + 1; k--)
                {
                    infix_exp[k].num = infix_exp[k - 1].num;
                    infix_exp[k].operator= infix_exp[k - 1].operator;
                    infix_exp[k].variable = infix_exp[k - 1].variable;
                }

                infix_exp[i + 1].num = NAN;
                infix_exp[i + 1].variable = '\0';
                infix_exp[i + 1].operator= '*';

                i++;
            }
        }

        // Special cases at the beginning of the expression
        if (infix_exp[0].operator== '+' ||
            infix_exp[0]
                .operator== '-' ||
            infix_exp[0]
                .operator== '*' ||
            infix_exp[0]
                .operator== '/' ||
            infix_exp[0]
                .operator== '^' ||
            infix_exp[0]
                .operator== '!' ||
            infix_exp[0]
                .operator== '%' ||
            infix_exp[0]
                .operator== ')')
        {
            free(infix_exp);
            return specified_exp;
        }

        // Special cases at the end of the expression
        if (infix_exp[infix_len - 1].operator== '+' ||
            infix_exp[infix_len - 1]
                .operator== '-' ||
            infix_exp[infix_len - 1]
                .operator== '*' ||
            infix_exp[infix_len - 1]
                .operator== '/' ||
            infix_exp[infix_len - 1]
                .operator== '^' ||
            infix_exp[infix_len - 1]
                .operator== '(')
        {
            free(infix_exp);
            return specified_exp;
        }
    }

    // After pre-processing
    /* printf("AFTER PRE-PROCESSING INFIX EXPRESSION:\n\n");
    for (int i = 0; i < infix_len; i++)
    {
        if (!isnan(infix_exp[i].num))
            printf("NUM = %.9lf", infix_exp[i].num);
        if (infix_exp[i].operator != '\0')
            printf("OP = %c", infix_exp[i].operator);
        if (infix_exp[i].variable != '\0')
            printf("VAR = %c", infix_exp[i].variable);
        printf("\n");
    }
    printf("Token len = %d\n", infix_len); */

    specified_exp.size = infix_len;
    specified_exp.tokens = infix_exp;

    return specified_exp;
}

_POSTFIX__ submodule_Parse(__INFIX__ specified_expression)
{
    int infix_len = specified_expression.size;
    _infix_ *infix_exp = (_infix_ *)malloc(infix_len * sizeof(_infix_));
    if (infix_exp == NULL)
    {
        perror("submodule_Parse: Failed to malloc infix_exp");
        _POSTFIX__ empty_expression = {0, NULL};
        return empty_expression;
    }
    memcpy(infix_exp, specified_expression.tokens, infix_len * sizeof(_infix_));

    _POSTFIX__ parsed_expression;
    parsed_expression.size = 0;
    parsed_expression.tokens = NULL;

    /* --------------------Parsing processor-------------------- */
    // Create memories for parsing
    _TOKENS_DATA_ *P_expression = (_TOKENS_DATA_ *)malloc(infix_len * sizeof(_TOKENS_DATA_));
    if (P_expression == NULL)
    {
        perror("Failed to create P_expression");
        free(infix_exp);
        return parsed_expression;
    }
    // Initialize P_expression with "empty" values
    for (int i = 0; i < infix_len; i++)
    {
        P_expression[i].num = NAN;
        P_expression[i].operator= '\0';
        P_expression[i].variable = '\0';
    }

    char *ope_stack = (char *)calloc(infix_len + 1, sizeof(char));
    if (ope_stack == NULL)
    {
        perror("Failed to create ope_stack");
        free(infix_exp);
        free(P_expression);
        return parsed_expression;
    }

    // Processor
    int P_index = 0;
    int ope_index = 0;
    for (int i = 0; i < infix_len; i++)
    {
        double _num_ = infix_exp[i].num;
        char _op_ = infix_exp[i].operator;
        if (_op_ == ',' || _op_ == '=')
        {
            free(ope_stack);
            free(P_expression);
            free(parsed_expression.tokens);
            _POSTFIX__ empty = {NULL, 0};
            return empty;
        }
        char _var_ = infix_exp[i].variable;

        // If the current token is a number or variable --> store to output stack
        if (!isnan(_num_))
        {
            P_expression[P_index++].num = _num_;
        }

        else if (_var_ != '\0')
        {
            P_expression[P_index++].variable = _var_;
        }

        // Else, if it's an operator
        else
        {
            // If it's the first op
            if (ope_index == 0 && ope_stack[0] == '\0')
            {
                ope_stack[ope_index++] = _op_;
            }

            // If the current op has a greater precedence than the last op in the stack OR it's an open bracket
            else if (precedent_of(ope_stack[ope_index - 1]) < precedent_of(_op_) || _op_ == '(')
            {
                ope_stack[ope_index++] = _op_;
            }

            // If the current op has a lower precedence than the last op in the stack
            else if (_op_ != ')')
            {
                while (precedent_of(_op_) <= precedent_of(ope_stack[ope_index - 1]) && ope_index > 0)
                {
                    P_expression[P_index++].operator= ope_stack[ope_index - 1];
                    ope_stack[--ope_index] = '\0';
                }
                ope_stack[ope_index++] = _op_;
            }

            // If it's a close bracket
            else if (_op_ == ')')
            {
                while (ope_stack[ope_index - 1] != '(' && ope_index > 0)
                {
                    P_expression[P_index++].operator= ope_stack[ope_index - 1];
                    ope_stack[--ope_index] = '\0';
                }
                ope_stack[--ope_index] = '\0';
            }
        }
    }

    // Push all the remaining op in the ope_stack to output stack
    while (ope_index > 0)
    {
        P_expression[P_index++].operator= ope_stack[--ope_index];
    }

    /* ----------After parsing---------- */
    /* printf("\nAFTER PARSING\n");
    for (int i = 0; i < P_index; i++)
    {
        double _num_ = P_expression[i].num;
        char _var_ = P_expression[i].variable;
        char _op_ = P_expression[i].operator;

        if(!isnan(_num_)) printf("Num = %.9lf\n", _num_);
        if(_var_ != '\0') printf("Var = %c\n", _var_);
        if(_op_ != '\0') printf("OP = %c\n", _op_);
    }
    printf("P_index = %d\n", P_index); */

    // Return final results
    parsed_expression.size = P_index;
    parsed_expression.tokens = P_expression;

    free(infix_exp);
    free(ope_stack);
    return parsed_expression;
}

void find_LPO(__INFIX__ specified_expression, char *LPO, int *LPO_pos)
{
    (*LPO) = '\0';
    (*LPO_pos) = 0;

    typedef struct
    {
        double num;
        char operator;
        char variable;
        int pos;
    } _infix_find_LPO;

    typedef struct
    {
        double num;
        char variable;
        char operator;
        int pos;
    } _TOKENS_DATA_find_LPO;

    typedef struct
    {
        char op;
        int pos;
    } _ope_struct_find_LPO;

    int infix_len = specified_expression.size;
    _infix_find_LPO *infix_exp = (_infix_find_LPO *)malloc(infix_len * sizeof(_infix_find_LPO));
    if (infix_exp == NULL)
    {
        perror("find_LPO: Failed to alloc infix_exp");
        return;
    }
    for (int i = 0; i < infix_len; i++)
    {
        infix_exp[i].num = specified_expression.tokens[i].num;
        infix_exp[i].operator= specified_expression.tokens[i].operator;
        infix_exp[i].variable = specified_expression.tokens[i].variable;
        infix_exp[i].pos = i;
    }

    /* --------------------Parsing processor-------------------- */
    // Create memories for parsing
    _TOKENS_DATA_find_LPO *P_expression = (_TOKENS_DATA_find_LPO *)malloc(infix_len * sizeof(_TOKENS_DATA_find_LPO));
    if (P_expression == NULL)
    {
        perror("Failed to create P_expression");
        free(infix_exp);
        return;
    }
    // Initialize P_expression with "empty" values
    for (int i = 0; i < infix_len; i++)
    {
        P_expression[i].num = NAN;
        P_expression[i].operator= '\0';
        P_expression[i].variable = '\0';
        P_expression[i].pos = 0;
    }

    _ope_struct_find_LPO *ope_stack = (_ope_struct_find_LPO *)calloc(infix_len + 1, sizeof(_ope_struct_find_LPO));
    if (ope_stack == NULL)
    {
        perror("Failed to create ope_stack");
        free(infix_exp);
        free(P_expression);
        return;
    }

    // Processor
    int P_index = 0;
    int ope_index = 0;
    for (int i = 0; i < infix_len; i++)
    {
        double _num_ = infix_exp[i].num;
        char _op_ = infix_exp[i].operator;
        char _var_ = infix_exp[i].variable;
        int _pos_ = infix_exp[i].pos;

        // If the current token is a number or variable --> store to output stack
        if (!isnan(_num_))
        {
            P_expression[P_index].num = _num_;
            P_expression[P_index++].pos = _pos_;
        }

        else if (_var_ != '\0')
        {
            P_expression[P_index].variable = _var_;
            P_expression[P_index++].pos = _pos_;
        }

        // Else, if it's an operator
        else
        {
            // If it's the first op
            if (ope_index == 0 && ope_stack[0].op == '\0')
            {
                ope_stack[ope_index].op = _op_;
                ope_stack[ope_index++].pos = _pos_;
            }

            // If the current op has a greater precedence than the last op in the stack OR it's an open bracket
            else if (precedent_of(ope_stack[ope_index - 1].op) < precedent_of(_op_) || _op_ == '(')
            {
                ope_stack[ope_index].op = _op_;
                ope_stack[ope_index++].pos = _pos_;
            }

            // If the current op has a lower precedence than the last op in the stack
            else if (_op_ != ')')
            {
                while (precedent_of(_op_) <= precedent_of(ope_stack[ope_index - 1].op) && ope_index > 0)
                {
                    P_expression[P_index].operator= ope_stack[ope_index - 1].op;
                    P_expression[P_index++].pos = ope_stack[ope_index - 1].pos;
                    ope_stack[ope_index - 1].op = '\0';
                    ope_stack[--ope_index].pos = 0;
                }
                ope_stack[ope_index].op = _op_;
                ope_stack[ope_index++].pos = _pos_;
            }

            // If it's a close bracket
            else if (_op_ == ')')
            {
                while (ope_stack[ope_index - 1].op != '(' && ope_index > 0)
                {
                    P_expression[P_index].operator= ope_stack[ope_index - 1].op;
                    P_expression[P_index++].pos = ope_stack[ope_index - 1].pos;
                    ope_stack[ope_index - 1].op = '\0';
                    ope_stack[--ope_index].pos = 0;
                }
                ope_stack[ope_index].op = '\0';
                ope_stack[--ope_index].pos = 0;
            }
        }
    }

    // Push all the remaining op in the ope_stack to output stack
    while (ope_index > 0)
    {
        P_expression[P_index].operator= ope_stack[ope_index - 1].op;
        P_expression[P_index++].pos = ope_stack[--ope_index].pos;
    }

    /* ----------After parsing---------- */
    /* printf("\nAFTER PARSING\n");
    for (int i = 0; i < P_index; i++)
    {
        double _num_ = P_expression[i].num;
        char _var_ = P_expression[i].variable;
        char _op_ = P_expression[i].operator;

        if(!isnan(_num_)) printf("Num = %.9lf\n", _num_);
        if(_var_ != '\0') printf("Var = %c\n", _var_);
        if(_op_ != '\0') printf("OP = %c\n", _op_);
    }
    printf("P_index = %d\n", P_index); */

    // Return final results
    // parsed_expression.size = P_index;
    // parsed_expression.tokens = P_expression;

    (*LPO) = P_expression[P_index - 1].operator;
    (*LPO_pos) = P_expression[P_index - 1].pos;

    free(infix_exp);
    free(ope_stack);
    free(P_expression);
    return;
}

void display_infix_exp(const __INFIX__ expression)
{
    if (expression.tokens == NULL)
        return;
    for (int i = 0; i < expression.size; i++)
    {
        if (expression.tokens[i].variable != '\0')
            printf("Var: %c\n", expression.tokens[i].variable);
        if (expression.tokens[i].operator!= '\0')
            printf("Op: %c\n", expression.tokens[i].operator);
        if (!isnan(expression.tokens[i].num))
            printf("Num: %.17lf\n", expression.tokens[i].num);
    }
}

void add_single_token(__INFIX__ *destination, const double num, const char variable, const char operator)
{
    // new size
    size_t new_size = (size_t)destination->size + 1;
    _infix_ *tmp;

    if (destination->tokens == NULL)
    {
        // malloc if tokens is null
        tmp = (_infix_ *)malloc(new_size * sizeof(_infix_));
    }
    else
        tmp = (_infix_ *)realloc(destination->tokens, new_size * sizeof(_infix_));

    if (tmp == NULL)
    {
        perror("add_single_token: Failed to allocate memory");
        return;
    }

    // Commit the new buffer and size
    destination->tokens = tmp;
    destination->size = (int)new_size;

    // Initialize the newly appended token
    _infix_ *new_tok = &destination->tokens[new_size - 1];
    new_tok->num = num;
    new_tok->variable = variable;
    new_tok->operator= operator;
}

void add_many_tokens(__INFIX__ *destination, const __INFIX__ source)
{
    if (source.size <= 0 || source.tokens == NULL)
        return;

    // If destination has no tokens, allocate new memory
    if (destination->tokens == NULL)
    {
        destination->tokens = (_infix_ *)malloc(source.size * sizeof(_infix_));
        if (destination->tokens == NULL)
        {
            perror("add_many_tokens: failed to allocate destination tokens");
            return;
        }
        memcpy(destination->tokens,
               source.tokens,
               source.size * sizeof(_infix_));
        destination->size = source.size;
    }
    else
    {
        // Append to existing array
        int new_size = destination->size + source.size;
        _infix_ *resized = (_infix_ *)realloc(destination->tokens, new_size * sizeof(_infix_));
        if (resized == NULL)
        {
            perror("add_many_tokens: failed to realloc destination tokens");
            return;
        }
        memcpy(resized + destination->size,
               source.tokens,
               source.size * sizeof(_infix_));
        destination->tokens = resized;
        destination->size = new_size;
    }
}

void check_for_valid_braket(__INFIX__ *copyof_input)
{
    int open_bracket = 0, close_bracket = 0;
    for (int i = 0; i < copyof_input->size; i++)
    {
        if (copyof_input->tokens[i].operator== '(')
            open_bracket++;
        else if (copyof_input->tokens[i].operator== ')')
            close_bracket++;
    }

    if (open_bracket > close_bracket)
    {
        for (int i = 1; i <= open_bracket - close_bracket; i++)
            add_single_token(copyof_input, NAN, '\0', ')');
    }

    else if (open_bracket < close_bracket)
    {
        int delta = close_bracket - open_bracket;
        _infix_ *tmp = (_infix_ *)realloc(copyof_input->tokens, (delta + copyof_input->size) * sizeof(_infix_));
        if (tmp == NULL)
        {
            perror("Check for valid bracket: Failed to realloc tmp");
            free(copyof_input->tokens);
            copyof_input->size = 0;
            copyof_input->tokens = NULL;
            return;
        }
        copyof_input->tokens = tmp;
        copyof_input->size += delta;

        for (int i = copyof_input->size - 1; i >= delta; i--)
        {
            copyof_input->tokens[i].num = copyof_input->tokens[i - delta].num;
            copyof_input->tokens[i].variable = copyof_input->tokens[i - delta].variable;
            copyof_input->tokens[i].operator= copyof_input->tokens[i - delta].operator;
        }

        for (int i = 0; i < delta; i++)
        {
            copyof_input->tokens[i].num = NAN;
            copyof_input->tokens[i].variable = '\0';
            copyof_input->tokens[i].operator= '(';
        }
    }
}

/*
This module compute the derivative of an Infix & specified function of x (or any variable)
#Supporting:
--Arithmetic operators: + - * / % ^ ! ( )
--Trig functions: sin() cos() tan() cot() sec() csc() arcsin() arccos() arctan() arccot()
--Hyperbolic functions: sinh() cosh() tanh() coth() arcsinh() arccosh() arctanh() arccoth()
--Logarithmic function: ln() & log(). If you want to calculate log(3,10), try using ln(10)/ln(3) instead
--Square & cube root function: sqrt() & cbrt()
--Absolute value function: abs()
--Other functions: gamma() ceil() floor() lambertw()

#If you want to calculate the n-th root of x (for n > 3), use exponentiation like x^(1/n) instead
#REAL numbers only
#Trig functions are computed in RADIAN unit

#Available CONSTANTS:
+e
+pi
+sqrt2
+sqrt.5 = sqrt(0.5)
+sqrt3
+g
+ln2
*/
__INFIX__ differentiate_I_exp(__INFIX__ specified_expression, const char var)
{
    __INFIX__ empty_expression = {0, NULL};
    if (specified_expression.size < 1 || specified_expression.tokens == NULL || var == '\0')
        return empty_expression;

    __INFIX__ copyof_input;

    // make a copy of the input
    {
        copyof_input.size = specified_expression.size;
        copyof_input.tokens = malloc(sizeof(*specified_expression.tokens) * specified_expression.size);
        if (copyof_input.tokens == NULL)
        {
            perror("Make copy: Failed to allocate memory");
            return empty_expression;
        }
        memcpy(copyof_input.tokens, specified_expression.tokens, sizeof(*specified_expression.tokens) * specified_expression.size);
    }
    /* Differentiation steps
    1/ Check for the appearence of var in the expression
    2/ Find the "Lowest precendet operator"
    3/ Create memory to hold du & dv
    4/ Handle simple cases & Implement the differentiate formula for complex tokens
    */

    // step 1
    bool var_detected = false;
    int num_of_var = 0;
    bool no_operator = true;
    {
        for (int i = 0; i < copyof_input.size; i++)
        {
            if (copyof_input.tokens[i].variable == var)
            {
                var_detected = true;
                num_of_var++;
            }
            else if (copyof_input.tokens[i].operator!= '(' && copyof_input.tokens[i].operator!= ')' && copyof_input.tokens[i].operator!= '\0')
                no_operator = false;
        }
        if (!var_detected)
        {
            copyof_input.size = 1;
            _infix_ *tmp = (_infix_ *)realloc(copyof_input.tokens, sizeof(_infix_));
            if (tmp == NULL)
            {
                perror("Step 1 - var detecting: Failed to realloc tmp");
                free(copyof_input.tokens);
                return empty_expression;
            }
            copyof_input.tokens = tmp;

            copyof_input.tokens[0].num = 0.0;
            copyof_input.tokens[0].variable = '\0';
            copyof_input.tokens[0].operator= '\0';

            return copyof_input;
        }
        else if (num_of_var == 1 && no_operator)
        {
            copyof_input.size = 1;
            _infix_ *tmp = (_infix_ *)realloc(copyof_input.tokens, sizeof(_infix_));
            if (tmp == NULL)
            {
                perror("Step 1 - single var detecting: Failed to realloc tmp");
                free(copyof_input.tokens);
                return empty_expression;
            }
            copyof_input.tokens = tmp;

            copyof_input.tokens[0].num = 1.0;
            copyof_input.tokens[0].variable = '\0';
            copyof_input.tokens[0].operator= '\0';
            return copyof_input;
        }
    }

    // Step 2
    char LPO;
    int pos;
    find_LPO(copyof_input, &LPO, &pos);

    // printf("LPO: %c | Pos = %d\n", LPO, pos);

    // step 3
    __INFIX__ _U_, _V_;
    __INFIX__ _DU_, _DV_;
    {
        // _U_ //
        _U_.size = pos;
        _U_.tokens = (_infix_ *)calloc(_U_.size, sizeof(_infix_));
        if (_U_.tokens == NULL)
        {
            perror("Step 3: Failed to malloc _U_");
            free(copyof_input.tokens);
            return empty_expression;
        }

        // _V_ //
        _V_.size = copyof_input.size - pos - 1;
        _V_.tokens = (_infix_ *)calloc(_V_.size, sizeof(_infix_));
        if (_V_.tokens == NULL)
        {
            perror("Step 3: Failed to malloc _V_");
            free(copyof_input.tokens);
            free(_U_.tokens);
            return empty_expression;
        }

        // _DU_ //
        _DU_.size = (copyof_input.size) * 5;
        _DU_.tokens = (_infix_ *)calloc(_DU_.size, sizeof(_infix_));
        if (_DU_.tokens == NULL)
        {
            perror("Step 3: Failed to allocte _DU_.tokens");
            free(copyof_input.tokens);
            free(_U_.tokens);
            free(_V_.tokens);
            return empty_expression;
        }

        // _DV_ //
        _DV_.size = _DU_.size;
        _DV_.tokens = (_infix_ *)calloc(_DV_.size, sizeof(_infix_));
        if (_DV_.tokens == NULL)
        {
            perror("Step 3: Failed to allocte _DV_.tokens");
            free(copyof_input.tokens);
            free(_U_.tokens);
            free(_V_.tokens);
            free(_DU_.tokens);
            return empty_expression;
        }

        for (int i = 0; i < _DU_.size; i++)
        {
            _DU_.tokens[i].num = NAN;
            _DV_.tokens[i].num = NAN;
        }
    }

    // Step 4
    {
        // 2 parameters operators
        if (LPO == '*' || LPO == '-' || LPO == '+' || LPO == '/' || LPO == '^')
        {
            // store to _U_ //
            for (int i = 0; i < _U_.size; i++)
            {
                _U_.tokens[i].num = copyof_input.tokens[i].num;
                _U_.tokens[i].operator= copyof_input.tokens[i].operator;
                _U_.tokens[i].variable = copyof_input.tokens[i].variable;
            }

            // store to _V_ //
            for (int i = pos + 1, v = 0; i < copyof_input.size; i++, v++)
            {
                _V_.tokens[v].num = copyof_input.tokens[i].num;
                _V_.tokens[v].variable = copyof_input.tokens[i].variable;
                _V_.tokens[v].operator= copyof_input.tokens[i].operator;
            }

            check_for_valid_braket(&_U_);
            check_for_valid_braket(&_V_);

            // Find du & dv
            _DU_ = differentiate_I_exp(_U_, var);
            _DV_ = differentiate_I_exp(_V_, var);

            // remove the original array
            free(copyof_input.tokens);
            copyof_input.size = 0;
            copyof_input.tokens = NULL;

            /* ====================================================================================================== */

            // addition || subtraction
            if (LPO == '+' || LPO == '-')
            {
                // const +|- v = +|-dv
                if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    if (LPO == '-')
                        add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }

                // u +|- const = du
                else if (_DV_.size == 1 && _DV_.tokens[0].num == 0.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DU_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }

                // u +|- v = du +|- dv
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DU_);
                    if (LPO == '-')
                        add_single_token(&copyof_input, NAN, '\0', '-');
                    else
                        add_single_token(&copyof_input, NAN, '\0', '+');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }

            // multiplication
            else if (LPO == '*')
            {
                // const*var = const
                if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0 && _DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_many_tokens(&copyof_input, _U_);
                }

                // var*const = const
                else if (_DV_.size == 1 && _DV_.tokens[0].num == 0.0 && _DU_.size == 1 && _DU_.tokens[0].num == 1.0)
                {
                    add_many_tokens(&copyof_input, _V_);
                }

                // const * v = dv * const
                else if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0)
                {
                    add_many_tokens(&copyof_input, _U_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _DV_);
                }

                // u * const = const * du
                else if (_DV_.size == 1 && _DV_.tokens[0].num == 0.0)
                {
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _DU_);
                }

                // u*v = du*v + dv*u
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DU_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _U_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }

            // Division
            else if (LPO == '/')
            {
                // const/var = (-const)/(var^2)
                if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0 && _DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _U_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }

                // const / v = (-const * dv)/(v^2)
                else if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _U_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }

                // u / v = (du * v - dv * u)/(v^2)
                else
                {
                    // numerator: du * v - dv * u
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DU_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _U_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    // denominator: v^2
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }

            // exponentiation
            else
            {
                add_single_token(&copyof_input, NAN, '\0', '(');
                // var ^ const = const * var ^ (const - 1)
                if (_DU_.size == 1 && _DU_.tokens[0].num == 1.0 && _DV_.size == 1 && _DV_.tokens[0].num == 0.0)
                {
                    /* ===== */
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    /* ===== */

                    // bool extern_var = false;
                    // for (short int ev = 0; ev < _V_.size; ev++)
                    // {
                    //     if (_V_.tokens[ev].variable != '\0' && _V_.tokens[ev].variable != var)
                    //     {
                    //         extern_var = true;
                    //         break;
                    //     }
                    // }

                    // if (!extern_var)
                    // {
                    //     double the_const = Compute_P_expression(submodule_Parse(_V_));
                    //     if (is_integer(the_const))
                    //     {
                    //         if ((the_const == 0.0 || fabs(the_const) <= __DBL_EPSILON__))
                    //         {
                    //             add_single_token(&copyof_input, 0.0, '\0', '\0');
                    //         }
                    //         else
                    //         {
                    //             add_single_token(&copyof_input, the_const, '\0', '\0');
                    //             add_single_token(&copyof_input, NAN, '\0', '*');
                    //             add_single_token(&copyof_input, NAN, var, '\0');
                    //             add_single_token(&copyof_input, NAN, '\0', '^');
                    //             add_single_token(&copyof_input, the_const - 1.0, '\0', '\0');
                    //         }
                    //     }
                    //     else
                    //     {
                    //         add_single_token(&copyof_input, the_const, '\0', '\0');
                    //         add_single_token(&copyof_input, NAN, '\0', '*');
                    //         add_single_token(&copyof_input, NAN, var, '\0');
                    //         add_single_token(&copyof_input, NAN, '\0', '^');
                    //         add_single_token(&copyof_input, NAN, '\0', '(');
                    //         add_single_token(&copyof_input, the_const, '\0', '\0');
                    //         add_single_token(&copyof_input, NAN, '\0', '-');
                    //         add_single_token(&copyof_input, 1.0, '\0', '\0');
                    //         add_single_token(&copyof_input, NAN, '\0', ')');
                    //     }
                    // }

                    // else
                    // {
                    //     add_many_tokens(&copyof_input, _V_);
                    //     add_single_token(&copyof_input, NAN, '\0', '*');
                    //     add_single_token(&copyof_input, NAN, var, '\0');
                    //     add_single_token(&copyof_input, NAN, '\0', '^');
                    //     add_single_token(&copyof_input, NAN, '\0', '(');
                    //     add_many_tokens(&copyof_input, _V_);
                    //     add_single_token(&copyof_input, NAN, '\0', '-');
                    //     add_single_token(&copyof_input, 1.0, '\0', '\0');
                    //     add_single_token(&copyof_input, NAN, '\0', ')');
                    // }
                }

                // const ^ var = ln(a) * const ^ var
                else if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0 && _DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    double the_const;
                    if (_U_.size > 1)
                        the_const = Compute_P_expression(submodule_Parse(_U_));
                    else
                        the_const = _U_.tokens[0].num;

                    if (fabs(the_const - EULER_NUMBER) < 1e-6)
                    {
                        add_single_token(&copyof_input, EULER_NUMBER, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_single_token(&copyof_input, NAN, var, '\0');
                    }
                    else
                    {
                        add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', ')');
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_single_token(&copyof_input, NAN, var, '\0');
                    }
                }

                // u ^ const = const * du * u^(const - 1)
                else if (_DV_.size == 1 && _DV_.tokens[0].num == 0.0)
                {
                    double the_const = Compute_P_expression(submodule_Parse(_V_));
                    if (is_integer(the_const))
                    {
                        add_single_token(&copyof_input, the_const, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _DU_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_single_token(&copyof_input, the_const - 1.0, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', ')');
                    }

                    else
                    {
                        // add_single_token(&copyof_input, the_const, '\0', '\0');
                        add_many_tokens(&copyof_input, _V_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _DU_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        // add_single_token(&copyof_input, the_const - 1.0, '\0', '\0');
                        add_many_tokens(&copyof_input, _V_);
                        add_single_token(&copyof_input, NAN, '\0', '-');
                        add_single_token(&copyof_input, 1.0, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', ')');
                    }
                }

                // const ^ v = ln(const) * dv * const ^ v
                else if (_DU_.size == 1 && _DU_.tokens[0].num == 0.0)
                {
                    double the_const;
                    if (_U_.size > 1)
                        the_const = Compute_P_expression(submodule_Parse(_U_));
                    else
                        the_const = _U_.tokens[0].num;

                    if (fabs(the_const - EULER_NUMBER) < 1e-6)
                    {
                        add_many_tokens(&copyof_input, _DV_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_single_token(&copyof_input, EULER_NUMBER, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_many_tokens(&copyof_input, _V_);
                    }

                    else
                    {
                        add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', ')');
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _DV_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_many_tokens(&copyof_input, _V_);
                    }
                }

                // u^v = (u^v)*(dv*ln(u) + v*(du/u))
                else
                {
                    // special case: x^x
                    if (
                        _DU_.size == 1 && _DU_.tokens[0].num == 1.0 && _DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                    {
                        // x^x derivative = x^x * (ln(x) + 1)
                        add_single_token(&copyof_input, NAN, var, '\0');
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_single_token(&copyof_input, NAN, var, '\0');
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_single_token(&copyof_input, NAN, var, '\0');
                        add_single_token(&copyof_input, NAN, '\0', ')');
                        add_single_token(&copyof_input, NAN, '\0', '+');
                        add_single_token(&copyof_input, 1.0, '\0', '\0');
                        add_single_token(&copyof_input, NAN, '\0', ')');
                    }
                    // general case: u^v = (u^v) * (v' * ln(u) + v * (u'/u))
                    else
                    {
                        // Add u^v
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', '^');
                        add_many_tokens(&copyof_input, _V_);
                        add_single_token(&copyof_input, NAN, '\0', ')');

                        add_single_token(&copyof_input, NAN, '\0', '*');

                        // Add v' * ln(u)
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _DV_);
                        add_single_token(&copyof_input, NAN, '\0', '*');
                        add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', ')');

                        // Add +
                        add_single_token(&copyof_input, NAN, '\0', '+');

                        // Add v * u'/u
                        add_many_tokens(&copyof_input, _V_);
                        add_single_token(&copyof_input, NAN, '\0', '*');

                        add_single_token(&copyof_input, NAN, '\0', '(');
                        add_many_tokens(&copyof_input, _DU_);
                        add_single_token(&copyof_input, NAN, '\0', '/');
                        add_many_tokens(&copyof_input, _U_);
                        add_single_token(&copyof_input, NAN, '\0', ')');

                        // Close parenthesis
                        add_single_token(&copyof_input, NAN, '\0', ')');
                    }
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
        }

        // functions
        else if (LPO != '!' && LPO != '(' && LPO != ')' && LPO != SPECIFIER_OF_FLOOR && LPO != SPECIFIER_OF_CEIL)
        {
            // store to _V_ //
            for (int i = pos + 1, v = 0; i < copyof_input.size; i++, v++)
            {
                _V_.tokens[v].num = copyof_input.tokens[i].num;
                _V_.tokens[v].variable = copyof_input.tokens[i].variable;
                _V_.tokens[v].operator= copyof_input.tokens[i].operator;
            }

            check_for_valid_braket(&_V_);

            // Find dv
            _DV_ = differentiate_I_exp(_V_, var);

            // refresh copyof_input to store result
            free(copyof_input.tokens);
            copyof_input.size = 0;
            copyof_input.tokens = NULL;

            // ============================================================================ //

            if (LPO == SPECIFIER_OF_SIN)
            {
                // sin(var)' = cos(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_COS)
            {
                // cos(var)' = -sin(var)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SIN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SIN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_TAN)
            {
                // tan(var)' = sec(var)^2
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SEC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SEC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_COT)
            {
                // cot(var)' = -csc(var)^2
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_SEC)
            {
                // sec(var)' = sec(var) * tan(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SEC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_TAN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SEC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_TAN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_CSC)
            {
                // csc(var)' = -csc(var) * cot(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSC);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }

            // Add these cases to the function differentiation section in differentiate_I_exp function
            // Insert after the existing trigonometric function cases

            else if (LPO == SPECIFIER_OF_SINH)
            {
                // sinh(var)' = cosh(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COSH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COSH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_COSH)
            {
                // cosh(var)' = sinh(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SINH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SINH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_TANH)
            {
                // tanh(var)' = sech(var)^2 = 1 - tanh(var)^2
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SECH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SECH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_COTH)
            {
                // coth(var)' = -csch(var)^2
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSCH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSCH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_SECH)
            {
                // sech(var)' = -sech(var) * tanh(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SECH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_TANH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SECH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_TANH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_CSCH)
            {
                // csch(var)' = -csch(var) * coth(var)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSCH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COTH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_CSCH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_COTH);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCSIN)
            {
                // arcsin(var)' = 1/sqrt(1-var^2)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCCOS)
            {
                // arccos(var)' = -1/sqrt(1-var^2)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCTAN)
            {
                // arctan(var)' = 1/(1+var^2)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCCOT)
            {
                // arccot(var)' = -1/(1+var^2)
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCSEC)
            {
                // arcsec(var)' = 1/((x^2)*sqrt(1-1/(x^2)))
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCCSC)
            {
                // arccsc(var)' = -1/(|var|*sqrt(var^2-1))
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCSINH)
            {
                // arcsinh(var)' = 1/sqrt(var^2+1)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCCOSH)
            {
                // arccosh(var)' = 1/sqrt(var^2-1)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCTANH)
            {
                // arctanh(var)' = 1/(1-var^2)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCCOTH)
            {
                // arccoth(var)' = 1/(1-var^2)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ARCSECH)
            {
                // arcsech(var)' = -1/(var*sqrt(1-var^2))
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_ARCCSCH)
            {
                // arccsch(var)' = -1/(|var|*sqrt(var^2+1))
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', '-');
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_SQRT)
            {
                // sqrt(var)' = 1/(2*sqrt(var))
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_SQRT);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_CBRT)
            {
                // cbrt(var)' = 1/(3*cbrt(var^2)) = 1/(3*var^(2/3))
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 3.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, 3.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 3.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '^');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 2.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, 3.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_ABS)
            {
                // abs(var)' = var/|var| = sign(var)
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_ABS);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_LN)
            {
                // ln(var)' = 1/var
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, var, '\0');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_many_tokens(&copyof_input, _V_);
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_LG)
            {
                // log10(var)' = 1/(var*ln(10))
                add_single_token(&copyof_input, NAN, '\0', '(');
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 10.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 10.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                add_single_token(&copyof_input, NAN, '\0', ')');
            }
            else if (LPO == SPECIFIER_OF_GAMMA)
            {
                // gamma(var)' = gamma(var) * digamma(var)
                // For simplicity, we'll use the approximation: gamma'(x) ≈ gamma(x) * ln(x) for x > 0
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_GAMMA);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_GAMMA);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LN);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
            else if (LPO == SPECIFIER_OF_LAMBERTW)
            {
                // lambertw(var)' = lambertw(var) / (var * (1 + lambertw(var)))
                if (_DV_.size == 1 && _DV_.tokens[0].num == 1.0)
                {
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LAMBERTW);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LAMBERTW);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, NAN, var, '\0');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
                else
                {
                    add_many_tokens(&copyof_input, _DV_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LAMBERTW);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', '/');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', '*');
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_single_token(&copyof_input, 1.0, '\0', '\0');
                    add_single_token(&copyof_input, NAN, '\0', '+');
                    add_single_token(&copyof_input, NAN, '\0', SPECIFIER_OF_LAMBERTW);
                    add_single_token(&copyof_input, NAN, '\0', '(');
                    add_many_tokens(&copyof_input, _V_);
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                    add_single_token(&copyof_input, NAN, '\0', ')');
                }
            }
        }
    }

    // Handle subtraction errors
    {
        if (copyof_input.tokens[0].operator== '-')
        {
            _infix_ *tmp = (_infix_ *)realloc(copyof_input.tokens, (copyof_input.size + 1) * sizeof(_infix_));
            if (tmp == NULL)
            {
                perror("Handle subtraction errors: Failed to realloc tmp");
                free(copyof_input.tokens);
                free(_U_.tokens);
                free(_V_.tokens);
                free(_DU_.tokens);
                free(_DV_.tokens);
                return empty_expression;
            }
            copyof_input.tokens = tmp;
            copyof_input.size++;

            for (int i = copyof_input.size - 1; i >= 1; i--)
            {
                copyof_input.tokens[i].num = copyof_input.tokens[i - 1].num;
                copyof_input.tokens[i].operator= copyof_input.tokens[i].operator;
                copyof_input.tokens[i].variable = copyof_input.tokens[i].variable;
            }

            copyof_input.tokens[0].num = 0.0;
            copyof_input.tokens[0].variable = '\0';
            copyof_input.tokens[0].operator= '\0';
        }

        for (int i = 1; i < copyof_input.size; i++)
        {
            if (copyof_input.tokens[i].operator== '-' && copyof_input.tokens[i - 1].operator== '(')
            {
                _infix_ *tmp = (_infix_ *)realloc(copyof_input.tokens, (1 + copyof_input.size) * sizeof(_infix_));
                if (tmp == NULL)
                {
                    perror("Handle subtraction errors: Failed to realloc tmp");
                    free(copyof_input.tokens);
                    free(_U_.tokens);
                    free(_V_.tokens);
                    free(_DU_.tokens);
                    free(_DV_.tokens);
                    return empty_expression;
                }
                copyof_input.tokens = tmp;
                copyof_input.size++;

                for (int k = copyof_input.size - 1; k >= i + 1; k--)
                {
                    copyof_input.tokens[k].num = copyof_input.tokens[k - 1].num;
                    copyof_input.tokens[k].operator= copyof_input.tokens[k - 1].operator;
                    copyof_input.tokens[k].variable = copyof_input.tokens[k - 1].variable;
                }
                copyof_input.tokens[i].num = 0.0;
                copyof_input.tokens[i].operator= '\0';
                copyof_input.tokens[i].variable = '\0';
            }
        }
    }

    // printf("[_U_]\n");
    // display_infix_exp(_U_);
    // printf("[_V_]\n");
    // display_infix_exp(_V_);

    // printf("[_DU_]\n");
    // display_infix_exp(_DU_);
    // printf("[_DV_]\n");
    // display_infix_exp(_DV_);

    free(_U_.tokens);
    free(_V_.tokens);
    free(_DU_.tokens);
    free(_DV_.tokens);
    return copyof_input;
}

string_ convert_INFIX_to_string(const __INFIX__ infix_exp)
{
    string_ empty_string = {0, NULL};

    if (infix_exp.size < 1 || infix_exp.tokens == NULL)
        return empty_string;

    string_ str_exp;
    str_exp.Len = MAX_STRING_INPUT_SIZE;
    str_exp.Content = create_new_buffer_with_sizeof(MAX_STRING_INPUT_SIZE);

    // Converter
    double num_;
    char variable_, operator_;
    for (int i = 0, j = 0; i < infix_exp.size && j < str_exp.Len; i++)
    {
        num_ = infix_exp.tokens[i].num;
        variable_ = infix_exp.tokens[i].variable;
        operator_ = infix_exp.tokens[i].operator;

        if (variable_ != '\0')
            str_exp.Content[j++] = variable_;
        else if (operator_ != '\0')
        {
            if (operator_ == SPECIFIER_OF_ABS)
                strcat(str_exp.Content, "abs");
            else if (operator_ == SPECIFIER_OF_SQRT)
                strcat(str_exp.Content, "sqrt");
            else if (operator_ == SPECIFIER_OF_CBRT)
                strcat(str_exp.Content, "cbrt");
            else if (operator_ == SPECIFIER_OF_SIN)
                strcat(str_exp.Content, "sin");
            else if (operator_ == SPECIFIER_OF_COS)
                strcat(str_exp.Content, "cos");
            else if (operator_ == SPECIFIER_OF_TAN)
                strcat(str_exp.Content, "tan");
            else if (operator_ == SPECIFIER_OF_COT)
                strcat(str_exp.Content, "cot");
            else if (operator_ == SPECIFIER_OF_SEC)
                strcat(str_exp.Content, "sec");
            else if (operator_ == SPECIFIER_OF_CSC)
                strcat(str_exp.Content, "csc");
            else if (operator_ == SPECIFIER_OF_ARCSIN)
                strcat(str_exp.Content, "arcsin");
            else if (operator_ == SPECIFIER_OF_ARCCOS)
                strcat(str_exp.Content, "arccos");
            else if (operator_ == SPECIFIER_OF_ARCTAN)
                strcat(str_exp.Content, "arctan");
            else if (operator_ == SPECIFIER_OF_ARCCOT)
                strcat(str_exp.Content, "arccot");
            else if (operator_ == SPECIFIER_OF_ARCSEC)
                strcat(str_exp.Content, "arcsec");
            else if (operator_ == SPECIFIER_OF_ARCCSC)
                strcat(str_exp.Content, "arccsc");
            else if (operator_ == SPECIFIER_OF_SINH)
                strcat(str_exp.Content, "sinh");
            else if (operator_ == SPECIFIER_OF_COSH)
                strcat(str_exp.Content, "cosh");
            else if (operator_ == SPECIFIER_OF_TANH)
                strcat(str_exp.Content, "tanh");
            else if (operator_ == SPECIFIER_OF_COTH)
                strcat(str_exp.Content, "coth");
            else if (operator_ == SPECIFIER_OF_SECH)
                strcat(str_exp.Content, "sech");
            else if (operator_ == SPECIFIER_OF_CSCH)
                strcat(str_exp.Content, "csch");
            else if (operator_ == SPECIFIER_OF_ARCSINH)
                strcat(str_exp.Content, "arcsinh");
            else if (operator_ == SPECIFIER_OF_ARCCOSH)
                strcat(str_exp.Content, "arccosh");
            else if (operator_ == SPECIFIER_OF_ARCTANH)
                strcat(str_exp.Content, "arctanh");
            else if (operator_ == SPECIFIER_OF_ARCCOTH)
                strcat(str_exp.Content, "arccoth");
            else if (operator_ == SPECIFIER_OF_ARCSECH)
                strcat(str_exp.Content, "arcsech");
            else if (operator_ == SPECIFIER_OF_ARCCSCH)
                strcat(str_exp.Content, "arccsch");
            else if (operator_ == SPECIFIER_OF_LN)
                strcat(str_exp.Content, "ln");
            else if (operator_ == SPECIFIER_OF_LG)
                strcat(str_exp.Content, "log");
            else if (operator_ == SPECIFIER_OF_GAMMA)
                strcat(str_exp.Content, "gamma");
            else if (operator_ == SPECIFIER_OF_CEIL)
                strcat(str_exp.Content, "ceil");
            else if (operator_ == SPECIFIER_OF_FLOOR)
                strcat(str_exp.Content, "floor");
            else if (operator_ == SPECIFIER_OF_LAMBERTW)
                strcat(str_exp.Content, "lambertw");
            else if (operator_ == SPECIFIER_OF_DIF)
                strcat(str_exp.Content, "dif");
            else if (operator_ == SPECIFIER_OF_INTEGRAL)
                strcat(str_exp.Content, "integral");
            else
            {
                // case: ) ope (
                if (infix_exp.tokens[i - 1].operator== ')' && infix_exp.tokens[i + 1].operator== '(')
                {
                    char special_case[4] = {' ', operator_, ' ', '\0'};
                    strcat(str_exp.Content, special_case);
                }

                // case: (num)
                // else if (operator_ == '(' && isfinite(infix_exp.tokens[i + 1].num) && infix_exp.tokens[i + 2].operator== ')')
                // {
                //     double _num_ = infix_exp.tokens[i + 1].num;
                //     char str_num[30] = {0};

                //     if (is_integer(_num_))
                //         sprintf(str_num, "%d", (int)_num_);
                //     else
                //         sprintf(str_num, "%.17lf", _num_);

                //     strcat(str_exp.Content, str_num);

                //     i += 2;
                // }

                // case: - negative_num
                else if (infix_exp.tokens[i].operator== '-' && infix_exp.tokens[i + 1].num<0.0)
                {
                    infix_exp.tokens[i + 1].num *= -1.0;
                    str_exp.Content[j++] = '+';
                }

                else
                    str_exp.Content[j++] = operator_;
            }
        }
        else
        {
            if (fabs(num_ - PI) < 1e-6)
                strcat(str_exp.Content, "pi");
            else if (fabs(num_ - EULER_NUMBER) < 1e-6)
                str_exp.Content[j++] = 'e';
            else if (fabs(num_ - _G_) < 1e-3)
                str_exp.Content[j++] = 'g';
            else if (fabs(num_ - LN_2) < 1e-6)
                strcat(str_exp.Content, "ln2");
            else if (fabs(num_ - SQRT_2) < 1e-6)
                strcat(str_exp.Content, "sqrt2");
            else if (fabs(num_ - SQRT_2_2) < 1e-6)
                strcat(str_exp.Content, "sqrt.5");
            else if (fabs(num_ - SQRT_3) < 1e-6)
                strcat(str_exp.Content, "sqrt3");
            else if (fabs(num_ - _C_) < 1)
                str_exp.Content[j++] = 'c';
            else
            {
                char str_num[30] = {0};
                if (fabs(num_) <= __DBL_EPSILON__ &&
                    (infix_exp.tokens[i - 1].operator== '-' || infix_exp.tokens[i - 1].operator== '+' || infix_exp.tokens[i - 1].operator== '(') &&
                    (infix_exp.tokens[i + 1].operator== '-' || infix_exp.tokens[i + 1].operator== '+' || infix_exp.tokens[i + 1].operator== ')'))
                {
                    continue;
                }
                else if (is_integer(num_))
                {
                    sprintf(str_num, "%d", (int)num_);
                }
                else
                {
                    sprintf(str_num, "%.19lf", num_);
                }
                strcat(str_exp.Content, str_num);
            }
        }

        j = strlen(str_exp.Content);
    }

    str_exp.Len = strlen(str_exp.Content);
    return str_exp;
}

void substitude_result(__INFIX__ *I_exp_tobe_replaced, const __INFIX__ replacement, const int index_start, const int index_end)
{
    int old_size = I_exp_tobe_replaced->size;
    /* Validate indices */
    if (index_start < 0 || index_end < index_start || index_end >= old_size)
        return;

    int remove_count = index_end - index_start + 1;
    int new_size = old_size - remove_count + replacement.size;

    /* Allocate new token array */
    _infix_ *new_tokens = malloc(new_size * sizeof(_infix_));
    if (!new_tokens)
    {
        return; /* out of memory */
    }

    /* 1. Copy tokens before index_start */
    if (index_start > 0)
    {
        memcpy(new_tokens,
               I_exp_tobe_replaced->tokens,
               index_start * sizeof(_infix_));
    }

    /* 2. Copy replacement tokens */
    if (replacement.size > 0)
    {
        memcpy(new_tokens + index_start,
               replacement.tokens,
               replacement.size * sizeof(_infix_));
    }

    /* 3. Copy tokens after index_end */
    int tail_count = old_size - (index_end + 1);
    if (tail_count > 0)
    {
        memcpy(new_tokens + index_start + replacement.size,
               I_exp_tobe_replaced->tokens + index_end + 1,
               tail_count * sizeof(_infix_));
    }

    // free old memory
    free(I_exp_tobe_replaced->tokens);
    I_exp_tobe_replaced->tokens = new_tokens;
    I_exp_tobe_replaced->size = new_size;
}

void copy_sub_I_exp(__INFIX__ *destination, __INFIX__ source, const short int index_start, const short int index_end)
{
    if (destination->tokens == NULL)
    {
        destination->size = index_end - index_start - 1;
        if (destination->size == 0)
            return;
        destination->tokens = (_infix_ *)calloc(destination->size, sizeof(_infix_));
        if (destination->tokens == NULL)
        {
            perror("Copy_sub_I_exp: Failed to malloc destination->tokens");
            return;
        }
    }

    int j = 0;
    for (int i = index_start + 1; i < index_end && j < (index_end - index_start + 1); i++, j++)
    {
        destination->tokens[j].num = source.tokens[i].num;
        destination->tokens[j].variable = source.tokens[i].variable;
        destination->tokens[j].operator= source.tokens[i].operator;
    }
}

bool handle_special_functions_(__INFIX__ *I_exp)
{
    /* no need for checking null pointer */

    _infix_ token_num[1] = {{NAN, '\0', '\0'}};
    __INFIX__ I_result = {1, token_num};

    for (int i = 0; i < I_exp->size; i++)
    {
        // ------------------ DERIVATIVE ------------------ //
        if (I_exp->tokens[i].operator== SPECIFIER_OF_DIF)
        {
            short int index_ddx = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_equal = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                bool found_colon_ = false;
                bool found_equal_ = false;

                // find outer_bracket_close
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (close_ == open_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LOG ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon++;

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                    }
                }

                // find equal
                if (I_exp->tokens[index_colon + 1].variable != '\0' && I_exp->tokens[index_colon + 2].operator== '=')
                    index_equal = index_colon + 2;
                else
                    return false;
                if (index_colon == -1 || index_equal == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("open = %d | colon = %d | equal = %d | close = %d\n", index_outer_bracket_open, index_colon, index_equal, index_outer_bracket_close);
            }

            char var;
            __INFIX__ function = {0, NULL}, valueOfVar = {0, NULL}, derivative;
            {
                // Extract the variable
                var = I_exp->tokens[index_colon + 1].variable;

                // extract the function
                copy_sub_I_exp(&function, *I_exp, index_outer_bracket_open, index_colon);
                if (function.tokens == NULL)
                    return false;

                // Handle nested special functions
                if (!handle_special_functions_(&function))
                {
                    free(function.tokens);
                    return false;
                }

                // Find derivative
                derivative = differentiate_I_exp(function, var);

                // Extract the value of variable
                copy_sub_I_exp(&valueOfVar, *I_exp, index_equal, index_outer_bracket_close);
                if (valueOfVar.tokens == NULL)
                {
                    free(function.tokens);
                    return false;
                }

                // evaluate valueOfVar
                double value = evaluate_I_exp(valueOfVar);

                if (isnan(value))
                {
                    free(function.tokens);
                    free(valueOfVar.tokens);
                    free(derivative.tokens);
                    return false;
                }

                // substitude valueofvar to var in the derivative
                for (int j = 0; j < derivative.size; j++)
                {
                    if (derivative.tokens[j].variable == var)
                    {
                        derivative.tokens[j].variable = '\0';
                        derivative.tokens[j].num = value;
                    }
                }
            }

            // check

            // printf("[__function__]\n");
            // display_infix_exp(function);
            // printf("[__DIFF__]\n");
            // display_infix_exp(derivative);
            // printf("[__var__] : %c\n", var);
            // printf("[__valueofvar__]\n");
            // display_infix_exp(valueOfVar);
            // printf("[__Result = %lf__]\n", result);

            // calculate the derivative & substitude to the expression
            _POSTFIX__ P_derivative = submodule_Parse(derivative);
            I_result.tokens[0].num = Compute_P_expression(P_derivative);
            free(P_derivative.tokens);

            // substitude
            substitude_result(I_exp, I_result, index_ddx, index_outer_bracket_close);

            free(function.tokens);
            free(valueOfVar.tokens);
            free(derivative.tokens);
        }

        // ------------------ INTEGRAL ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_INTEGRAL)
        {
            // integral(,,,)
            short int index_integral = i;
            short int index_outerbracket_open = i + 1;
            short int index_first_colon = -1;
            short int index_second_colon = -1;
            short int index_third_colon = -1;
            short int index_outer_bracket_close = -1;

            // find indice
            {
                // Find the index of the outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = index_outerbracket_open; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // Find the first colon
                {
                    short int skip_colon = 0;
                    for (short int k = index_outerbracket_open + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_GCD ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LCM ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_PERMUTATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_COMBINATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LOG)
                            skip_colon++;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_first_colon = k;
                            break;
                        }
                    }
                }

                // Find the second colon
                if (I_exp->tokens[index_first_colon + 1].variable != '\0' && I_exp->tokens[index_first_colon + 2].operator== ',')
                    index_second_colon = index_first_colon + 2;
                else
                    return false;

                // Find index of the third colon
                {
                    short int skip_colon = 0;
                    for (short int k = index_second_colon + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_GCD ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LCM ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_PERMUTATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_COMBINATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LOG)
                            skip_colon++;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_third_colon = k;
                            break;
                        }
                    }
                }

                if (index_first_colon == -1 || index_second_colon == -1 || index_third_colon == -1 || index_outer_bracket_close == -1)
                    return false;
            }

            // check
            // printf("integral = %d | open_ = %d | 1colon = %d | 2colon = %d | 3colon = %d | close_ = %d\n", index_integral, index_outerbracket_open, index_first_colon, index_second_colon, index_third_colon, index_outer_bracket_close);

            // Extract the function
            __INFIX__ function = {0, NULL};
            copy_sub_I_exp(&function, *I_exp, index_outerbracket_open, index_first_colon);

            // handle nested special functions
            if (!handle_special_functions_(&function))
            {
                free(function.tokens);
                return false;
            }

            // Extract the variable
            char var = I_exp->tokens[index_first_colon + 1].variable;

            // Extract the lower bound
            __INFIX__ lower_bound = {0, NULL};
            copy_sub_I_exp(&lower_bound, *I_exp, index_second_colon, index_third_colon);

            // Extract the upper bound
            __INFIX__ upper_bound = {0, NULL};
            copy_sub_I_exp(&upper_bound, *I_exp, index_third_colon, index_outer_bracket_close);

            // check
            // printf("\nFUNCTION\n");
            // display_infix_exp(function);
            // printf("\nLOWER BOUND\n");
            // display_infix_exp(lower_bound);
            // printf("\nUPPER BOUND\n");
            // display_infix_exp(upper_bound);

            // calculate the integral & substitude to the integral
            double l_bound = evaluate_I_exp(lower_bound);
            double u_bound = evaluate_I_exp(upper_bound);

            if (isnan(l_bound) || isnan(u_bound))
            {
                free(function.tokens);
                free(lower_bound.tokens);
                free(upper_bound.tokens);
                return false;
            }

            I_result.tokens[0].num = integral_definite_infix(function, var, l_bound, u_bound);
            // substitude
            substitude_result(I_exp, I_result, index_integral, index_outer_bracket_close);

            free(function.tokens);
            free(lower_bound.tokens);
            free(upper_bound.tokens);
        }

        // ------------------ SIGMA-SUM || SUM-SEQUENCE ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_SIGMA_SUM)
        {
            short int index_sumsequence = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon_1 = -1;
            short int index_colon_2 = -1;
            short int index_colon_3 = -1;
            short int index_colon_4 = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // Find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = index_outer_bracket_open; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }
                }

                // find colon 1
                {
                    short int skip_colon = 0;
                    for (short int k = index_outer_bracket_open + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_GCD ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LCM ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_PERMUTATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_COMBINATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LOG)
                            skip_colon++;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_1 = k;
                            break;
                        }
                    }
                }

                // find colon 2
                if (I_exp->tokens[index_colon_1 + 1].variable != '\0' && I_exp->tokens[index_colon_1 + 2].operator== ',')
                    index_colon_2 = index_colon_1 + 2;
                else
                    return false;

                // find colon 3
                {
                    short int skip_colon = 0;
                    for (short int k = index_colon_2 + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_3 = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                // find colon 4
                {
                    short int skip_colon = 0;
                    for (short int k = index_colon_3 + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_4 = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon_1 == -1 || index_colon_2 == -1 || index_colon_3 == -1 || index_colon_4 == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("sum = %d | open = %d | c1 = %d | c2 = %d | c3 = %d | c4 = %d | close = %d\n", index_sumsequence, index_outer_bracket_open, index_colon_1, index_colon_2, index_colon_3, index_colon_4, index_outer_bracket_close);

                __INFIX__ function = {0, NULL};
                char var;
                __INFIX__ I_start = {0, NULL};
                __INFIX__ I_end = {0, NULL};
                __INFIX__ I_step = {0, NULL};

                double start, end, step, result;

                // extract the function
                copy_sub_I_exp(&function, *I_exp, index_outer_bracket_open, index_colon_1);

                // handle nested special functions
                if (!handle_special_functions_(&function))
                {
                    free(function.tokens);
                    return false;
                }

                // extract the variable
                var = I_exp->tokens[index_colon_1 + 1].variable;

                // extract the starting value
                copy_sub_I_exp(&I_start, *I_exp, index_colon_2, index_colon_3);

                // extract the ending value
                copy_sub_I_exp(&I_end, *I_exp, index_colon_3, index_colon_4);

                // extract the stepping value
                copy_sub_I_exp(&I_step, *I_exp, index_colon_4, index_outer_bracket_close);

                // evaluate start ; end & step
                start = evaluate_I_exp(I_start);
                end = evaluate_I_exp(I_end);
                step = evaluate_I_exp(I_step);

                result = sum_sequence(function, var, start, end, step);

                if (isnan(result))
                {
                    free(function.tokens);
                    free(I_start.tokens);
                    free(I_end.tokens);
                    free(I_step.tokens);
                    return false;
                }

                I_result.tokens[0].num = result;

                // substitude result to I_exp
                substitude_result(I_exp, I_result, index_sumsequence, index_outer_bracket_close);

                free(function.tokens);
                free(I_start.tokens);
                free(I_end.tokens);
                free(I_step.tokens);
            }
        }

        // ------------------ PRODUCT-SEQUENCE ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
        {
            short int index_productsequence = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon_1 = -1;
            short int index_colon_2 = -1;
            short int index_colon_3 = -1;
            short int index_colon_4 = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // Find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = index_outer_bracket_open; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }
                }

                // find colon 1
                {
                    short int skip_colon = 0;
                    for (short int k = index_outer_bracket_open + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_GCD ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LCM ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_PERMUTATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_COMBINATIONS ||
                            I_exp->tokens[k]
                                .operator== SPECIFIER_OF_LOG)
                            skip_colon++;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_1 = k;
                            break;
                        }
                    }
                }

                // find colon 2
                if (I_exp->tokens[index_colon_1 + 1].variable != '\0' && I_exp->tokens[index_colon_1 + 2].operator== ',')
                    index_colon_2 = index_colon_1 + 2;
                else
                    return false;

                // find colon 3
                {
                    short int skip_colon = 0;
                    for (short int k = index_colon_2 + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_3 = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                // find colon 4
                {
                    short int skip_colon = 0;
                    for (short int k = index_colon_3 + 1; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon_4 = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon_1 == -1 || index_colon_2 == -1 || index_colon_3 == -1 || index_colon_4 == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("sum = %d | open = %d | c1 = %d | c2 = %d | c3 = %d | c4 = %d | close = %d\n", index_sumsequence, index_outer_bracket_open, index_colon_1, index_colon_2, index_colon_3, index_colon_4, index_outer_bracket_close);

                __INFIX__ function = {0, NULL};
                char var;
                __INFIX__ I_start = {0, NULL};
                __INFIX__ I_end = {0, NULL};
                __INFIX__ I_step = {0, NULL};

                double start, end, step, result;

                // extract the function
                copy_sub_I_exp(&function, *I_exp, index_outer_bracket_open, index_colon_1);

                // handle nested special functions
                if (!handle_special_functions_(&function))
                {
                    free(function.tokens);
                    return false;
                }

                // extract the variable
                var = I_exp->tokens[index_colon_1 + 1].variable;

                // extract the starting value
                copy_sub_I_exp(&I_start, *I_exp, index_colon_2, index_colon_3);

                // extract the ending value
                copy_sub_I_exp(&I_end, *I_exp, index_colon_3, index_colon_4);

                // extract the stepping value
                copy_sub_I_exp(&I_step, *I_exp, index_colon_4, index_outer_bracket_close);

                // evaluate start ; end & step
                start = evaluate_I_exp(I_start);
                end = evaluate_I_exp(I_end);
                step = evaluate_I_exp(I_step);

                result = product_sequence(function, var, start, end, step);

                if (isnan(result))
                {
                    free(function.tokens);
                    free(I_start.tokens);
                    free(I_end.tokens);
                    free(I_step.tokens);
                    return false;
                }

                I_result.tokens[0].num = result;

                // substitude result to I_exp
                substitude_result(I_exp, I_result, index_productsequence, index_outer_bracket_close);

                free(function.tokens);
                free(I_start.tokens);
                free(I_end.tokens);
                free(I_step.tokens);
            }
        }

        // ------------------ Greatest Common Divisor ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_GCD)
        {
            short int index_GCD = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon == -1 || index_outer_bracket_close == -1)
                    return false;
            }

            __INFIX__ I_value1 = {0, NULL};
            __INFIX__ I_value2 = {0, NULL};
            double value1, value2;

            // extract the expressions
            copy_sub_I_exp(&I_value1, *I_exp, index_outer_bracket_open, index_colon);
            copy_sub_I_exp(&I_value2, *I_exp, index_colon, index_outer_bracket_close);

            // evaluate the expressions
            value1 = evaluate_I_exp(I_value1);
            value2 = evaluate_I_exp(I_value2);

            // puts("\nVALUE\n");
            // display_infix_exp(I_value1);
            // display_infix_exp(I_value2);

            free(I_value1.tokens);
            free(I_value2.tokens);

            // Calculate GCD
            if (!is_integer(value1) || !is_integer(value2) || value1 > value2)
                return false;

            I_result.tokens[0].num = (double)gcd((int)value1, (int)value2);
            // Substitude
            substitude_result(I_exp, I_result, index_GCD, index_outer_bracket_close);

            // puts("\n[AFTER]\n");
            // display_infix_exp(*I_exp);
        }

        // ------------------ Least Common Multiplier ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_LCM)
        {
            short int index_LCM = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("INDEX: LCM = %d | open = %d | colon = %d | close = %d\n", index_LCM, index_outer_bracket_open, index_colon, index_outer_bracket_close);
            }

            __INFIX__ I_value1 = {0, NULL};
            __INFIX__ I_value2 = {0, NULL};
            double value1, value2;

            // extract the first expression
            copy_sub_I_exp(&I_value1, *I_exp, index_outer_bracket_open, index_colon);
            copy_sub_I_exp(&I_value2, *I_exp, index_colon, index_outer_bracket_close);

            // evaluate the expressions
            value1 = evaluate_I_exp(I_value1);
            value2 = evaluate_I_exp(I_value2);

            // puts("\nVALUE\n");
            // display_infix_exp(I_value1);
            // display_infix_exp(I_value2);

            free(I_value1.tokens);
            free(I_value2.tokens);

            // Calculate GCD
            if (!is_integer(value1) || !is_integer(value2) || value1 > value2)
                return false;

            I_result.tokens[0].num = (double)lcm((int)value1, (int)value2);
            // Substitude
            substitude_result(I_exp, I_result, index_LCM, index_outer_bracket_close);

            // puts("\n[AFTER]\n");
            // display_infix_exp(*I_exp);
        }

        // ------------------ Permutations ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_PERMUTATIONS)
        {
            short int index_permutations = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("INDEX: LCM = %d | open = %d | colon = %d | close = %d\n", index_LCM, index_outer_bracket_open, index_colon, index_outer_bracket_close);
            }

            __INFIX__ I_value1 = {0, NULL};
            __INFIX__ I_value2 = {0, NULL};
            double value1, value2;

            // extract the first expression
            copy_sub_I_exp(&I_value1, *I_exp, index_outer_bracket_open, index_colon);
            copy_sub_I_exp(&I_value2, *I_exp, index_colon, index_outer_bracket_close);

            // evaluate the expressions
            value1 = evaluate_I_exp(I_value1);
            value2 = evaluate_I_exp(I_value2);

            // puts("\nVALUE\n");
            // display_infix_exp(I_value1);
            // display_infix_exp(I_value2);

            free(I_value1.tokens);
            free(I_value2.tokens);

            // Calculate GCD
            if (!is_integer(value1) || !is_integer(value2))
                return false;
            I_result.tokens[0].num = permutations((int)value1, (int)value2);
            // Substitude
            substitude_result(I_exp, I_result, index_permutations, index_outer_bracket_close);

            // puts("\n[AFTER]\n");
            // display_infix_exp(*I_exp);
        }

        // ------------------ Combinations ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_COMBINATIONS)
        {
            short int index_combinations = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("INDEX: LCM = %d | open = %d | colon = %d | close = %d\n", index_LCM, index_outer_bracket_open, index_colon, index_outer_bracket_close);
            }

            __INFIX__ I_value1 = {0, NULL};
            __INFIX__ I_value2 = {0, NULL};
            double value1, value2;

            // extract the first expression
            copy_sub_I_exp(&I_value1, *I_exp, index_outer_bracket_open, index_colon);
            copy_sub_I_exp(&I_value2, *I_exp, index_colon, index_outer_bracket_close);

            // evaluate the expressions
            value1 = evaluate_I_exp(I_value1);
            value2 = evaluate_I_exp(I_value2);

            // puts("\nVALUE\n");
            // display_infix_exp(I_value1);
            // display_infix_exp(I_value2);

            free(I_value1.tokens);
            free(I_value2.tokens);

            // Calculate GCD
            if (!is_integer(value1) || !is_integer(value2))
                return false;
            I_result.tokens[0].num = combinations((int)value1, (int)value2);
            // Substitude
            substitude_result(I_exp, I_result, index_combinations, index_outer_bracket_close);

            // puts("\n[AFTER]\n");
            // display_infix_exp(*I_exp);
        }

        // ------------------ Logarithm ------------------ //
        else if (I_exp->tokens[i].operator== SPECIFIER_OF_LOG)
        {
            short int index_logarithm = i;
            short int index_outer_bracket_open = i + 1;
            short int index_colon = -1;
            short int index_outer_bracket_close = -1;

            // Find indice
            {
                // find outer close bracket
                {
                    short int open_ = 0;
                    short int close_ = 0;
                    for (short int k = i + 1; k < I_exp->size; k++)
                    {
                        if (I_exp->tokens[k].operator== '(')
                            open_++;
                        else if (I_exp->tokens[k].operator== ')')
                            close_++;

                        if (open_ == close_)
                        {
                            index_outer_bracket_close = k;
                            break;
                        }
                    }

                    if (open_ != close_)
                        return false;
                }

                // find colon
                {
                    short int skip_colon = 0;
                    for (short int k = i + 2; k < index_outer_bracket_close; k++)
                    {
                        if (I_exp->tokens[k].operator== ',' && skip_colon == 0)
                        {
                            index_colon = k;
                            break;
                        }

                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_DIF ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_GCD ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LOG ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_LCM ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_PERMUTATIONS ||
                                 I_exp->tokens[k]
                                     .operator== SPECIFIER_OF_COMBINATIONS)
                            skip_colon += 1;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_INTEGRAL)
                            skip_colon += 3;
                        else if (I_exp->tokens[k].operator== SPECIFIER_OF_SIGMA_SUM || I_exp->tokens[k].operator== SPECIFIER_OF_PRODUCT_OF_SEQUENCE)
                            skip_colon += 4;
                        else if (I_exp->tokens[k].operator== ',' && skip_colon != 0)
                            skip_colon--;
                    }
                }

                if (index_colon == -1 || index_outer_bracket_close == -1)
                    return false;

                // check
                // printf("INDEX: LCM = %d | open = %d | colon = %d | close = %d\n", index_LCM, index_outer_bracket_open, index_colon, index_outer_bracket_close);
            }

            __INFIX__ I_base = {0, NULL};
            __INFIX__ I_expression = {0, NULL};
            double base, expression;

            // extract the first expression
            copy_sub_I_exp(&I_base, *I_exp, index_outer_bracket_open, index_colon);
            copy_sub_I_exp(&I_expression, *I_exp, index_colon, index_outer_bracket_close);

            // evaluate the expressions
            base = evaluate_I_exp(I_base);
            expression = evaluate_I_exp(I_expression);

            // puts("\nVALUE\n");
            // display_infix_exp(I_value1);
            // display_infix_exp(I_value2);

            free(I_base.tokens);
            free(I_expression.tokens);

            // Calculate the logarithm
            I_result.tokens[0].num = logarithm(base, expression);
            if (isnan(I_result.tokens[0].num))
                return false;
            // Substitude
            substitude_result(I_exp, I_result, index_logarithm, index_outer_bracket_close);

            // puts("\n[AFTER]\n");
            // display_infix_exp(*I_exp);
        }
    }

    return true;
}

double integral_definite_infix(__INFIX__ infix_function, const char var, const double lower_bound, const double upper_bound)
{
    double result;
    _POSTFIX__ P_function = {0, NULL};

    // Validate input
    if (infix_function.size == 0 || infix_function.tokens == NULL)
        return NAN;

    // optimze function for minimum delay
    optimize_I_exp(&infix_function);

    // Convert infix to postfix for computation
    P_function = submodule_Parse(infix_function);

    if (P_function.size == 0 || P_function.tokens == NULL)
        return NAN;

    double n = 100000.0; // Number of subintervals - Larger n --> More accurate
    double a, b, h;
    char str_var[2] = {var, '\0'};

    if (lower_bound != -INFINITY && lower_bound != INFINITY && upper_bound != INFINITY && upper_bound != -INFINITY)
    {
        a = lower_bound;
        b = upper_bound;
        h = (b - a) / n;
    }
    // Beta version; may return wrong values for infinite bounds
    else
    {
        a = (double)((lower_bound == -INFINITY) ? -100000 : lower_bound);
        b = (double)((upper_bound == INFINITY) ? 100000 : upper_bound);
        h = (b - a) / (1000 * n);
    }

    // Apply Simpson's rule
    result = Compute_P_function(P_function, str_var, a) + Compute_P_function(P_function, str_var, b);

    for (double i = 1.0; i < n; i++)
    {
        double x = a + i * h;
        double coefficient;
        if ((int)i % 2 == 0)
            coefficient = 2;
        else
            coefficient = 4;

        double result_p = result;
        result += coefficient * Compute_P_function(P_function, str_var, x);

        // if (fabs(result_p - result) <= __DBL_EPSILON__)
        // {
        //     printf("i = %.1lf\n", i);
        //     break;
        // }
    }

    result *= (h / 3);

    // Clean up allocated memory
    free(P_function.tokens);
    return result;
}

void display_postfix_exp(_POSTFIX__ P_exp)
{
    if (P_exp.size < 1 || P_exp.tokens == NULL)
        return;

    double num_;
    char var_, op_;

    for (short int i = 0; i < P_exp.size; i++)
    {
        num_ = P_exp.tokens[i].num;
        var_ = P_exp.tokens[i].variable;
        op_ = P_exp.tokens[i].operator;

        if (!isnan(num_))
            printf("Num: %.17lf\n", num_);
        else if (var_ != '\0')
            printf("Var: %c\n", var_);
        else
            printf("Op: %c\n", op_);
    }
}

void optimize_P_exp(_POSTFIX__ *P_exp)
{
    if (P_exp->size < 2 || P_exp->tokens == NULL)
        return;

    // check
    printf("[Before]\n\n");
    display_postfix_exp(*P_exp);
    putchar('\n');

    char OP_;
    bool standard_op;
    bool new_changes;

    for (short int i = 0; i < P_exp->size; i++)
    {
        new_changes = false;
        standard_op = false;
        OP_ = P_exp->tokens[i].operator;

        if (OP_ == '\0')
            continue;

        // 2-parameter operators
        if ((OP_ == '-' || OP_ == '+' || OP_ == '*' || OP_ == '/' || OP_ == '^' || OP_ == '%') && !isnan(P_exp->tokens[i - 1].num) && !isnan(P_exp->tokens[i - 2].num))
        {
            standard_op = true;
            new_changes = true;

            // check
            printf("\nOP_ = %c\n", OP_);

            switch (OP_)
            {
            case '+': // addition
                P_exp->tokens[i - 2].num = P_exp->tokens[i - 2].num + P_exp->tokens[i - 1].num;
                break;
            case '-': // substraction
                P_exp->tokens[i - 2].num = P_exp->tokens[i - 2].num - P_exp->tokens[i - 1].num;
                break;
            case '*': // multiplication
                P_exp->tokens[i - 2].num = P_exp->tokens[i - 2].num * P_exp->tokens[i - 1].num;
                break;
            case '/': // division
            {
                if (P_exp->tokens[i - 1].num == 0)
                    return;
                P_exp->tokens[i - 2].num = P_exp->tokens[i - 2].num / P_exp->tokens[i - 1].num;
                break;
            }
            case '%': // remainder modulo
            {
                if (!is_integer(P_exp->tokens[i - 2].num) || !is_integer(P_exp->tokens[i - 1].num))
                    return;
                P_exp->tokens[i - 2].num = (double)(((int)P_exp->tokens[i - 2].num) % ((int)P_exp->tokens[i - 1].num));
                break;
            }
            case '^': // exponential
                P_exp->tokens[i - 2].num = pow(P_exp->tokens[i - 2].num, P_exp->tokens[i - 1].num);
                break;
            default:
                break;
            }
        }

        // 1-parameter functions
        else if (OP_ != SPECIFIER_OF_DIF && OP_ != SPECIFIER_OF_INTEGRAL &&
                 OP_ != '-' &&
                 OP_ != '+' &&
                 OP_ != '*' &&
                 OP_ != '/' &&
                 OP_ != '^' &&
                 OP_ != '%')
        {
            new_changes = true;

            switch (OP_)
            {
            case SPECIFIER_OF_SIN: // sin
                P_exp->tokens[i - 1].num = sin(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SINH: // sinh
                P_exp->tokens[i - 1].num = sinh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SEC: // sec
                P_exp->tokens[i - 1].num = 1 / cos(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_SECH: // sech
                P_exp->tokens[i - 1].num = 1 / cosh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSEC: // arcsec
                P_exp->tokens[i - 1].num = arcsec(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSECH: // arcsech
                P_exp->tokens[i - 1].num = arcsech(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COS: // cos
                P_exp->tokens[i - 1].num = cos(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COSH: // cosh
                P_exp->tokens[i - 1].num = cosh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSC: // csc
                P_exp->tokens[i - 1].num = 1 / sin(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_CSCH: // csch
                P_exp->tokens[i - 1].num = csch(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSC: // arccsc
                P_exp->tokens[i - 1].num = arccsc(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCSCH: // arccsch
                P_exp->tokens[i - 1].num = arccsch(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TAN: // tan
                P_exp->tokens[i - 1].num = tan(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_TANH: // tanh
                P_exp->tokens[i - 1].num = tanh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COT: // cot
                P_exp->tokens[i - 1].num = 1 / tan(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_COTH: // coth
                P_exp->tokens[i - 1].num = coth(P_exp->tokens[i - 1].num);
                break;
            case '!': // factorial
            {
                // Check if it's an integer or not
                if (!is_integer(P_exp->tokens[i - 1].num) || P_exp->tokens[i - 1].num < 0)
                    return;
                int fac = 1;
                int n = (int)P_exp->tokens[i - 1].num;
                for (int f = 1; f <= n; f++)
                    fac *= f;
                P_exp->tokens[i - 1].num = (double)fac;
                break;
            }
            case SPECIFIER_OF_ARCSIN: // arcsin
                P_exp->tokens[i - 1].num = asin(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCSINH: // arcsinh
                P_exp->tokens[i - 1].num = asinh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOS: // arccos
                P_exp->tokens[i - 1].num = acos(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOSH: // arccosh
                P_exp->tokens[i - 1].num = acosh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTAN: // arctan
                P_exp->tokens[i - 1].num = atan(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCTANH: // arctanh
                P_exp->tokens[i - 1].num = atanh(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_ARCCOT: // arccot
            {
                if (P_exp->tokens[i - 1].num > 0)
                    P_exp->tokens[i - 1].num = atan(1 / (P_exp->tokens[i - 1].num));
                else
                    P_exp->tokens[i - 1].num = atan(1 / (P_exp->tokens[i - 1].num)) + PI;
                break;
            }
            case SPECIFIER_OF_ARCCOTH: // arccoth
                P_exp->tokens[i - 1].num = arccoth(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LN: // ln
            {
                if (P_exp->tokens[i - 1].num <= 0)
                    return;
                P_exp->tokens[i - 1].num = log(P_exp->tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_LG: // log10
            {
                if (P_exp->tokens[i - 1].num <= 0)
                    return;
                P_exp->tokens[i - 1].num = log10(P_exp->tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_SQRT: // sqrt
            {
                if (P_exp->tokens[i - 1].num < 0)
                    return;
                P_exp->tokens[i - 1].num = sqrt(P_exp->tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_ABS: // abs
            {
                if (P_exp->tokens[i - 1].num < 0)
                    P_exp->tokens[i - 1].num = -P_exp->tokens[i - 1].num;
                break;
            }
            case SPECIFIER_OF_CBRT: // cuberoot
                P_exp->tokens[i - 1].num = cbrt(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_GAMMA: // gamma function
            {
                if (P_exp->tokens[i - 1].num < 0)
                    return;
                P_exp->tokens[i - 1].num = gamma_function(P_exp->tokens[i - 1].num);
                break;
            }
            case SPECIFIER_OF_CEIL: // ceiling function
                P_exp->tokens[i - 1].num = ceil(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_FLOOR: // floor function
                P_exp->tokens[i - 1].num = floor(P_exp->tokens[i - 1].num);
                break;
            case SPECIFIER_OF_LAMBERTW: // lambert W function
            {
                if (P_exp->tokens[i - 1].num < -1 / EULER_NUMBER)
                    return;
                P_exp->tokens[i - 1].num = lambertw_real(P_exp->tokens[i - 1].num);
                break;
            }
            default:
                break;
            }
        }

        if (!new_changes)
            continue;

        // Realloc P_exp
        if (standard_op)
        {
            // shifting left
            for (int k = i - 1; k < P_exp->size - 2; k++)
            {
                P_exp->tokens[k].num = P_exp->tokens[k + 2].num;
                P_exp->tokens[k].operator= P_exp->tokens[k + 2].operator;
                P_exp->tokens[k].variable = P_exp->tokens[k + 2].variable;
            }

            // shrink memories
            _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(P_exp->tokens, (P_exp->size - 2) * sizeof(_TOKENS_DATA_));
            if (temp_ptr == NULL)
            {
                perror("optimize_P_exp - standard_op: Failed to realloc temp_ptr");
                return;
            }
            P_exp->tokens = temp_ptr;
            P_exp->size -= 2;
            i -= 2;
        }
        else
        {
            // shifting left
            for (int k = i; k < P_exp->size - 1; k++)
            {
                P_exp->tokens[k].num = P_exp->tokens[k + 1].num;
                P_exp->tokens[k].operator= P_exp->tokens[k + 1].operator;
                P_exp->tokens[k].variable = P_exp->tokens[k + 1].variable;
            }

            // shrink memories
            _TOKENS_DATA_ *temp_ptr = (_TOKENS_DATA_ *)realloc(P_exp->tokens, (P_exp->size - 1) * sizeof(_TOKENS_DATA_));
            if (temp_ptr == NULL)
            {
                perror("optimize_P_exp - functions: Failed to realloc temp_ptr");
                return;
            }
            P_exp->tokens = temp_ptr;
            P_exp->size--;
            i -= 1;
        }
    }
}

void optimize_I_exp(__INFIX__ *I_exp)
{
    if (I_exp->size < 2 || I_exp->tokens == NULL)
        return;

    // reference
    // puts("[Before]\n\n");
    // display_infix_exp(*I_exp);

    _infix_ token_num[1] = {NAN, '\0', '\0'};
    __INFIX__ replacement = {1, token_num};
    char OP_;
    double num_;
    bool standard_op;
    bool new_changes;
    short int index_start, index_end;

    for (short int i = 0; i < I_exp->size; i++)
    {
        OP_ = I_exp->tokens[i].operator;
        standard_op = false;
        new_changes = false;

        if (OP_ == '+' ||
            OP_ == '-' ||
            OP_ == '*' ||
            OP_ == '/' ||
            OP_ == '^' ||
            OP_ == '%' ||
            OP_ == '!' ||
            OP_ == '(' ||
            OP_ == ')')
            standard_op = true;

        // Optimizer
        {
            // For OP
            if (OP_ != '\0' &&
                OP_ != SPECIFIER_OF_INTEGRAL &&
                OP_ != SPECIFIER_OF_DIF &&
                OP_ != SPECIFIER_OF_SIGMA_SUM &&
                OP_ != SPECIFIER_OF_PRODUCT_OF_SEQUENCE &&
                OP_ != SPECIFIER_OF_PERMUTATIONS &&
                OP_ != SPECIFIER_OF_COMBINATIONS &&
                OP_ != SPECIFIER_OF_GCD &&
                OP_ != SPECIFIER_OF_LCM &&
                OP_ != ',' &&
                OP_ != '=')
            {
                // case 1: = | , | ( | + | - NUM + | - NUM + | - | ) | , | =
                if ((i == 1 || I_exp->tokens[i - 2].operator== '=' || I_exp->tokens[i - 2].operator== ',' || I_exp->tokens[i - 2].operator== '(' || I_exp->tokens[i - 2].operator== '+' || I_exp->tokens[i - 2].operator== '-') &&
                    !isnan(I_exp->tokens[i - 1].num) &&
                    (OP_ == '+' || OP_ == '-') &&
                    !isnan(I_exp->tokens[i + 1].num) &&
                    (i + 2 == I_exp->size || I_exp->tokens[i + 2].operator== '+' || I_exp->tokens[i + 2].operator== '-' || I_exp->tokens[i + 2].operator== ')' || I_exp->tokens[i + 2].operator== ',' || I_exp->tokens[i + 2].operator== '='))
                {
                    new_changes = true;

                    // puts("Case 1");

                    if (I_exp->tokens[i - 2].operator== '-')
                    {
                        I_exp->tokens[i - 2].operator= '+';
                        replacement.tokens[0].num = (OP_ == '+') ? (-(I_exp->tokens[i - 1].num) + I_exp->tokens[i + 1].num) : (-(I_exp->tokens[i - 1].num) - I_exp->tokens[i + 1].num);
                    }
                    else
                        replacement.tokens[0].num = (OP_ == '+') ? (I_exp->tokens[i - 1].num + I_exp->tokens[i + 1].num) : (I_exp->tokens[i - 1].num - I_exp->tokens[i + 1].num);

                    index_start = i - 1;
                    index_end = i + 1;
                }

                // case 2: NUM * | / | ^ | % NUM
                else if ((OP_ == '*' || OP_ == '/' || OP_ == '^' || OP_ == '%') &&
                         !isnan(I_exp->tokens[i - 1].num) &&
                         !isnan(I_exp->tokens[i + 1].num))
                {
                    new_changes = true;

                    // puts("case 2");

                    switch (OP_)
                    {
                    case '*':
                        replacement.tokens[0].num = I_exp->tokens[i - 1].num * I_exp->tokens[i + 1].num;
                        break;
                    case '/':
                    {
                        if (I_exp->tokens[i + 1].num == 0.0)
                            return;
                        replacement.tokens[0].num = I_exp->tokens[i - 1].num / I_exp->tokens[i + 1].num;
                        break;
                    }
                    case '^':
                        replacement.tokens[0].num = pow(I_exp->tokens[i - 1].num, I_exp->tokens[i + 1].num);
                        break;
                    case '%':
                    {
                        if (!is_integer(I_exp->tokens[i - 1].num) && !isnan(I_exp->tokens[i + 1].num))
                            return;
                        replacement.tokens[0].num = (double)(((int)I_exp->tokens[i - 1].num) % ((int)I_exp->tokens[i + 1].num));
                        break;
                    }
                    default:
                        break;
                    }

                    index_start = i - 1;
                    index_end = i + 1;
                }

                // case 3: NUM !
                else if (OP_ == '!' && !isnan(I_exp->tokens[i - 1].num))
                {
                    if (I_exp->tokens[i - 1].num < 0 || !is_integer(I_exp->tokens[i - 1].num))
                        return;

                    replacement.tokens[0].num = (double)factorial((int)I_exp->tokens[i - 1].num);

                    new_changes = true;

                    index_start = i - 1;
                    index_end = i;
                }

                // case 4: functions( NUM )
                else if (!isnan(I_exp->tokens[i + 1].num) && !standard_op)
                {
                    // puts("case 4");
                    new_changes = true;
                    double num_ = I_exp->tokens[i + 1].num;
                    double replacement_num;

                    // printf("Case 4: OP_ = %c | num_ = %lf\n", OP_, num_);

                    switch (OP_)
                    {
                    case SPECIFIER_OF_SIN:
                        replacement_num = sin(num_);
                        break;
                    case SPECIFIER_OF_SINH:
                        replacement_num = sinh(num_);
                        break;
                    case SPECIFIER_OF_ARCSIN:
                        replacement_num = asin(num_);
                        break;
                    case SPECIFIER_OF_ARCSINH:
                        replacement_num = asinh(num_);
                        break;
                    case SPECIFIER_OF_COS:
                        replacement_num = cos(num_);
                        break;
                    case SPECIFIER_OF_COSH:
                        replacement_num = cosh(num_);
                        break;
                    case SPECIFIER_OF_ARCCOS:
                        replacement_num = acos(num_);
                        break;
                    case SPECIFIER_OF_ARCCOSH:
                        replacement_num = acosh(num_);
                        break;
                    case SPECIFIER_OF_TAN:
                        replacement_num = tan(num_);
                        break;
                    case SPECIFIER_OF_TANH:
                        replacement_num = tanh(num_);
                        break;
                    case SPECIFIER_OF_ARCTAN:
                        replacement_num = atan(num_);
                        break;
                    case SPECIFIER_OF_ARCTANH:
                        replacement_num = atanh(num_);
                        break;
                    case SPECIFIER_OF_COT:
                        replacement_num = 1.0 / tan(num_);
                        break;
                    case SPECIFIER_OF_COTH:
                        replacement_num = 1.0 / tanh(num_);
                        break;
                    case SPECIFIER_OF_ARCCOT:
                    {
                        if (I_exp->tokens[i + 1].num > 0.0)
                            replacement_num = atan(1.0 / num_);
                        else
                            replacement_num = atan(1.0 / num_) + PI;
                        break;
                    }
                    case SPECIFIER_OF_ARCCOTH:
                        replacement_num = arccoth(num_);
                        break;
                    case SPECIFIER_OF_SEC:
                        replacement_num = 1.0 / cos(num_);
                        break;
                    case SPECIFIER_OF_SECH:
                        replacement_num = 1.0 / cosh(num_);
                        break;
                    case SPECIFIER_OF_ARCSEC:
                        replacement_num = acos(1.0 / num_);
                        break;
                    case SPECIFIER_OF_ARCSECH:
                        replacement_num = acosh(1.0 / num_);
                        break;
                    case SPECIFIER_OF_CSC:
                        replacement_num = 1.0 / sin(num_);
                        break;
                    case SPECIFIER_OF_CSCH:
                        replacement_num = 1.0 / sinh(num_);
                        break;
                    case SPECIFIER_OF_ARCCSC:
                        replacement_num = asin(1.0 / num_);
                        break;
                    case SPECIFIER_OF_ARCCSCH:
                        replacement_num = asinh(1.0 / num_);
                        break;
                    case SPECIFIER_OF_SQRT:
                    {
                        if (num_ < 0.0)
                            return;
                        replacement_num = sqrt(num_);
                        break;
                    }
                    case SPECIFIER_OF_CBRT:
                        replacement_num = cbrt(num_);
                        break;
                    case SPECIFIER_OF_ABS:
                        replacement_num = fabs(num_);
                        break;
                    case SPECIFIER_OF_LN:
                    {
                        if (num_ <= 0.0)
                            return;
                        replacement_num = log(num_);
                        break;
                    }
                    case SPECIFIER_OF_LG:
                    {
                        if (num_ <= 0.0)
                            return;
                        replacement_num = log10(num_);
                        break;
                    }
                    case SPECIFIER_OF_GAMMA:
                    {
                        if (num_ < 0.0)
                            return;
                        replacement_num = tgamma(num_);
                        break;
                    }
                    case SPECIFIER_OF_CEIL:
                        replacement_num = ceil(num_);
                        break;
                    case SPECIFIER_OF_FLOOR:
                        replacement_num = floor(num_);
                        break;
                    case SPECIFIER_OF_LAMBERTW:
                    {
                        if (num_ < -1.0 / EULER_NUMBER)
                            return;
                        replacement_num = lambertw_real(num_);
                        break;
                    }
                    default:
                        return;
                    }

                    // printf("Num = %lf | Replacement_num = %lf\n", num_, replacement_num);

                    replacement.tokens[0].num = replacement_num;

                    index_start = i;
                    index_end = i + 1;
                }
            }

            // for num
            else if (OP_ == '\0' && !isnan(I_exp->tokens[i].num) && i > 0)
            {
                // case 1: ( NUM )
                if (I_exp->tokens[i - 1].operator== '(' && I_exp->tokens[i + 1].operator== ')')
                {
                    // puts("NUM - Case 1");
                    new_changes = true;

                    replacement.tokens[0].num = I_exp->tokens[i].num;

                    index_start = i - 1;
                    index_end = i + 1;
                }
            }
        }

        if (!new_changes)
            continue;

        // substitude
        substitude_result(I_exp, replacement, index_start, index_end);
        i = -1;
    }

    // puts("\n[After]\n");
    // display_infix_exp(*I_exp);
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

// sum-sequence OR sigma sum
double sum_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step)
{
    // check for valid input
    if (step == 0.0 ||
        fabs(step) <= __DBL_EPSILON__ ||
        (step > 0.0 && start > end) ||
        (step < 0.0 && start < end) ||
        isnan(step) ||
        isnan(start) ||
        isnan(end) ||
        I_function.tokens == NULL ||
        I_function.size <= 0)
        return NAN;

    // Pre-scan to find all positions where the variable appears
    int *var_positions = NULL;
    int var_count = 0;

    // Count variable occurrences first
    for (int i = 0; i < I_function.size; i++)
    {
        if (I_function.tokens[i].variable == var)
        {
            var_count++;
        }
    }

    // Early exit for constant functions (no variables to substitute)
    if (var_count == 0)
    {
        double constant_value = evaluate_I_exp(I_function);
        if (isnan(constant_value) || isinf(constant_value))
        {
            printf("Error: Constant function evaluation failed\n");
            return NAN;
        }

        // Calculate number of iterations
        double range = fabs(end - start);
        double abs_step = fabs(step);
        int num_iterations = (int)(range / abs_step) + 1;

        return constant_value * num_iterations;
    }

    // Allocate array for variable positions
    var_positions = (int *)malloc(var_count * sizeof(int));
    if (var_positions == NULL)
    {
        perror("sum_sequence - Failed to allocate var_positions");
        return NAN;
    }

    // Store variable positions
    int pos_index = 0;
    for (int i = 0; i < I_function.size; i++)
    {
        if (I_function.tokens[i].variable == var)
        {
            var_positions[pos_index++] = i;
        }
    }

    // Make a copy for optimization and substituting variables
    __INFIX__ copyof_I_function;
    copyof_I_function.size = I_function.size;
    copyof_I_function.tokens = (_infix_ *)malloc(I_function.size * sizeof(_infix_));
    if (copyof_I_function.tokens == NULL)
    {
        perror("sum_sequence - Failed to allocate copyof_I_function");
        free(var_positions);
        return NAN;
    }

    // Copy the function structure
    memcpy(copyof_I_function.tokens, I_function.tokens, I_function.size * sizeof(_infix_));

    // Optimize function for faster computation
    optimize_I_exp(&copyof_I_function);

    // Store original values at variable positions for restoration
    double *original_values = (double *)malloc(var_count * sizeof(double));
    if (original_values == NULL)
    {
        perror("sum_sequence - Failed to allocate original_values");
        free(var_positions);
        free(copyof_I_function.tokens);
        return NAN;
    }

    for (int i = 0; i < var_count; i++)
        original_values[i] = copyof_I_function.tokens[var_positions[i]].num;

    double sum = 0.0;
    double current_value = start;
    int iteration_count = 0;
    const int max_iterations = 1000000; // Prevent infinite loops
    bool ascending = (step > 0.0);

    // Main computation loop
    while (iteration_count < max_iterations)
    {
        // Check termination condition based on step direction
        if (ascending && current_value > end)
            break;
        if (!ascending && current_value < end)
            break;

        // Substitute the variable at all known positions (faster than scanning)
        for (int i = 0; i < var_count; i++)
            copyof_I_function.tokens[var_positions[i]].num = current_value;

        // Evaluate the function at current value
        double function_value = evaluate_I_exp(copyof_I_function);

        // Check if evaluation was successful
        if (!isnan(function_value) && !isinf(function_value))
            sum += function_value;

        // Move to next value
        current_value += step;
        iteration_count++;
    }

    // Clean up allocated memory
    free(var_positions);
    free(original_values);
    free(copyof_I_function.tokens);

    return sum;
}

// calculate the product of a sequence
double product_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step)
{
    // check for valid input
    if (step == 0.0 ||
        fabs(step) <= __DBL_EPSILON__ ||
        (step > 0.0 && start > end) ||
        (step < 0.0 && start < end) ||
        isnan(step) ||
        isnan(start) ||
        isnan(end) ||
        I_function.tokens == NULL ||
        I_function.size <= 0)
        return NAN;

    // Pre-scan to find all positions where the variable appears
    int *var_positions = NULL;
    int var_count = 0;

    // Count variable occurrences first
    for (int i = 0; i < I_function.size; i++)
    {
        if (I_function.tokens[i].variable == var)
        {
            var_count++;
        }
    }

    // Early exit for constant functions (no variables to substitute)
    if (var_count == 0)
    {
        double constant_value = evaluate_I_exp(I_function);
        if (isnan(constant_value) || isinf(constant_value))
        {
            printf("Error: Constant function evaluation failed\n");
            return NAN;
        }

        // Calculate number of iterations
        double range = fabs(end - start);
        double abs_step = fabs(step);
        int num_iterations = (int)(range / abs_step) + 1;

        // For products: constant^num_iterations
        if (constant_value == 0.0)
            return 0.0;
        else if (constant_value == 1.0)
            return 1.0;
        else
            return pow(constant_value, num_iterations);
    }

    // Allocate array for variable positions
    var_positions = (int *)malloc(var_count * sizeof(int));
    if (var_positions == NULL)
    {
        perror("product_sequence - Failed to allocate var_positions");
        return NAN;
    }

    // Store variable positions
    int pos_index = 0;
    for (int i = 0; i < I_function.size; i++)
    {
        if (I_function.tokens[i].variable == var)
        {
            var_positions[pos_index++] = i;
        }
    }

    // Make a copy for optimization and substituting variables
    __INFIX__ copyof_I_function;
    copyof_I_function.size = I_function.size;
    copyof_I_function.tokens = (_infix_ *)malloc(I_function.size * sizeof(_infix_));
    if (copyof_I_function.tokens == NULL)
    {
        perror("product_sequence - Failed to allocate copyof_I_function");
        free(var_positions);
        return NAN;
    }

    // Copy the function structure
    memcpy(copyof_I_function.tokens, I_function.tokens, I_function.size * sizeof(_infix_));

    // Optimize function for faster computation
    optimize_I_exp(&copyof_I_function);

    // Store original values at variable positions for restoration
    double *original_values = (double *)malloc(var_count * sizeof(double));
    if (original_values == NULL)
    {
        perror("product_sequence - Failed to allocate original_values");
        free(var_positions);
        free(copyof_I_function.tokens);
        return NAN;
    }

    for (int i = 0; i < var_count; i++)
        original_values[i] = copyof_I_function.tokens[var_positions[i]].num;

    double product = 1.0; // Initialize product to 1 (multiplicative identity)
    double current_value = start;
    int iteration_count = 0;
    const int max_iterations = 1000000; // Prevent infinite loops
    bool ascending = (step > 0.0);

    // Main computation loop
    while (iteration_count < max_iterations)
    {
        // Check termination condition based on step direction
        if (ascending && current_value > end)
            break;
        if (!ascending && current_value < end)
            break;

        // Substitute the variable at all known positions (faster than scanning)
        for (int i = 0; i < var_count; i++)
            copyof_I_function.tokens[var_positions[i]].num = current_value;

        // Evaluate the function at current value
        double function_value = evaluate_I_exp(copyof_I_function);

        // Check if evaluation was successful
        if (!isnan(function_value) && !isinf(function_value))
        {
            product *= function_value;

            // Early exit if product becomes zero
            if (product == 0.0)
            {
                // Clean up and return early
                free(var_positions);
                free(original_values);
                free(copyof_I_function.tokens);
                return 0.0;
            }

            // Check for overflow/underflow
            if (isinf(product) || product == 0.0)
            {
                break; // Exit loop if overflow/underflow occurs
            }
        }

        // Move to next value
        current_value += step;
        iteration_count++;
    }

    // Clean up allocated memory
    free(var_positions);
    free(original_values);
    free(copyof_I_function.tokens);

    return product;
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

__INFIX__ convert_P_to_I_exp(const _POSTFIX__ P_exp)
{
    __INFIX__ result;
    result.tokens = NULL;
    result.size = 0;

    if (P_exp.size == 0)
    {
        return result;
    }

    // Stack to hold sub-expressions (each as an __INFIX__ structure)
    __INFIX__ expression_stack[1000];
    int stack_top = -1;

    // Process each token in the postfix expression
    for (int i = 0; i < P_exp.size; i++)
    {
        _TOKENS_DATA_ current = P_exp.tokens[i];

        // If it's a number or variable, create a single-token infix expression
        if (current.operator== '\0')
        {
            stack_top++;
            expression_stack[stack_top].size = 1;
            expression_stack[stack_top].tokens = (_infix_ *)malloc(sizeof(_infix_));

            expression_stack[stack_top].tokens[0].num = current.num;
            expression_stack[stack_top].tokens[0].operator= '\0';
            expression_stack[stack_top].tokens[0].variable = current.variable;
        }
        // If it's a unary operator (functions)
        else if (current.operator== SPECIFIER_OF_SIN || current.operator== SPECIFIER_OF_COS ||
                 current.operator== SPECIFIER_OF_TAN || current.operator== SPECIFIER_OF_COT ||
                 current.operator== SPECIFIER_OF_SEC || current.operator== SPECIFIER_OF_CSC ||
                 current.operator== SPECIFIER_OF_ARCSIN || current.operator== SPECIFIER_OF_ARCCOS ||
                 current.operator== SPECIFIER_OF_ARCTAN || current.operator== SPECIFIER_OF_ARCCOT ||
                 current.operator== SPECIFIER_OF_SINH || current.operator== SPECIFIER_OF_COSH ||
                 current.operator== SPECIFIER_OF_TANH || current.operator== SPECIFIER_OF_COTH ||
                 current.operator== SPECIFIER_OF_ARCSINH || current.operator== SPECIFIER_OF_ARCCOSH ||
                 current.operator== SPECIFIER_OF_ARCTANH || current.operator== SPECIFIER_OF_ARCCOTH ||
                 current.operator== SPECIFIER_OF_LN || current.operator== SPECIFIER_OF_LG ||
                 current.operator== SPECIFIER_OF_SQRT || current.operator== SPECIFIER_OF_CBRT ||
                 current.operator== SPECIFIER_OF_ABS || current.operator== SPECIFIER_OF_GAMMA ||
                 current.operator== SPECIFIER_OF_CEIL || current.operator== SPECIFIER_OF_FLOOR ||
                 current.operator== SPECIFIER_OF_LAMBERTW)
        {

            if (stack_top >= 0)
            {
                __INFIX__ operand = expression_stack[stack_top--];

                // Create new expression: function(operand)
                __INFIX__ new_expr;
                new_expr.size = 3 + operand.size; // function + ( + operand + )
                new_expr.tokens = (_infix_ *)malloc(new_expr.size * sizeof(_infix_));

                int idx = 0;
                // Add function - properly initialize all fields
                new_expr.tokens[idx].num = 0.0;
                new_expr.tokens[idx].operator= current.operator;
                new_expr.tokens[idx].variable = '\0';
                idx++;

                // Add opening parenthesis - properly initialize all fields
                new_expr.tokens[idx].num = 0.0;
                new_expr.tokens[idx].operator= '(';
                new_expr.tokens[idx].variable = '\0';
                idx++;

                // Add operand
                for (int j = 0; j < operand.size; j++)
                {
                    new_expr.tokens[idx++] = operand.tokens[j];
                }

                // Add closing parenthesis - properly initialize all fields
                new_expr.tokens[idx].num = 0.0;
                new_expr.tokens[idx].operator= ')';
                new_expr.tokens[idx].variable = '\0';

                // Push back to stack
                expression_stack[++stack_top] = new_expr;

                // Free the operand
                free(operand.tokens);
            }
        }
        // If it's a binary operator
        else
        {
            if (stack_top >= 1)
            {
                __INFIX__ right = expression_stack[stack_top--];
                __INFIX__ left = expression_stack[stack_top--];

                // For simplicity, let's not use complex precedence logic for now
                // Just create: left operator right (without extra parentheses)
                __INFIX__ new_expr;
                new_expr.size = left.size + 1 + right.size; // left + operator + right
                new_expr.tokens = (_infix_ *)malloc(new_expr.size * sizeof(_infix_));

                int idx = 0;

                // Add left operand
                for (int j = 0; j < left.size; j++)
                {
                    new_expr.tokens[idx++] = left.tokens[j];
                }

                // Add operator - properly initialize all fields
                new_expr.tokens[idx].num = 0.0;
                new_expr.tokens[idx].operator= current.operator;
                new_expr.tokens[idx].variable = '\0';
                idx++;

                // Add right operand
                for (int j = 0; j < right.size; j++)
                {
                    new_expr.tokens[idx++] = right.tokens[j];
                }

                // Push back to stack
                expression_stack[++stack_top] = new_expr;

                // Free the operands
                free(left.tokens);
                free(right.tokens);
            }
        }
    }

    // The final result should be the only element left in the stack
    if (stack_top == 0)
    {
        result = expression_stack[0];
    }

    return result;
}

/**
 * Merges two numbers with an operator between them
 * @param I_exp Pointer to the infix expression structure
 * @param index Index of the first number in the expression
 */
void merge_2_num(__INFIX__ *I_exp, const short int index)
{
    _infix_ token_num[1] = {NAN, '\0', '\0'};
    __INFIX__ replacement = {1, token_num};

    switch (I_exp->tokens[index + 1].operator)
    {
    case '+':
    {
        if (index >= 1 && I_exp->tokens[index - 1].operator== '-')
        {
            if (I_exp->tokens[index + 2].num >= I_exp->tokens[index].num)
            {
                replacement.tokens[0].num = I_exp->tokens[index + 2].num - I_exp->tokens[index].num;
                I_exp->tokens[index - 1].operator= '+';
            }
            else
                replacement.tokens[0].num = I_exp->tokens[index].num - I_exp->tokens[index + 2].num;
        }
        else
            replacement.tokens[0].num = I_exp->tokens[index].num + I_exp->tokens[index + 2].num;

        break;
    }
    case '-':
    {
        if (index >= 1 && I_exp->tokens[index - 1].operator== '-')
            replacement.tokens[0].num = I_exp->tokens[index].num + I_exp->tokens[index + 2].num;
        else
        {
            replacement.tokens[0].num = I_exp->tokens[index].num - I_exp->tokens[index + 2].num;

            if (replacement.tokens[0].num < 0.0 && index >= 1 && I_exp->tokens[index - 1].operator== '-')
            {
                I_exp->tokens[index - 1].operator= '-';
                replacement.tokens[0].num *= -1.0;
            }
        }
        break;
    }
    case '*':
        replacement.tokens[0].num = I_exp->tokens[index].num * I_exp->tokens[index + 2].num;
        break;
    case '^':
        replacement.tokens[0].num = pow(I_exp->tokens[index].num, I_exp->tokens[index + 2].num);
        break;
    case '%':
    {
        if (is_integer(I_exp->tokens[index].num) && is_integer(I_exp->tokens[index + 2].num))
            replacement.tokens[0].num = (double)(((int)I_exp->tokens[index].num) % ((int)I_exp->tokens[index + 2].num));
        break;
    }
    default:
        break;
    }

    substitude_result(I_exp, replacement, index, index + 2);
}

/**
 * Merges a number enclosed in brackets by removing the brackets
 */
void merge_num_and_bracket(__INFIX__ *I_exp, const short int index)
{
    _infix_ token_num[1] = {I_exp->tokens[index + 1].num, '\0', '\0'};
    __INFIX__ replacement = {1, token_num};
    substitude_result(I_exp, replacement, index, index + 2);
}

/**
 * Removes multiplication by 1 from the expression
 */
void merge_multiplier_of_one(__INFIX__ *I_exp, const short int index)
{
    for (short int i = index; i + 2 < I_exp->size; i++)
    {
        I_exp->tokens[i].num = I_exp->tokens[i + 2].num;
        I_exp->tokens[i].variable = I_exp->tokens[i + 2].variable;
        I_exp->tokens[i].operator= I_exp->tokens[i + 2].operator;
    }

    _infix_ *temp = (_infix_ *)realloc(I_exp->tokens, (I_exp->size - 2) * sizeof(_infix_));
    if (temp == NULL)
    {
        perror("merge_multiplier_of_one - oen_first: Failed to realloc temp");
        return;
    }
    I_exp->tokens = temp;
    I_exp->size -= 2;
}

/**
 * Handles multiplication by zero, replacing the entire term with 0
 * @param I_exp Pointer to the infix expression structure
 * @param index Index where the multiplication by 0 occurs
 * @param zero_first Boolean indicating if zero is the first operand
 */
void merge_multiplier_of_zero(__INFIX__ *I_exp, const short int index, const bool zero_first)
{
    _infix_ token_num[1] = {0.0, '\0', '\0'};
    __INFIX__ replacement = {1, token_num};

    if (zero_first)
    {
        short int index_end = -1;
        short int open_bracket = 0;
        short int close_bracket = 0;

        for (short int i = index + 2; i < I_exp->size; i++)
        {
            if (I_exp->tokens[i].operator== '(')
                open_bracket++;
            else if (I_exp->tokens[i].operator== ')')
                close_bracket++;

            if ((open_bracket == close_bracket && (I_exp->tokens[i].operator== '+' || I_exp->tokens[i].operator== '-')) || i + 1 == I_exp->size)
            {
                if (i + 1 == I_exp->size)
                    index_end = i;
                else
                    index_end = i - 1;
                break;
            }
        }

        if (index_end == -1)
            return;

        substitude_result(I_exp, replacement, index, index_end);
    }

    else
    {
        short int index_start = -1;
        short int open_bracket = 0;
        short int close_bracket = 0;

        for (short int i = index - 1; i >= 0; i--)
        {
            if (I_exp->tokens[i].operator== ')')
                close_bracket++;
            else if (I_exp->tokens[i].operator== '(')
                open_bracket++;

            if ((open_bracket == close_bracket && (I_exp->tokens[i].operator== '-' || I_exp->tokens[i].operator== '+')) || i == 0)
            {
                if (i == 0)
                    index_start = 0;
                else
                    index_start = i + 1;
                break;
            }
        }

        if (index_start == -1)
            return;

        substitude_result(I_exp, replacement, index_start, index - 1);
    }
}

/**
 * Removes unnecessary nested brackets from the expression
 */
bool merge_unused_bracket(__INFIX__ *I_exp, const short int index)
{

    short int index_next_bracket = index + 1;
    short int open_bracket = 0;
    short int close_bracket = 0;
    short int index_outer_bracket_close = -1;

    for (short int u = index_next_bracket; u < I_exp->size; u++)
    {
        if (I_exp->tokens[u].operator== '(')
            open_bracket++;
        else if (I_exp->tokens[u].operator== ')')
            close_bracket++;

        if (open_bracket == close_bracket)
        {
            index_outer_bracket_close = u;
            break;
        }
    }

    if (index_outer_bracket_close == -1 || (index_outer_bracket_close + 1 < I_exp->size && I_exp->tokens[index_outer_bracket_close + 1].operator!= '+' && I_exp->tokens[index_outer_bracket_close + 1].operator!= '-' && I_exp->tokens[index_outer_bracket_close + 1].operator!= ')'))
        return false;

    __INFIX__ replacement = {0, NULL};

    copy_sub_I_exp(&replacement, *I_exp, index_next_bracket, index_outer_bracket_close);

    substitude_result(I_exp, replacement, index_next_bracket, index_outer_bracket_close);

    if (replacement.tokens != NULL)
        free(replacement.tokens);

    return true;
}

/**
 * Removes exponentiation by 1 (x^1 becomes x)
 */
void merge_pow_of_one(__INFIX__ *I_exp, const short int index)
{
    for (short int i = index; i + 2 < I_exp->size; i++)
    {
        I_exp->tokens[i].num = I_exp->tokens[i + 2].num;
        I_exp->tokens[i].operator= I_exp->tokens[i + 2].operator;
        I_exp->tokens[i].variable = I_exp->tokens[i + 2].variable;
    }

    _infix_ *temp = (_infix_ *)realloc(I_exp->tokens, (I_exp->size - 2) * sizeof(_infix_));
    if (temp != NULL)
    {
        I_exp->tokens = temp;
        I_exp->size -= 2;
    }
    else
        perror("merge_pow_of_one: Failed to realloc temp");
}

/**
 * Handles exponentiation by 0 (x^0 becomes 1)
 */
void merge_pow_of_zero(__INFIX__ *I_exp, const short int index)
{
    _infix_ token_num[1] = {1.0, '\0', '\0'};
    __INFIX__ replacement = {1, token_num};

    if (isfinite(I_exp->tokens[index - 1].num))
    {
        substitude_result(I_exp, replacement, index - 1, index + 1);
    }
    else
    {
        short int open_bracket = 0;
        short int close_bracket = 0;
        short int index_outer_open_backet = -1;
        for (short int i = index - 1; i >= 0; i--)
        {
            if (I_exp->tokens[i].operator== '(')
                open_bracket++;
            else if (I_exp->tokens[i].operator== ')')
                close_bracket++;

            if ((open_bracket == close_bracket && (I_exp->tokens[i].operator== '+' || I_exp->tokens[i].operator== '-' || I_exp->tokens[i].operator== '*' || I_exp->tokens[i].operator== '/' || I_exp->tokens[i].operator== '^' || I_exp->tokens[i].operator== '!' || I_exp->tokens[i].operator== '%')))
            {
                index_outer_open_backet = i + 1;

                break;
            }

            else if (i == 0)
            {
                index_outer_open_backet = 0;
                break;
            }
            else if (open_bracket == close_bracket && i - 1 >= 0 && I_exp->tokens[i - 1].operator== '(')
            {
                index_outer_open_backet = i;
                break;
            }
        }

        if (index_outer_open_backet == -1)
            return;

        substitude_result(I_exp, replacement, index_outer_open_backet, index + 1);
    }
}

/**
 * Reformats and simplifies the infix expression for better readability
 * @param I_exp Pointer to the infix expression structure to reformat
 */
// NOTE:
// This function does not reduce OR optimze the expression for faster computation. It just makes the expression look better
void reformat_I_exp(__INFIX__ *I_exp)
{
    if (I_exp->size < 2 || I_exp->tokens == NULL)
        return;

    for (short int i = 0; i < I_exp->size; i++)
    {
        double num_ = I_exp->tokens[i].num;
        char operator_ = I_exp->tokens[i].operator;
        char variable_ = I_exp->tokens[i].variable;

        // case 1: num + | - | * | ^ | %% | num
        // except for built-in const & division
        if (i >= 1 &&
            I_exp->tokens[i - 1].operator!= '*' && I_exp->tokens[i - 1].operator!= '/' && I_exp->tokens[i - 1].operator!= '^' &&
            isfinite(num_) &&
            i + 1 < I_exp->size &&
            I_exp->tokens[i + 1].operator!= '/' &&
            i + 2<I_exp->size &&
            isfinite(I_exp->tokens[i + 2].num) &&
            i + 3 < I_exp->size &&
            (I_exp->tokens[i + 3].operator!= '*' && I_exp->tokens[i + 3].operator!= '/' && I_exp->tokens[i + 3].operator!= '^') &&
            num_ != PI && num_ != EULER_NUMBER && num_ != _G_ && num_ != _C_ && num_ != LN_2 && num_ != SQRT_2 && num_ != SQRT_2_2 && num_ != SQRT_3 &&
            I_exp->tokens[i + 2].num != PI && I_exp->tokens[i + 2].num != EULER_NUMBER && I_exp->tokens[i + 2].num != _G_ && I_exp->tokens[i + 2].num != _C_ && I_exp->tokens[i + 2].num != LN_2 && I_exp->tokens[i + 2].num != SQRT_2 && I_exp->tokens[i + 2].num != SQRT_2_2 && I_exp->tokens[i + 2].num != SQRT_3)
        {
            merge_2_num(I_exp, i);
            i = -1;
        }

        // case 2: (num)
        else if (i >= 1 &&
                 (I_exp->tokens[i - 1].operator== '+' || I_exp->tokens[i - 1].operator== '-' || I_exp->tokens[i - 1].operator== '*' || I_exp->tokens[i - 1].operator== '/' || I_exp->tokens[i - 1].operator== '^' || I_exp->tokens[i - 1].operator== '%') &&
                 operator_ == '(' && i + 1 < I_exp->size &&
                 isfinite(I_exp->tokens[i + 1].num) &&
                 i + 2 < I_exp->size &&
                 I_exp->tokens[i + 2].operator== ')')
        {
            merge_num_and_bracket(I_exp, i);
            i = -1;
        }

        // case 3: 1 * | * 1
        else if (i + 1 < I_exp->size && ((num_ == 1.0 && I_exp->tokens[i + 1].operator== '*') || (operator_ == '*' && I_exp->tokens[i + 1].num == 1.0)))
        {
            merge_multiplier_of_one(I_exp, i);
            i = -1;
        }

        // case 4: 0 * | * 0
        else if (((num_ == 0.0 || fabs(num_) <= __DBL_EPSILON__) &&
                  i + 1 < I_exp->size &&
                  I_exp->tokens[i + 1].operator== '*') ||
                 (operator_ == '*' &&
                  i + 1 < I_exp->size &&
                  (I_exp->tokens[i + 1].num == 0.0 || fabs(I_exp->tokens[i + 1].num) <= __DBL_EPSILON__)))
        {
            if (operator_ == '*')
                merge_multiplier_of_zero(I_exp, i, false);
            else
                merge_multiplier_of_zero(I_exp, i, true);
            i = -1;
        }

        // case 5: (((((...)))))
        else if (operator_ == '(' && i + 1 < I_exp->size && I_exp->tokens[i + 1].operator== '(')
        {
            if (merge_unused_bracket(I_exp, i))
                i = -1;
        }

        // case 6: (...) ^ 1
        else if (operator_ == '^' && I_exp->tokens[i + 1].num == 1.0)
        {
            merge_pow_of_one(I_exp, i);
            i = -1;
        }

        // case 7: (...) ^ 0
        else if (operator_ == '^' && (I_exp->tokens[i + 1].num == 0.0 || fabs(I_exp->tokens[i + 1].num) <= __DBL_EPSILON__))
        {
            merge_pow_of_zero(I_exp, i);
            i = -1;
        }
    }

    // case 8: (...)
    {
        short int open_bracket = 0;
        short int close_bracket = 0;
        short int outer_close_bracket = -1;
        for (short int i = 0; i < I_exp->size; i++)
        {
            if (I_exp->tokens[i].operator== '(')
                open_bracket++;
            else if (I_exp->tokens[i].operator== ')')
                close_bracket++;

            if (open_bracket == close_bracket && open_bracket * close_bracket != 0)
            {
                outer_close_bracket = i;
                break;
            }
        }

        if (I_exp->tokens[0].operator== '(' && outer_close_bracket == I_exp->size - 1)
        {
            for (short int i = 0; i + 1 < I_exp->size; i++)
            {
                I_exp->tokens[i].num = I_exp->tokens[i + 1].num;
                I_exp->tokens[i].operator= I_exp->tokens[i + 1].operator;
                I_exp->tokens[i].variable = I_exp->tokens[i + 1].variable;
            }

            _infix_ *temp = (_infix_ *)realloc(I_exp->tokens, (I_exp->size - 2) * sizeof(_infix_));
            if (temp != NULL)
            {
                I_exp->tokens = temp;
                I_exp->size -= 2;
            }
            else
            {
                perror("reformat_I_exp - case8: Failed to realloc temp");
                return;
            }
        }
    }
}

__INFIX__ copy_infix_expression(const __INFIX__ source)
{
    __INFIX__ copyof_source;
    copyof_source.size = source.size;
    copyof_source.tokens = (_infix_ *)malloc(source.size * sizeof(_infix_));
    if (copyof_source.tokens == NULL)
    {
        copyof_source.size = 0;
        return copyof_source;
    }

    for (short int i = 0; i < source.size; i++)
    {
        copyof_source.tokens[i].num = source.tokens[i].num;
        copyof_source.tokens[i].variable = source.tokens[i].variable;
        copyof_source.tokens[i].operator= source.tokens[i].operator;
    }

    return copyof_source;
}

_POSTFIX__ copy_postfix_expression(const _POSTFIX__ source)
{
    _POSTFIX__ copyof_source;
    copyof_source.size = source.size;
    copyof_source.tokens = (_TOKENS_DATA_ *)malloc(source.size * sizeof(_TOKENS_DATA_));
    if (copyof_source.tokens == NULL)
    {
        copyof_source.size = 0;
        return copyof_source;
    }

    for (short int i = 0; i < source.size; i++)
    {
        copyof_source.tokens[i].num = source.tokens[i].num;
        copyof_source.tokens[i].variable = source.tokens[i].variable;
        copyof_source.tokens[i].operator= source.tokens[i].operator;
    }

    return copyof_source;
}

#endif