#version 430 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat VP;

void main()
{
    gl_Position = VP * transform * vec4(aPos, 1.0);
}      