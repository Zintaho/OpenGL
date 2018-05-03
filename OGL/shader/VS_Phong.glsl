#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec3 normal;

out vec3 worldPos;
out vec3 newNormal;

uniform mat4 transform;
uniform mat4 vp;

void main()
{
	vec3 tempNormal = normalize(normal); //현재, CPU에서 전달하는 정점 노멀은 정규화 되어있지 않다
	vec4 tempPos = transform * vec4(position, 1.0);

    gl_Position =  vp * transform * vec4(position, 1.0);

	worldPos = vec3(tempPos.xyz);
	newNormal = normalize(mat3(transpose(inverse(transform))) * tempNormal);
}      