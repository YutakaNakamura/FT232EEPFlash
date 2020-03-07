#pragma once

#include <string>
#include <vector>

class FileUtil
{
public:
	FileUtil();
	~FileUtil();

	static bool WriteBinary(const std::string &filename, const std::vector<unsigned char> &pCharVec);
	static bool ReadBinary(const std::string &filename, std::vector<unsigned char> &pOutputVec);

};

