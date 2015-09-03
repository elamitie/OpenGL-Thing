#include "Display.h"
#include "Error.h"

namespace lame {

	Display::Display(int width, int height, const std::string& title, unsigned int flags /* NONE */)
	{
		Uint32 _flags = SDL_WINDOW_OPENGL;

		m_Closed = false;
		m_Width = width;
		m_Height = height;
		m_Title = title;

		if (flags & INVISIBLE)
			_flags |= SDL_WINDOW_HIDDEN;
		if (flags & FULLSCREEN)
			_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (flags & BORDERLESS)
			_flags |= SDL_WINDOW_BORDERLESS;

		SDL_Init(SDL_INIT_EVERYTHING);

		m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, _flags);
		if (m_Window == nullptr)
			FatalError("Could not create SDL Window!");

		m_Context = SDL_GL_CreateContext(m_Window);
		if (m_Context == nullptr)
			FatalError("Could not create SDL GL Context!");

		GLenum error = glewInit();
		if (error != GLEW_OK)
			FatalError("Failed to initialize GLEW!");

		std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

		SDL_GL_SetSwapInterval(0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Display::~Display()
	{
		Dispose();
	}

	void Display::Update()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				m_Closed = true;
				break;
			case SDL_KEYDOWN:
				m_Keyboard.HandleKeyDown(e);
				break;
			case SDL_KEYUP:
				m_Keyboard.HandleKeyUp(e);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_Mouse.HandleMouseDown(e);
				break;
			case SDL_MOUSEBUTTONUP:
				m_Mouse.HandleMouseUp(e);
				break;
			}
		}
	}

	void Display::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void Display::Dispose()
	{
		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Display::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
