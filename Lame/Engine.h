#pragma once

#include <SDL/SDL.h>
#include "Display.h"
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include <vector>

namespace lame {

	class Engine
	{
	public:
		Engine(Display* display, double framerate);
		virtual ~Engine();

		void run();

	protected:
		virtual void update();
		virtual void render();
		void dispose();

	protected:
		Display*    m_display;
		double      m_frametime;
		int         m_width;
		int         m_height;
	};
}