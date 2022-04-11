#pragma once
#include <glm/glm.hpp>


namespace Hound {
	struct DirectionalLight {
		glm::vec3 direction;

		// phong's value
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		// attenuation coefficient
		float linear;
		float constant;
		float quadratic;
	};
}
#pragma once
