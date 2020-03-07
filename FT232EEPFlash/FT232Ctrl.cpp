#include "stdafx.h"
#include "FT232Ctrl.hpp"


#include <windows.h>
#pragma comment(lib, "FTD2XX.lib")
#include "FTD2XX.h"

#include <vector>
#include <iostream>

#include "ShortCharConverter.h"

FT232Ctrl::FT232Ctrl()
{
}


FT232Ctrl::~FT232Ctrl()
{
}

bool FT232Ctrl::Open() {

	mFtStatus = FT_Open(0, &mFtHandle);
	if (mFtStatus != FT_OK)
	{
		printf("FT_Open failed.\n");
		exit(1);

		return 1;
	}

	return 0;
}

bool FT232Ctrl::Close() {
	FT_Close(mFtHandle);
	return 0;
}

bool FT232Ctrl::ReadEEPROM(std::vector<unsigned char> &pROMData) {
	
	unsigned short readData;
	std::vector<unsigned short> readDataVec;
	for (int i = 0; i < 128; i++) {
		if (FT_ReadEE(mFtHandle, i, &readData) != FT_OK) {
			perror("FT_ReadEE");
			return 1;
		}
		printf("%04X%c", readData, i % 8 == 7 ? '\n' : ' ');
		readDataVec.push_back(readData);
	}

	pROMData = ShortCharConverter::ShortToChar(readDataVec);

	return 0;
}

bool FT232Ctrl::WriteEEPROM(const std::vector<unsigned char> &pWriteData) {

	std::vector<unsigned short> inputshortvec;

	inputshortvec = ShortCharConverter::CharToShort(pWriteData);

	if (inputshortvec.size() != 128) {
		return 1;
	}

	//EEPWRITE
	for (int i = 0; i < 128; i++) {

		if (FT_WriteEE(mFtHandle, i, inputshortvec.at(i)) != FT_OK) {
			perror("FT_WriteEE");
			return 1;
		}

	}

	return 0;
}

bool FT232Ctrl::WriteEEPROMwithChecksum(const std::vector<unsigned char> &pWriteData) {

	std::vector<unsigned char> calculatedData = CheckSum(pWriteData);

	WriteEEPROM(calculatedData);

	return 0;
}


std::vector<unsigned char> FT232Ctrl::CheckSum(const std::vector<unsigned char> &pCharVec) {
	uint8_t buf[256];
	int size = sizeof(buf);
	unsigned short checksum, value;

	// calculate checksum
	checksum = 0xAAAA;

	for (int i = 0; i < size / 2 - 1; i++)
	{
		value = pCharVec.at(i * 2);
		value += pCharVec.at((i * 2) + 1) << 8;

		checksum = value ^ checksum;
		checksum = (checksum << 1) | (checksum >> 15);
	}

	std::cout << "末端2Bytesをチェックサムにより置き換えします。" << std::endl;
	printf("%02x, %02x", pCharVec.at(size - 2), pCharVec.at(size - 1));//入力データ(置き換え前)
	std::cout << "->";
	printf("%02x, %02x", checksum & 0xFF, (checksum >> 8) & 0xFF);//チェックサムデータ(置き換え後)
	std::cout << std::endl;

	std::vector<unsigned char> calculatedData;
	calculatedData = pCharVec;

	calculatedData.at(size - 2) = checksum & 0xFF;
	calculatedData.at(size - 1) = (checksum >> 8) & 0xFF;

	calculatedData.pop_back(); //1文字余計になるので消す

	return calculatedData;
}