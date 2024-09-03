#pragma once
#include <stdint.h>
#include <stddef.h>
/*
 *  these are the basic numerical types
 */
// 8-bit integers
#define i8 int8_t
#define u8 uint8_t

// 16-bit integers
#define i16 int16_t
#define u16 uint16_t

// 32-bit integers
#define i32 int32_t
#define u32 uint32_t

// 64-bit integers
#define i64 int64_t
#define u64 uint64_t

// floating point values
#define f32 float
#define f64 double

// 80-bit floating point (x86 long double)
#define f80 long double

// we need pi for maths
#define pi 3.141592f

// finely the bools
typedef enum { false, true } bool;

typedef enum {Vec2, Vec3, Vec4, error} vecType;
/*
 * these are the more complex but still basic datatypes
 */

typedef struct vec2 {
        f64 x;
        f64 y;
} vec2;

typedef struct vec3 {
        f64 x;
        f64 y;
        f64 z;
} vec3;

typedef struct vec4 {
        f64 x;
        f64 y;
        f64 z;
        f64 w;
} vec4;

typedef union homogeneousVec2 {
        vec2 vec2;
        vec3 vec3;
} homogeneousVec2;

typedef union homogeneousVec3 {
        vec3 vec3;
        vec4 vec4;
} homogeneousVec3;

typedef struct vec {
        vecType type;
        union {
                vec2 vec2;
                vec3 vec3;
                vec4 vec4;
        } data;
} vec;

typedef struct polygon {
        size_t size;
        vec2 *points;
} polygon;

typedef float mat4[16];

typedef struct matrix {
        i32 r;
        i32 c;
        i32 *data;
} matrix;
