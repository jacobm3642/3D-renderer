#include "dataTypes.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

vec2 vec_add(vec2 v1, vec2 v2)
{
        vec2 out;
        out.x = v1.x + v2.x;
        out.y = v1.y + v2.y;

        return out;
}

vec2 vec_subtract(vec2 v1, vec2 v2)
{
        vec2 out = {v1.x - v2.x, v1.y - v2.y};
        return out;
}

i32 dot(vec2 a, vec2 b)
{
        return ((a.x * b.x)+ (a.y * b.y));
}

i32 signed_area(vec2 a, vec2 b, vec2 c)
{
        vec2 p = vec_subtract(b, a);
        vec2 q = vec_subtract(c, a);

        return ((p.x * q.y) - (q.x * p.y));
}

bool is_ccw(vec2 a, vec2 b, vec2 c)
{
        i32 area = signed_area(a, b, c);
        return area > 0 ? true : false;
}

bool line_intersect(vec2 a, vec2 b, vec2 c, vec2 d)
{
        return (is_ccw(a, d, b) != is_ccw(a, c, b)) && (is_ccw(c, a, d) != is_ccw(c, b, d)) ? true : false; 
}
