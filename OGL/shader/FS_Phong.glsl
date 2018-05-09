#version 430 core

in vec3 worldPos;
in vec3 newNormal;
uniform vec3 eye;

out vec4 fragColor;	

//Light
uniform vec3 LightDirection = normalize(vec3(0.0,0.5,-1.0));
uniform vec4 LightColor = vec4(1.0,1.0,1.0,1.0);
uniform vec4 LightAmbient = vec4(0.9,0.9,0.9,1.0);

//Material
uniform vec4 MaterialAmbient = vec4(0.17,0.01,0.01,0.55);
uniform vec4 MaterialDiffuse = vec4(0.61, 0.04, 0.04, 0.55);
uniform vec4 MaterialSpecular = vec4(0.73,0.63,0.63,0.55);
uniform float MaterialShininess = 76.8;
uniform vec4 MaterialEmission = vec4(0.96, 0.89, 0.51, 1.0);

void main()
{
	vec3 normal = normalize(newNormal); //래스터라이저에 의해 보간된 노멀의 정규화

	float lightAmount = dot(-LightDirection, -normal);
	lightAmount = max(0.0, lightAmount);

	//Diffuse
	vec3 diff = vec3(LightColor.r * MaterialDiffuse.r , LightColor.g * MaterialDiffuse.g, LightColor.b * MaterialDiffuse.b);
	vec3 PhongD = diff * lightAmount;
	
	//Specular
	vec3 r = normalize(2.0f * -normal * dot(-normal, -LightDirection) + LightDirection);
	vec3 v = normalize(eye - worldPos);
	float spec = pow(max(dot(r,v),0.0f),MaterialShininess);
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



	fragColor = vec4(PhongD + PhongA+ PhongS + PhongE, 1.0);	
}

  