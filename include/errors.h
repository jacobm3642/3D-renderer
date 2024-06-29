#pragma once

#include "dataTypes.h"

typedef enum error_type {
        unknown_error,
        out_of_memory,
        failed_to_start
} error_type;

typedef struct error_frame {
        error_type error;
        bool logfile;
        char error_message[256];
} error_frame;


void display_error(i32 error_block_index);
void FATAL_ERROR(const char *error_message, error_type error_ctx);
