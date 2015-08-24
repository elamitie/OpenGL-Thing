#include "TextureCache.h"
#include "ImageLoader.h"

namespace lamengine {

	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::getTexture(const std::string& filepath)
	{
		auto iterator = mTextureMap.find(filepath);

		if (iterator == mTextureMap.end())
		{
			Texture tex = ImageLoader::loadPNG(filepath);
			mTextureMap.insert(std::make_pair(filepath, tex));
			return tex;
		}

		return iterator->second;
	}

}