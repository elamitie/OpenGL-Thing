#include "ResourceManager.h"

namespace lame {

	TextureCache ResourceManager::mTextureCache;

	Texture ResourceManager::getTexture(const std::string& filepath)
	{
		return mTextureCache.getTexture(filepath);
	}

}