#version 440 core

// define the lights
struct PointLight{
	vec3 position;
	// phong's values
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	// attenuation
	float constant;
	float linear;
	float quadratic;
};

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

struct SpotLight{
	vec3 position;
	vec3 direction; // spotlight direction
	// phong's values
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	// angles
	float cuterOff;
	float outerCutOff;
	// attenuation
	float constant;
	float linear;
	float quadratic;
};

// define the material interface
struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// create material instance
uniform Material uMaterial;

// create light uniforms
#define NO_OF_POINT_LIGHTS 4

uniform DirectionalLight uDirLight;
uniform PointLight uPointLights[NO_OF_POINT_LIGHTS];
uniform SpotLight uSpotLight;

// camera position
uniform vec3 uCameraPos;

// receive incoming data from previous shader stages
in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;


// function prototypes/forward declaration for each light's calc
// each function is allowed to take in an instance of a light becos
// multiple uniform instance of a DirLight for example, might be present in a shader 
vec3 calcDirLight(DirectionalLight, vec3, vec3);
vec3 calcPointLight();
vec3 calcSpotLight();


void main(void){
	vec3 lightDir = normalize(uSpotLight.position - FragPos);

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

	// spotlight calcs
	// intensity = theta - outerCutOff(gamma) / epsilon(innerCutOff - outerCutOff)
	float theta = dot(lightDir, normalize(-uSpotLight.direction)); // spotlight theta
	// we do innerCutOff - outerCutOff becos the cosine value for 19.5(0.94264) is lesser than the cosine value for 12.5(0.976296) and
	// it is cosine values we're working with not angles
	float epsilon = uSpotLight.cuterOff - uSpotLight.outerCutOff; 
	float intensity = clamp((theta - uSpotLight.outerCutOff) / epsilon, 0.0, 1.0);

	// use the spotlight intensity value to affect the diffuse and specular values
	diffuse *= intensity;
	specular *= intensity;

	// attenuation
	float distance = length(uSpotLight.position - FragPos);
	float attenuation = 1.0 / (uSpotLight.constant + uSpotLight.linear * distance + uSpotLight.quadratic * (distance * distance));

	// have computed attenuation value affect lighting results
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0);
	
} // end of main


vec3 calcDirLight(DirectionalLight pDirLight, vec3 pNormal, vec3 pViewDir){
	
	return vec3(0.0);
}

vec3 calcPointLight(){

	return vec3(0.0);
}

vec3 calcSpotLight(){

	return vec3(0.0);
}