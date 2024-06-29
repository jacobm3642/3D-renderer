#pragma once

#include "dataTypes.h"

#include <SDL2/SDL.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glu.h>

typedef struct WindowState {
        SDL_Window *window;
        SDL_Surface *surface;
        SDL_GLContext glContext;
        bool running;
        i16 width, height;
        i32 blockIndex;
        f32 deltaTime, totalTime;
} WindowState;


WindowState *WindowInit();
