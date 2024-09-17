#pragma once
#include "dataTypes.h"
#include "stackallocator.h"

void deallocate(void *ptr);
void *allocate(size_t size);
stackAllocator *get_stack_ptr();
void *retrive_ptr(i32 i);
