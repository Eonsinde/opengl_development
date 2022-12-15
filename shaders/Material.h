#pragma once
#include <glm/glm.hpp>


namespace Hound {
	struct Material
	{
		// Material Name
		std::string name;

		// Ambient Color
		glm::vec3 ambient;
		// Diffuse Color
		glm::vec3 diffuse;
		// Specular Color
		glm::vec3 specular;

		// Specular Exponent/shininess
		float specExp = 0.0f;
		// Optical Density - law of refraction
		float Ni = 0.0f;
		// Dissolve
		float dissolve = 1.0f;

		// Illumination
		int illum = 0;

		// Ambient Texture Map
		std::string map_ambient;
		// Diffuse Texture Map
		std::string map_diffuse;
		// Specular Texture Map
		std::string map_specular;
		// Specular Hightlight Map
		std::string map_Ns;
		// Alpha Texture Map
		std::string map_d;
		// Bump Map
		std::string map_bump;
	};
}
