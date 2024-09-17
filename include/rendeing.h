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
        u16 count;
        u16 index_count;
        f32 scale;
        GLuint transformMat;
        GLuint scaleMat;
        GLuint posMat;
        vec3 pos;
        union {                
                u32 shaderProgram;
                struct {
                        u32 vertexShader;
                        u32 fragmentShader;
                } shaders;
        } shader;
        vec4 *vertices;
        u8 *indices;
        Rotation rotation;
} Object;

void startRenderer();
void draw_triangle_mesh_GL(Object *obj);
Object *parce_manafest(char *name);
void begin_frame();
void free_object(Object *obj);
