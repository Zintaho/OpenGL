#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec2 uv;
layout(location = 2) in  vec3 normal;

out VS_OUT {
    vec3 oNormal;
} vs_out;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 transform;

void main()
{
    gl_Position = proj * view * transform * vec4(position, 1.0); 
    mat3 normalMatrix = mat3(transpose(inverse(view * transform)));
    vs_out.oNormal = normalize(vec3(proj * vec4(normalMatrix * normal, 0.0)));
}