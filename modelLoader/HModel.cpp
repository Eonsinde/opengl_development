#include "HModel.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include "utils.h"
 

namespace Hound {
	HModel::HModel()
	{
		m_meshes.reserve(10);
	}

	bool HModel::Load(const std::string& filename)
	{
		std::fstream file(filename, std::ios_base::in);

		if (!file) {
			std::cerr << "ERR::HModel::Failed to load model file::" << filename << "\n";
			return false;
		}

		HMesh rawMesh;
		std::string lastMaterialName;

		std::string line;
		std::string lastName;
		std::vector<HFace> faces_vector;

		TokenVector subStrings;
		subStrings.reserve(10);

		while (!file.eof()) {
			std::getline(file, line);
			subStrings.clear();

			if (!line.empty()) {
				tokenize(line, subStrings);

				// comments
				if (subStrings[0] == "#") {
					std::cout << "Some Comment: " << line << "\n";
					continue;
				}

				// vertex data
				if (subStrings[0] == "v") {
					rawMesh.vertices.push_back(glm::vec3(
						std::stof(subStrings[1]),
						std::stof(subStrings[2]),
						std::stof(subStrings[3])
					));
					continue;
				}
				
				// normal data
				if (subStrings[0] == "vn") {
					rawMesh.normals.push_back(glm::vec3(
						std::stof(subStrings[1]),
						std::stof(subStrings[2]),
						std::stof(subStrings[3])
					));
					continue;
				}

				// texture coord data
				if (subStrings[0] == "vn") {
					rawMesh.textCoords.push_back(glm::vec2(
						std::stof(subStrings[1]),
						std::stof(subStrings[2])
					));
					continue;
				}

				// face data
				if (subStrings[0] == "f") {
					// subStrings format here: [f, 21/123/123, 12/34/65, 75/32/123]

					HFace faces; // stores data in format: { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }
					TokenVector numbers;
					numbers.reserve(10);

					for (int i = 1; i <= 3; i++) {
						numbers.clear();
						HVertexGroup face;
						
						// tokenize subString content: 21/123/123
						tokenize(subStrings[i], numbers, "/");
						
						// store derived tokens in face
						face.v = std::stoi(numbers[0]) - 1;
						face.t = std::stoi(numbers[1]) - 1;
						face.n = std::stoi(numbers[2]) - 1;

						faces.push_back(face);
					}

					// faces vector stores faces
					// stores data in format : { { { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }, { { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} } }
					// i.e a vector that stores vector of Faces
					faces_vector.push_back(faces);
					
					continue;
				}

				// material group
				if (subStrings[0] == "use_mtl" || subStrings[0] == "usemtl") {
					lastMaterialName = subStrings[1];
					continue;
				}

				// material file
				if (subStrings[0] == "mtlib") {
					// (TODO): load material
					continue;
				}

				// group data
				if (subStrings[0] == "g" || subStrings[0] == "o") {
					if (!faces_vector.empty()) {
						HMesh mesh;
						mesh.name = lastName;
						mesh.materialName = lastMaterialName;

						// sort vertex data

						m_meshes.push_back(mesh);
					}

					lastName = subStrings[1];
					faces_vector.clear();
					continue;
				}
			}
		}

		return true;
	}

	void HModel::Update()
	{

	}

	void HModel::Render()
	{

	}
}
