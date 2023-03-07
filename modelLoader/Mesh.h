#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "utils.h"


class Shader;

namespace Hound {
	struct Vertex 
	{
		friend std::ostream& operator<<(std::ostream& os, const Vertex obj);

		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		/*glm::vec3 tangent;
		glm::vec3 bitangent;*/
	};

	struct MeshTexture {
		uint32_t id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		// mesh name
		std::string name;
		// mesh data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<MeshTexture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
		void Draw(Shader& shader);

	private:
		// render data
		unsigned int m_VAO, m_VBO, m_EBO;
		void setupMesh();
	};
}


