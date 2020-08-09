#pragma once
#include "GLTexture.h"
#include <map>
#include <string>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string texturePath);

private:
	std::map<std::string, GLTexture> _textureMap;
};


class TextureLoader
{
public:
	static GLTexture getTexture(std::string texturePath);

private:
	static TextureCache _textureCache;
};

