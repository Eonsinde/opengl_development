#version 440 core

struct DirectionalLight{
	vec3 direction;
	// phong's values
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
uniform DirectionalLight uDirectionalLight;

// light properties
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uCameraPos;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;


void main(void){
	// ambient
	vec3 ambient = uDirectionalLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

	// diffuse
	vec3 lightDir = normalize(-uDirectionalLight.direction);
	float diffuseImpact = max(dot(lightDir, Normal), 0.0); 
	vec3 diffuse = uDirectionalLight.diffuse * diffuseImpact * vec3(texture(uMaterial.diffuse, TexCoord));

	// specular
	vec3 refNegLightDir = reflect(-lightDir, Normal); // reflected negated light direction
	vec3 viewDir = normalize(uCameraPos - FragPos);
	float specImpact = pow(max(dot(refNegLightDir, viewDir), 0.0), uMaterial.shininess);
	vec3 specular = uDirectionalLight.specular * specImpact * vec3(texture(uMaterial.specular, TexCoord));

	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0);
}