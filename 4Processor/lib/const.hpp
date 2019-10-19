
typedef short Command_t;
typedef int Argument_t;

enum StackCommands
{
    CMD_BAD_VALUE = 1,
    CMD_PUSH,
    CMD_PUSH_REG,
    CMD_POP,
    CMD_POP_REG,
    CMD_IN,
    CMD_OUT,
    CMD_ADD,
    CMD_SUB,
    CMD_MUL,
    CMD_DIV,
    CMD_SQRT,
    CMD_SIN,
    CMD_COS,
    CMD_END,
    CMD_COMMENT,
};

enum StackValues
{
    ARG_BAD_VALUE = 0,
    ARG_NUMBER,
    ARG_REG_AX,
    ARG_REG_BX,
    ARG_REG_CX,
    ARG_REG_DX,
};
