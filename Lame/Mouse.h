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

		void HandleMouseDown(const SDL_Event& ev);
		void HandleMouseUp(const SDL_Event& ev);

		static bool Clicked(unsigned int button);
		static int  GetDX();
		static int  GetDY();
		static int  GetMouseButton();
		static bool MouseGrabbed();

	private:
		static std::vector<unsigned int> mClickedButtons;
		static int						 mX;
		static int						 mY;
		static int						 mButton;
		static bool						 mGrabbed;
	};

}