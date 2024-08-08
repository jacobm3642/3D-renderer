#include "dataTypes.h"
#include "errors.h"
#include "stackallocator.h"
#include "engine.h"

#include <setjmp.h>

#ifdef test 
#include "tests.h"  
#endif

stackAllocator mainMem;
jmp_buf fatal_error;

int main()
{
        init_allocator(&mainMem, 1000000);
        allocate_block(&mainMem, 100); // for env vars
#ifdef test 
        runTests();
#endif
        i32 returnvalue;
        
        if(!(returnvalue = setjmp(fatal_error))) {
                engineMain();
        } else {
                display_error(returnvalue);
        }
        free_allocator(&mainMem);
        return 0;
}
