#include "rendeing.h"
#include "stackallocator.h"
#include "window.h"
#include "stringStream.h"
#include <stdlib.h>
#include <wchar.h>

void startRenderer(WindowState *window)
{
        glViewport(0, 0, window->width, window->height);
        glClearColor(0.5f, 1.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window->window);
}

GLuint compileShader(char *path, GLenum shaderType)
{
        GLuint shader = glCreateShader(shaderType);
        const char *shaderSource = readRes(path);
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

Object *parce_manafest(char *name)
{
        Object *obj = malloc(sizeof(Object));
        char *contence = readRes(name);
        return  obj;
}
