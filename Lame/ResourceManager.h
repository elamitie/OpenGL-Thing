#pragma once

#include "TextureCache.h"

namespace lame {

	class ResourceManager
	{
	public:
		static Texture getTexture(const std::string& filepath);

	private:
		static TextureCache mTextureCache;
	};

}