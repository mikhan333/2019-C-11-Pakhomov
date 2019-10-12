#ifndef STACK_H
#define STACK_H

#define STACK_INITIAL_MAXSIZE 100
#define STACK_DELTA_SIZE 50

typedef unsigned Canary_t;
#define STACK_CANARY1 0xDEADBEEFU
#define STACK_CANARY2 0x38023802U
#define STACK_HASH_SEED 0x1A4E41CDL

#define STACK_ASSERT_OK       \
    {                         \
        if (!StackOk(this_))  \
        {                     \
            StackDump(this_); \
            assert(!"Ok");    \
        }                     \
    }

#define STACK_NEW_HASH(stk)                \
    {                                      \
        if (stk->inspection_level == 2)    \
            stk->hash = StackGetHash(stk); \
    }

#define StackInit(stk)    \
    Stack_t stk = {#stk}; \
    StackConstruct(&stk);

enum StackError // TODO use this
{
    STACK_OVERFLOW = 1,
    STACK_UNDERFLOW,
    STACK_INTERNAL_ERROR,
    STACK_INDEX_OUT_OF_BOUNDS,
    STACK_OUT_OF_MEMORY,
};

typedef int Elem_t;
struct Stack_t
{
    char name[30];
    Canary_t canary_start;
    short inspection_level;
    char file_dump[30] = "./debug.log";

    char *data;
    size_t size;
    size_t max_size;

    unsigned hash;
    short errno_st = 0;
    Canary_t canary_end;
};

bool StackConstruct(Stack_t *this_, const short int flag = 2, const char *file_dump = nullptr);
bool StackDestructor(Stack_t *this_);
bool StackPush(Stack_t *this_, const Elem_t elem);
Elem_t StackPop(Stack_t *this_, int *err = nullptr);

Elem_t *StackAt(const Stack_t *this_, const size_t iter);
bool StackOk(const Stack_t *this_);
void StackAssertOk(const Stack_t *this_);
bool StackDump(const Stack_t *this_);
bool StackSetSize(Stack_t *this_, const size_t max_size);

unsigned StackGetHash(const Stack_t *this_);
void StackHashAddData(unsigned *hash, unsigned data, unsigned seed);

#endif /* STACK_H */
