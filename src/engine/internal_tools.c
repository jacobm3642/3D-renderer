#include "dataTypes.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

stackAllocator *get_stack_ptr()
{
        return &mainMem;
}

void *retrive_ptr(i32 i)
{
        return mainMem.allocatedFrames[i].sptr;
}

void *allocate(size_t size)
{
        return mainMem.allocatedFrames[allocate_block(&mainMem, size)].sptr;
}

void deallocate(void *ptr)
{
        free_block_ptr(&mainMem, ptr);
}
