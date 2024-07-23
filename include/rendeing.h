#pragma once

#include "engine.h"
#include "window.h"

typedef struct Object {
        GLuint shaderProgram;
        GLuint VBO;
        GLsizei vertexCount;
        struct Object **sub_objs;
} Object;

void startRenderer(WindowState *window);
