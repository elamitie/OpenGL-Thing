#include "Texture.h"

namespace lame {

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}