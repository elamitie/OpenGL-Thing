#pragma once

#include "TextureCache.h"

namespace lame {

	class ResourceManager
	{
	public:
		static Texture GetTexture(const std::string& filepath);

	private:
		static TextureCache m_TextureCache;
	};

}