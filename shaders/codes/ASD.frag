#version 440 core

uniform vec3 uPixelColor;

// light properties
uniform vec3 uLightPos;
uniform vec3 uLightColor;

in vec3 FragPos ;
in vec3 TexCoord;
in vec3 Normal;

out vec4 fragColor;


void main(void){
	// ambient
	vec3 ambient = uLightColor * 0.2;

	// diffuse
	vec3 lightDir = normalize(uLightPos - FragPos);
	float diffuseImpact = max(dot(lightDir, Normal), 0.0); 
	vec3 diffuse = uLightColor * diffuseImpact;

	fragColor = vec4(uPixelColor, 1.0) * (ambient + diffuse);
}