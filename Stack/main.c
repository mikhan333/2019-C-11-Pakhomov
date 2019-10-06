#include <stdio.h>
#include <stdlib.h>
#include "src/Stack.h"

void test_stack_ordinary()
{
    Stack st = {};
    StackConstruct(&st);
    StackPush(&st, 10);
    Type_t x;

    bool err = StackPop(&st, &x);
    if (!err)
        printf("Something wrong\n");
    printf("number: %d\n", x);

    StackDestructor(&st);
}

void test_stack()
{
    test_stack_ordinary();
    printf("Tests succesfully completed\n");
}

int main()
{
    printf("---------------------------------------------------\n");
    printf("This is a program for testing Stack\n"
           "from file Stack.c and lib Stack.h\n"
           "Created by Mikhail Pakhomov\n\n");
    test_stack();
    printf("---------------------------------------------------\n");

    return 0;
}
