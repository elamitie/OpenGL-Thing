#pragma once

#include <string>
#include "Texture.h"

namespace lame {

	class ImageLoader
	{
	public:
		static Texture loadPNG(std::string filepath);
	};

}

