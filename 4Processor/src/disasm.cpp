#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cassert>
#include "../lib/const.hpp"

const char *get_command(const Command_t command)
{
    switch (command)
    {
    case CMD_PUSH:
        return "push";
        break;
    case CMD_PUSH_REG:
        return "push";
        break;
    case CMD_POP:
        return "pop";
        break;
    case CMD_POP_REG:
        return "pop";
        break;
    case CMD_IN:
        return "in";
        break;
    case CMD_OUT:
        return "out";
        break;
    case CMD_ADD:
        return "add";
        break;
    case CMD_SUB:
        return "sub";
        break;
    case CMD_MUL:
        return "mul";
        break;
    case CMD_DIV:
        return "div";
        break;
    case CMD_SQRT:
        return "sqrt";
        break;
    case CMD_SIN:
        return "sin";
        break;
    case CMD_COS:
        return "cos";
        break;
    case CMD_END:
        return "end";
        break;
    default:
        return "";
        break;
    }
}

const char *get_argument(const Command_t argument)
{
    switch (argument)
    {
    case ARG_REG_AX:
        return "ax";
        break;
    case ARG_REG_BX:
        return "bx";
        break;
    case ARG_REG_CX:
        return "cx";
        break;
    case ARG_REG_DX:
        return "dx";
        break;
    default:
        return "";
        break;
    }
}

int main(int argc, char *argv[])
{
    printf("---------------------------------------------------\n");
    printf("This is a disassembler programm\n"
           "from file disasm.cpp\n"
           "Created by Mikhail Pakhomov\n\n");
    const char *path_file_in = "build/test_asm.bin";
    const char *path_file_out = "build/test_disasm.txt";
    if (argc == 3)
    {
        path_file_in = argv[1];
        path_file_out = argv[2];
    }

    FILE *file_in = fopen(path_file_in, "rb");
    if (file_in == NULL)
    {
        printf("ERROR: open_file(): problem with opening the file : %s\n", path_file_in);
        exit(EXIT_FAILURE);
    }
    FILE *file_out = fopen(path_file_out, "w");
    if (file_in == NULL)
    {
        printf("ERROR: open_file(): problem with opening the file : %s\n", path_file_out);
        exit(EXIT_FAILURE);
    }

    const char *stack_command, *stack_argument;
    Command_t command;
    Argument_t number;
    while (fread(&command, sizeof(Command_t), 1, file_in) == 1)
    {
        stack_command = get_command(command);
        printf("%s", stack_command);
        switch (command)
        {
        case CMD_PUSH:
            fread(&number, sizeof(Argument_t), 1, file_in);
            printf(" %d", number);
            fprintf(file_out, "%s %d", stack_command, number);
            break;
        case CMD_PUSH_REG:
            fread(&command, sizeof(Command_t), 1, file_in);
            stack_argument = get_argument(command);
            printf(" %s", stack_argument);
            fprintf(file_out, "%s %s", stack_command, stack_argument);
            break;
        case CMD_POP_REG:
            fread(&command, sizeof(Command_t), 1, file_in);
            stack_argument = get_argument(command);
            printf(" %s", stack_argument);
            fprintf(file_out, "%s %s", stack_command, stack_argument);
            break;
        case CMD_BAD_VALUE:
            printf("ERROR : incorrect command : %d", command);
            assert(!"Cmd bad value");
            break;
        default:
            fprintf(file_out, "%s", stack_command);
            break;
        }
        fprintf(file_out, "\n");
        printf("\n");
    }

    fclose(file_in);
    fclose(file_out);

    printf("---------------------------------------------------\n");
    return EXIT_SUCCESS;
}
