#include "Keyboard.h"

namespace lame {

	bool Keyboard::mKeys[65536];
	std::vector<Key> Keyboard::mPressedKeys;

	Keyboard::Keyboard()
	{
		for (unsigned int i = 0; i < 65536; i++)
			mKeys[i] = false;
	}

	Keyboard::~Keyboard()
	{
	}

	void Keyboard::HandleKeyDown(const SDL_Event& ev)
	{
		mKeys[ev.key.keysym.scancode] = true;
	}

	void Keyboard::HandleKeyUp(const SDL_Event& ev)
	{
		mKeys[ev.key.keysym.scancode] = false;

		if (!mPressedKeys.empty() && std::find(mPressedKeys.begin(), mPressedKeys.end(), ev.key.keysym.scancode) != mPressedKeys.end())
			mPressedKeys.erase(std::find(mPressedKeys.begin(), mPressedKeys.end(), ev.key.keysym.scancode));
	}

	bool Keyboard::Pressed(Key key)
	{
		return mKeys[key];
	}

	bool Keyboard::Clicked(Key key)
	{
		bool p = Pressed(key);
		if (!p) return false;
		if (!mPressedKeys.empty() && std::find(mPressedKeys.begin(), mPressedKeys.end(), key) != mPressedKeys.end())
			return false;
		mPressedKeys.push_back(key);
		return true;
	}

}
