// #define NDEBUG
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cstring>
#include <cerrno>
#include "Stack.h"

bool StackConstruct(
    Stack_t *this_,
    const short int flag /* = 2 */,
    const char *file_dump /* = nullptr */,
    const char *rights /* = nullptr */)
{
    // TODO STACK_ASSERT_OK ?
    if (file_dump)
        strcpy(this_->file_dump, file_dump);
    FILE *fd;
    if (rights)
        fd = fopen(this_->file_dump, rights);
    else
        fd = fopen(this_->file_dump, "w");
    if (!fd)
        return false;
    fclose(fd);

    this_->size = 0;
    this_->inspection_level = flag;

    if (!StackSetSize(this_, STACK_INITIAL_MAXSIZE))
        return false;
    if (flag)
    {
        this_->canary_start = STACK_CANARY1;
        this_->canary_end = STACK_CANARY2;

        *(Canary_t *)this_->data = STACK_CANARY1;
        *(Canary_t *)StackAt(this_, this_->max_size) = STACK_CANARY2;
        STACK_NEW_HASH(this_);
    }

    STACK_ASSERT_OK;
    return true;
}

bool StackDestructor(Stack_t *this_)
{
    // STACK_ASSERT_OK;

    this_->size = 0;
    this_->max_size = 0;
    free(this_->data);
    this_->data = nullptr;
    this_->data_copy = nullptr;
    this_->hash = 0;
    this_->errno_st = 0;
    // TODO STACK_ASSERT_OK ?
    return true;
}

Elem_t *StackAt(const Stack_t *this_, const size_t iter)
{
    if (this_->inspection_level)
        return (Elem_t *)(this_->data + sizeof(Canary_t) + sizeof(Elem_t) * iter);
    else
        return (Elem_t *)(this_->data + sizeof(Elem_t) * iter);
}

bool StackPush(Stack_t *this_, const Elem_t elem)
{
    STACK_ASSERT_OK;

    if (this_->size >= this_->max_size)
    {
        if (!StackSetSize(this_, 2 * this_->max_size))
            return false; // TODO change this_->errno_st ?
    }
    *StackAt(this_, this_->size++) = elem;

    STACK_NEW_HASH(this_);
    STACK_ASSERT_OK;
    return true;
}

Elem_t StackPop(Stack_t *this_, bool *err /* = nullptr */)
{
    STACK_ASSERT_OK;
    if (this_->size <= 0)
    {
        if (err)
            *err = true;
        return 0;
    }

    Elem_t elem = *StackAt(this_, --this_->size);
    if (this_->size < this_->max_size / 2 - STACK_DELTA_SIZE)
    {
        StackSetSize(this_, this_->max_size / 2); // TODO should we handle the error?
    }

    STACK_NEW_HASH(this_);
    STACK_ASSERT_OK;
    if (err)
        *err = false;
    return elem;
}

bool StackOk(Stack_t *this_)
{
    bool not_error = false;
    if (!this_)
        errno = EFAULT;

    else if (!this_->data)
        this_->errno_st = STACK_NULLPTR_DATA;
    else if (this_->data != this_->data_copy)
        this_->errno_st = STACK_INCORRECT_PTR_DATA;
    else if (
        this_->max_size > (this_->size + STACK_DELTA_SIZE) * 2 ||
        this_->size > this_->max_size)
        this_->errno_st = STACK_INCORRECT_SIZE;
    else if (this_->inspection_level < 0 || this_->inspection_level > 2)
        this_->errno_st = STACK_INCORRECT_INSPECTION_LEVEL;

    else if (this_->inspection_level)
    {
        if (this_->canary_start != STACK_CANARY1)
            this_->errno_st = STACK_BAD_CANARY_START;
        else if (this_->canary_end != STACK_CANARY2)
            this_->errno_st = STACK_BAD_CANARY_END;
        else if (*(Canary_t *)this_->data != STACK_CANARY1)
            this_->errno_st = STACK_BAD_DATA_CANARY_START;
        else if (*(Canary_t *)StackAt(this_, this_->max_size) != STACK_CANARY2)
            this_->errno_st = STACK_BAD_DATA_CANARY_END;

        else if (this_->inspection_level == 2)
        {
            if (this_->hash != StackGetHash(this_))
                this_->errno_st = STACK_BAD_HASH;
            else
                not_error = true;
        }
        else
            not_error = true;
    }
    else
        not_error = true;
    return not_error;
}

bool StackDump(Stack_t *this_)
{
    FILE *fd = fopen(this_->file_dump, "a");
    if (!fd)
        return false;

    if (!this_)
    {
        fprintf(fd, "Stack_t (ERROR!!!) - nullptr {}\n");
        return true;
    }

    fprintf(
        fd,
        "Stack_t \"%s\" [%p] (%s)\n",
        this_->name,
        &this_->canary_start,
        StackOk(this_) ? "ok" : "ERROR!!!");
    fprintf(
        fd,
        "{\n"
        "\tcanary1 = 0x%08x %s\n"
        "\tsize    = %lu %s\n\n"
        "\tdata[%lu] = [%p] %s\n"
        "\t{\n",
        this_->canary_start, this_->errno_st == STACK_BAD_CANARY_START ? "(BAD CANARY VALUE)" : "",
        this_->size, this_->errno_st == STACK_INCORRECT_SIZE ? "(BAD SIZE VALUE)" : "",
        this_->max_size, this_->data, this_->errno_st == STACK_INCORRECT_PTR_DATA ? "(BAD POINTER VALUE)" : "");

    if (this_->errno_st != STACK_NULLPTR_DATA &&
        this_->errno_st != STACK_INCORRECT_PTR_DATA &&
        this_->errno_st != STACK_INCORRECT_SIZE)
    {
        if (this_->inspection_level)
            fprintf(
                fd,
                "\t\t-[can]:0x%08x %s\n",
                *(Canary_t *)this_->data,
                this_->errno_st == STACK_BAD_DATA_CANARY_START ? "(BAD CANARY VALUE)" : "");
        for (size_t i = 0; i < this_->max_size; i++)
        {
            if (i >= this_->size)
                fprintf(fd, "\t\t [%3lu]:%f\n", i, *StackAt(this_, i)); // TODO %d or %f
            else
                fprintf(fd, "\t\t*[%3lu]:%f\n", i, *StackAt(this_, i));
        }
        if (this_->inspection_level)
            fprintf(
                fd,
                "\t\t-[can]:0x%08x %s\n\n",
                *(Canary_t *)StackAt(this_, this_->max_size),
                this_->errno_st == STACK_BAD_DATA_CANARY_END ? "(BAD CANARY VALUE)" : "");
    }

    fprintf(
        fd,
        "\t}\n"
        "\tfile_dump        = %s\n"
        "\tinspection_level = %d %s\n\n"
        "\thash    = 0x%08x %s\n"
        "\tcanary2 = 0x%08x %s\n",
        this_->file_dump,
        this_->inspection_level, this_->errno_st == STACK_INCORRECT_INSPECTION_LEVEL ? "(BAD VER-LEVEL VALUE)" : "",
        this_->hash, this_->errno_st == STACK_BAD_HASH ? "(BAD HASH VALUE)" : "",
        this_->canary_end, this_->errno_st == STACK_BAD_CANARY_END ? "(BAD CANARY VALUE)" : "");

    fprintf(fd, "\terrno   = %d (", this_->errno_st);
    switch (this_->errno_st)
    {
    case 0:
        fprintf(fd, "no error");
        break;
    case STACK_NULLPTR_DATA:
        fprintf(fd, "data pointer is nullptr");
        break;
    case STACK_INCORRECT_SIZE:
        fprintf(fd, "bad size");
        break;
    case STACK_INCORRECT_INSPECTION_LEVEL:
        fprintf(fd, "bad inspection level");
        break;
    case STACK_BAD_CANARY_START:
        fprintf(fd, "bad canary start, should be: 0x%08x", STACK_CANARY1);
        break;
    case STACK_BAD_CANARY_END:
        fprintf(fd, "bad canary end, should be: 0x%08x", STACK_CANARY2);
        break;
    case STACK_BAD_DATA_CANARY_START:
        fprintf(fd, "bad data-canary start, should be: 0x%08x", STACK_CANARY1);
        break;
    case STACK_BAD_DATA_CANARY_END:
        fprintf(fd, "bad data-canary end, should be: 0x%08x", STACK_CANARY2);
        break;
    case STACK_BAD_HASH:
        fprintf(fd, "bad hash value, should be: 0x%08x", StackGetHash(this_));
        break;
    case STACK_INCORRECT_PTR_DATA:
        fprintf(fd, "bad pointer data, copy pointer is: [%p]", this_->data_copy);
        break;
    default:
        fprintf(fd, "unrecognized error");
    }
    fprintf(fd, ")\n}\n");

    fclose(fd);
    return true;
}

bool StackSetSize(Stack_t *this_, const size_t max_size)
{
    // TODO STACK_ASSERT_OK ?
    char *new_data;
    if (this_->inspection_level)
        new_data = (char *)realloc(this_->data, max_size * sizeof(Elem_t) + 2 * sizeof(Canary_t));
    else
        new_data = (char *)realloc(this_->data, max_size * sizeof(Elem_t));

    if (!new_data)
        return false;
    this_->data = new_data;
    this_->data_copy = new_data;
    this_->max_size = max_size;

    if (this_->inspection_level)
    {
        *(Canary_t *)StackAt(this_, max_size) = STACK_CANARY2;
        STACK_NEW_HASH(this_);
    }
    // TODO STACK_ASSERT_OK ?
    return true;
}

/**
 * Hash functions
 */
static const unsigned char SHashTable[256] =
    {
        0xa3, 0xd7, 0x09, 0x83, 0xf8, 0x48, 0xf6, 0xf4, 0xb3, 0x21, 0x15, 0x78, 0x99, 0xb1, 0xaf, 0xf9,
        0xe7, 0x2d, 0x4d, 0x8a, 0xce, 0x4c, 0xca, 0x2e, 0x52, 0x95, 0xd9, 0x1e, 0x4e, 0x38, 0x44, 0x28,
        0x0a, 0xdf, 0x02, 0xa0, 0x17, 0xf1, 0x60, 0x68, 0x12, 0xb7, 0x7a, 0xc3, 0xe9, 0xfa, 0x3d, 0x53,
        0x96, 0x84, 0x6b, 0xba, 0xf2, 0x63, 0x9a, 0x19, 0x7c, 0xae, 0xe5, 0xf5, 0xf7, 0x16, 0x6a, 0xa2,
        0x39, 0xb6, 0x7b, 0x0f, 0xc1, 0x93, 0x81, 0x1b, 0xee, 0xb4, 0x1a, 0xea, 0xd0, 0x91, 0x2f, 0xb8,
        0x55, 0xb9, 0xda, 0x85, 0x3f, 0x41, 0xbf, 0xe0, 0x5a, 0x58, 0x80, 0x5f, 0x66, 0x0b, 0xd8, 0x90,
        0x35, 0xd5, 0xc0, 0xa7, 0x33, 0x06, 0x65, 0x69, 0x45, 0x00, 0x94, 0x56, 0x6d, 0x98, 0x9b, 0x76,
        0x97, 0xfc, 0xb2, 0xc2, 0xb0, 0xfe, 0xdb, 0x20, 0xe1, 0xeb, 0xd6, 0xe4, 0xdd, 0x47, 0x4a, 0x1d,
        0x42, 0xed, 0x9e, 0x6e, 0x49, 0x3c, 0xcd, 0x43, 0x27, 0xd2, 0x07, 0xd4, 0xde, 0xc7, 0x67, 0x18,
        0x89, 0xcb, 0x30, 0x1f, 0x8d, 0xc6, 0x8f, 0xaa, 0xc8, 0x74, 0xdc, 0xc9, 0x5d, 0x5c, 0x31, 0xa4,
        0x70, 0x88, 0x61, 0x2c, 0x9f, 0x0d, 0x2b, 0x87, 0x50, 0x82, 0x54, 0x64, 0x26, 0x7d, 0x03, 0x40,
        0x34, 0x4b, 0x1c, 0x73, 0xd1, 0xc4, 0xfd, 0x3b, 0xcc, 0xfb, 0x7f, 0xab, 0xe6, 0x3e, 0x5b, 0xa5,
        0xad, 0x04, 0x23, 0x9c, 0x14, 0x51, 0x22, 0xf0, 0x29, 0x79, 0x71, 0x7e, 0xff, 0x8c, 0x0e, 0xe2,
        0x0c, 0xef, 0xbc, 0x72, 0x75, 0x6f, 0x37, 0xa1, 0xec, 0xd3, 0x8e, 0x62, 0x8b, 0x86, 0x10, 0xe8,
        0x08, 0x77, 0x11, 0xbe, 0x92, 0x4f, 0x24, 0xc5, 0x32, 0x36, 0x9d, 0xcf, 0xf3, 0xa6, 0xbb, 0xac,
        0x5e, 0x6c, 0xa9, 0x13, 0x57, 0x25, 0xb5, 0xe3, 0xbd, 0xa8, 0x3a, 0x01, 0x05, 0x59, 0x2a, 0x46};

unsigned StackGetHash(const Stack_t *this_)
{
    unsigned hash = 0;
    unsigned rotate = 2;
    unsigned seed = STACK_HASH_SEED;

    for (size_t i = 0; i != this_->size; i++)
    {
        hash += SHashTable[(*(int *)StackAt(this_, i)) & 255];
        hash = (hash << (32 - rotate)) | (hash >> rotate);
        hash = (hash + i) * seed;
    }

    StackHashAddData(&hash, (long)this_->data, seed);
    StackHashAddData(&hash, this_->size, seed);
    StackHashAddData(&hash, this_->max_size, seed);

    return hash;
}

void StackHashAddData(unsigned *hash, unsigned data, unsigned seed)
{
    *hash = (*hash + data) * seed;
}
