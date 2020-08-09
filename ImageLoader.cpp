#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOfile.h"
#include "errors.h"

GLTexture ImageLoader::loadimg(std::string filename)
{
	GLTexture texture = {};

	//input and output data for decodePNG()
	std::vector<unsigned char> input;
	std::vector<unsigned char> output;

	unsigned long width, height;

	//Read contents of image file into a buffer
	if (IOfile::readToBuffer(filename, input) == false)
		fatal("Error: Failed to load PNG file! - ImageLoader::loadimg() [ImageLoader.cpp]");

	//Decoding .png
	int error = decodePNG(output, width, height, &(input[0]), input.size());
	if (error != 0)
		fatal("Error: decodePNG failed width error " + std::to_string(error) + "  - ImageLoader::loadimg() [ImageLoader.cpp]");

	//Generate the openGL texture object
	glGenTextures(1, &(texture.id));

	//Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture.id);
	//Upload the pixels to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(output[0]));

	//Set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Generate the mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	//Return a copy of the texture data
	return texture;

}