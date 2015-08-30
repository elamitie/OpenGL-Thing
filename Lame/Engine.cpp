#include "Engine.h"
#include "Keyboard.h"
#include "ImageLoader.h"
#include <iostream>

namespace lame {

	Engine::Engine(IDisplay* display, double framerate)
		: mDisplay(display)
	{
		mFrametime = 1.0 / framerate;
		mWidth = display->getWidth();
		mHeight = display->getHeight();
		
		mCamera.init(mWidth, mHeight);

		mColorShader.compile("Shaders/basic_color.vert", "Shaders/basic_color.frag");
		mColorShader.addAttribute("vertexPos");
		mColorShader.addAttribute("vertexColor");
		mColorShader.addAttribute("vertexUV");
		mColorShader.link();

		mBatch.init();
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
				mCamera.update();

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

		if (Keyboard::pressed(W))
			mCamera.setPosition(mCamera.getPosition() + glm::vec2( 0.0,  5.0));
		else if (Keyboard::pressed(S))
			mCamera.setPosition(mCamera.getPosition() + glm::vec2( 0.0, -5.0));
		else if (Keyboard::pressed(A))
			mCamera.setPosition(mCamera.getPosition() + glm::vec2(-5.0,  0.0));
		else if (Keyboard::pressed(D))
			mCamera.setPosition(mCamera.getPosition() + glm::vec2( 5.0,  0.0));
	}

	void Engine::draw()
	{
		mDisplay->clear();
		mColorShader.enable();
		glActiveTexture(GL_TEXTURE0);

		mColorShader.setUniform("tex", 0);
		mColorShader.setUniform("projectionMatrix", mCamera.getCamMatrix());

		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		static Texture tex = ResourceManager::getTexture("Textures/jimmyjump/PNG/CharacterRight_Standing.png");

		mBatch.begin();
		for (int i = 0; i < 800; i++)
		{
			mBatch.draw(glm::vec4(0, 0, 50, 50),
				glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
				tex.id,
				0.0f,
				color);
			mBatch.draw(glm::vec4(50, 0, 50, 50),
				glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
				tex.id,
				0.0f,
				color);
		}
		mBatch.end();
		mBatch.renderBatch();

		glBindTexture(GL_TEXTURE_2D, 0);
		mColorShader.disable();
		mDisplay->swapBuffers();
	}

}