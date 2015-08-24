#pragma once

#include <string>
#include "Texture.h"

namespace lamengine {

	class ImageLoader
	{
	public:
		static Texture loadPNG(std::string filepath);
	};

}

