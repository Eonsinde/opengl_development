#pragma once
#include <glm/glm.hpp>


namespace Hound {
	struct Material {
		// this are sampling locations for textures on the GPU
		glm::vec3 diffuse;
		glm::vec3 specular;
		// determines how shiny the specular highlight is
		float shininess;
	};
}
