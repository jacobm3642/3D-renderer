#include "dataTypes.h"

#include <math.h>

mat4 *rotation_matrix_x(vec2 angle, mat4 *out) 
{
        float theta = (angle.x * M_PI) / angle.y;
        float cos_theta = cos(theta);
        float sin_theta = sin(theta);

        (*out)[0] = 1.0f;      (*out)[1] = 0.0f;       (*out)[2] = 0.0f;       (*out)[3] = 0.0f;
        (*out)[4] = 0.0f;      (*out)[5] = cos_theta;  (*out)[6] = -sin_theta; (*out)[7] = 0.0f;
        (*out)[8] = 0.0f;      (*out)[9] = sin_theta;  (*out)[10] = cos_theta; (*out)[11] = 0.0f;
        (*out)[12] = 0.0f;     (*out)[13] = 0.0f;      (*out)[14] = 0.0f;      (*out)[15] = 1.0f;

        return out;
}

mat4 *rotation_matrix_y(vec2 angle, mat4 *out) 
{
        float theta = (angle.x * M_PI) / angle.y;
        float cos_theta = cos(theta);
        float sin_theta = sin(theta);

        (*out)[0] = cos_theta;  (*out)[1] = 0.0f;      (*out)[2] = sin_theta;  (*out)[3] = 0.0f;
        (*out)[4] = 0.0f;       (*out)[5] = 1.0f;      (*out)[6] = 0.0f;       (*out)[7] = 0.0f;
        (*out)[8] = -sin_theta; (*out)[9] = 0.0f;      (*out)[10] = cos_theta; (*out)[11] = 0.0f;
        (*out)[12] = 0.0f;      (*out)[13] = 0.0f;     (*out)[14] = 0.0f;      (*out)[15] = 1.0f;

        return out;
}

mat4 *rotation_matrix_z(vec2 angle, mat4 *out) 
{
        float theta = (angle.x * M_PI) / angle.y;
        float cos_theta = cos(theta);
        float sin_theta = sin(theta);

        (*out)[0] = cos_theta;  (*out)[1] = -sin_theta; (*out)[2] = 0.0f;  (*out)[3] = 0.0f;
        (*out)[4] = sin_theta;  (*out)[5] = cos_theta;  (*out)[6] = 0.0f;  (*out)[7] = 0.0f;
        (*out)[8] = 0.0f;       (*out)[9] = 0.0f;       (*out)[10] = 1.0f; (*out)[11] = 0.0f;
        (*out)[12] = 0.0f;      (*out)[13] = 0.0f;      (*out)[14] = 0.0f; (*out)[15] = 1.0f;

        return out;
}

mat4 *scale_matrix(float scale, mat4 *out)
{
        (*out)[0] = scale;      (*out)[1] = 0.0f;       (*out)[2] = 0.0f;   (*out)[3] = 0.0f;
        (*out)[4] = 0.0f;       (*out)[5] = scale;      (*out)[6] = 0.0f;   (*out)[7] = 0.0f;
        (*out)[8] = 0.0f;       (*out)[9] = 0.0f;       (*out)[10] = scale; (*out)[11] = 0.0f;
        (*out)[12] = 0.0f;      (*out)[13] = 0.0f;      (*out)[14] = 0.0f;  (*out)[15] = 1.0f;

        return out;
}

// not correct
mat4 *traslation_matrix(vec3 pos, mat4 *out)
{ 
        (*out)[0] = 0.0f;      (*out)[1] = 0.0f;       (*out)[2] = 0.0f;   (*out)[3] = pos.x;
        (*out)[4] = 0.0f;       (*out)[5] = .0f;      (*out)[6] = 0.0f;   (*out)[7] = pos.y;
        (*out)[8] = 0.0f;       (*out)[9] = 0.0f;       (*out)[10] = 0.0f; (*out)[11] = pos.z;
        (*out)[12] = 0.0f;      (*out)[13] = 0.0f;      (*out)[14] = 0.0f;  (*out)[15] = 0.0f;
        
        return out;
}

mat4* matrix_multiply(mat4 *a, mat4 *b, mat4 *out)
{
        mat4 temp;

        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        temp[i*4 + j] = (*a)[i*4 + 0] * (*b)[0*4 + j] +
                                (*a)[i*4 + 1] * (*b)[1*4 + j] +
                                (*a)[i*4 + 2] * (*b)[2*4 + j] +
                                (*a)[i*4 + 3] * (*b)[3*4 + j];
                }
        }

        for (int i = 0; i < 16; i++) {
                (*out)[i] = temp[i];
        }

        return out;
}
