#pragma once
#include "GLTexture.h"
#include <string>

class ImageLoader
{
public:
	static GLTexture loadimg(std::string filename);
};

