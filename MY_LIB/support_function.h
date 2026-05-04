#ifndef SP_FUNCTIONS
#define SP_FUNCTIONS

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
#include <MY_LIB/types_and_specifiers.h>

void copy_sub_I_exp(__INFIX__ *destination, __INFIX__ source, const short int index_start, const short int index_end);
void substitude_result(__INFIX__ *I_exp_tobe_replaced, const __INFIX__ replacement, const int index_start, const int index_end);
void display_postfix_exp(_POSTFIX__ P_exp);

// ------------------------------------------------- //

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


#endif