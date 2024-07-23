#include <check.h>
#include <stdio.h>

#include "dataTypes.h"
#include "geometric_tools.h"
#include "tests.h"

void runTests()
{
        vec2 total = {0, 0};
        
        total = vec_add(run_geo_tests(), total);
        total = vec_add(stack_allocator_tests(), total);
        
        if (total.x == total.y) {
                printf("\n \x1b[32m");  
        } else {
                printf("\n \x1b[31m");  
        }

        printf("%d of %d total passed \x1b[0m \n", (int)total.x, (int)total.y);
}
