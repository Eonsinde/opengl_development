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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        unsigned char* data = stbi_load(filePath, &mTextureInfo.width, &mTextureInfo.height, &mTextureInfo.nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureInfo.width, mTextureInfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
}

