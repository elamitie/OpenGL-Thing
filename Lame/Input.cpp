#include "Input.h"

namespace lame {

	void Input::clearKeyboard()
	{
		m_pressed.clear();
		m_released.clear();
	}

	void Input::clearMouse()
	{
		m_mousePressed.clear();
		m_mouseReleased.clear();
	}

	void Input::handleKeyDown(const SDL_Event& ev)
	{
		m_pressed[ev.key.keysym.scancode] = true;
		m_held[ev.key.keysym.scancode] = true;
	}

	void Input::handleKeyUp(const SDL_Event& ev)
	{
		m_released[ev.key.keysym.scancode] = true;
		m_held[ev.key.keysym.scancode] = false;
	}

	void Input::handleMouseDown(const SDL_Event& ev)
	{
		m_mousePressed[ev.button.button] = true;
		m_mouseHeld[ev.button.button] = true;
	}

	void Input::handleMouseUp(const SDL_Event& ev)
	{
		m_mouseReleased[ev.button.button] = true;
		m_mouseHeld[ev.button.button] = false;
	}

	bool Input::keyPressed(SDL_Scancode key)
	{
		return m_pressed[key];
	}

	bool Input::keyReleased(SDL_Scancode key)
	{
		return m_released[key];
	}

	bool Input::keyHeld(SDL_Scancode key)
	{
		return m_held[key];
	}

	bool Input::mousePressed(Uint8 button)
	{
		return m_mousePressed[button];
	}

	bool Input::mouseReleased(Uint8 button)
	{
		return m_mouseReleased[button];
	}

	bool Input::mouseHeld(Uint8 button)
	{
		return m_mouseHeld[button];
	}

}
