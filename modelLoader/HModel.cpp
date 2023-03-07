#include "HModel.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
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
					// stores data in format : { { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }, { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} } }
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
				// NB: this logic is backlogged
				// the data before a given group at subStrings[0] is processed at this point
				if (subStrings[0] == "g" || subStrings[0] == "o") {
					if (!faces_vector.empty()) {
						HMesh mesh;
						mesh.name = lastName;
						mesh.materialName = lastMaterialName;

						// sort vertex data
						SortVertexData(mesh, rawMesh, faces_vector);

						m_meshes.push_back(mesh);
					}

					lastName = subStrings[1];
					faces_vector.clear();
					continue;
				}
			}
		}

		file.close();

		// since reading the data is backlogged
		// ensure any existing final is processed
		if (!faces_vector.empty()) {
			HMesh mesh;
			mesh.name = lastName;
			mesh.materialName = lastMaterialName;

			// sort vertex data
			SortVertexData(mesh, rawMesh, faces_vector);

			m_meshes.push_back(mesh);
		}

		return true;
	}

	void HModel::Update()
	{

	}

	void HModel::Render()
	{

	}

	/// <summary>
	///	SortVertexData: builds a mesh using the parsed faces data
	/// </summary>
	/// <param name="newMesh">: this is the mesh that holds the final results after sorting</param>
	/// <param name="oldMesh">: the positions textCoords normals of this mesh is used</param>
	/// <param name="faces_vector">: contains indices that helps define how a single position, textCoord and normal are related and can be read to define a mesh</param>
	void HModel::SortVertexData(HMesh& newMesh, const HMesh& oldMesh, const std::vector<HFace>& faces_vector)
	{
		unsigned int count;
		std::unordered_map<HVertexGroup, unsigned int, HashFunction> map;

		for (const HFace& faces : faces_vector) { // faces_vector: { 0:{ {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }, 1:{ {21, 123, 123}, {12, 34, 65}, {75, 32, 123} } }
			for (int i{}; i < 3; i++) { // faces: { 0:{21, 123, 123}, 1:{12, 34, 65}, 2:{75, 32, 123} }
				auto it = map.find(faces[i]); // does face: {21, 123, 123} exist in map

				if (it == map.end()) { // if face exists
					newMesh.vertices.push_back(oldMesh.vertices[faces[i].v]);
					newMesh.textCoords.push_back(oldMesh.textCoords[faces[i].t]);
					newMesh.normals.push_back(oldMesh.normals[faces[i].n]);
					newMesh.hvertices.push_back({
						oldMesh.vertices[faces[i].v], // position
						oldMesh.textCoords[faces[i].t], // textCoord
						oldMesh.normals[faces[i].n], // normal
						{ 1.0f, 1.0f, 1.0f, 1.0f } // color
					});

					newMesh.indices.push_back(count);

					map[faces[i]] = count;
					count++;
				}
				else {
					newMesh.indices.push_back(it->second);
				}
			}
		}
	}

	bool operator==(const HVertexGroup& lhsObj, const HVertexGroup& rhsObj)
	{
		return (lhsObj.v == rhsObj.v && lhsObj.t == rhsObj.t && lhsObj.n == rhsObj.n);
	}
};

