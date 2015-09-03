#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

#include "Keyboard.h"
#include "Mouse.h"

namespace lame {

	enum DisplayFlags { NONE = 0x0, INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Display
	{
	public:
		Display(int width, int height, const std::string& title, unsigned int flags = 0x0);
		~Display();

		void Update();
		void SwapBuffers();
		void Dispose();
		void Clear();

		inline bool IsClosed()  { return m_Closed; }
		inline int  GetWidth()  { return m_Width; }
		inline int  GetHeight() { return m_Height; }

	private:
		bool          m_Closed;
		int           m_Width;
		int           m_Height;
		std::string   m_Title;
		SDL_Window*   m_Window;
		SDL_GLContext m_Context;
		Keyboard	  m_Keyboard;
		Mouse		  m_Mouse;
	};

}

