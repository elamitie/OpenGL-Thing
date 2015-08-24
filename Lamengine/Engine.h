#pragma once

#include <SDL/SDL.h>
#include "IDisplay.h"
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

namespace lamengine {

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

		IDisplay*              mDisplay;
		double	               mFrametime;
		Sprite                 mSprite;
		std::vector<Sprite*>   mSprites;
		Shader	               mColorShader;
	};
}