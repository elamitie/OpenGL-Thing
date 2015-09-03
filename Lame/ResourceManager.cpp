#include "ResourceManager.h"

namespace lame {

	TextureCache ResourceManager::m_TextureCache;

	Texture ResourceManager::GetTexture(const std::string& filepath)
	{
		return m_TextureCache.GetTexture(filepath);
	}

}