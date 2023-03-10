#include "HModel.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"
#include "../renderer/VertexArray.h"
#include "../renderer/buffers/VertexBuffer.h"
#include "../renderer/buffers/IndexBuffer.h"
#include "../shaders/Shader.h"


namespace Hound {
	HModel::HModel()
	{

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
		// (TODO): drawMode
		int drawMode = 0; // 0 for triangles, 1 for quads

		TokenVector subStrings;
		subStrings.reserve(10);

		while (!file.eof()) {
			std::getline(file, line);
			subStrings.clear();

			if (!line.empty()) {
				tokenize(line, subStrings);

				// comments
				if (subStrings[0] == "#") {
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
				if (subStrings[0] == "vt") {
					rawMesh.textCoords.push_back(glm::vec2(
						std::stof(subStrings[1]),
						std::stof(subStrings[2])
					));
					continue;
				}

				// face data
				if (subStrings[0] == "f") {
					// subStrings format here: [f, 21/123/123, 12/34/65, 75/32/123]

					HFace face; // stores data in format: { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }
					TokenVector numbers;
					numbers.reserve(10);
				
					if (subStrings.size() > 4) { // set draw mode to Quad
						for (int i = 1; i <= 4; i++) {
							numbers.clear();
							HVertexGroup vertexGroup;

							// tokenize subString content: 21/123/123
							tokenize(subStrings[i], numbers, "/");

							// store derived tokens in face
							vertexGroup.v = std::stoi(numbers[0]) - 1;
							vertexGroup.t = std::stoi(numbers[1]) - 1;
							vertexGroup.n = std::stoi(numbers[2]) - 1;

							face.push_back(vertexGroup);
						}
					}
					else { // set draw mode to triangle
						for (int i = 1; i <= 3; i++) {
							numbers.clear();
							HVertexGroup vertexGroup;

							// tokenize subString content: 21/123/123
							tokenize(subStrings[i], numbers, "/");

							// store derived tokens in face
							vertexGroup.v = std::stoi(numbers[0]) - 1;
							vertexGroup.t = std::stoi(numbers[1]) - 1;
							vertexGroup.n = std::stoi(numbers[2]) - 1;

							face.push_back(vertexGroup);
						}
					}
					

					// face vector stores face
					// stores data in format : { { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }, { {21, 123, 123}, {12, 34, 65}, {75, 32, 123} } }
					// i.e a vector that stores vector of face
					faces_vector.push_back(face);
					
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

				/*if (subStrings[0] == "s") {
					if (subStrings[1] == "off") {
						std::cout << "Not using triangles\n";
						groupNumber = subStrings[1];
					}
					else {
						std::cout << "Using triangles\n";
						groupNumber = subStrings[1];
					}
				}*/

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
						// set up the mesh's data in the GPU
						mesh.SetupMesh();
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
			// set up the mesh's data in the GPU
			mesh.SetupMesh();
			m_meshes.push_back(mesh);
		}

		std::cout << "HModel::Sucessfully loaded model\n";
		return true;
	}

	void HModel::Update()
	{

	}

	void HModel::Render(Shader& shader)
	{
		shader.setMat4fv("uModel", glm::value_ptr(Entity::GetTransform().GetMatrix()));
		shader.setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.6f)));

		if (m_meshes.size()) {
			// call the draw method for each mesh that makes up the model
			for (int i{}; i < m_meshes.size(); i++) {
				m_meshes[i].Draw(shader);
			}
		}
	}

	void HModel::Print()
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
		unsigned int count{};
		std::unordered_map<HVertexGroup, unsigned int, HashFunction> map;
		std::unordered_map<int, unsigned int> test_map;

		for (const HFace& face : faces_vector) { // faces_vector: { 0:{ {21, 123, 123}, {12, 34, 65}, {75, 32, 123} }, 1:{ {21, 123, 123}, {12, 34, 65}, {75, 32, 123} } }
			for (int i{}; i < face.size(); i++) { // face: { 0:{21, 123, 123}, 1:{12, 34, 65}, 2:{75, 32, 123} }
				auto it = map.find(face[i]); // does point: {21, 123, 123} exist in map
				auto test_it = test_map.find(face[i].v); // does point.v: 21 exist in map

				if (test_it == test_map.end()) {
					std::cout << "Not in map: " << face[i].v << " :: " << count << ", adding to map\n";

					newMesh.vertices.push_back(oldMesh.vertices[face[i].v]);
					newMesh.textCoords.push_back(oldMesh.textCoords[face[i].t]);
					newMesh.normals.push_back(oldMesh.normals[face[i].n]);

					newMesh.hvertices.push_back({
						oldMesh.vertices[face[i].v], // position
						oldMesh.textCoords[face[i].t], // textCoord
						oldMesh.normals[face[i].n], // normal
						{ 1.0f, 1.0f, 1.0f, 1.0f } // color
					});

					newMesh.indices.push_back(count);
					test_map[face[i].v] = count;
					count++;
				}
				else {
					std::cout << "Present in map: " << face[i].v << " :: " << test_it->second << ", adding to map\n";
					newMesh.indices.push_back(test_it->second);
				}

				//if (it == map.end()) { // if face exists
				//	std::cout << count << " - Not in map, adding to map\n";
				//	newMesh.vertices.push_back(oldMesh.vertices[face[i].v]);
				//	newMesh.textCoords.push_back(oldMesh.textCoords[face[i].t]);
				//	newMesh.normals.push_back(oldMesh.normals[face[i].n]);
				//	//HVertex temp = {
				//	//	oldMesh.vertices[face[i].v], // position
				//	//	oldMesh.textCoords[face[i].t], // textCoord
				//	//	oldMesh.normals[face[i].n], // normal
				//	//	{ 1.0f, 1.0f, 1.0f, 1.0f } // color
				//	//};
				//	//std::cout << temp << "\n";
				//	newMesh.hvertices.push_back({
				//		oldMesh.vertices[face[i].v], // position
				//		oldMesh.textCoords[face[i].t], // textCoord
				//		oldMesh.normals[face[i].n], // normal
				//		{ 1.0f, 1.0f, 1.0f, 1.0f } // color
				//	});
				//	newMesh.indices.push_back(count);
				//	map[face[i]] = count;
				//	count++;
				//}
				//else {
				//	std::cout << "Present in map, adding to map\n";
				//	newMesh.indices.push_back(it->second);
				//}
			}

			// set the draw mode for the mesh
			if (face.size() > 3) {
				newMesh.drawMode = 1; // QUAD                                                                                                                                                                                                                                                                                                                                                                                                                           
			}
			else {
				newMesh.drawMode = 0; // TRIANGLE
			}
		}
	}

	// create VAO and VBO for a given mesh
	void HMesh::SetupMesh()
	{
		m_VAO = new VertexArray();
		m_VBO = new VertexBuffer();

		if (drawMode == 0) { // triangle
			m_EBO = new IndexBuffer();

			m_VBO->Set(vertices, VERTEX_ATTRIB::VA_POSITION);
			m_EBO->Set(indices);

			m_VAO->RegisterBuffer(*m_VBO);
			m_VAO->RegisterBuffer(*m_EBO);
		}
		else if (drawMode == 1) {
			m_VBO->Set(hvertices, VERTEX_ATTRIB::VA_POS_TEXCOORD_NORMAL_COLOR);

			m_VAO->RegisterBuffer(*m_VBO);
		}
	}

	void HMesh::Draw(Shader& shader)
	{
		switch (drawMode) {
		case 1:
			m_VAO->Bind();
			glDrawArrays(GL_LINE_LOOP, 0, hvertices.size());
			m_VAO->Unbind();
			return;

		case 0:
		default:
			m_VAO->Bind();
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
			m_VAO->Unbind();
			return;
		}
	}

	// function used to logged an HVertex instance props
	std::ostream& operator<<(std::ostream& os, const HVertex obj)
	{
		os << "position: { " << obj.position.x << " " << obj.position.y << " " << obj.position.z << " }, "
			<< "texCoord: { " << obj.textCoord.x << " " << obj.textCoord.y << " }, "
			<< "normal: { " << obj.normal.x << " " << obj.normal.y << " " << obj.normal.z << " }, "
			<< "color: { " << obj.colors.x << " " << obj.colors.y << " " << obj.colors.z << " }" << "\n";

		return os;
	}

	bool operator==(const HVertexGroup& lhsObj, const HVertexGroup& rhsObj)
	{
		return (lhsObj.v == rhsObj.v && lhsObj.t == rhsObj.t && lhsObj.n == rhsObj.n);
	}
};

