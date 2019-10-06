#ifndef STACK_H
#define STACK_H

#define STACK_INITIAL_MAXSIZE 100
#define STACK_DELTA_SIZE 50

typedef enum Bool_t
{
    false,
    true,
} bool;

typedef enum StackError_t // TODO use this
{
    STACK_OVERFLOW, // TODO more errors
    STACK_UNDERFLOW,
    STACK_INTERNAL_ERROR,
} StackError;

typedef int Type_t;
typedef struct Stack_t
{
    Type_t *data;
    int size;
    int max_size;
} Stack;

bool StackConstruct(Stack *this_);
bool StackDestructor(Stack *this_);
bool StackPush(Stack *this_, const Type_t elem);
bool StackPop(Stack *this_, Type_t *elem);
bool StackOk(const Stack *this_);
bool StackDump(const Stack *this_);

bool StackSetSize(Stack *this_, const int size);
#endif
