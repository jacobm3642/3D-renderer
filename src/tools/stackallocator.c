#include "stackallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void init_allocator(stackAllocator *allocator, size_t size)
{
    allocator->size = size;
    allocator->offset = 0;
    allocator->frameCount = 0;
    allocator->maxFrames = size / 10;  // Adjust maxFrames as per your requirement
    allocator->allocatedFrames = malloc(sizeof(dataFrame) * allocator->maxFrames);
    allocator->blob = malloc(size);
}

i32 allocate_block(stackAllocator *allocator, size_t size)
{
    if (allocator->offset + size > allocator->size) return -1; // Not enough space
    if (allocator->frameCount == allocator->maxFrames) return -1; // Max frames reached
    size_t frameIndex = allocator->frameCount;
    allocator->allocatedFrames[frameIndex].size = size;
    allocator->allocatedFrames[frameIndex].inUse = true;
    allocator->allocatedFrames[frameIndex].sptr = allocator->blob + allocator->offset;
    
    allocator->frameCount++;
    
    allocator->offset += size;
    return frameIndex; // Return index of allocated frame
}

void free_allocator(stackAllocator *allocator)
{
    free(allocator->allocatedFrames);
    free(allocator->blob);
}

void print_frameData(stackAllocator *allocator, size_t index)
{
        printf("DataFrame %zu:\n", index);
        printf("Size: %zu\n", allocator->allocatedFrames[index].size);
}

void print_allocator(stackAllocator *allocator)
{
    printf("Allocator Data:\n");
    printf("Size: %zu\n", allocator->size);
    printf("In use: %zu%%\n", (allocator->offset * 100) / allocator->size);
    printf("Open Frames: %zu out of %zu\n", allocator->frameCount, allocator->maxFrames);
}
