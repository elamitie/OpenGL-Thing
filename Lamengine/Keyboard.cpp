#include "Keyboard.h"

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

void Keyboard::handleKeyDown(const SDL_Event& ev)
{
	mKeys[ev.key.keysym.scancode] = true;
}

void Keyboard::handleKeyUp(const SDL_Event& ev)
{
	mKeys[ev.key.keysym.scancode] = false;

	if (!mPressedKeys.empty() && std::find(mPressedKeys.begin(), mPressedKeys.end(), ev.key.keysym.scancode) != mPressedKeys.end())
		mPressedKeys.erase(std::find(mPressedKeys.begin(), mPressedKeys.end(), ev.key.keysym.scancode));
}

bool Keyboard::pressed(Key key)
{
	return mKeys[key];
}

bool Keyboard::clicked(Key key)
{
	bool p = pressed(key);
	if (!p) return false;
	if (!mPressedKeys.empty() && std::find(mPressedKeys.begin(), mPressedKeys.end(), key) != mPressedKeys.end())
		return false;
	mPressedKeys.push_back(key);
	return true;
}
