#version 430 core

attribute vec3 position;

uniform mat4 transform;
uniform mat4 vp;

void main()
{
    gl_Position =  vp * transform * vec4(position, 1.0);
}      