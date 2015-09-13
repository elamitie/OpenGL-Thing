#include "ResourceManager.h"

namespace lame {

	TextureCache ResourceManager::m_textureCache;

	Texture ResourceManager::getTexture(const std::string& filepath)
	{
		return m_textureCache.getTexture(filepath);
	}

}