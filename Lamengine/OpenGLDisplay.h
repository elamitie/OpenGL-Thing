#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

#include "IDisplay.h"
#include "Keyboard.h"
#include "Mouse.h"

class OpenGLDisplay : public IDisplay
{
public:
	OpenGLDisplay(int width, int height, const std::string& title);
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