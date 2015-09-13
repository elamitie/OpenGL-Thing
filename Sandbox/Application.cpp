#include "Application.h"

Application::Application(Display* display, double framerate)
	:Engine(display, framerate)
{
	camera.init(m_width, m_height);

	shader.compile("Shaders/basic_color.vert", "Shaders/basic_color.frag");
	shader.addAttribute("vertexPos");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.link();

	batch.init();
}

Application::~Application()
{
}

void Application::update()
{
	camera.update();
}

void Application::render()
{
	Texture texture = ResourceManager::getTexture("Textures/jimmyjump/PNG/CharacterRight_Standing.png");

	shader.enable();
	shader.setUniform("tex", 0);
	shader.setUniform("projectionMatrix", camera.getCamMatrix());

	batch.begin();
	batch.draw({ 0, 0, 50, 50 }, texture, 0, Color::white());
	batch.end();
	batch.renderBatches();

	shader.disable();
}
