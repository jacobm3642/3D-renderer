#include "dataTypes.h"
#include "stackallocator.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"

extern stackAllocator mainMem;
extern jmp_buf fatal_error;

void FATAL_ERROR(const char *error_message, error_type error_ctx)
{
        i32 error_block_index = allocate_block(&mainMem, sizeof(error_frame));
        if (error_block_index == -1) longjmp(fatal_error, error_block_index);
        
        error_frame *error = (error_frame *)mainMem.allocatedFrames[error_block_index].sptr;
        error->logfile = false;
        error->error = error_ctx;
        memcpy(error->error_message, error_message, sizeof(error->error_message));\
        
        longjmp(fatal_error, error_block_index);
}

void display_error(i32 error_block_index)
{
        if (error_block_index == -1) {
                printf("\x1b[31m NO MEMORY LEFT \x1b[0m\n");
                return;
        }
        
        error_frame *error = mainMem.allocatedFrames[error_block_index].sptr;
        printf("\x1b[31m ERROR: \x1b[0m %s\n", error->error_message);
        free_block(&mainMem, error_block_index);
}
