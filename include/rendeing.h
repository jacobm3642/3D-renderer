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
        GLuint shaderProgram;
        GLuint VBO;
        GLsizei vertexCount;
        struct Object **sub_objs;
} Object;

void startRenderer(WindowState *window);
