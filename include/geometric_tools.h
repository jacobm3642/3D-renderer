#pragma once
#include "dataTypes.h"

vec2 vec_add(vec2 v1, vec2 v2);
vec2 vec_subtract(vec2 v1, vec2 v2);
bool is_ccw(vec2 a, vec2 b, vec2 c);
i32 signed_area(vec2 a, vec2 b, vec2 c);
i32 dot(vec2 a, vec2 b);
bool line_intersect(vec2 a, vec2 b, vec2 c, vec2 d);
float lerp(float v0, float v1, float t);
void scale(vec2 *a, float scale);
void normalize(vec2 *p_vec);
