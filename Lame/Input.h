#pragma once

#include <SDL/SDL.h>
#include <map>
#include <algorithm>
#include <iostream>

namespace lame {

	enum class MouseButton
	{
		MouseLeft = 1,
		MouseRight = 2,
		MouseMiddle = 3
	};

	class Input
	{
	public:
		Input(){};
		~Input(){};
		
		void clearKeyboard();
		void clearMouse();

		void handleKeyDown(const SDL_Event& ev);
		void handleKeyUp(const SDL_Event& ev);
		void handleMouseDown(const SDL_Event& ev);
		void handleMouseUp(const SDL_Event& ev);

		bool keyPressed(SDL_Scancode key);
		bool keyReleased(SDL_Scancode key);
		bool keyHeld(SDL_Scancode key);

		// TODO: Revisit this later??
		bool mousePressed(Uint8 button);
		bool mouseReleased(Uint8 button);
		bool mouseHeld(Uint8 button);

	private:
		std::map<SDL_Scancode, bool> m_pressed;
		std::map<SDL_Scancode, bool> m_released;
		std::map<SDL_Scancode, bool> m_held;

		std::map<Uint8, bool> m_mousePressed;
		std::map<Uint8, bool> m_mouseReleased;
		std::map<Uint8, bool> m_mouseHeld;
	};

}