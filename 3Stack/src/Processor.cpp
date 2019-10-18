#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "../lib/Stack.h"

bool pop_two_elem(Stack_t *stk, Elem_t *value1, Elem_t *value2)
{
    bool err = false;
    *value2 = StackPop(stk, &err);
    if (err)
    {
        printf("pop_two_elem() : ERROR : 0 elements in Stack\n");
        return false;
    }
    *value1 = StackPop(stk, &err);
    if (err)
    {
        printf("pop_two_elem() : ERROR : 1 element in Stack\n");
        StackPush(stk, *value2);
        return false;
    }
    return true;
}

void input_command(Stack_t *stk)
{
    char stack_command[10];
    Elem_t value1 = 0, value2 = 0, result = 0;
    bool err = false;
    while (true)
    {
        scanf("%s", stack_command);
        if (!strcmp(stack_command, "push"))
        {
            scanf("%lf", &value1);
            if (!StackPush(stk, value1))
            {
                printf("input_command() : Push Error\n");
                continue;
            }
        }
        else if (!strcmp(stack_command, "pop"))
        {
            value1 = StackPop(stk, &err);
            if (err)
            {
                printf("input_command() : Pop Error\n");
                continue;
            }
            printf("%f\n", value1);
        }
        else if (!strcmp(stack_command, "add"))
        {
            if (!pop_two_elem(stk, &value1, &value2))
            {
                printf("input_command() : Add Error\n");
                continue;
            }
            result = value1 + value2;
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "sub"))
        {
            if (!pop_two_elem(stk, &value1, &value2))
            {
                printf("input_command() : Sub Error\n");
                continue;
            }
            result = value1 - value2;
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "mul"))
        {
            if (!pop_two_elem(stk, &value1, &value2))
            {
                printf("input_command() : Mul Error\n");
                continue;
            }
            result = value1 * value2;
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "div"))
        {
            if (!pop_two_elem(stk, &value1, &value2))
            {
                printf("input_command() : Div Error\n");
                continue;
            }
            result = value1 / value2;
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "sqrt"))
        {
            value1 = StackPop(stk, &err);
            if (err)
            {
                printf("input_command() : Sqrt Error\n");
                continue;
            }
            if (value1 < 0)
            {
                printf("input_command() : Sqrt Error : value < 0\n");
                StackPush(stk, value1);
                continue;
            }
            result = sqrt(value1);
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "sin"))
        {
            value1 = StackPop(stk, &err);
            if (err)
            {
                printf("input_command() : Sin Error\n");
                continue;
            }
            result = sin(value1);
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "cos"))
        {
            value1 = StackPop(stk, &err);
            if (err)
            {
                printf("input_command() : Cos Error\n");
                continue;
            }
            result = cos(value1);
            StackPush(stk, result);
            printf("%f\n", result);
        }
        else if (!strcmp(stack_command, "end"))
        {
            StackDestructor(stk);
            break;
        }
        else 
        {
            printf("input_command() : Unreasonable Command\n");
        }
        result = 0;
    }
}

int main()
{
    printf("---------------------------------------------------\n");
    printf("This is a processor program based on Stack\n"
           "from file Processor.c and lib Stack.h\n"
           "Created by Mikhail Pakhomov\n\n");

    StackInit(st);
    input_command(&st);

    printf("---------------------------------------------------\n");
    return 0;
}