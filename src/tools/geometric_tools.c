#include "dataTypes.h"
#include "stackallocator.h"

extern stackAllocator mainMem;

// hey look it's famous
// i know there are better ways but i just wanna use the famous quick inverse sqrt
// 2nd iteration was readded inorder io be within 0.0001 of the real value
float Q_rsqrt(float number)
{
        long i = 0;
        float x2 = 0, y = 0;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y  = number;
        i  = * ( long * ) &y;                       // evil floating point bit level hacking
        i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
        y  = * ( float * ) &i;
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

        return y;
}

float lerp(float v0, float v1, float t) 
{
        return (1 - t) * v0 + t * v1;
}

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

void scale(vec2 *a, float scale)
{
        a->x *= scale;
        a->y *= scale;
}

void normalize(vec2 *p_vec)
{
        float v = dot(*p_vec, *p_vec);
        v = Q_rsqrt(v);
        scale(p_vec, v);
}

i32 signed_area(vec2 a, vec2 b, vec2 c)
{
    vec2 p = vec_subtract(b, a);
    vec2 q = vec_subtract(c, a);

    return (p.x * q.y) - (q.x * p.y);
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
