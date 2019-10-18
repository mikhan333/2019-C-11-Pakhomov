#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cassert>
#include <const.hpp>
// TODO enum & type of data & type of comands --- in the file - lib.h
// TODO commands in different function from main
// TODO Makefile


int check_command(const char *stack_command)
{
    if (!strcmp(stack_command, "push"))
        return CMD_PUSH;
    else if (!strcmp(stack_command, "pop"))
        return CMD_POP;
    else if (!strcmp(stack_command, "in"))
        return CMD_IN;
    else if (!strcmp(stack_command, "out"))
        return CMD_OUT;
    else if (!strcmp(stack_command, "add"))
        return CMD_ADD;
    else if (!strcmp(stack_command, "sub"))
        return CMD_SUB;
    else if (!strcmp(stack_command, "mul"))
        return CMD_MUL;
    else if (!strcmp(stack_command, "div"))
        return CMD_DIV;
    else if (!strcmp(stack_command, "sqrt"))
        return CMD_SQRT;
    else if (!strcmp(stack_command, "sin"))
        return CMD_SIN;
    else if (!strcmp(stack_command, "cos"))
        return CMD_COS;
    else if (!strcmp(stack_command, "end"))
        return CMD_END;
    else if (*stack_command == ';')
        return CMD_COMMENT;
    return CMD_BAD_VALUE;
}

bool isnumber(const char *stack_value)
{
    int i = 0;
    char elem;
    while ((elem = *(stack_value + i++)) != '\0')
    {
        if (!isdigit(elem))
            return false;
    }
    return true;
}

int check_argument(const char *stack_argument)
{
    if (isnumber(stack_argument))
        return ARG_NUMBER;
    else if (!strcmp(stack_argument, "ax"))
        return ARG_REG_AX;
    else if (!strcmp(stack_argument, "bx"))
        return ARG_REG_BX;
    else if (!strcmp(stack_argument, "cx"))
        return ARG_REG_CX;
    else if (!strcmp(stack_argument, "dx"))
        return ARG_REG_DX;
    return ARG_BAD_VALUE;
}

int main(int argc, char *argv[])
{
    printf("---------------------------------------------------\n");
    printf("This is a assembler programm\n"
           "from file asm.cpp\n"
           "Created by Mikhail Pakhomov\n\n");
    char default_path_in[] = "test.txt";
    char default_path_out[] = "test.bin";
    char *path_file_in = default_path_in;
    char *path_file_out = default_path_out;
    if (argc == 3)
    {
        path_file_in = argv[1];
        path_file_out = argv[2];
    }

    FILE *file_in = fopen(path_file_in, "r");
    if (file_in == NULL)
    {
        printf("ERROR: open_file(): problem with opening the file : %s\n", path_file_in);
        exit(EXIT_FAILURE);
    }
    FILE *file_out = fopen(path_file_out, "wb");
    if (file_in == NULL)
    {
        printf("ERROR: open_file(): problem with opening the file : %s\n", path_file_out);
        exit(EXIT_FAILURE);
    }

    char stack_command[20];
    short result, argument;
    int number;
    while (fscanf(file_in, "%s", stack_command) != EOF) // TODO normal code
    {
        result = check_command(stack_command);
        printf("%s", stack_command);
        switch (result)
        {
        case CMD_PUSH:
            if (fscanf(file_in, "%s", stack_command) == EOF)
            {
                printf("ERROR : incorrect argument : %s", stack_command);
                assert(!"Push bad value");
                break;
            }
            printf(" %s", stack_command);
            argument = check_argument(stack_command);
            switch (argument)
            {
            case ARG_NUMBER:
                number = atoi(stack_command);
                fwrite(&result, sizeof(short), 1, file_out);
                fwrite(&number, sizeof(int), 1, file_out);
                break;
            case ARG_BAD_VALUE:
                printf("ERROR : incorrect argument : %s", stack_command);
                assert(!"Push bad value");
                break;
            default:
                result = CMD_PUSH_REG;
                fwrite(&result, sizeof(short), 1, file_out);
                fwrite(&argument, sizeof(short), 1, file_out);
                break;
            }
            break;
        case CMD_POP:
            if (fscanf(file_in, "%s", stack_command) == EOF)
            {
                fwrite(&result, sizeof(short), 1, file_out);
                break;
            }
            printf(" %s", stack_command);
            argument = check_argument(stack_command);
            if (argument == ARG_NUMBER ||
                argument == ARG_BAD_VALUE)
            {
                fwrite(&result, sizeof(short), 1, file_out);
                fseek(file_in, -sizeof(char) * strlen(stack_command), SEEK_CUR);
            }
            else
            {
                result = CMD_POP_REG;
                fwrite(&result, sizeof(short), 1, file_out);
                fwrite(&argument, sizeof(short), 1, file_out);
            }
            break;
        case CMD_BAD_VALUE:
            printf("ERROR : incorrect command : %s", stack_command);
            assert(!"Cmd bad value");
            break;
        case CMD_COMMENT:
            fgets(nullptr, 255, file_in);
            break;
        default:
            fwrite(&result, sizeof(short), 1, file_out);
            break;
        }
        printf("\n");
    }

    fclose(file_in);
    fclose(file_out);

    printf("---------------------------------------------------\n");
    return EXIT_SUCCESS;
}