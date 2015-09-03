#include "Engine.h"
#include "Keyboard.h"
#include "ImageLoader.h"
#include <iostream>

namespace lame {

	Engine::Engine(Display* display, double framerate)
		: m_Display(display)
	{
		m_Frametime = 1.0 / framerate;
		m_Width = display->GetWidth();
		m_Height = display->GetHeight();
		
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

	void Engine::Run()
	{
		int frames = 0;
		double unprocessedTime = 0.0;
		double frameCounterTime = 0.0;

		Uint32 previousTime = SDL_GetTicks();

		while (!m_Display->IsClosed())
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

			while (unprocessedTime > m_Frametime)
			{
				shouldRender = true;

				m_Display->Update();
				update();
				//m_Camera.Update();

				unprocessedTime -= m_Frametime;
			}

			if (shouldRender)
			{
				frames++;
				m_Display->Clear();
				render();
				m_Display->SwapBuffers();
			}
		}
	}

	void Engine::dispose()
	{
		m_Display->Dispose();
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