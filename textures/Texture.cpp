#include "Texture.h"

#include <iostream>
#include <stb_image/stb_image.h>


namespace Hound {
	Texture::Texture(const char* filePath)
		: m_ID{ } {
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID); 
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filePath, &mTextureInfo.width, &mTextureInfo.height, &mTextureInfo.nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (mTextureInfo.nrChannels == 1)
                format = GL_RED;
            else if (mTextureInfo.nrChannels == 3)
                format = GL_RGB;
            else if (mTextureInfo.nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, mTextureInfo.width, mTextureInfo.height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "ERR::Failed_to_load_texture\n";
        }
        stbi_image_free(data);
        unbind();
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_ID);
	}

	void Texture::setWrappingPropetires(int wrapBehaviour)
	{
		this->bind();
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapBehaviour); // set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapBehaviour);
		this->unbind();
	}

	unsigned int Texture::TextureFromFile(const char* pFileName, const std::string& directory, bool gamma)
	{
		std::string filePath = directory + '/' + std::string(pFileName); // e.g assets/girl_model/textures/diffuse_material.png

		// create a GLtexture based on the texture for the mesh
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
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
			std::cout << "Texture failed to load at path: " << filePath << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}
}

