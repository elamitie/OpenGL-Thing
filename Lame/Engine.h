#pragma once

#include <SDL/SDL.h>
#include "IDisplay.h"
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera2D.h"
#include <vector>

namespace lame {

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
		int					   mWidth;
		int					   mHeight;
		Sprite                 mSprite;
		std::vector<Sprite*>   mSprites;
		Shader	               mColorShader;
		Camera2D			   mCamera;
	};
}