#pragma once

#include "TextureCache.h"

class ResourceManager
{
public:
	static Texture getTexture(const std::string& filepath);

private:
	static TextureCache mTextureCache;
};