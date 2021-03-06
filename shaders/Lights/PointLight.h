#pragma once
#include <glm/glm.hpp>


namespace Hound {
	struct PointLight {
		glm::vec3 position;

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
