#include "Engine.h"
#include "Keyboard.h"
#include <iostream>

Engine::Engine(IDisplay* display, double framerate)
: mDisplay(display)
{
	mFrametime = 1.0 / framerate;
		
	mColorShader.compile("Shaders/basic_color.vert", "Shaders/basic_color.frag");
	mColorShader.addAttribute("vertexPos");
	mColorShader.addAttribute("vertexColor");
	mColorShader.link();

	mSprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
}

Engine::~Engine()
{
	dispose();
}

void Engine::run()
{
	int frames = 0;
	double unprocessedTime = 0.0;
	double frameCounterTime = 0.0;

	Uint32 previousTime = SDL_GetTicks();

	while (!mDisplay->isClosed())
	{
		bool render = false;

		Uint32 currentTime = SDL_GetTicks();
		Uint32 passedTime = currentTime - previousTime;
		previousTime = currentTime;

		unprocessedTime += passedTime / 1000.0;
		frameCounterTime += passedTime / 1000.0;

		if (frameCounterTime >= 1.0f)
		{
			std::cout << frames << " fps" << std::endl;
			frames = 0;
			frameCounterTime = 0.0;
		}

		while (unprocessedTime > mFrametime)
		{
			render = true;

			update();

			unprocessedTime -= mFrametime;
		}

		if (render)
		{
			frames++;
			draw();
		}
	}
}

void Engine::dispose()
{
	mDisplay->dispose();
}

void Engine::update()
{
	mDisplay->update();
}

void Engine::draw()
{
	mDisplay->clear();
	mColorShader.enable();
	mSprite.draw();
	mColorShader.disable();
	mDisplay->swapBuffers();
}