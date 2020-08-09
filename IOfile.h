#pragma once
#include <vector>
#include <string>

class IOfile
{
public:
	static bool readToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

