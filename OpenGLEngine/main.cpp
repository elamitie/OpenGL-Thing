#include <iostream>
#include "Engine.h"
#include "OpenGLDisplay.h"

int main(int argc, char** argv)
{
	Engine engine(new OpenGLDisplay(800, 600, "OpenGL"), 60.0);
	engine.run();

	return 0;
}