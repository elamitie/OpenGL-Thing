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

		mSprites.push_back(new Sprite());
		mSprites.back()->init(0.0f, 0.0f, mWidth / 2, mWidth / 2, "Textures/jimmyjump/PNG/CharacterRight_Standing.png");

		mSprites.push_back(new Sprite()); 
		mSprites.back()->init(mWidth / 2, 0.0f, mWidth / 2, mWidth / 2, "Textures/jimmyjump/PNG/CharacterRight_Standing.png");

	}

	Engine::~Engine()
	{
		for (auto& s : mSprites)
			delete s;

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
		{
			mCamera.setPosition(mCamera.getPosition() + glm::vec2(0.0, 1.0));
		}
		else if (Keyboard::pressed(S))
		{
			mCamera.setPosition(mCamera.getPosition() + glm::vec2(0.0, -1.0));
		}
	}

	void Engine::draw()
	{
		mDisplay->clear();
		mColorShader.enable();
		glActiveTexture(GL_TEXTURE0);
		GLint textureLocation = mColorShader.getUniformLocation("tex");
		glUniform1i(textureLocation, 0);

		GLint projection = mColorShader.getUniformLocation("projectionMatrix");
		glm::mat4 cameraMatrix = mCamera.getCamMatrix();

		glUniformMatrix4fv(projection, 1, GL_FALSE, &(cameraMatrix[0][0]));

		for (auto& s : mSprites)
			s->draw();

		glBindTexture(GL_TEXTURE_2D, 0);
		mColorShader.disable();
		mDisplay->swapBuffers();
	}

}