#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <stb_image/stb_image.h>


namespace Hound {
	// Defined type to hold tokens
	typedef std::vector<const char*> TokenVector;

	// sentence and delimiter
	TokenVector tokenize(std::string s, std::string del=" ") 
	{ 
		TokenVector tokens;
		int start = 0;
		int end = s.find(del); 
		while (end != -1) {
			std::cout << s.substr(start, end - start) << std::endl;
			tokens.push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size(); // move forward by delimiter size
			end = s.find(del, start); // find delimiter again by setting start position
		}
		std::cout << s.substr(start, end - start);
		tokens.push_back(s.substr(start, end - start).c_str());

		return tokens;
	}

	// sentence,(reference)where to store tokens and delimiter
	void tokenize(std::string s, TokenVector& pTokens, std::string del=" ") 
	{
		// this is a more optimized version 
		int start = 0;
		int end = s.find(del);
		while (end != -1) {
			pTokens.push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size();
			end = s.find(del, start); // find delimiter again by setting start position
		}
		pTokens.push_back(s.substr(start, end - start).c_str());
	}

	// sentence, (ptr)where to store tokens and delimiter
	void tokenize(std::string s, TokenVector* pTokens, std::string del=" ") 
	{
		// this is a more optimized version 
		int start = 0;
		int end = s.find(del);
		while (end != -1) {
			pTokens->push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size();
			end = s.find(del, start); // find delimiter again by setting start position
		}
		pTokens->push_back(s.substr(start, end - start).c_str());
	}

	// loading textures
	unsigned int TextureFromFile(const char* pFileName, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(pFileName);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << pFileName << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}
}
