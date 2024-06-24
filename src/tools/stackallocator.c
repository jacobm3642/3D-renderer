#include "stackallocator.h"
#include "dataTypes.h"
#include <stdio.h>
#include <stdlib.h>


void init_allocator(stackAllocator *allocator, size_t size)
{
        allocator->size = size;
        allocator->offset = 0;
        allocator->frameCount = 0;
        allocator->maxFrames = size / 10;
        allocator->allocatedFrames = malloc(sizeof(dataFrame) * allocator->maxFrames);
        allocator->blob = malloc(size);
}

i32 allocate_block(stackAllocator *allocator, size_t size)
{
        if (allocator->offset + size > allocator->size) {
                printf("\x1b[31m Warning: \x1b[0m stackallocator size exceeded\n");
                return -1;
        };
        if (allocator->frameCount == allocator->maxFrames) { 
                printf("\x1b[31m Warning: \x1b[0m stackallocator Frames stack size exceeded\n");
                return -1;
        };

        size_t frameIndex = allocator->frameCount;
        allocator->allocatedFrames[frameIndex].size = size;
        allocator->allocatedFrames[frameIndex].inUse = true;
        allocator->allocatedFrames[frameIndex].sptr = allocator->blob + allocator->offset;

        allocator->frameCount++;

        allocator->offset += size;
        return frameIndex;
}

void deallocate(stackAllocator *s)
{
        size_t i = s->frameCount - 1;
        while (s->frameCount > 0) { 
                if (s->allocatedFrames[i].inUse) break;

                s->offset -= s->allocatedFrames[i].size;
                s->frameCount -= 1;
                i -= 1;
        }
}

void free_block(stackAllocator *s, size_t index)
{
        if (index >= s->frameCount) return;
        s->allocatedFrames[index].inUse = false;
        deallocate(s);
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
