#pragma once

#include "dataTypes.h"
#include "engine.h"
#include "window.h"

typedef struct objectManafest {
        char *vertexShader;
        char *fragmentShader;
        vec2 *vertices;
} objectManafest;

typedef struct Object {
        vec2* vertices;
        size_t count;
        union {                
                unsigned int shaderProgram;
                struct {
                        unsigned int vertexShader;
                        unsigned int fragmentShader;
                } shaders;
        } shader;

} Object;

typedef struct Objnode {
        Object *obj;
        struct Objnode *left;
        struct Objnode *right;
} Objnode;

void startRenderer(WindowState *window);
