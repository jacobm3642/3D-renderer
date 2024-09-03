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
        vec4 *vertices;
        float *vertices_f;
        u8 *indices;
        size_t count;
        i32 index_count;
        GLuint transformMat;
        GLuint scaleMat;
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
void draw_triangle_mesh_GL(Object *obj, WindowState *window);
Object *parce_manafest(char *name);
void begin_frame();
