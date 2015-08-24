#pragma once

#include <string>
#include "Texture.h"

class ImageLoader
{
public:
	static Texture loadPNG(std::string filepath);
};

