#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


namespace Hound {
	struct HMesh {
		std::string name;
		std::string materialName;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textCoords;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec3> normals;
	};

	struct HVertexGroup {
		int v = -1;
		int t = -1;
		int n = -1;

		bool operator==(const HVertexGroup& other) {
			return (v == other.v && t == other.t && n == other.n);
		}
	};

	typedef std::vector<HVertexGroup> HFace;

	class HModel
	{
	public:
		HModel();

		bool Load(const std::string& filename);
		void Update();
		void Render();

	private:
		std::vector<HMesh> m_meshes;
	};
};


