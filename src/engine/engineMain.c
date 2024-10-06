#include "dataTypes.h"
#include "engine.h"
#include "window.h"
#include "rendeing.h"
#include "object_handleing.h"
#include "game_of_life.h"

#include <time.h>
#include <stdio.h>
#include <math.h>

#include "engine_internal.h"

void handleEvent(WindowState *windowState) 
{        
        SDL_Event event;
        
        if (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        windowState->running = 0;
                        break;
                case SDL_KEYUP:
                        printf("key up detected\n");
                        break;
                case SDL_KEYDOWN:
                        printf( "Key press detected\n" );
                        break;
                case SDL_MOUSEBUTTONDOWN:
                        printf( "mouse press detected\n" );
                        break;
                case SDL_MOUSEBUTTONUP:
                        printf( "mouse unpress detected\n" );
                        break;
                }
        }
}

void mainLoop(WindowState *windowState)
{
        f32 secondAcumulator = 0;
        f32 target = 1;
        f32 frameAcumulator = 0;
        f32 frameTarget = 0.008;
        f32 dt = 0;
        u32 preTicks = SDL_GetTicks();
        u32 curTicks = 0;
        u32 fps = 0;
        startRenderer();
        int grid_size = 10000;
        int n = 100;
        vec4 wi = {1, 1, 1, 1};
        //vec2 size = {n, n};
        Objnode **grid = allocate(sizeof(intptr_t) * grid_size);
        for (int i = 0; i < grid_size; i++) {
                grid[i] = add_man("basic.man");
                grid[i]->obj->scale = 0.2;

                // Calculate dx and dy
                float dx = (i % n) * (2.0f / n) - 1.0f + 0.1;
                float dy = 1.0f - (floor(i / n) * (2.0f / n)) - 0.1;

                vec3 pos = {dx, dy, 0};
                grid[i]->obj->pos = pos;
                if (i % 2 == 0) {
                        grid[i]->obj->color = wi;
                }
        }  
        while (windowState->running) {
                curTicks = SDL_GetTicks();
                windowState->deltaTime = (curTicks - preTicks)/ 1000.0f;
                windowState->totalTime += windowState->deltaTime;
                preTicks = curTicks;
                dt = windowState->deltaTime;
                secondAcumulator += dt;
                frameAcumulator += dt;
                if (secondAcumulator >= target) {
                        printf("FPS: %d\n", fps);
                        fps = 0;
                        secondAcumulator -= target;
                }

                if (frameAcumulator >= frameTarget || !FRAME_LIMITED) {

                        //game_of_life(grid, size);
                        begin_frame();

                        //render_all();
                        SDL_GL_SwapWindow(windowState->window);
                        fps++;

                        frameAcumulator -= frameTarget;
                }

                handleEvent(windowState);
                GLenum error = glGetError();
                if(error != GL_NO_ERROR) {
                        printf("OpenGL error: %d\n", error);
                }
        }
        printf("main loop exited at %f second elapsed\n", windowState->totalTime);
}

void engineMain()
{
        allocate(sizeof(Object));
        
        WindowState *window = WindowInit();
        mainLoop(window);
}
