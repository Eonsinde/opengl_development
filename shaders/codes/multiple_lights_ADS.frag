#version 440 core

// define the lights
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

// create lights' instances
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
vec3 CalcPointLight(PointLight, vec3 , vec3 ,vec3);
vec3 calcSpotLight(SpotLight, vec3, vec3, vec3);
float calcLightAttenutation(float);


void main(void){
	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(uCameraPos - FragPos);
	vec3 result = vec3(0.0);

	// phase 1: Directional lighting
//	result = calcDirLight(uDirLight, norm, viewDir);
	// phase 2: Point lights
	for(int i = 0; i < NO_OF_POINT_LIGHTS; i++)
		result += CalcPointLight(uPointLights[i], norm, FragPos, viewDir);
	// phase 3: Spot light
//	result += calcSpotLight(uSpotLight, norm, FragPos, viewDir);
	
	fragColor = vec4(result, 1.0);
} // end of main


// used to compute directional light parameters
vec3 calcDirLight(DirectionalLight pLight, vec3 pNormal, vec3 pViewDir) {
	vec3 lightDir = normalize(-pLight.direction);

	// ambient
	vec3 ambient = pLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

	// diffuse
	float diffuseImpact = max(dot(lightDir, pNormal), 0.0); 
	vec3 diffuse = pLight.diffuse * diffuseImpact * vec3(texture(uMaterial.diffuse, TexCoord));

	// specular
	vec3 refNegLightDir = reflect(lightDir, pNormal); // reflected negated light direction
	float specImpact = pow(max(dot(refNegLightDir, pViewDir), 0.0), uMaterial.shininess);
	vec3 specular = pLight.specular * specImpact * vec3(texture(uMaterial.specular, TexCoord));

	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 CalcPointLight(PointLight pLight, vec3 pNormal, vec3 pFragPos, vec3 pViewDir) {
	vec3 lightDir = normalize(pLight.position - pFragPos);

	// ambient
	vec3 ambient = pLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

	// diffuse
	float diffuseImpact = max(dot(lightDir, pNormal), 0.0); 
	vec3 diffuse = pLight.diffuse * diffuseImpact * vec3(texture(uMaterial.diffuse, TexCoord));

	// specular
	vec3 refNegLightDir = reflect(-lightDir, pNormal); // reflected negated light direction
	float specImpact = pow(max(dot(refNegLightDir, pViewDir), 0.0), uMaterial.shininess);
	vec3 specular = pLight.specular * specImpact * vec3(texture(uMaterial.specular, TexCoord));

	// attenuation
	float distance = length(pLight.position - pFragPos);
//	float attenuation = calcLightAttenutation(distance);
	float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

	// have computed attenuation value affect lighting results
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 calcSpotLight(SpotLight pLight, vec3 pNormal, vec3 pFragPos, vec3 pViewDir){
	vec3 lightDir = normalize(pLight.position - FragPos);

	// ambient
	vec3 ambient = pLight.ambient * vec3(texture(uMaterial.diffuse, TexCoord));

	// diffuse
	float diffuseImpact = max(dot(lightDir, pNormal), 0.0); 
	vec3 diffuse = pLight.diffuse * diffuseImpact * vec3(texture(uMaterial.diffuse, TexCoord));

	// specular
	vec3 refNegLightDir = reflect(-lightDir, pNormal); // reflected negated light direction
	float specImpact = pow(max(dot(refNegLightDir, pViewDir), 0.0), uMaterial.shininess);
	vec3 specular = pLight.specular * specImpact * vec3(texture(uMaterial.specular, TexCoord));

	// spotlight calcs
	// intensity = theta - outerCutOff(gamma) / epsilon(innerCutOff - outerCutOff)
	float theta = dot(lightDir, normalize(-pLight.direction)); // spotlight theta
	// we do innerCutOff - outerCutOff becos the cosine value for 
	// 19.5(0.94264) is lesser than the cosine value for 12.5(0.976296) 
	// and it is cosine values we're working with not angles
	float epsilon = pLight.cuterOff - pLight.outerCutOff; 
	float intensity = clamp((theta - pLight.outerCutOff) / epsilon, 0.0, 1.0);

	// use the spotlight intensity value to affect the diffuse and specular values
	diffuse *= intensity;
	specular *= intensity;

	// attenuation
	float distance = length(pLight.position - pFragPos);
	float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

	// have computed attenuation value affect lighting results
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	return result;
}


// picking attenuation values to use based on distance
float calcLightAttenutation(float pDistance) { 
	float attenuation = 0.0;

	if (pDistance >= 0 && pDistance <= 6) { // 7 (7, pDistance, 7]
		attenuation = 1.0 / (1.0 + (0.7 * pDistance) + (1.8 * (pDistance * pDistance)));
	} else if (pDistance >= 7 && pDistance <= 12) { // 13
		attenuation = 1.0 / (1.0 + (0.35 * pDistance) + (0.44 * (pDistance * pDistance)));
	} else if (pDistance >= 13 && pDistance <= 19) { // 20
		attenuation = 1.0 / (1.0 + (0.22 * pDistance) + (0.20 * (pDistance * pDistance)));
	} else if (pDistance >= 20 && pDistance <= 31) { // 32
		attenuation = 1.0 / (1.0 + (0.14 * pDistance) + (0.07 * (pDistance * pDistance)));
	} else if (pDistance >= 50) { // 50
		attenuation = 1.0 / (1.0 + (0.09 * pDistance) + (0.032 * (pDistance * pDistance)));
	} else if (pDistance >= 65) { // 65
		attenuation = 1.0 / (1.0 + (0.07 * pDistance) + (0.017 * (pDistance * pDistance)));
	} else if (pDistance >= 100) { // 100
		attenuation = 1.0 / (1.0 + (0.045 * pDistance) + (0.0075 * (pDistance * pDistance)));
	} else if (pDistance >= 160) { // 160
		attenuation = 1.0 / (1.0 + (0.027 * pDistance) + (0.0028 * (pDistance * pDistance)));
	} else if (pDistance >= 200) { // 200
		attenuation = 1.0 / (1.0 + (0.022 * pDistance) + (0.0019 * (pDistance * pDistance)));
	} else if (pDistance >= 325) { // 325
		attenuation = 1.0 / (1.0 + (0.014 * pDistance) + (0.0007 * (pDistance * pDistance)));
	} else if (pDistance >= 600) { // 600
		attenuation = 1.0 / (1.0 + (0.007 * pDistance) + (0.0002 * (pDistance * pDistance)));
	} else if (pDistance >= 3250) { // 3250
		attenuation = 1.0 / (1.0 + (0.0014 * pDistance) + (0.000007 * (pDistance * pDistance)));
	}

	return attenuation;
}