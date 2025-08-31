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
#include <MY_LIB/lexer_and_format.h>
#include <MY_LIB/extra_math_function.h>

//=================================================================================================================//
//                                                   MACROES                                                       //
//=================================================================================================================//

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

int estimate_upper_bound(int n);

int *find_prime_factors(int n, int *num_of_fac);

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

void Least_Operator(char *expression, char *L_O, int *pos_of_op);

double limit_left(char *function, const char _varriable_, const double _x_);
double limit_right(char *function, const char _varriable_, const double _x_);
double limit(char *function, const char _varriable_, const double _x_);

void sort_int_array(int *arr, int size);
void sort_double_array(double *arr, int size);

int compare_ints(const void *a, const void *b);
int compare_doubles(const void *a, const void *b);

_POSTFIX__ Parse(char *expression);
_POSTFIX__ submodule_Parse(__INFIX__ specified_expression);

double Compute_P_expression(const _POSTFIX__ P_expression);
double Compute_P_function(_POSTFIX__ function, char *_variables_, ...);
double evaluate_function(char *_function_, const char *_variables_, ...);
double evaluate_I_1_var_function(const __INFIX__ I_function, const char var, const double value);
double evaluate(char *expression);
double evaluate_I_exp(__INFIX__ I_exp);

void check_for_valid_braket(__INFIX__ *copyof_input);

void add_many_tokens(__INFIX__ *destination, const __INFIX__ source);
void add_single_token(__INFIX__ *destination, const double num, const char variable, const char operator);

__INFIX__ differentiate_I_exp(__INFIX__, const char);
void find_LPO(__INFIX__ specified_expression, char *LPO, int *LPO_pos);

void substitude_result(__INFIX__ *I_exp_tobe_replaced, const __INFIX__ replacement, const int index_start, const int index_end);

void copy_sub_I_exp(__INFIX__ *destination, __INFIX__ source, const short int index_start, const short int index_end);
__INFIX__ copy_infix_expression(const __INFIX__ source);
_POSTFIX__ copy_postfix_expression(const _POSTFIX__ source);

bool handle_special_functions_(__INFIX__ *I_exp);

double integral_definite(char *function, const char, const double lower_bound, const double upper_bound);
double integral_definite_infix(__INFIX__ infix_function, const char var, const double lower_bound, const double upper_bound);
double integral_GaussianQuadrature500(const __INFIX__ I_function, const char var, double a, double b);

double sum(double start, double end, double step);
double sum_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step);
double product_sequence(__INFIX__ I_function, const char var, const double start, const double end, const double step);

double random_in_range_double(const double a, const double b);

//=================================================================================================================//
//                                            FUNCTIONS DEFINITION                                                //
//=================================================================================================================//

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

// Function to estimate the upper bound for the nth prime
int estimate_upper_bound(int n)
{
    if (n < 6)
        return 15;
    return (int)(n * (log(n) + log(log(n))));
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
        _op_ = __operator__(copy_expression, i);

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
                ope_stack[ope_index]._op_ = __operator__(expression, token);
                _increase_(&token, ope_stack[ope_index]._op_);
                ope_stack[ope_index++].pos = token;
                // printf("%s\n", ope_stack->_op_);
                break;
            }
            else if (precedent_of(ope_stack[ope_index - 1]._op_) < precedent_of(__operator__(expression, token)) || expression[token] == '(')
            {
                ope_stack[ope_index]._op_ = __operator__(expression, token);
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
    // Make a copy of P_expression
    _POSTFIX__ cloned_exp;

    cloned_exp.tokens = (_TOKENS_DATA_ *)malloc(P_expression.size * sizeof(_TOKENS_DATA_));
    if (cloned_exp.tokens == NULL)
    {
        perror("Compute_P_expression: Failed to malloc cloned_exp.tokens");
        return NAN;
    }
    for (int i = 0; i < P_expression.size; i++)
    {
        cloned_exp.tokens[i].num = P_expression.tokens[i].num;
        cloned_exp.tokens[i].operator= P_expression.tokens[i].operator;
        cloned_exp.tokens[i].variable = P_expression.tokens[i].variable;

        // Variable without value
        if (P_expression.tokens[i].variable != '\0' && isnan(cloned_exp.tokens[i].num))
        {
            cloned_exp.tokens[i].num = 0;
            cloned_exp.tokens[i].variable = '\0';
        }
    }
    cloned_exp.size = P_expression.size;

    for (unsigned short int i = 0; i < cloned_exp.size && cloned_exp.size > 1; i++)
    {
        char OP = cloned_exp.tokens[i].operator;

        if (OP == '\0')
            continue;

        bool two_param_OP = false;

        switch (OP)
        {
        case '+': // addition
            cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num + cloned_exp.tokens[i - 1].num;
            two_param_OP = true;
            break;
        case '-': // substraction
            cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num - cloned_exp.tokens[i - 1].num;
            two_param_OP = true;
            break;
        case '*': // multiplication
            cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num * cloned_exp.tokens[i - 1].num;
            two_param_OP = true;
            break;
        case '/': // division
        {
            if (cloned_exp.tokens[i - 1].num == 0.0)
            {
                free(cloned_exp.tokens);
                return NAN;
            }
            cloned_exp.tokens[i - 2].num = cloned_exp.tokens[i - 2].num / cloned_exp.tokens[i - 1].num;
            two_param_OP = true;
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
            two_param_OP = true;
            break;
        }
        case '^': // exponential
            cloned_exp.tokens[i - 2].num = pow(cloned_exp.tokens[i - 2].num, cloned_exp.tokens[i - 1].num);
            two_param_OP = true;
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

        // after completing 1 calculation

        // 2 parameter operator
        if (two_param_OP)
        {
            // shift the array 2 index down
            for (unsigned short int k = i - 1; k < cloned_exp.size; k++)
            {
                cloned_exp.tokens[k].num = cloned_exp.tokens[k + 2].num;
                cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 2].variable;
                cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 2].operator;
            }

            cloned_exp.size -= 2;
        }

        // 1 parameter operator & function
        else
        {
            for (unsigned short int k = i; k < cloned_exp.size; k++)
            {
                cloned_exp.tokens[k].num = cloned_exp.tokens[k + 1].num;
                cloned_exp.tokens[k].variable = cloned_exp.tokens[k + 1].variable;
                cloned_exp.tokens[k].operator= cloned_exp.tokens[k + 1].operator;
            }

            cloned_exp.size--;
        }

        // reset index to the starting of the array
        i = -1;
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

            // old method
            // I_result.tokens[0].num = integral_definite_infix(function, var, l_bound, u_bound);
            // use faster method
            I_result.tokens[0].num = integral_GaussianQuadrature500(function, var, l_bound, u_bound);
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

double integral_GaussianQuadrature500(const __INFIX__ I_function, const char var, double a, double b)
{
    // check for valid parameter
    if (I_function.size <= 0 || I_function.tokens == NULL)
        return NAN;
    if (var == '\0' || var == 'c' || var == 'e' || var == 'g')
        return NAN;
    if (is_zero(b - a))
        return 0.0;

    double sign = 1.0;

    if (b < a)
    {
        double temp = b;
        b = a;
        a = temp;

        sign = -1.0;
    }

    // Gauss–Legendre weights and nodes for n = 500
    double weights[500] = {
        2.962364450555644e-05,
        6.89570728205074e-05,
        0.0001083460286934494,
        0.00014773577476858758,
        0.0001871207158557841,
        0.00022649858871036835,
        0.00026586765326214174,
        0.00030522629426960014,
        0.00034457293521267176,
        0.00038390601413328845,
        0.0004232239754797741,
        0.00046252526700028325,
        0.0005018083384640074,
        0.0005410716410692871,
        0.0005803136271951402,
        0.000619532750301983,
        0.0006587274648936571,
        0.0006978962265239956,
        0.0007370374918303779,
        0.0007761497185724115,
        0.0008152313656796535,
        0.0008542808933021158,
        0.000893296762876444,
        0.000932277437164903,
        0.0009712213803292163,
        0.0010101270579808048,
        0.0010489929372477008,
        0.001087817486819288,
        0.0011265991770259313,
        0.001165336479880678,
        0.0012040278691495142,
        0.0012426718204084238,
        0.001281266811103743,
        0.0013198113206112235,
        0.0013583038302951032,
        0.0013967428235689707,
        0.001435126785955902,
        0.0014734542051496194,
        0.0015117235710660469,
        0.0015499333759148874,
        0.0015880821142481758,
        0.0016261682830269436,
        0.0016641903816764746,
        0.0017021469121446798,
        0.0017400363789658421,
        0.0017778572893161115,
        0.0018156081530703236,
        0.001853287482865466,
        0.0018908937941571266,
        0.0019284256052762908,
        0.001965881437489857,
        0.0020032598150595254,
        0.002040559265296426,
        0.0020777783186228162,
        0.002114915508628639,
        0.0021519693721285143,
        0.002188938449221406,
        0.002225821283344368,
        0.0022626164213351667,
        0.0022993224134848934,
        0.0023359378135980493,
        0.002372461179047586,
        0.0024088910708330792,
        0.0024452260536369447,
        0.0024814646958799965,
        0.002517605569780819,
        0.002553647251408836,
        0.0025895883207401,
        0.002625427361717593,
        0.002661162962301729,
        0.0026967937145305747,
        0.002732318214571503,
        0.0027677350627784056,
        0.002803042863747332,
        0.0028382402263707513,
        0.0028733257638912033,
        0.0029082980939583803,
        0.002943155838680796,
        0.0029778976246835577,
        0.00301252208315887,
        0.003047027849922231,
        0.003081413565465014,
        0.0031156778750098773,
        0.0031498194285608304,
        0.0031838368809594727,
        0.003217728891937881,
        0.003251494126168959,
        0.0032851312533203917,
        0.0033186389481087075,
        0.003352015890349023,
        0.0033852607650076893,
        0.0034183722622554867,
        0.0034513490775173413,
        0.0034841899115251916,
        0.003516893470368367,
        0.0035494584655435877,
        0.00358188361400878,
        0.0036141676382310047,
        0.003646309266237613,
        0.0036783072316653666,
        0.0037101602738126944,
        0.0037418671376866883,
        0.003773426574055361,
        0.003804837339493149,
        0.003836098196433851,
        0.003867207913216991,
        0.0038981652641361577,
        0.003928969029489261,
        0.003959617995624746,
        0.003990110954990722,
        0.004020446706180627,
        0.004050624053982821,
        0.004080641809426447,
        0.004110498789828243,
        0.004140193818840072,
        0.004169725726493957,
        0.0041990933492489805,
        0.004228295530036822,
        0.004257331118307547,
        0.0042861989700751614,
        0.004314897947962083,
        0.004343426921244604,
        0.004371784765896552,
        0.0043999703646348965,
        0.0044279826069618155,
        0.00445582038921107,
        0.004483482614589362,
        0.004510968193219391,
        0.0045382760421856716,
        0.00456540508557294,
        0.004592354254512642,
        0.004619122487221592,
        0.004645708729046646,
        0.004672111932504433,
        0.004698331057323403,
        0.004724365070484263,
        0.004750212946261073,
        0.004775873666261864,
        0.004801346219468435,
        0.004826629602276515,
        0.0048517228185342275,
        0.00487662487958296,
        0.004901334804294899,
        0.004925851619113117,
        0.004950174358088109,
        0.004974302062917719,
        0.004998233782983438,
        0.005021968575388622,
        0.0050455055049957115,
        0.005068843644462379,
        0.005091982074279162,
        0.005114919882804143,
        0.0051376561663007345,
        0.005160190028971686,
        0.005182520582995276,
        0.005204646948559886,
        0.005226568253898823,
        0.005248283635325007,
        0.005269792237264015,
        0.005291093212288935,
        0.005312185721152992,
        0.0053330689328232265,
        0.005353742024512282,
        0.005374204181711729,
        0.0053944545982239096,
        0.005414492476193589,
        0.005434317026139524,
        0.0054539274669850564,
        0.005473323026089905,
        0.005492502939279499,
        0.005511466450875798,
        0.005530212813727121,
        0.005548741289236881,
        0.005567051147393393,
        0.005585141666798403,
        0.005603012134695254,
        0.005620661846997398,
        0.005638090108315948,
        0.005655296231986928,
        0.005672279540098546,
        0.005689039363517814,
        0.005705575041916978,
        0.005721885923799338,
        0.005737971366525118,
        0.005753830736336728,
        0.005769463408383799,
        0.005784868766747513,
        0.005800046204465446,
        0.005814995123554662,
        0.005829714935036055,
        0.005844205058957262,
        0.0058584649244152655,
        0.005872493969579246,
        0.005886291641712568,
        0.005899857397194459,
        0.0059131907015417305,
        0.005926291029429498,
        0.005939157864711969,
        0.0059517907004430015,
        0.005964189038895738,
        0.0059763523915825675,
        0.005988280279274043,
        0.0059999722320179675,
        0.006011427789157794,
        0.006022646499350913,
        0.0060336279205863005,
        0.006044371620201972,
        0.006054877174902154,
        0.006065144170773736,
        0.006075172203302678,
        0.006084960877390096,
        0.00609450980736758,
        0.006103818617012571,
        0.0061128869395630355,
        0.0061217144177320906,
        0.006130300703721955,
        0.006138645459237711,
        0.006146748355500514,
        0.006154609073260782,
        0.006162227302810531,
        0.006169602743995684,
        0.0061767351062279605,
        0.0061836241084962116,
        0.006190269479377487,
        0.006196670957047914,
        0.0062028282892927005,
        0.006208741233516407,
        0.0062144095567522924,
        0.006219833035671499,
        0.006225011456591944,
        0.006229944615486749,
        0.006234632317992107,
        0.006239074379415165,
        0.006243270624741095,
        0.006247220888640169,
        0.006250925015474178,
        0.006254382859302553,
        0.006257594283888137,
        0.0062605591627025725,
        0.006263277378931298,
        0.006265748825478026,
        0.006267973404969174,
        0.006269951029757515,
        0.006271681621925733,
        0.0062731651132894245,
        0.006274401445399896,
        0.006275390569546302,
        0.006276132446757668,
        0.006276627047804515,
        0.006276874353199775,
        0.006276874353199775,
        0.006276627047804515,
        0.006276132446757668,
        0.006275390569546302,
        0.006274401445399896,
        0.0062731651132894245,
        0.006271681621925733,
        0.006269951029757515,
        0.006267973404969174,
        0.006265748825478026,
        0.006263277378931298,
        0.0062605591627025725,
        0.006257594283888137,
        0.006254382859302553,
        0.006250925015474178,
        0.006247220888640169,
        0.006243270624741095,
        0.006239074379415165,
        0.006234632317992107,
        0.006229944615486749,
        0.006225011456591944,
        0.006219833035671499,
        0.0062144095567522924,
        0.006208741233516407,
        0.0062028282892927005,
        0.006196670957047914,
        0.006190269479377487,
        0.0061836241084962116,
        0.0061767351062279605,
        0.006169602743995684,
        0.006162227302810531,
        0.006154609073260782,
        0.006146748355500514,
        0.006138645459237711,
        0.006130300703721955,
        0.0061217144177320906,
        0.0061128869395630355,
        0.006103818617012571,
        0.00609450980736758,
        0.006084960877390096,
        0.006075172203302678,
        0.006065144170773736,
        0.006054877174902154,
        0.006044371620201972,
        0.0060336279205863005,
        0.006022646499350913,
        0.006011427789157794,
        0.0059999722320179675,
        0.005988280279274043,
        0.0059763523915825675,
        0.005964189038895738,
        0.0059517907004430015,
        0.005939157864711969,
        0.005926291029429498,
        0.0059131907015417305,
        0.005899857397194459,
        0.005886291641712568,
        0.005872493969579246,
        0.0058584649244152655,
        0.005844205058957262,
        0.005829714935036055,
        0.005814995123554662,
        0.005800046204465446,
        0.005784868766747513,
        0.005769463408383799,
        0.005753830736336728,
        0.005737971366525118,
        0.005721885923799338,
        0.005705575041916978,
        0.005689039363517814,
        0.005672279540098546,
        0.005655296231986928,
        0.005638090108315948,
        0.005620661846997398,
        0.005603012134695254,
        0.005585141666798403,
        0.005567051147393393,
        0.005548741289236881,
        0.005530212813727121,
        0.005511466450875798,
        0.005492502939279499,
        0.005473323026089905,
        0.0054539274669850564,
        0.005434317026139524,
        0.005414492476193589,
        0.0053944545982239096,
        0.005374204181711729,
        0.005353742024512282,
        0.0053330689328232265,
        0.005312185721152992,
        0.005291093212288935,
        0.005269792237264015,
        0.005248283635325007,
        0.005226568253898823,
        0.005204646948559886,
        0.005182520582995276,
        0.005160190028971686,
        0.0051376561663007345,
        0.005114919882804143,
        0.005091982074279162,
        0.005068843644462379,
        0.0050455055049957115,
        0.005021968575388622,
        0.004998233782983438,
        0.004974302062917719,
        0.004950174358088109,
        0.004925851619113117,
        0.004901334804294899,
        0.00487662487958296,
        0.0048517228185342275,
        0.004826629602276515,
        0.004801346219468435,
        0.004775873666261864,
        0.004750212946261073,
        0.004724365070484263,
        0.004698331057323403,
        0.004672111932504433,
        0.004645708729046646,
        0.004619122487221592,
        0.004592354254512642,
        0.00456540508557294,
        0.0045382760421856716,
        0.004510968193219391,
        0.004483482614589362,
        0.00445582038921107,
        0.0044279826069618155,
        0.0043999703646348965,
        0.004371784765896552,
        0.004343426921244604,
        0.004314897947962083,
        0.0042861989700751614,
        0.004257331118307547,
        0.004228295530036822,
        0.0041990933492489805,
        0.004169725726493957,
        0.004140193818840072,
        0.004110498789828243,
        0.004080641809426447,
        0.004050624053982821,
        0.004020446706180627,
        0.003990110954990722,
        0.003959617995624746,
        0.003928969029489261,
        0.0038981652641361577,
        0.003867207913216991,
        0.003836098196433851,
        0.003804837339493149,
        0.003773426574055361,
        0.0037418671376866883,
        0.0037101602738126944,
        0.0036783072316653666,
        0.003646309266237613,
        0.0036141676382310047,
        0.00358188361400878,
        0.0035494584655435877,
        0.003516893470368367,
        0.0034841899115251916,
        0.0034513490775173413,
        0.0034183722622554867,
        0.0033852607650076893,
        0.003352015890349023,
        0.0033186389481087075,
        0.0032851312533203917,
        0.003251494126168959,
        0.003217728891937881,
        0.0031838368809594727,
        0.0031498194285608304,
        0.0031156778750098773,
        0.003081413565465014,
        0.003047027849922231,
        0.00301252208315887,
        0.0029778976246835577,
        0.002943155838680796,
        0.0029082980939583803,
        0.0028733257638912033,
        0.0028382402263707513,
        0.002803042863747332,
        0.0027677350627784056,
        0.002732318214571503,
        0.0026967937145305747,
        0.002661162962301729,
        0.002625427361717593,
        0.0025895883207401,
        0.002553647251408836,
        0.002517605569780819,
        0.0024814646958799965,
        0.0024452260536369447,
        0.0024088910708330792,
        0.002372461179047586,
        0.0023359378135980493,
        0.0022993224134848934,
        0.0022626164213351667,
        0.002225821283344368,
        0.002188938449221406,
        0.0021519693721285143,
        0.002114915508628639,
        0.0020777783186228162,
        0.002040559265296426,
        0.0020032598150595254,
        0.001965881437489857,
        0.0019284256052762908,
        0.0018908937941571266,
        0.001853287482865466,
        0.0018156081530703236,
        0.0017778572893161115,
        0.0017400363789658421,
        0.0017021469121446798,
        0.0016641903816764746,
        0.0016261682830269436,
        0.0015880821142481758,
        0.0015499333759148874,
        0.0015117235710660469,
        0.0014734542051496194,
        0.001435126785955902,
        0.0013967428235689707,
        0.0013583038302951032,
        0.0013198113206112235,
        0.001281266811103743,
        0.0012426718204084238,
        0.0012040278691495142,
        0.001165336479880678,
        0.0011265991770259313,
        0.001087817486819288,
        0.0010489929372477008,
        0.0010101270579808048,
        0.0009712213803292163,
        0.000932277437164903,
        0.000893296762876444,
        0.0008542808933021158,
        0.0008152313656796535,
        0.0007761497185724115,
        0.0007370374918303779,
        0.0006978962265239956,
        0.0006587274648936571,
        0.000619532750301983,
        0.0005803136271951402,
        0.0005410716410692871,
        0.0005018083384640074,
        0.00046252526700028325,
        0.0004232239754797741,
        0.00038390601413328845,
        0.00034457293521267176,
        0.00030522629426960014,
        0.00026586765326214174,
        0.00022649858871036835,
        0.0001871207158557841,
        0.00014773577476858758,
        0.0001083460286934494,
        6.89570728205074e-05,
        2.962364450555644e-05};

    double nodes[500] = {
        -0.9999884567522129,
        -0.9999391798145371,
        -0.9998505288592006,
        -0.9997224876879449,
        -0.9995550589335447,
        -0.9993482486165864,
        -0.9991020646933555,
        -0.9988165167849478,
        -0.9984916161049857,
        -0.9981273754352638,
        -0.9977238091159455,
        -0.997280933040936,
        -0.9967987646553128,
        -0.9962773229536412,
        -0.9957166284786823,
        -0.9951167033202715,
        -0.9944775711142633,
        -0.9937992570414846,
        -0.9930817878266696,
        -0.992325191737358,
        -0.9915294985827499,
        -0.9906947397125084,
        -0.9898209480155092,
        -0.9889081579185339,
        -0.9879564053849051,
        -0.9869657279130641,
        -0.9859361645350886,
        -0.9848677558151522,
        -0.9837605438479229,
        -0.9826145722569035,
        -0.9814298861927109,
        -0.9802065323312958,
        -0.9789445588721034,
        -0.977644015536173,
        -0.9763049535641788,
        -0.9749274257144106,
        -0.9735114862606945,
        -0.9720571909902542,
        -0.9705645972015134,
        -0.9690337637018371,
        -0.9674647508052152,
        -0.9658576203298855,
        -0.9642124355958984,
        -0.9625292614226219,
        -0.9608081641261872,
        -0.9590492115168765,
        -0.957252472896451,
        -0.9554180190554201,
        -0.9535459222702526,
        -0.9516362563005288,
        -0.9496890963860347,
        -0.947704519243797,
        -0.9456826030650609,
        -0.9436234275122095,
        -0.9415270737156246,
        -0.9393936242704907,
        -0.9372231632335403,
        -0.9350157761197427,
        -0.9327715498989343,
        -0.930490572992392,
        -0.9281729352693497,
        -0.9258187280434574,
        -0.9234280440691834,
        -0.9210009775381599,
        -0.9185376240754719,
        -0.9160380807358894,
        -0.9135024460000439,
        -0.9109308197705482,
        -0.9083233033680599,
        -0.9056799995272898,
        -0.9030010123929542,
        -0.9002864475156713,
        -0.8975364118478033,
        -0.8947510137392416,
        -0.8919303629331384,
        -0.8890745705615831,
        -0.8861837491412231,
        -0.8832580125688314,
        -0.8802974761168184,
        -0.877302256428691,
        -0.8742724715144563,
        -0.8712082407459724,
        -0.8681096848522449,
        -0.864976925914671,
        -0.8618100873622285,
        -0.8586092939666133,
        -0.8553746718373237,
        -0.8521063484166915,
        -0.8488044524748606,
        -0.8454691141047138,
        -0.8421004647167475,
        -0.8386986370338935,
        -0.8352637650862903,
        -0.8317959842060023,
        -0.8282954310216877,
        -0.8247622434532156,
        -0.8211965607062316,
        -0.8175985232666736,
        -0.8139682728952365,
        -0.8103059526217874,
        -0.8066117067397293,
        -0.802885680800317,
        -0.7991280216069218,
        -0.7953388772092481,
        -0.7915183968974999,
        -0.7876667311964989,
        -0.7837840318597541,
        -0.7798704518634826,
        -0.7759261454005825,
        -0.7719512678745576,
        -0.7679459758933952,
        -0.7639104272633951,
        -0.7598447809829524,
        -0.7557491972362932,
        -0.7516238373871631,
        -0.7474688639724699,
        -0.7432844406958796,
        -0.7390707324213666,
        -0.7348279051667179,
        -0.7305561260969925,
        -0.7262555635179349,
        -0.7219263868693439,
        -0.7175687667183971,
        -0.7131828747529303,
        -0.7087688837746735,
        -0.704326967692442,
        -0.6998573015152848,
        -0.6953600613455899,
        -0.6908354243721447,
        -0.6862835688631563,
        -0.6817046741592265,
        -0.6770989206662871,
        -0.6724664898484908,
        -0.6678075642210626,
        -0.6631223273431083,
        -0.6584109638103826,
        -0.6536736592480159,
        -0.648910600303201,
        -0.6441219746378392,
        -0.6393079709211461,
        -0.6344687788222193,
        -0.6296045890025642,
        -0.624715593108583,
        -0.6198019837640233,
        -0.6148639545623893,
        -0.609901700059314,
        -0.604915415764894,
        -0.5999052981359867,
        -0.5948715445684692,
        -0.5898143533894622,
        -0.5847339238495148,
        -0.5796304561147554,
        -0.5745041512590039,
        -0.5693552112558506,
        -0.5641838389706982,
        -0.5589902381527688,
        -0.5537746134270766,
        -0.5485371702863653,
        -0.5432781150830126,
        -0.5379976550208994,
        -0.5326959981472461,
        -0.5273733533444159,
        -0.5220299303216851,
        -0.5166659396069802,
        -0.5112815925385833,
        -0.505877101256806,
        -0.5004526786956304,
        -0.4950085385743205,
        -0.4895448953890009,
        -0.48406196440420657,
        -0.4785599616444009,
        -0.4730391038854647,
        -0.4674996086461556,
        -0.46194169417953745,
        -0.45636557946438167,
        -0.45077148419653945,
        -0.4451596287802858,
        -0.4395302343196359,
        -0.4338835226096335,
        -0.42821971612761245,
        -0.4225390380244314,
        -0.41684171211568133,
        -0.4111279628728678,
        -0.4053980154145666,
        -0.3996520954975543,
        -0.3938904295079136,
        -0.38811324445211376,
        -0.38232076794806663,
        -0.3765132282161589,
        -0.37069085407026003,
        -0.36485387490870713,
        -0.35900252070526706,
        -0.35313702200007535,
        -0.3472576098905531,
        -0.34136451602230194,
        -0.33545797257997717,
        -0.32953821227813995,
        -0.32360546835208853,
        -0.3176599745486687,
        -0.3117019651170644,
        -0.3057316747995684,
        -0.2997493388223338,
        -0.2937551928861058,
        -0.2877494731569357,
        -0.28173241625687584,
        -0.27570425925465675,
        -0.269665239656347,
        -0.2636155953959953,
        -0.2575555648262563,
        -0.25148538670899967,
        -0.24540530020590262,
        -0.23931554486902742,
        -0.2332163606313831,
        -0.22710798779747213,
        -0.22099066703382264,
        -0.2148646393595063,
        -0.2087301461366422,
        -0.20258742906088745,
        -0.19643673015191443,
        -0.19027829174387526,
        -0.18411235647585422,
        -0.17793916728230763,
        -0.17175896738349253,
        -0.1655720002758839,
        -0.15937850972258097,
        -0.15317873974370322,
        -0.14697293460677596,
        -0.14076133881710645,
        -0.1345441971081505,
        -0.12832175443187002,
        -0.1220942559490822,
        -0.11586194701980015,
        -0.10962507319356599,
        -0.1033838801997762,
        -0.09713861393800015,
        -0.09088952046829167,
        -0.08463684600149451,
        -0.07838083688954174,
        -0.0721217396157496,
        -0.0658598007851062,
        -0.05959526711455543,
        -0.05332838542327645,
        -0.04705940262295916,
        -0.040788565708075965,
        -0.034516121746150395,
        -0.02824231786802273,
        -0.021967401258113205,
        -0.015691619144683082,
        -0.009415218790093976,
        -0.0031384474810658676,
        0.0031384474810658676,
        0.009415218790093976,
        0.015691619144683082,
        0.021967401258113205,
        0.02824231786802273,
        0.034516121746150395,
        0.040788565708075965,
        0.04705940262295916,
        0.05332838542327645,
        0.05959526711455543,
        0.0658598007851062,
        0.0721217396157496,
        0.07838083688954174,
        0.08463684600149451,
        0.09088952046829167,
        0.09713861393800015,
        0.1033838801997762,
        0.10962507319356599,
        0.11586194701980015,
        0.1220942559490822,
        0.12832175443187002,
        0.1345441971081505,
        0.14076133881710645,
        0.14697293460677596,
        0.15317873974370322,
        0.15937850972258097,
        0.1655720002758839,
        0.17175896738349253,
        0.17793916728230763,
        0.18411235647585422,
        0.19027829174387526,
        0.19643673015191443,
        0.20258742906088745,
        0.2087301461366422,
        0.2148646393595063,
        0.22099066703382264,
        0.22710798779747213,
        0.2332163606313831,
        0.23931554486902742,
        0.24540530020590262,
        0.25148538670899967,
        0.2575555648262563,
        0.2636155953959953,
        0.269665239656347,
        0.27570425925465675,
        0.28173241625687584,
        0.2877494731569357,
        0.2937551928861058,
        0.2997493388223338,
        0.3057316747995684,
        0.3117019651170644,
        0.3176599745486687,
        0.32360546835208853,
        0.32953821227813995,
        0.33545797257997717,
        0.34136451602230194,
        0.3472576098905531,
        0.35313702200007535,
        0.35900252070526706,
        0.36485387490870713,
        0.37069085407026003,
        0.3765132282161589,
        0.38232076794806663,
        0.38811324445211376,
        0.3938904295079136,
        0.3996520954975543,
        0.4053980154145666,
        0.4111279628728678,
        0.41684171211568133,
        0.4225390380244314,
        0.42821971612761245,
        0.4338835226096335,
        0.4395302343196359,
        0.4451596287802858,
        0.45077148419653945,
        0.45636557946438167,
        0.46194169417953745,
        0.4674996086461556,
        0.4730391038854647,
        0.4785599616444009,
        0.48406196440420657,
        0.4895448953890009,
        0.4950085385743205,
        0.5004526786956304,
        0.505877101256806,
        0.5112815925385833,
        0.5166659396069802,
        0.5220299303216851,
        0.5273733533444159,
        0.5326959981472461,
        0.5379976550208994,
        0.5432781150830126,
        0.5485371702863653,
        0.5537746134270766,
        0.5589902381527688,
        0.5641838389706982,
        0.5693552112558506,
        0.5745041512590039,
        0.5796304561147554,
        0.5847339238495148,
        0.5898143533894622,
        0.5948715445684692,
        0.5999052981359867,
        0.604915415764894,
        0.609901700059314,
        0.6148639545623893,
        0.6198019837640233,
        0.624715593108583,
        0.6296045890025642,
        0.6344687788222193,
        0.6393079709211461,
        0.6441219746378392,
        0.648910600303201,
        0.6536736592480159,
        0.6584109638103826,
        0.6631223273431083,
        0.6678075642210626,
        0.6724664898484908,
        0.6770989206662871,
        0.6817046741592265,
        0.6862835688631563,
        0.6908354243721447,
        0.6953600613455899,
        0.6998573015152848,
        0.704326967692442,
        0.7087688837746735,
        0.7131828747529303,
        0.7175687667183971,
        0.7219263868693439,
        0.7262555635179349,
        0.7305561260969925,
        0.7348279051667179,
        0.7390707324213666,
        0.7432844406958796,
        0.7474688639724699,
        0.7516238373871631,
        0.7557491972362932,
        0.7598447809829524,
        0.7639104272633951,
        0.7679459758933952,
        0.7719512678745576,
        0.7759261454005825,
        0.7798704518634826,
        0.7837840318597541,
        0.7876667311964989,
        0.7915183968974999,
        0.7953388772092481,
        0.7991280216069218,
        0.802885680800317,
        0.8066117067397293,
        0.8103059526217874,
        0.8139682728952365,
        0.8175985232666736,
        0.8211965607062316,
        0.8247622434532156,
        0.8282954310216877,
        0.8317959842060023,
        0.8352637650862903,
        0.8386986370338935,
        0.8421004647167475,
        0.8454691141047138,
        0.8488044524748606,
        0.8521063484166915,
        0.8553746718373237,
        0.8586092939666133,
        0.8618100873622285,
        0.864976925914671,
        0.8681096848522449,
        0.8712082407459724,
        0.8742724715144563,
        0.877302256428691,
        0.8802974761168184,
        0.8832580125688314,
        0.8861837491412231,
        0.8890745705615831,
        0.8919303629331384,
        0.8947510137392416,
        0.8975364118478033,
        0.9002864475156713,
        0.9030010123929542,
        0.9056799995272898,
        0.9083233033680599,
        0.9109308197705482,
        0.9135024460000439,
        0.9160380807358894,
        0.9185376240754719,
        0.9210009775381599,
        0.9234280440691834,
        0.9258187280434574,
        0.9281729352693497,
        0.930490572992392,
        0.9327715498989343,
        0.9350157761197427,
        0.9372231632335403,
        0.9393936242704907,
        0.9415270737156246,
        0.9436234275122095,
        0.9456826030650609,
        0.947704519243797,
        0.9496890963860347,
        0.9516362563005288,
        0.9535459222702526,
        0.9554180190554201,
        0.957252472896451,
        0.9590492115168765,
        0.9608081641261872,
        0.9625292614226219,
        0.9642124355958984,
        0.9658576203298855,
        0.9674647508052152,
        0.9690337637018371,
        0.9705645972015134,
        0.9720571909902542,
        0.9735114862606945,
        0.9749274257144106,
        0.9763049535641788,
        0.977644015536173,
        0.9789445588721034,
        0.9802065323312958,
        0.9814298861927109,
        0.9826145722569035,
        0.9837605438479229,
        0.9848677558151522,
        0.9859361645350886,
        0.9869657279130641,
        0.9879564053849051,
        0.9889081579185339,
        0.9898209480155092,
        0.9906947397125084,
        0.9915294985827499,
        0.992325191737358,
        0.9930817878266696,
        0.9937992570414846,
        0.9944775711142633,
        0.9951167033202715,
        0.9957166284786823,
        0.9962773229536412,
        0.9967987646553128,
        0.997280933040936,
        0.9977238091159455,
        0.9981273754352638,
        0.9984916161049857,
        0.9988165167849478,
        0.9991020646933555,
        0.9993482486165864,
        0.9995550589335447,
        0.9997224876879449,
        0.9998505288592006,
        0.9999391798145371,
        0.9999884567522129};

    _POSTFIX__ P_function = submodule_Parse(I_function);
    double sum = 0.0;
    double _A_ = (b - a) / 2.0;
    double _B_ = (b + a) / 2.0;
    for (unsigned short int i = 0; i < 500; i++)
    {
        // sum += weights[i] * ni_eval_P_function(P_function, var, _A_ * nodes[i] + _B_);

        double x_i = _A_ * nodes[i] + _B_;

        _POSTFIX__ copyof_P_function = copy_postfix_expression(P_function);

        for (unsigned short int p = 0; p < copyof_P_function.size; p++)
        {
            if (copyof_P_function.tokens[p].variable == var)
            {
                copyof_P_function.tokens[p].num = x_i;
                copyof_P_function.tokens[p].variable = '\0';
            }
        }

        sum += weights[i] * Compute_P_expression(copyof_P_function);

        free(copyof_P_function.tokens);
        copyof_P_function.tokens = NULL;
    }

    free(P_function.tokens);

    sum *= sign * _A_;

    return sum;
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

    double n = 1000.0; // Number of subintervals - Larger n --> More accurate
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

    memcpy(copyof_source.tokens, source.tokens, sizeof(_infix_) * source.size);

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

    memcpy(copyof_source.tokens, source.tokens, sizeof(_infix_) * source.size);

    return copyof_source;
}

double evaluate_I_1_var_function(const __INFIX__ I_function, const char var, const double value)
{
    // Parse to postfix type
    _POSTFIX__ P_function = submodule_Parse(I_function);

    // substitude variable
    for (unsigned short int i = 0; i < P_function.size; i++)
    {
        if (P_function.tokens[i].variable == var)
        {
            P_function.tokens[i].num = value;
            P_function.tokens[i].variable = '\0';
        }
    }

    double result = Compute_P_expression(P_function);

    free(P_function.tokens);

    return result;
}

#endif