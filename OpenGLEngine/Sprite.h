#pragma once

#include "Vertex.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);
	void draw();

private:
	float mX;
	float mY;
	float mWidth;
	float mHeight;
	GLuint mVbo;
};

