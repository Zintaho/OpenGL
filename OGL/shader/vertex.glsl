#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec4 gNormal;

void main()
{
	gl_Position = vec4(position,1.0);
	gNormal = vec4(normal, 1.0);
}      