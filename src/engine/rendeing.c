#include "rendeing.h"
#include "dataTypes.h"
#include "engine.h"
#include "engine_internal.h"
#include "stringTools.h"
#include "window.h"
#include "stringStream.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

GLuint compileShader(char *ss, GLenum shaderType)
{
        GLuint shader = glCreateShader(shaderType);
        const char *shaderSource = ss;
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        // Check for compilation errors
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
                printf("\033[1;31m ERROR IN SHADER\033[0m");
        }

        free((void*)shaderSource);

        return shader;
}

GLuint buildShader(char *path, GLenum shaderType)
{
        char *type;
        switch (shaderType) {
                case GL_VERTEX_SHADER: 
                        type = "vertexShaders";
                        break;
                case GL_FRAGMENT_SHADER:
                        type = "fragmentShaders";
                        break;
        }
        char *ss = readShader(path, type);
        return compileShader(ss, shaderType);
}

GLuint attachShader(GLuint vertexShader, GLuint fragmentShader)
{
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
}

void parce_line(char *line, Object *obj)
{
        if (line[0] == '\n') {
                return;
        }
        if (line[1] == 's') {
                if (line[0] == 'v') {
                        obj->shader.shaders.vertexShader = buildShader(&line[3], GL_VERTEX_SHADER);
                }
                if (line[0] == 'f') {
                        obj->shader.shaders.fragmentShader = buildShader(&line[3], GL_FRAGMENT_SHADER);
                }
                return;
        }
        if (line[0] == 'v' && line[1] == '2') {
                int d = 0;
                char **vertices = splitString(&line[3], ' ', &d);
                
                vec4 *out = &obj->vertices[obj->count];
                if (d == 2) {
                        out->x = stringToFloat(vertices[0]); 
                        out->y = stringToFloat(vertices[1]);
                }
                obj->count++;

                return;
        }

}

Object *parce_manafest(char *name)
{
        Object *obj = allocate(sizeof(Object));
        obj->vertices = allocate(sizeof(vec2) * 3);
        char *contence = readRes(name);
        int substrings = 0;
        char **lines = splitString(contence, '\n', &substrings);
        for (int i = 0; i < substrings; i++) {
                parce_line(lines[i], obj);
        }

        obj->shader.shaderProgram = attachShader(obj->shader.shaders.vertexShader, obj->shader.shaders.fragmentShader);

        return  obj;
}

void print_v_c(Object *obj)
{
        for (size_t i = 0; i < obj->count; i++) {
                printf("Vertex %zu: (%f, %f)\n", i, obj->vertices[i].x, obj->vertices[i].y);
        }
}

//Object *genrate_object(char *vertexShader, char *fragmentShader, vec2 *vertices)
//{

//}

void drawTriangle_GL(Object *obj)
{
    float *vertices = allocate(3 * obj->count);
    for (size_t i = 0;i < obj->count; i++) {
            vertices[i*3] = obj->vertices[i].x;
            vertices[i*3 + 1] = obj->vertices[i].y;
    }
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, obj->count * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glUseProgram(obj->shader.shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void drawVec2Array(Object *obj) 
{ 
    unsigned int VAO, VBO;
    float *vert = allocate(obj->count * 3 * sizeof(float));
    
    if (vert == NULL) {
        fprintf(stderr, "Failed to allocate memory for vertices.\n");
        return;
    }

    for (size_t i = 0; i < obj->count; i++) {
        vert[i * 3] = obj->vertices[i].x;
        vert[i * 3 + 1] = obj->vertices[i].y;
        vert[i * 3 + 2] = 0.0f;
        printf("Vertex %zu: (%f, %f, %f)\n", i, vert[i * 3], vert[i * 3 + 1], vert[i * 3 + 2]);
    }
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, obj->count * 3 * sizeof(float), vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(obj->shader.shaderProgram);

    // Change this line according to what you want to draw
    glDrawArrays(GL_POINTS, 0, obj->count);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    deallocate(vert);
}

void begin_frame()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 1.0f, 0.0f, 1.0f);
}

void startRenderer(WindowState *window)
{
        printf("%f\n", window->deltaTime);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
}
