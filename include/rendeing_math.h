#pragma once
#include "dataTypes.h"

mat4* rotation_matrix_x(float angle, mat4 *out);
mat4* rotation_matrix_y(float angle, mat4 *out);
mat4* rotation_matrix_z(float angle, mat4 *out);
mat4* matrix_multiply(mat4 *a, mat4 *b, mat4 *out);
mat4 *scale_matrix(float scale, mat4 *out);
mat4 *traslation_matrix(vec3 pos, mat4 *out);
