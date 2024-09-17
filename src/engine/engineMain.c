#include "dataTypes.h"
#include "engine.h"
#include "window.h"
#include "rendeing.h"

#include <stdio.h>

#include "engine_internal.h"

void handleEvent(WindowState *windowState) 
{        
        SDL_Event event;
        
        if (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        windowState->running = 0;
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

        Object *obj = parce_manafest("basic.man");

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

                        begin_frame();

                        draw_triangle_mesh_GL(obj);
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
        print_allocator(get_stack_ptr());
        print_frameData(get_stack_ptr(), 0);
        
        WindowState *window = WindowInit();
        mainLoop(window);
}
