#version 430 core

in vec3 normal0;
out vec4 fragColor;
  
void main()
{
	fragColor = vec4(0.9,0.9,0.1,1.0) * clamp(dot(-normalize(vec3(0.0,0.0,-1.0)),-normal0),0.2,1.0);
}