#pragma once

#include <vector>


union ShortCharConvertUnion {
	unsigned char mChar[2];
	unsigned short mShort;
};


class ShortCharConverter
{
public:
	ShortCharConverter();
	~ShortCharConverter();

	static std::vector<unsigned char> ShortToChar(const std::vector<unsigned short> &pShort);
	static std::vector<unsigned short> CharToShort(const std::vector<unsigned char> &pChar);
};

