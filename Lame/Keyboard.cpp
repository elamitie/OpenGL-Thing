#include "Keyboard.h"

namespace lame {

	bool Keyboard::m_keys[65536];
	std::vector<Key> Keyboard::m_pressedKeys;

	Keyboard::Keyboard()
	{
		for (unsigned int i = 0; i < 65536; i++)
			m_keys[i] = false;
	}

	Keyboard::~Keyboard()
	{
	}

	void Keyboard::handleKeyDown(const SDL_Event& ev)
	{
		m_keys[ev.key.keysym.scancode] = true;
	}

	void Keyboard::handleKeyUp(const SDL_Event& ev)
	{
		m_keys[ev.key.keysym.scancode] = false;

		if (!m_pressedKeys.empty() && std::find(m_pressedKeys.begin(), m_pressedKeys.end(), ev.key.keysym.scancode) != m_pressedKeys.end())
			m_pressedKeys.erase(std::find(m_pressedKeys.begin(), m_pressedKeys.end(), ev.key.keysym.scancode));
	}

	bool Keyboard::pressed(Key key)
	{
		return m_keys[key];
	}

	bool Keyboard::clicked(Key key)
	{
		bool p = pressed(key);
		if (!p) return false;
		if (!m_pressedKeys.empty() && std::find(m_pressedKeys.begin(), m_pressedKeys.end(), key) != m_pressedKeys.end())
			return false;
		m_pressedKeys.push_back(key);
		return true;
	}

}
