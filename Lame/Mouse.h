#pragma once

#include <SDL/SDL.h>
#include <vector>
#include <algorithm>

namespace lame {

	enum Button
	{
		LEFT = SDL_BUTTON_LEFT,
		RIGHT = SDL_BUTTON_RIGHT,
		MIDDLE = SDL_BUTTON_MIDDLE
	};

	class Mouse
	{
	public:
		Mouse();
		~Mouse();

		void handleMouseDown(const SDL_Event& ev);
		void handleMouseUp(const SDL_Event& ev);

		static bool clicked(unsigned int button);
		static int  getDX();
		static int  getDY();
		static int  getMouseButton();
		static bool mouseGrabbed();

	private:
		static std::vector<unsigned int> m_clickedButtons;
		static int						 m_x;
		static int						 m_y;
		static int						 m_button;
		static bool						 m_grabbed;
	};

}