#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec3 normal;

out vec3 normal0;

uniform mat4 transform;
uniform mat4 vp;

void main()
{
    gl_Position =  vp * transform * vec4(position, 1.0);
	normal0 = normalize(normal);
	normal0 = normalize(mat3(transpose(inverse(transform))) * normal0);
}      