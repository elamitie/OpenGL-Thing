#include "TextureCache.h"
#include "ImageLoader.h"

namespace lame {

	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::getTexture(const std::string& filepath)
	{
		auto iterator = m_textureMap.find(filepath);

		if (iterator == m_textureMap.end())
		{
			Texture tex = ImageLoader::loadPNG(filepath);
			m_textureMap.insert(std::make_pair(filepath, tex));
			return tex;
		}

		return iterator->second;
	}

}