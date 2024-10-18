#pragma once
#include "dataTypes.h"

typedef struct key_value_pair {
        u64 key;
        void *value;
} key_value_pair;

typedef struct Dict {
        u32 size;
        u32 fullness;
        key_value_pair **table;
} Dict;

Dict *init_Dict(u32 size);
void *look_up(Dict *dict, char *key);
void add_key_value(Dict *dict, key_value_pair *value);
