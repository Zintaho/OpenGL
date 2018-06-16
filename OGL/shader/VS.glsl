#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec2 uv;
layout(location = 2) in  vec3 normal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

out vec3 oNormal;

void main()
{
    gl_Position =  proj * view * transform * vec4(position, 1.0);
	oNormal = normal;
}