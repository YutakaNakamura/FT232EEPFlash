#include "stdafx.h"
#include "ShortCharConverter.h"

#include <vector>

ShortCharConverter::ShortCharConverter()
{
}


ShortCharConverter::~ShortCharConverter()
{
}


std::vector<unsigned char> ShortCharConverter::ShortToChar(const std::vector<unsigned short> &pShortVec) {
	ShortCharConvertUnion Converter;
	std::vector<unsigned char> charvec;

	for (const auto& e : pShortVec) {
		Converter.mShort = e;
		charvec.push_back(Converter.mChar[1]);
		charvec.push_back(Converter.mChar[0]);
	}

	return charvec;
}

std::vector<unsigned short> ShortCharConverter::CharToShort(const std::vector<unsigned char> &pCharVec) {
	ShortCharConvertUnion Converter;

	std::vector<unsigned short> shortvec;

	bool Odd = 1;
	for (const auto& e : pCharVec) {
		Converter.mChar[Odd] = e;
		if (!Odd) {
			shortvec.push_back(Converter.mShort);
		};
		Odd = !Odd;
	}

	return shortvec;

}