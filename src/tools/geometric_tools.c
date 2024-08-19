#include "dataTypes.h"
#include "stackallocator.h"
#include "engine_internal.h"

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

vec uni_vec_add(vec v1, vec v2)
{
        vec out = {error, .data.vec4 = {-1, -1, -1, -1}};
        if (v1.type != v2.type) {
                return out;
        }
        if (v1.type == error || v2.type == error) {
                return out;
        }

        out.type = v1.type;

        // the fall-through is intentional
        switch (v1.type) {
                case Vec4:
                        out.data.vec4.w = v1.data.vec4.w + v2.data.vec4.w;
                case Vec3:
                        out.data.vec4.z = v1.data.vec4.z + v2.data.vec4.z;
                case Vec2:
                        out.data.vec4.y = v1.data.vec4.y + v2.data.vec4.y;
                        out.data.vec4.x = v1.data.vec4.x + v2.data.vec4.x;
                        break;
                case error:
                        // redundent but clang gets mad if i dont include it 
                        out.type = error;
        }

        return out;
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

//vec Bezier_spline(vec p0, vec p1, vec p2, vec p3, f32 t)
//{
//        vec out = {error, .data.vec2 = {-1, -1}};
//        if (t < 0 || t > 1) {
//                return out;
//        }
//        if (p0.type != Vec2) {
//                return out;
//        }
//        if (!(p0.type == p1.type == p2.type == p3.type)) {
//                return out;
//        }
//        out.type = p0.type;
//        
//}
