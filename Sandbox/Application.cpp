#include "Application.h"

Application::Application(Display* display, double framerate)
	:Engine(display, framerate)
{
	camera.Init(m_Width, m_Height);

	shader.Compile("Shaders/basic_color.vert", "Shaders/basic_color.frag");
	shader.AddAttribute("vertexPos");
	shader.AddAttribute("vertexColor");
	shader.AddAttribute("vertexUV");
	shader.Link();

	batch.Init();
}

Application::~Application()
{
}

void Application::update()
{
	camera.Update();
}

void Application::render()
{
	static Texture texture = ResourceManager::GetTexture("Textures/jimmyjump/PNG/CharacterRight_Standing.png");

	shader.Enable();
	shader.SetUniform("tex", 0);
	shader.SetUniform("projectionMatrix", camera.GetCamMatrix());

	batch.Begin();
	batch.Draw({ 0, 0, 50, 50 }, { 0.0f, 0.0f, 1.0f, 1.0f }, texture.id, 0, Color::white());
	batch.End();
	batch.RenderBatches();

	shader.Disable();
}
