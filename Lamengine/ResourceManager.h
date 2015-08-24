#pragma once

#include "TextureCache.h"

namespace lamengine {

	class ResourceManager
	{
	public:
		static Texture getTexture(const std::string& filepath);

	private:
		static TextureCache mTextureCache;
	};

}