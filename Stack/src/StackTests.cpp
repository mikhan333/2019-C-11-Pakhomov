#include <iostream>
#include <cstdlib>
#include <cassert>
#include "../lib/Stack.h"

#define EPSILON 1e-4
#define CHECK_EQUAL(a, b) ((((b)-EPSILON < (a)) && ((b) + EPSILON > (a))) ? true : false)

void test_stack_ordinary()
{
    bool err = 0;
    Elem_t value = 10;
    StackInit(st);

    StackPush(&st, value);
    Elem_t x = StackPop(&st, &err);
    assert(!err);
    assert(CHECK_EQUAL(value, x));

    x = StackPop(&st, &err);
    assert(err);

    StackDestructor(&st);
}

void test_stack_growth()
{
    Stack_t stk_growth = {"stk_growth"};
    StackConstruct(&stk_growth, 2, "debug/debug_growth.log");
    int i = 0;
    bool err = 0;
    Elem_t x;

    for (; i < 50; i++)
    {
        StackPush(&stk_growth, i);
        if (i % 10 == 0)
            StackDump(&stk_growth);
    }

    for (i--; i >= 0; --i)
    {
        if (i % 10 == 0)
            StackDump(&stk_growth);
        x = StackPop(&stk_growth, &err);
        assert(!err);
        assert(CHECK_EQUAL(x, i));
    }
    assert(stk_growth.max_size <= STACK_INITIAL_MAXSIZE);

    StackDestructor(&stk_growth);
}

void test_stack_big_data()
{
    Stack_t stk_big_data = {"stk_big_data"};
    StackConstruct(&stk_big_data, 2, "debug/debug_big_data.log");
    bool err = false;

    StackDump(&stk_big_data);
    for (int i = 0; i < 1e3; i++)
        assert(StackPush(&stk_big_data, 666));
    StackDump(&stk_big_data);
    while(!err)
        StackPop(&stk_big_data, &err);
    StackDump(&stk_big_data);

    StackDestructor(&stk_big_data);
}

void test_stack_ver_level(short level)
{
    bool err = 0;
    Elem_t value = 10;
    char path_file[30];
    sprintf(path_file, "%s%d%s", "debug/debug_ver_level_", level, ".log");

    Stack_t stk_verifications_levels = {"stk_verifications_levels"};
    StackConstruct(&stk_verifications_levels, level, path_file);
    StackDump(&stk_verifications_levels);

    StackPush(&stk_verifications_levels, value);
    StackDump(&stk_verifications_levels);
    Elem_t x = StackPop(&stk_verifications_levels, &err);
    assert(!err);
    assert(CHECK_EQUAL(value, x));
    x = StackPop(&stk_verifications_levels, &err);
    assert(err);
    StackDump(&stk_verifications_levels);

    StackDestructor(&stk_verifications_levels);
}

void test_stack_verifications_levels()
{
    test_stack_ver_level(0);
    test_stack_ver_level(1);
    test_stack_ver_level(2);
}

void test_stack_boundaries()
{
    
}

void test_stack()
{
    test_stack_ordinary();
    test_stack_growth();
    test_stack_big_data();
    test_stack_verifications_levels();
    test_stack_boundaries();
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
