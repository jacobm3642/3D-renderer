#pragma once
#include "dataTypes.h"

mat4* rotation_matrix_x(vec2 angle, mat4 *out);
mat4* rotation_matrix_y(vec2 angle, mat4 *out);
mat4* rotation_matrix_z(vec2 angle, mat4 *out);
mat4* matrix_multiply(mat4 *a, mat4 *b, mat4 *out);
mat4 *scale_matrix(float scale, mat4 *out);
