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
        if (line[0] == 'v') {
                int d = 0;
                char **vertices = splitString(&line[3], ' ', &d);

                vec2 out; 
                if (d == 2) {
                        out.x = stringToFloat(vertices[0]); 
                        out.y = stringToFloat(vertices[1]);
                        obj->vertices[obj->count] = out;
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
        printf("count %d\n", (int)obj->count);
        for (size_t i = 0; i < obj->count; i++) {
                printf("%f\n", obj->vertices[i].x);
                printf("%f\n", obj->vertices[i].y);
        }
}

//Object *genrate_object(char *vertexShader, char *fragmentShader, vec2 *vertices)
//{
        
//}

void drawVec2Array(Object *obj) {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, obj->count * sizeof(vec2), obj->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(obj->shader.shaderProgram);

    glDrawArrays(GL_TRIANGLES, 0, obj->count);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void startRenderer(WindowState *window)
{
        glViewport(0, 0, window->width, window->height);
        glClearColor(0.5f, 1.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Object *basic = parce_manafest("basic.man");
        print_v_c(basic);
        drawVec2Array(basic);
        SDL_GL_SwapWindow(window->window);
}
