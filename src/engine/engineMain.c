#include "dataTypes.h"
#include "stackallocator.h"
#include "engine.h"
#include "window.h"
#include "rendeing.h"

#include <stdio.h>

extern stackAllocator mainMem;

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
        f32 acumulator = 0;
        f32 target = 1;
        f32 dt = 0;
        u32 preTicks = SDL_GetTicks();
        u32 curTicks = 0;

        while (windowState->running) {
                curTicks = SDL_GetTicks();
                windowState->deltaTime = (curTicks - preTicks)/ 1000.0f;
                windowState->totalTime += windowState->deltaTime;
                preTicks = curTicks;
                dt = windowState->deltaTime;
                acumulator += dt;

                if (acumulator >= target) {
                        

                        acumulator -= 1;
                }
                

                handleEvent(windowState);

        }
        printf("main loop exited at %f second elapsed\n", windowState->totalTime);
}

void engineMain()
{
        WindowState *window = WindowInit();
        startRenderer(window);
        mainLoop(window);
}
