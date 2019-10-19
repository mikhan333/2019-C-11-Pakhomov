#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include "../../3Stack/lib/Stack.h"
#include "../lib/const.hpp"

#define PUSH(stk, number)                                      \
    {                                                          \
        if (!StackPush(&stk, number))                          \
        {                                                      \
            StackDump(&stk);                                   \
            printf("ERROR : StackPush : number=%d\n", number); \
            assert(!"StackPush");                              \
        }                                                      \
    }

#define POP(stk, number, err)                                      \
    {                                                              \
        number = StackPop(&stk, &err);                             \
        if (err)                                                   \
        {                                                          \
            StackDump(&stk);                                       \
            printf("ERROR : StackPop : zero elements in stack\n"); \
            assert(!"StackPop");                                   \
        }                                                          \
    }

#define POP_TWO(stk, number1, number2)                                    \
    {                                                                     \
        if (!StackPopTwoElem(&stk, &number1, &number2))                   \
        {                                                                 \
            StackDump(&stk);                                              \
            printf("ERROR : StackPopTwoElem : zero elements in stack\n"); \
            assert(!"StackPopTwo");                                       \
        }                                                                 \
    }

bool StackPopTwoElem(Stack_t *stk, Elem_t *value1, Elem_t *value2)
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

int main(int argc, char *argv[])
{
    printf("---------------------------------------------------\n");
    printf("This is a processor program based on Stack\n"
           "from file cpu.cpp and lib Stack.h\n"
           "Created by Mikhail Pakhomov\n\n");
    const char *path_file_in = (argc == 2) ? argv[1] : "build/test_asm.bin";
    FILE *file_in = fopen(path_file_in, "rb");
    if (file_in == NULL)
    {
        printf("ERROR: open_file(): problem with opening the file : %s\n", path_file_in);
        exit(EXIT_FAILURE);
    }

    /**
     * @brief Construct a new Stack Init object
     * 
     */
    StackInit(stk);

    /**
     * @brief Create registers
     * 
     */
    Argument_t ax, bx, cx, dx;

    /**
     * @brief Input arguments and commands from bin file
     * 
     */
    Command_t command, argument;
    Argument_t number, number2;

    /**
     * @brief Start reading input file
     * 
     */
    bool err = false;
    bool exitCase = false;
    while (fread(&command, sizeof(Command_t), 1, file_in) == 1)
    {
        switch (command)
        {
        case CMD_PUSH:
            fread(&number, sizeof(Argument_t), 1, file_in);
            PUSH(stk, number);
            break;
        case CMD_PUSH_REG:
            fread(&argument, sizeof(Command_t), 1, file_in);
            switch (argument)
            {
            case ARG_REG_AX:
                number = ax;
                break;
            case ARG_REG_BX:
                number = bx;
                break;
            case ARG_REG_CX:
                number = cx;
                break;
            case ARG_REG_DX:
                number = dx;
                break;
            default:
                printf("ERROR : PushReg : incorrect reg=%d", argument);
                assert(!"PushReg");
                break;
            }
            PUSH(stk, number);
            break;
        case CMD_POP:
            POP(stk, number, err);
            break;
        case CMD_POP_REG:
            POP(stk, number, err);
            fread(&argument, sizeof(Command_t), 1, file_in);
            switch (argument)
            {
            case ARG_REG_AX:
                ax = number;
                break;
            case ARG_REG_BX:
                bx = number;
                break;
            case ARG_REG_CX:
                cx = number;
                break;
            case ARG_REG_DX:
                dx = number;
                break;
            default:
                printf("ERROR : PopReg : incorrect reg=%d", argument);
                assert(!"PopReg");
                break;
            }
            break;
        case CMD_IN:
            scanf("%d", &number);
            PUSH(stk, number);
            break;
        case CMD_OUT:
            POP(stk, number, err);
            printf("%d\n", number);
            break;
        case CMD_ADD:
            POP_TWO(stk, number, number2);
            PUSH(stk, number + number2);
            break;
        case CMD_SUB:
            POP_TWO(stk, number, number2);
            PUSH(stk, number - number2);
            break;
        case CMD_MUL:
            POP_TWO(stk, number, number2);
            PUSH(stk, number * number2);
            break;
        case CMD_DIV:
            POP_TWO(stk, number, number2);
            PUSH(stk, number / number2);
            break;
        case CMD_SQRT:
            POP(stk, number, err);
            PUSH(stk, sqrt(number));
            break;
        case CMD_SIN:
            POP(stk, number, err);
            PUSH(stk, sin(number));
            break;
        case CMD_COS:
            POP(stk, number, err);
            PUSH(stk, cos(number));
            break;
        case CMD_END:
            exitCase = true;
            break;
        default:
            printf("ERROR : IncorrectCommand=%d\n", command);
            assert(!"IncorrectCommand");
            break;
        }

        if (exitCase)
            break;
    }

    fclose(file_in);

    printf("---------------------------------------------------\n");
    return EXIT_SUCCESS;
}