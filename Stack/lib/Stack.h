/**
 * @file Stack.h
 * @author Pakhomov Mikhail
 * @brief Lib with Stack
 * @version 0.1
 * @date 2019-10-18
 * 
 * Define NDEBUG for switching off all asserts and
 * checking and hashing Stack (with canaries)
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef STACK_H
#define STACK_H

/**
 * @brief Initial sizes
 */
#define STACK_INITIAL_MAXSIZE 32
#define STACK_DELTA_SIZE STACK_INITIAL_MAXSIZE / 2

/**
 * @brief Canaries
 * 
 */
typedef unsigned Canary_t;
#define STACK_CANARY1 0xDEADBEEFU
#define STACK_CANARY2 0x38023802U
#define STACK_HASH_SEED 0x1A4E41CDL

/**
 * @brief Function for debug and logging
 * 
 */
#define STACK_ASSERT_OK       \
    {                         \
        if (!StackOk(this_))  \
        {                     \
            StackDump(this_); \
            assert(!"Ok");    \
        }                     \
    }

/**
 * @brief Init functions
 * 
 */
#define StackName(stk) Stack_t stk = {#stk}
#define StackInit(stk) \
    StackName(stk);    \
    StackConstruct(&stk);

enum StackError
{
    STACK_NULLPTR_DATA = 1,
    STACK_INCORRECT_SIZE,
    STACK_BAD_CANARY_START,
    STACK_BAD_CANARY_END,
    STACK_BAD_DATA_CANARY_START,
    STACK_BAD_DATA_CANARY_END,
    STACK_BAD_HASH,
    STACK_INCORRECT_PTR_DATA,
};

/**
 * @brief Structure that implements Stack
 * 
 */
typedef double Elem_t;
struct Stack_t
{
    char name[30];
    Canary_t canary_start;
    char file_dump[30] = "debug/debug.log";

    char *data;
    size_t size;
    char *data_copy;
    size_t max_size;

    unsigned hash;
    short errno_st = 0;
    Canary_t canary_end;
};

/**
 * @brief Initialize memory and flags for Stack
 * 
 * @param this_ - pointer to the Stack
 * @param flag  - level of protection
 * @param file_dump - path to the otput dump file
 * @param rights - rights to open file
 * @return true - Ok
 * @return false - Error
 */
bool StackConstruct(
    Stack_t *this_,
    const char *file_dump = nullptr,
    const char *rights = nullptr);

/**
 * @brief  Destructor for struct Stack
 * 
 * @param this_ - pointer to the Stack
 * @return true - Ok
 * @return false - Error
 */
bool StackDestructor(
    Stack_t *this_);

/**
 * @brief Push elem with type Elem_t to the Stack
 * 
 * @param this_ - pointer to the Stack
 * @param elem - value of elem
 * @return true - Ok
 * @return false - Error
 */
bool StackPush(
    Stack_t *this_,
    const Elem_t elem);

/**
 * @brief Pop element from Stack
 * 
 * @param this_ - pointer to the Stack
 * @param err - false if there is problem
 * @return Elem_t - return value, which pop from Stack
 */
Elem_t StackPop(
    Stack_t *this_,
    bool *err = nullptr);

/**
 * @brief Get pointer to the number of element from Stack
 * 
 * @param this_ - pointer to the Stack
 * @param iter - number of element
 * @return Elem_t* - pointer to the return value 
 */
Elem_t *StackAt(
    const Stack_t *this_,
    const size_t iter);

/**
 * @brief Check stack validity
 * 
 * @param this_ - pointer to the Stack
 * @return true - Ok
 * @return false - Error
 */
bool StackOk(
    Stack_t *this_);

/**
 * @brief Write data from Stack in the output file
 * 
 * @param this_ - pointer to the Stack
 * @return true - Ok
 * @return false - Error
 */
bool StackDump(
    Stack_t *this_);

/**
 * @brief Set the size for Stack
 * 
 * @param this_ - pointer to the Stack
 * @param max_size - new maximum size for Stack (can be smaller)
 * @return true - Ok
 * @return false - Error
 */
bool StackSetSize(
    Stack_t *this_,
    const size_t max_size);

/**
 * @brief Count the hash for all structure
 * 
 * @param this_ - pointer to the Stack
 * @return unsigned - new hash
 */
unsigned StackGetHash(
    Stack_t *this_);

#endif /* STACK_H */
