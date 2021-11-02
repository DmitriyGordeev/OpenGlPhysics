#pragma once
#include "GLTexture.h"
#include <map>
#include <string>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(const std::string& texturePath);

private:
	std::map<std::string, GLTexture> _textureMap;
};


class TextureLoader
{
public:
	static GLTexture getTexture(const std::string& texturePath);

private:
	static TextureCache _textureCache;
};

