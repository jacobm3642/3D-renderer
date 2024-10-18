#include "DSA.h"
#include "dataTypes.h"
#include "engine_internal.h"


#include <stdio.h>
/*
 * so i need a hash funtion 
 * to store key value pairs
 */


u64 hash(char *str)
{
        u64 hash = 5381;
        i32 c;

        while ((c = *str++)) {
                hash = ((hash << 5) + hash) + c;
        }

        return hash;
}

Dict *init_Dict(u32 size)
{
        Dict *out;
        out = allocate(sizeof(Dict));
        out->size = size;
        out->fullness = 0;
        out->table = allocate(sizeof(intptr_t) * size);
        return  out;
}

key_value_pair *pair(char *key, void *value)
{
        key_value_pair *p;
        p = allocate(sizeof(key_value_pair));
        p->key = hash(key);
        p->value = value;
        return p;
}

void add_key_value(Dict *dict, key_value_pair *value)
{
        if (dict->fullness >= dict->size) {
                printf("dict is full\n");
                return;
        }
        
        dict->fullness++;
        dict->table[value->key % dict->size] = value;
}

void *look_up(Dict *dict, char *key)
{
        u64 h = hash(key);
        key_value_pair *pair = dict->table[h % dict->size];
        u64 count = 0; 

        while (true) {
                if (pair->key == 0 || count == dict->size){
                        return (void *)0;
                }
                if (h == pair->key) {
                        return pair;
                }
                
                count++;
                if (((u64)pair - (u64)dict->table) >= dict->size) {
                        pair = dict->table[0];
                } else {
                        pair++;
                }
        }
        return (void *)0;
}
