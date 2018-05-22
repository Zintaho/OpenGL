#version 430 core

layout(location = 0) in  vec3 position;

out vec4 color;

uniform mat4 transform;
uniform mat4 vp;

void main()
{
	gl_Position = transform * vec4(position,1.0);
	color = vec4(clamp(position,0.0,1.0),1.0);
}      