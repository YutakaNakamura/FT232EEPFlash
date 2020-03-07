#pragma once

#include <windows.h>
#include "FTD2XX.h"
#include <vector>

//union ShortCharConverter {
//	unsigned char mChar[2];
//	unsigned short mShort;
//};

class FT232Ctrl
{

private:
	FT_HANDLE mFtHandle;
	FT_STATUS mFtStatus;
public:
	FT232Ctrl();
	~FT232Ctrl();
	bool Open();
	bool Close();

	bool ReadEEPROM(std::vector<unsigned char> &pROMData);
	bool WriteEEPROM(const std::vector<unsigned char> &pWriteData);

	bool WriteEEPROMwithChecksum(const std::vector<unsigned char> &pWriteData);

	std::vector<unsigned char> CheckSum(const std::vector<unsigned char> &pCharVec);
};

