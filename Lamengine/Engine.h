#pragma once

#include <SDL/SDL.h>
#include "IDisplay.h"
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

using namespace std;

class Engine
{
public:
	Engine(IDisplay* display, double framerate);
	~Engine();

	void run();
	void dispose();

private:
	void update();
	void draw();

	IDisplay*         mDisplay;
	double	          mFrametime;
	Sprite            mSprite;
	vector<Sprite*>   mSprites;
	Shader	          mColorShader;
};