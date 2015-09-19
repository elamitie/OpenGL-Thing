#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

#include "Input.h"

namespace lame {

	enum DisplayFlags { NONE = 0x0, INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Display
	{
	public:
		Display(int width, int height, const std::string& title, unsigned int flags = 0x0);
		~Display();

		void update(Input* input);
		void swapBuffers();
		void dispose();
		void clear();

		inline bool isClosed()  { return m_closed; }
		inline int  getWidth()  { return m_width; }
		inline int  getHeight() { return m_height; }

	private:
		bool          m_closed;
		int           m_width;
		int           m_height;
		std::string   m_title;
		SDL_Window*   m_window;
		SDL_GLContext m_context;
	};

}

