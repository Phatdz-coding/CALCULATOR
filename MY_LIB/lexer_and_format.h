#ifndef LEXER_AND_FORMAT_H
#define LEXER_AND_FORMAT_H

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
#include <MY_LIB/extra_math_function.h>

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
//                                                 MACROES
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //

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

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //

void optimize_I_exp(__INFIX__ *I_exp);

void optimize_P_exp(_POSTFIX__ *P_exp);

__INFIX__ convert_string_to_INFIX(char *expression);

char __operator__(char *expression, int token);

void _increase_(int *token, char op);

void reformat_I_exp(__INFIX__ *I_exp);

void merge_2_num(__INFIX__ *I_exp, const short int index);
void merge_num_and_bracket(__INFIX__ *I_exp, const short int index);
void merge_multiplier_of_one(__INFIX__ *I_exp, const short int index);
void merge_multiplier_of_zero(__INFIX__ *I_exp, const short int index, const bool zero_first);
bool merge_unused_bracket(__INFIX__ *I_exp, const short int index);
void merge_pow_of_one(__INFIX__ *I_exp, const short int index);
void merge_pow_of_zero(__INFIX__ *I_exp, const short int index);

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //


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
char __operator__(char *expression, int token)
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

#endif