#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

#include "IDisplay.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace lamengine {

	enum DisplayFlags { NONE = 0x0, INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class OpenGLDisplay : public IDisplay
	{
	public:
		OpenGLDisplay(int width, int height, const std::string& title, unsigned int flags = NONE);
		~OpenGLDisplay();

		void update() override;
		void swapBuffers() override;

		bool isClosed() override;
		void dispose() override;
		void clear() override;

	private:
		SDL_Window*    mWindow;
		SDL_GLContext  mContext;
		int			   mWidth;
		int			   mHeight;
		bool           mClosed;
		std::string    mTitle;
		Keyboard	   mKeyboard;
		Mouse		   mMouse;
	};

}