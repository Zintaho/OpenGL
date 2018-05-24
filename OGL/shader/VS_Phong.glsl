#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec2 uv;
layout(location = 2) in  vec3 normal;

out vec2 interUV;
out vec3 worldPos;
out vec3 newNormal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vec3 tempNormal = normalize(normal); //����, CPU���� �����ϴ� ���� ����� ����ȭ �Ǿ����� �ʴ�
	vec4 tempPos = transform * vec4(position, 1.0);

    gl_Position =  proj * view * transform * vec4(position, 1.0);

	worldPos = vec3(tempPos.xyz);
	newNormal = normalize(mat3(transpose(inverse(transform))) * tempNormal);

	interUV = uv;
}      