#version 440 core

struct SpotLight{
	vec3 position;
	vec3 direction; // spotlight direction
	// phong's values
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	// angles
	float cuterOff;
	// attenuation
	float constant;
	float linear;
	float quadratic;
};

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material uMaterial;
uniform SpotLight uSpotLight;

// camera position
uniform vec3 uCameraPos;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;


void main(void){
	vec3 lightDir = normalize(uSpotLight.position - FragPos);
	float theta = dot(lightDir, normalize(-uSpotLight.direction)); // spotlight theta

	if (theta > uSpotLight.cuterOff){ // in other words:- if theta is lesser than cuterOff angle 
		// do lighting
		// ambient
		vec3 ambient = uSpotLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

		// diffuse
		float diffuseImpact = max(dot(lightDir, Normal), 0.0); 
		vec3 diffuse = uSpotLight.diffuse * diffuseImpact * vec3(texture(uMaterial.diffuse, TexCoord));

		// specular
		vec3 refNegLightDir = reflect(-lightDir, Normal); // reflected negated light direction
		vec3 viewDir = normalize(uCameraPos - FragPos);
		float specImpact = pow(max(dot(refNegLightDir, viewDir), 0.0), uMaterial.shininess);
		vec3 specular = uSpotLight.specular * specImpact * vec3(texture(uMaterial.specular, TexCoord));

		// attenuation
		float distance = length(uSpotLight.position - FragPos);
		float attenuation = 1.0 / (uSpotLight.constant + uSpotLight.linear * distance + uSpotLight.quadratic * (distance * distance));

		// have computed attenuation value affect lighting results
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		vec3 result = ambient + diffuse + specular;
		fragColor = vec4(result, 1.0);
	}
	else{
		// use ambient lighting
		vec3 ambient = uSpotLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

		fragColor = vec4(ambient, 1.0);
	}	
} // end of main