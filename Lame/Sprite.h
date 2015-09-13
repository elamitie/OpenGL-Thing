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

		void init(float x, float y, float width, float height, const std::string& texturePath);
		void draw();

	private:
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		GLuint m_vbo;
		Texture m_texture;
	};

}

