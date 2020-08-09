#include "IOfile.h"
#include <fstream>

bool IOfile::readToBuffer(std::string filename, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filename, std::ios::binary);
	if (file.fail())
	{
		perror(filename.c_str());
		return false;
	}

	//Go to the end of file
	file.seekg(0, std::ios::end);

	//Get size of file
	int size = file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce size by header
	size -= file.tellg();

	buffer.resize(size);
	file.read((char *)&(buffer[0]), size);
	file.close();

	return true;
}
