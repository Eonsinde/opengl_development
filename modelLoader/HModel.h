#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;

namespace Hound {
	struct HVertex {
		glm::vec3 position;
		glm::vec2 textCoord;
		glm::vec3 normal;
		glm::vec4 colors;
	};

	std::ostream& operator<<(std::ostream&, const HVertex);

	struct HMesh {
		friend class HModel;
		std::string name;
		std::string materialName;
		std::vector<unsigned int> indices;
		std::vector<HVertex> hvertices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textCoords;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec3> normals;
		// used to determine what draw call to trigger
		int drawMode = 0; // triangles by default
	
		void Draw(Shader&);

	private:
		// render data
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_EBO;

		void SetupMesh();
	};

	struct HVertexGroup {
		friend bool operator==(const HVertexGroup& lhsObj, const HVertexGroup& rhsObj);

		int v = -1;
		int t = -1;
		int n = -1;
	};

	typedef std::vector<HVertexGroup> HFace;

	class HashFunction {
	public:
		size_t operator()(const HVertexGroup& v) const {
			return (size_t)v.v + v.t + v.n;
		}
	};

	class HModel
	{
	public:
		HModel();

		bool Load(const std::string& filename);
		void Update();
		void Render(Shader& shader);
		void Print();

	private:
		void SortVertexData(HMesh& newMesh, const HMesh& oldMesh, const std::vector<HFace>& faces);
		std::vector<HMesh> m_meshes;
	};
};


