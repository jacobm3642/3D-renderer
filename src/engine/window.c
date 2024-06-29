#include "window.h"
#include "errors.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

WindowState *WindowInit()
{
        i16 width = 1080;
        i16 height = 720;

        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
                FATAL_ERROR("SDL Video failed to init\n", failed_to_start);
        }

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

        SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              width, height,
                                              0);

        if(!window)
        {   
                FATAL_ERROR("Failed to create window\n", failed_to_start);
        }

        glewExperimental = GL_TRUE;
        SDL_Surface *window_surface = SDL_GetWindowSurface(window);

        if(!window_surface)
        {
                FATAL_ERROR("Failed to get the surface from the window\n", failed_to_start);
        }


        SDL_GLContext glContex = SDL_GL_CreateContext(window);

        GLenum glewError = glewInit();

        if (glewError != GLEW_OK) {
                printf("glew is being a little silly\n");
                FATAL_ERROR((const char *)glewGetErrorString(glewError), failed_to_start);
        }


        WindowState *windowState;
        i32 WindowBlockIndex = allocate_block(&mainMem, sizeof(WindowState));
        if (WindowBlockIndex == -1) FATAL_ERROR("window Block can't be allocted", failed_to_start);

        windowState = (WindowState *)mainMem.allocatedFrames[WindowBlockIndex].sptr;

        windowState->window = window;
        windowState->surface = window_surface;
        windowState->glContext = glContex;
        windowState->width = width;
        windowState->height = height;
        windowState->running = 1;
        windowState->totalTime = 0.0f;
        windowState->blockIndex = WindowBlockIndex;

        return windowState;
}
