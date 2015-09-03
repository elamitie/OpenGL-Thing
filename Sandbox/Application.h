#pragma once

#include <Lame/Engine.h>
using namespace lame;

class Application : public Engine
{
public:
	Application(Display* display, double framerate);
	~Application();

protected:
	void update() override;
	void render() override;

private:
	SpriteBatch batch;
	Camera2D camera;
	Shader shader;
};

