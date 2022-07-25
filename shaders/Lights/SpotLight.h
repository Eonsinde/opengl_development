#pragma once
#include <glm/glm.hpp>


namespace Hound {
	struct SpotLight {
		glm::vec3 position;
		glm::vec3 direction; // spotlight direction

		// phong's value
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		// spot light props
		float cuterOff;
		float outerCutOff;
		float theta;

		// attenuation coefficient
		float linear;
		float constant;
		float quadratic;
	};
}
