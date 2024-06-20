#include <stdio.h>
#ifdef test 
#include "tests.h"  
#endif

int main()
{
#ifdef test 
        runTests();
        return  0;
#endif
        printf("ruinning main\n");

        return 0;
}
