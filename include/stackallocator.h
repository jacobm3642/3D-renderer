#pragma once
#include "dataTypes.h"

typedef struct dataFrame{
        size_t size;
        bool inUse;
        void *sptr;
} dataFrame;

typedef struct stackAllocator {
    size_t offset;
    size_t size;
    size_t frameCount;
    size_t maxFrames;
    dataFrame *allocatedFrames;
    void *blob;
} stackAllocator;

void init_allocator(stackAllocator *allocator, size_t size);
void print_allocator(stackAllocator *allocator);
void free_allocator(stackAllocator *allocator);
i32 allocate_block(stackAllocator *allocator, size_t size);
void print_frameData(stackAllocator *allocator, size_t index);

