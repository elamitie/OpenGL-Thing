#include <iostream>
#include <Lame/Engine.h>
#include <Lame/OpenGLDisplay.h>

int main(int argc, char** argv)
{
	lame::Engine engine(new lame::OpenGLDisplay(800, 600, "OpenGL"), 60.0);
	engine.run();

	return 0;
}