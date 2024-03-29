#ifndef __HTEXTURE_H__
#define __HTEXTURE_H__

#include <glad/glad.h>
#include <string>

namespace Hound {
	class Texture
	{
	public:
		struct TextureInfo {
			int width;
			int height;
			int internalFormat; // RGBA(png)/RGB(jpeg)
			int nrChannels;
		} mTextureInfo;

	public:
		Texture(const char*);
		~Texture();

		void activeTexture(int loc) const { glActiveTexture(GL_TEXTURE0 + loc); bind(); }
		void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); };
		void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };
		void setWrappingPropetires(int);

		// used to create GLTexture from a given texture file on hard disk
		static unsigned int TextureFromFile(const char*, const std::string&, bool = 0);

	private:
		unsigned int m_ID;
	};
}

#endif

