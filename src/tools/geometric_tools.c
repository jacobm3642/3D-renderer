#include "dataTypes.h"

vec2 vec_add(vec2 v1, vec2 v2)
{
        vec2 out;
        out.x = v1.x + v2.x;
        out.y = v1.y + v2.y;

        return out;
}
