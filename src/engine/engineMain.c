#include "dataTypes.h"
#include "stackallocator.h"
#include "engine.h"
#include "window.h"

#include <stdio.h>

extern stackAllocator mainMem;

void engineMain()
{
        WindowState *window = WindowInit();
        print_frameData(&mainMem, window->blockIndex);
}
