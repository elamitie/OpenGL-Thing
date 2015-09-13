#pragma once

#include <GL/glew.h>

namespace lame {

	class Texture
	{
		friend class ImageLoader;
	public:
		Texture() : m_width(0), m_height(0), m_texture(0) {}
		~Texture(){}

		void bind();
		void unbind();

		inline int    getWidth()  { return m_width;   }
		inline int    getHeight() { return m_height;  }
		inline GLuint getID()     { return m_texture; }

		inline void setWidth(int width)   { m_width = width;   }
		inline void setHeight(int height) { m_height = height; }

	private:
		int    m_width;
		int    m_height;
		GLuint m_texture;
	};

}