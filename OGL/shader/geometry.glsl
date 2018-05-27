#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

in vec4 gNormal[];

void createVertex()
{
	gl_Position = proj*view*transform*gl_in[0].gl_Position;
	EmitVertex();
	
	
	gl_Position = proj*view*transform*gl_in[0].gl_Position + gNormal[0];
	EmitVertex();

	
	
	gl_Position = proj*view*transform*gl_in[0].gl_Position + gNormal[0] + vec4(0.0,0.05,0.0,1.0);
	EmitVertex();
}

void main()
{

	createVertex();
	EndPrimitive();
}
