#include "TextureCache.h"
#include "ImageLoader.h"

namespace lame {

	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::GetTexture(const std::string& filepath)
	{
		auto iterator = m_TextureMap.find(filepath);

		if (iterator == m_TextureMap.end())
		{
			Texture tex = ImageLoader::LoadPNG(filepath);
			m_TextureMap.insert(std::make_pair(filepath, tex));
			return tex;
		}

		return iterator->second;
	}

}