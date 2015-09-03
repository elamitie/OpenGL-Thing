#pragma once

#include "Vertex.h"
#include "ResourceManager.h"
#include <string>

namespace lame {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height, const std::string& texturePath);
		void Draw();

	private:
		float m_X;
		float m_Y;
		float m_Width;
		float m_Height;
		GLuint m_Vbo;
		Texture m_Texture;
	};

}

