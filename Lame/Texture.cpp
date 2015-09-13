#include "Texture.h"

namespace lame {

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}