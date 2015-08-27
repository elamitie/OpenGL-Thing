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
		float mX;
		float mY;
		float mWidth;
		float mHeight;
		GLuint mVbo;
		Texture mTexture;
	};

}

