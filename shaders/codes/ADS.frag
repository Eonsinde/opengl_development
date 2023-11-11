#version 440 core

uniform vec3 uPixelColor;

// light properties
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uCameraPos;

in vec3 FragPos;
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

	// specular
	vec3 refNegLightDir = reflect(-lightDir, Normal); // reflected negated light direction
	vec3 viewDir = normalize(uCameraPos - FragPos);
	float specStrength = 0.5;
	float specImpact = pow(max(dot(refNegLightDir, viewDir), 0.0), 32);
	vec3 specular = uLightColor * specStrength * specImpact;

	fragColor = vec4(uPixelColor, 1.0) * vec4(ambient + diffuse + specular, 1.0);
}