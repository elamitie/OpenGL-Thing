#include "Display.h"
#include "Error.h"

namespace lame {

	Display::Display(int width, int height, const std::string& title, unsigned int flags /* NONE */)
	{
		Uint32 _flags = SDL_WINDOW_OPENGL;

		m_closed = false;
		m_width = width;
		m_height = height;
		m_title = title;

		if (flags & INVISIBLE)
			_flags |= SDL_WINDOW_HIDDEN;
		if (flags & FULLSCREEN)
			_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (flags & BORDERLESS)
			_flags |= SDL_WINDOW_BORDERLESS;

		SDL_Init(SDL_INIT_EVERYTHING);

		m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, _flags);
		if (m_window == nullptr)
			fatalError("Could not create SDL Window!");

		m_context = SDL_GL_CreateContext(m_window);
		if (m_context == nullptr)
			fatalError("Could not create SDL GL Context!");

		GLenum error = glewInit();
		if (error != GLEW_OK)
			fatalError("Failed to initialize GLEW!");

		std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

		SDL_GL_SetSwapInterval(0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Display::~Display()
	{
		dispose();
	}

	void Display::update()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				m_closed = true;
				break;
			case SDL_KEYDOWN:
				m_keyboard.handleKeyDown(e);
				break;
			case SDL_KEYUP:
				m_keyboard.handleKeyUp(e);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_mouse.handleMouseDown(e);
				break;
			case SDL_MOUSEBUTTONUP:
				m_mouse.handleMouseUp(e);
				break;
			}
		}
	}

	void Display::swapBuffers()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Display::dispose()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Display::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
