#pragma once

#include <GL/glew.h>

namespace lame {

	class Texture
	{
		friend class ImageLoader;
	public:
		Texture() : m_Width(0), m_Height(0), m_Texture(0) {}
		~Texture(){}

		void Bind();
		void Unbind();

		inline int    GetWidth()  { return m_Width;   }
		inline int    GetHeight() { return m_Height;  }
		inline GLuint GetID()     { return m_Texture; }

		inline void SetWidth(int width)   { m_Width = width;   }
		inline void SetHeight(int height) { m_Height = height; }

	private:
		int    m_Width;
		int    m_Height;
		GLuint m_Texture;
	};

}