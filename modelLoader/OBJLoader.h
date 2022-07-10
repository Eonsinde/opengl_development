#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <glm/glm.hpp>
#include "Mesh.h"
#include "utils.h"


namespace Hound {
	std::vector<Vertex> loadObjMesh(const char* filePath) {
		// vertex data
		std::vector<glm::vec3> vertex_positions;
		std::vector<glm::vec3> vertex_normals;
		std::vector<glm::vec2> vertex_texCoords;
		// face indices
		std::vector<int> vertex_position_indices;
		std::vector<int> vertex_normal_indices;
		std::vector<int> vertex_texcoord_indices;
		// vertices
		std::vector<Vertex> vertices;

		//utils
		std::ifstream in_file{ filePath };
		std::stringstream sstream;
		std::string line{ "" };
		std::string prefix{ "" };
		std::string mtl_file_path;
		std::string temp_string;
		glm::vec3 temp_vec3;
		glm::vec2 temp_vec2;
		int temp_int{ };

		if (!in_file.is_open()) {
			std::cerr << "ERR::OBJLoader::Failed_to_perform_open_operation_on_file::" << filePath << "\n";
		}

		while (std::getline(in_file, line)) {
			sstream.clear();
			sstream.str(line);
			sstream >> prefix;

			if (prefix == "#") {

			}
			else if (prefix == "o") {
			
			}
			else if (prefix == "s") {

			}
			else if (prefix == "use_mtl" || prefix == "usemtl") {

			}
			else if (prefix == "mtllib") {
				// get the MTLlib file path  
				while (sstream >> temp_string) {
					mtl_file_path += temp_string;
				}

				// read MTL data
			}
			else if (prefix == "v") {
				sstream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_positions.push_back(temp_vec3);
			}
			else if (prefix == "vt") { // vertex_texCoord
				sstream >> temp_vec2.x >> temp_vec2.y;
				vertex_texCoords.push_back(temp_vec2);
			}
			else if (prefix == "vn") { // vertex_normal
				sstream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_positions.push_back(temp_vec3);
			}
			else if (prefix == "f") { // faces defined by indices
				// NB: 123/32/34 is returned in format 123, 32, 34 by the tokenize function
				//sstream >> temp_string;
				TokenVector actual_tokens;

				while (sstream >> temp_string) { // loops through "123/32/34 213/324/23 13/343/124" :- "123/32/34", "213/324/23"
					tokenize(temp_string, actual_tokens, "/"); // tokenizes 123/32/34 :- 123, 32, 34
					// we subtract one from each index here becos the indices start count from 1 and arrays use 0 not 1
					vertex_position_indices.push_back(atoi(actual_tokens[0])-1);
					vertex_texcoord_indices.push_back(atoi(actual_tokens[1])-1);
					vertex_normal_indices.push_back(atoi(actual_tokens[2])-1);
				}
			}
		}

		return vertices;
	}
}