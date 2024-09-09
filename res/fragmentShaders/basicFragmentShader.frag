#version 330 core

out vec4 FragColor;
uniform mat4 transform;

void main()
{
   FragColor = transform * vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
