#include "dataTypes.h"
#include "stackallocator.h"
#include <stdio.h>
#ifdef test 
#include "tests.h"  
#endif

stackAllocator mainMem;

int main()
{
        init_allocator(&mainMem, 1000000);
#ifdef test 
        runTests();
#endif
        printf("ruinning main\n");

        free_allocator(&mainMem);
        return 0;
}
