#version 430 core

out vec4 color;

void main()
{
	color = vec4(clamp(sin(gl_FragCoord.x),0.0,1.0),clamp(sin(gl_FragCoord.y),0.0,1.0),clamp(sin(gl_FragCoord.z),0.0,1.0),1.0);
}