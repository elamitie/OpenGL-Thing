#include "Mouse.h"

namespace lame {

	int  Mouse::m_x;
	int  Mouse::m_y;
	int  Mouse::m_button;
	bool Mouse::m_grabbed = false;
	std::vector<unsigned int> Mouse::m_clickedButtons;

	Mouse::Mouse()
	{
	}

	Mouse::~Mouse()
	{
	}

	bool Mouse::clicked(unsigned int button)
	{
		bool clicked = m_button == button;
		if (!clicked) return false;
		if (!m_clickedButtons.empty() && std::find(m_clickedButtons.begin(), m_clickedButtons.end(), button) != m_clickedButtons.end())
			return false;
		m_clickedButtons.push_back(button);
		return true;
	}

	int Mouse::getDX()
	{
		// Temp
		return 800 / 2 - m_x;
	}

	int Mouse::getDY()
	{
		// Temp
		return 600 / 2 - m_y;
	}

	int Mouse::getMouseButton()
	{
		return m_button;
	}

	bool Mouse::mouseGrabbed()
	{
		return m_grabbed;
	}

	void Mouse::handleMouseDown(const SDL_Event& ev)
	{
		m_button = ev.button.button;
	}

	void Mouse::handleMouseUp(const SDL_Event& ev)
	{
		m_button = 0;
		if (!m_clickedButtons.empty() && std::find(m_clickedButtons.begin(), m_clickedButtons.end(), ev.button.button) != m_clickedButtons.end())
			m_clickedButtons.erase(std::find(m_clickedButtons.begin(), m_clickedButtons.end(), ev.button.button));
	}

}
