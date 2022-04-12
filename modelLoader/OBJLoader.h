#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <glm/glm.hpp>
#include "./Vertex.h"


namespace Hound {
	typedef std::vector<const char*> TokenVector;

	TokenVector tokenize(std::string s, std::string del=" ") // sentence and delimiter
	{
		TokenVector tokens;
		int start = 0;
		int end = s.find(del);
		while (end != -1) {
			std::cout << s.substr(start, end - start) << std::endl;
			tokens.push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size();
			end = s.find(del, start); // find delimiter again by setting start position
		}
		std::cout << s.substr(start, end - start);
		tokens.push_back(s.substr(start, end - start).c_str());

		return tokens;
	}

	std::vector<Vertex> loadMesh(const char* filePath) {
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

		std::stringstream sstream;
		std::ifstream in_file{ filePath };
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
				// get what is left in stream 
				mtl_file_path = sstream.str();
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
					actual_tokens = tokenize(temp_string, "/"); // tokenizes 123/32/34 :- 123, 32, 34
					vertex_position_indices.push_back(atoi(actual_tokens[0]));
					vertex_texcoord_indices.push_back(atoi(actual_tokens[1]));
					vertex_normal_indices.push_back(atoi(actual_tokens[2]));
				}
			}
		}

		return vertices;
	}
}