#include "stackallocator.h"
#include "dataTypes.h"
#include "errors.h"
#include <stdint.h>
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
#ifndef DEBUG
                FATAL_ERROR("memerror", out_of_memory);
#endif
                return -1;
        };
        if (allocator->frameCount == allocator->maxFrames) { 
                printf("\x1b[31m Warning: \x1b[0m stackallocator Frames stack size exceeded\n");
#ifndef DEBUG
                FATAL_ERROR("memerror", out_of_memory);
#endif
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

void clean_stack(stackAllocator *s)
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
        clean_stack(s);
}

void free_block_ptr(stackAllocator *s, void *ptr)
{
        intptr_t ptrintrp = (intptr_t)ptr;

        for (size_t i = 0; i < s->frameCount; i++) {
                if (ptr == s->allocatedFrames[i].sptr) {
                        free_block(s, i);
                        return;
                }
                if (ptrintrp > (intptr_t)s->allocatedFrames[i].sptr && ptrintrp < (intptr_t)s->allocatedFrames[i].sptr + (intptr_t)s->allocatedFrames[i].size) {
                        free_block(s, i);
                        return;
                }
        }
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
