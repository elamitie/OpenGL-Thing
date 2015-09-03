#include "Mouse.h"

namespace lame {

	int  Mouse::mX;
	int  Mouse::mY;
	int  Mouse::mButton;
	bool Mouse::mGrabbed = false;
	std::vector<unsigned int> Mouse::mClickedButtons;

	Mouse::Mouse()
	{
	}

	Mouse::~Mouse()
	{
	}

	bool Mouse::Clicked(unsigned int button)
	{
		bool clicked = mButton == button;
		if (!clicked) return false;
		if (!mClickedButtons.empty() && std::find(mClickedButtons.begin(), mClickedButtons.end(), button) != mClickedButtons.end())
			return false;
		mClickedButtons.push_back(button);
		return true;
	}

	int Mouse::GetDX()
	{
		// Temp
		return 800 / 2 - mX;
	}

	int Mouse::GetDY()
	{
		// Temp
		return 600 / 2 - mY;
	}

	int Mouse::GetMouseButton()
	{
		return mButton;
	}

	bool Mouse::MouseGrabbed()
	{
		return mGrabbed;
	}

	void Mouse::HandleMouseDown(const SDL_Event& ev)
	{
		mButton = ev.button.button;
	}

	void Mouse::HandleMouseUp(const SDL_Event& ev)
	{
		mButton = 0;
		if (!mClickedButtons.empty() && std::find(mClickedButtons.begin(), mClickedButtons.end(), ev.button.button) != mClickedButtons.end())
			mClickedButtons.erase(std::find(mClickedButtons.begin(), mClickedButtons.end(), ev.button.button));
	}

}
