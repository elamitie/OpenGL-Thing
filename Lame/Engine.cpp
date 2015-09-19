#include "Engine.h"
#include "Input.h"
#include "ImageLoader.h"
#include <iostream>

namespace lame {

	Engine::Engine(Display* display, double framerate)
		: m_display(display)
	{
		m_frametime = 1.0 / framerate;
		m_width = display->getWidth();
		m_height = display->getHeight();
		m_input = new Input();
		
		//m_Camera.Init(m_Width, m_Height);

		//m_ColorShader.Compile("Shaders/basic_color.vert", "Shaders/basic_color.frag");
		//m_ColorShader.AddAttribute("vertexPos");
		//m_ColorShader.AddAttribute("vertexColor");
		//m_ColorShader.AddAttribute("vertexUV");
		//m_ColorShader.Link();

		//m_Batch.Init();
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

		while (!m_display->isClosed())
		{
			bool shouldRender = false;

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

			while (unprocessedTime > m_frametime)
			{
				shouldRender = true;

				m_input->clearKeyboard();
				m_input->clearMouse();
				m_display->update(m_input);
				update();

				unprocessedTime -= m_frametime;
			}

			if (shouldRender)
			{
				frames++;
				m_display->clear();
				render();
				m_display->swapBuffers();
			}
		}
	}

	void Engine::dispose()
	{
		m_display->dispose();
	}

	void Engine::update()
	{
		/*if (Keyboard::Pressed(W))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2( 0.0,  5.0));
			else if (Keyboard::Pressed(S))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2( 0.0, -5.0));
			else if (Keyboard::Pressed(A))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2(-5.0,  0.0));
			else if (Keyboard::Pressed(D))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2( 5.0,  0.0));*/
	}

	void Engine::render()
	{
		//m_ColorShader.Enable();
		//glActiveTexture(GL_TEXTURE0);

		//m_ColorShader.SetUniform("tex", 0);
		//m_ColorShader.SetUniform("projectionMatrix", m_Camera.GetCamMatrix());

		//static Texture tex = ResourceManager::GetTexture("Textures/jimmyjump/PNG/CharacterRight_Standing.png");

		//m_Batch.Begin();
		//m_Batch.Draw(glm::vec4(0, 0, 50, 50), 
		//			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		//			tex.id,
		//			0.0f,
		//			{ 255, 255, 255, 255 } /* Color Initialization C++11 */);
		//m_Batch.End();
		//m_Batch.RenderBatches();

		//glBindTexture(GL_TEXTURE_2D, 0);
		//m_ColorShader.Disable();
	}

}