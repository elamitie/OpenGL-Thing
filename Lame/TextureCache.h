#pragma once

#include "Texture.h"
#include <map>

namespace lame {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Texture getTexture(const std::string& filepath);

	private:
		std::map<std::string, Texture> mTextureMap;
	};

}