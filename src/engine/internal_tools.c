#include "dataTypes.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

void *allocate(size_t size)
{
        return mainMem.allocatedFrames[allocate_block(&mainMem, size)].sptr;
}

void deallocate(void *ptr)
{
        free_block_ptr(&mainMem, ptr);
}
