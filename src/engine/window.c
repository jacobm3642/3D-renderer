#include "window.h"
#include "errors.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

WindowState *WindowInit()
{
        i16 width = 1080;
        i16 height = 720;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
                FATAL_ERROR("SDL Video failed to init\n", failed_to_start);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              width, height,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (!window)
        {
                FATAL_ERROR("Failed to create window\n", failed_to_start);
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glContext);
        if (!glContext)
        {
                FATAL_ERROR("Failed to create OpenGL context\n", failed_to_start);
        }
        
        SDL_GL_SetSwapInterval(1);
        
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
                printf("GLEW error: %s\n", glewGetErrorString(glewError));
                FATAL_ERROR((const char *)glewGetErrorString(glewError), failed_to_start);
        }

        SDL_Surface *window_surface = SDL_GetWindowSurface(window);
        if (!window_surface)
        {
                FATAL_ERROR("Failed to get the surface from the window\n", failed_to_start);
        }

        WindowState *windowState = NULL;
        i32 WindowBlockIndex = allocate_block(&mainMem, sizeof(WindowState));
        if (WindowBlockIndex == -1)
        {
                FATAL_ERROR("Window block can't be allocated\n", failed_to_start);
        }

        windowState = (WindowState *)mainMem.allocatedFrames[WindowBlockIndex].sptr;

        windowState->window = window;
        windowState->surface = window_surface;
        windowState->glContext = glContext;
        windowState->width = width;
        windowState->height = height;
        windowState->running = 1;
        windowState->totalTime = 0.0f;
        windowState->blockIndex = WindowBlockIndex;

        return windowState;
}
