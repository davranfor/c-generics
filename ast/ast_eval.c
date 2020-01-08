#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ast_data.h"
#include "ast_eval.h"

ast_data ast_plus(ast_data a, ast_data b)
{
    (void)b;
    return a;
}

ast_data ast_minus(ast_data a, ast_data b)
{
    (void)b;
    if (a.type == TYPE_NUMBER)
    {
        a.number = -a.number;
    }
    return a;
}

ast_data ast_not(ast_data a, ast_data b)
{
    (void)b;
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number == 0;
    return a;
}

ast_data ast_mul(ast_data a, ast_data b)
{
    if ((a.type == TYPE_NUMBER) && (b.type == TYPE_NUMBER))
    {
        a.number = a.number * b.number;
    }
    return a;
}

ast_data ast_div(ast_data a, ast_data b)
{
    if ((a.type == TYPE_NUMBER) && (b.type == TYPE_NUMBER))
    {
        a.number = a.number / b.number;
    }
    return a;
}

ast_data ast_rem(ast_data a, ast_data b)
{
    if ((a.type == TYPE_NUMBER) && (b.type == TYPE_NUMBER))
    {
        a.number = (int)a.number % (int)b.number;
    }
    return a;
}

ast_data ast_add(ast_data a, ast_data b)
{
    if ((a.type == TYPE_NUMBER) && (b.type == TYPE_NUMBER))
    {
        a.number = a.number + b.number;
    }
    return a;
}

ast_data ast_sub(ast_data a, ast_data b)
{
    if ((a.type == TYPE_NUMBER) && (b.type == TYPE_NUMBER))
    {
        a.number = a.number - b.number;
    }
    return a;
}

ast_data ast_lt(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number < b.number;
    return a;
}

ast_data ast_gt(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number > b.number;
    return a;
}

ast_data ast_lt_or_eq(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number <= b.number;
    return a;
}

ast_data ast_gt_or_eq(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number >= b.number;
    return a;
}

ast_data ast_is_eq(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number == b.number;
    return a;
}

ast_data ast_not_eq(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number != b.number;
    return a;
}

ast_data ast_bit_and(ast_data a, ast_data b)
{
    (void)b;
    return a;
}

ast_data ast_and(ast_data a, ast_data b)
{
    if (a.type != TYPE_BOOLEAN)
    {
        a.type = TYPE_BOOLEAN;
    }
    a.number = a.number && b.number;
    return a;
}

ast_data ast_eq(ast_data a, ast_data b)
{
    a.variable->data = b;
    return b;
}

///////////////////////////////////////////////////////////////////////////////

#define MAX_FRAME 8192

static ast_data frame[MAX_FRAME];
static int counter;

int push_data(ast_data data)
{
    if (counter == MAX_FRAME)
    {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    frame[counter++] = data;
    return 1;
}

ast_data pop_data(void)
{
    if (counter == 0)
    {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return frame[--counter];    
}

static ast_data *peek_data(void)
{
    if (counter == 0)
    {
        fprintf(stderr, "Empty stack\n");
        exit(EXIT_FAILURE);
    }
    return &frame[counter - 1];    
}

///////////////////////////////////////////////////////////////////////////////
// Maths
///////////////////////////////////////////////////////////////////////////////

int ast_abs(void)
{
    ast_data *data = peek_data();

    data->number = fabs(data->number);
    return 1;
}

int ast_ceil(void)
{
    ast_data *data = peek_data();

    data->number = ceil(data->number);
    return 1;
}

int ast_cos(void)
{
    ast_data *data = peek_data();

    data->number = cos(data->number);
    return 1;
}

int ast_cosh(void)
{
    ast_data *data = peek_data();

    data->number = cosh(data->number);
    return 1;
}

int ast_exp(void)
{
    ast_data *data = peek_data();

    data->number = exp(data->number);
    return 1;
}

int ast_floor(void)
{
    ast_data *data = peek_data();

    data->number = floor(data->number);
    return 1;
}

int ast_log(void)
{
    ast_data *data = peek_data();

    data->number = log(data->number);
    return 1;
}

int ast_log10(void)
{
    ast_data *data = peek_data();

    data->number = log10(data->number);
    return 1;
}

int ast_pow(void)
{
    ast_data b = pop_data();
    ast_data *a = peek_data();

    a->number = pow(a->number, b.number);
    return 1;
}

int ast_rand(void)
{
    ast_data data;

    data.type = TYPE_NUMBER;
    data.number = rand();
    return push_data(data);
}

int ast_round(void)
{
    ast_data *data = peek_data();

    data->number = round(data->number);
    return 1;
}

int ast_sin(void)
{
    ast_data *data = peek_data();

    data->number = sin(data->number);
    return 1;
}

int ast_sinh(void)
{
    ast_data *data = peek_data();

    data->number = sinh(data->number);
    return 1;
}

int ast_sqr(void)
{
    ast_data *data = peek_data();

    data->number = sqrt(data->number);
    return 1;
}

int ast_tan(void)
{
    ast_data *data = peek_data();

    data->number = tan(data->number);
    return 1;
}

int ast_tanh(void)
{
    ast_data *data = peek_data();

    data->number = tanh(data->number);
    return 1;
}

int ast_trunc(void)
{
    ast_data *data = peek_data();

    data->number = trunc(data->number);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Misc
///////////////////////////////////////////////////////////////////////////////

int ast_print(void)
{
    ast_data *data = peek_data();

    switch (data->type)
    {
        case TYPE_BOOLEAN:
            printf("%s\n", data->number ? "true" : "false");
            data->type = TYPE_NUMBER;
            return 1;
        case TYPE_NUMBER:
            data->number = printf("%g\n", data->number);
            data->type = TYPE_NUMBER;
            return 1;
        case TYPE_STRING:
            data->number = printf("%s\n", data->string);
            data->type = TYPE_NUMBER;
            return 1;
        default:
            printf("Can not print this value\n");
            return 0;
    }
}

