#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 scale;
uniform mat4 pos;

void main()
{
        gl_Position = scale * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f) * pos;
}
