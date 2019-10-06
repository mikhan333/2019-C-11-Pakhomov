#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

bool StackConstruct(Stack *this_)
{
    assert(StackOk(this_));

    this_->size = 0;
    StackSetSize(this_, STACK_INITIAL_MAXSIZE);
    return true;
}

bool StackDestructor(Stack *this_) 
{
    assert(StackOk(this_));

    this_->size = 0;
    free(this_->data);
    this_->data = NULL;
}

bool StackPush(Stack *this_, const Type_t elem)
{
    assert(StackOk(this_));
    if (this_->size >= this_->max_size)
    {
        if (!StackSetSize(this_, 2 * this_->max_size))
            return false;
    }

    this_->data[this_->size++] = elem;
    return true;
}

bool StackPop(Stack *this_, Type_t *elem)
{
    assert(StackOk(this_));
    if (this_->size <= 0)
        return false;
    if (!elem)
        return false;

    *elem = this_->data[--this_->size];

    if (this_->size < this_->max_size / 2 - STACK_DELTA_SIZE)
    {
        StackSetSize(this_, this_->max_size / 2); // TODO should we handle the error?
    }
    return true;
}

bool StackOk(const Stack *this_) // TODO this function & dublicate internal data
{
    return true;
}

bool StackDump(const Stack *this_) // TODO this function
{

}

bool StackSetSize(Stack *this_, const int max_size)
{
    assert(StackOk(this_));
    if (this_->size > max_size || max_size <= 0)
        return false;

    Type_t *new_data = (Type_t *)realloc(this_->data, max_size * sizeof(Type_t));
    if (!new_data)
        return false;
    if (this_->data != new_data)
        free(this_->data);
    
    this_->data = new_data;
    this_->max_size = max_size;
    return true;
}
