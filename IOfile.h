#pragma once
#include <vector>
#include <string>

class IOfile
{
public:
	static bool readToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
};

