#include "OpenGLDisplay.h"
#include <iostream>

OpenGLDisplay::OpenGLDisplay(int width, int height, const std::string& title)
{
	mWidth = width;
	mHeight = height;
	mTitle = title;

	// TODO: Handle errors
	SDL_Init(SDL_INIT_EVERYTHING);

	mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_OPENGL);
	if (mWindow == nullptr)
		std::cout << "Fatal: Could not create SDL Window" << std::endl;

	mContext = SDL_GL_CreateContext(mWindow);
	if (mContext == nullptr)
		std::cout << "Fatal: Could not create GL Context" << std::endl;

	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "Failed to initialize glew!" << std::endl;

	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

OpenGLDisplay::~OpenGLDisplay()
{
	dispose();
}

void OpenGLDisplay::update()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mClosed = true;
			break;
		case SDL_KEYDOWN:
			mKeyboard.handleKeyDown(e);
			break;
		case SDL_KEYUP:
			mKeyboard.handleKeyUp(e);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mMouse.handleMouseDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			mMouse.handleMouseUp(e);
			break;
		}
	}
}

void OpenGLDisplay::swapBuffers()
{
	SDL_GL_SwapWindow(mWindow);
}

bool OpenGLDisplay::isClosed()
{
	return mClosed;
}

void OpenGLDisplay::dispose()
{
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void OpenGLDisplay::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

