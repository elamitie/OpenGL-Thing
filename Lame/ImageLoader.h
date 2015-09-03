#pragma once

#include <string>
#include "Texture.h"

namespace lame {

	class ImageLoader
	{
	public:
		static Texture LoadPNG(std::string filepath);
	};

}

