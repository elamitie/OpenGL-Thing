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
		~Engine();

		void Run();

	private:
		virtual void update();
		virtual void render();
		void dispose();

		Display*    m_Display;
		double      m_Frametime;
		int         m_Width;
		int         m_Height;
		Shader      m_ColorShader;
		Camera2D    m_Camera;
		SpriteBatch	m_Batch;
	};
}