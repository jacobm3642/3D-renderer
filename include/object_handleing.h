#pragma once
#include "rendeing.h"

typedef struct Objnode {
        Object *obj;
        struct Objnode *left;
        struct Objnode *right;
} Objnode;


void render_tree(Objnode *n);
void render_all();
Objnode *add_man(char *path);
void free_objnode(Objnode *n);
