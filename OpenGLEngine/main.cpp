#include <iostream>
#include <Lamengine/Engine.h>
#include <Lamengine/OpenGLDisplay.h>

int main(int argc, char** argv)
{
	lamengine::Engine engine(new lamengine::OpenGLDisplay(800, 600, "OpenGL"), 60.0);
	engine.run();

	return 0;
}