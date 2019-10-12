#include <iostream>
#include <cstdlib>
#include "src/Stack.h"

void test_stack_ordinary()
{
    // Stack_t st = {};
    // StackConstruct(&st);
    StackInit(st);
    StackPush(&st, 10);
    StackPush(&st, 20);
    StackPush(&st, 5);
    StackDump(&st);
    int err = 0;

    Elem_t x = StackPop(&st, &err);
    if (err)
        printf("Something wrong %d\n", err);
    printf("number: %d\n", x);

    StackDestructor(&st);
}

// TODO correct tests
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
