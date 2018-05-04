#version 430 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec3 normal;

out vec4 color;

uniform mat4 transform;
uniform mat4 vp;
uniform vec3 eye;

//Light
uniform vec3 LightDirection = normalize(vec3(0.0,0.5,-1.0));
uniform vec4 LightColor = vec4(1.0,1.0,1.0,1.0);
uniform vec4 LightAmbient = vec4(0.9,0.9,0.9,1.0);

//Material
uniform vec4 MaterialDiffuse = vec4(0.96, 0.89, 0.51, 1.0);
uniform vec4 MaterialSpecular = vec4(0.63,0.56,0.37,1.0);
uniform float MaterialShininess = 61.2;
uniform vec4 MaterialAmbient = vec4(0.25,0.20,0.07,1.0);
uniform vec4 MaterialEmission = vec4(0.96, 0.89, 0.51, 1.0);

void main()
{
	vec3 newNormal = normalize(normal); //현재, CPU에서 전달하는 정점 노멀은 정규화 되어있지 않다
	vec4 tempPos = transform * vec4(position, 1.0);
	vec3 worldPos = tempPos.xyz;

    gl_Position =  vp * transform * vec4(position, 1.0);

	float lightAmount = dot(-LightDirection, -newNormal);
	lightAmount = max(0.0, lightAmount);

	//Diffuse
	vec3 diff = vec3(LightColor.r * MaterialDiffuse.r , LightColor.g * MaterialDiffuse.g, LightColor.b * MaterialDiffuse.b);
	vec3 PhongD = diff * lightAmount;
	
	//Specular
	vec3 Refl = 2.0f * -newNormal * dot(-newNormal, -LightDirection) + LightDirection;
	vec3 View = normalize(eye - worldPos);
	float spec = pow(max(dot(Refl,View),0.0f),MaterialShininess);
	if(lightAmount <= 0.0f)
	{
		spec = 0.0f;
	}
	vec3 PhongS = spec * LightColor.rgb * MaterialSpecular.rgb;

	//Ambient
	vec3 PhongA = LightAmbient.rgb * MaterialAmbient.rgb;

	//Emission
	float emitPower = 0.0f;
	vec3 PhongE = MaterialEmission.rgb * emitPower;

	color = vec4(PhongD + PhongS+ PhongA + PhongE, 1.0);	
}      