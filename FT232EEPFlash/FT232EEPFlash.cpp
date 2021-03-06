#include "stdafx.h"

#include "FT232Ctrl.hpp"
#include "FileUtil.h"

#include <iostream>
#include <string>

#include "ModeCtrl.h"

#include "AA.h"
int _tmain(int argc, _TCHAR* argv[]) {

	ModeCtrl mode;

	std::locale::global(std::locale("japanese"));

	//std::cout << "テスト動作" << std::endl;

	//if (argc < 2) {
	//	std::cout << "引数が足りません。2以上を指定すること。ReadMeをよく読みなさい。" << std::endl;
	//	return 1;
	//}

	mode.CheckMode(argc, argv);
	ModeCtrl::Mode modestatus;
	modestatus = mode.GetMode();

	ModeCtrl::Error errorstatus;
	errorstatus = mode.GetError();

	if (modestatus == ModeCtrl::Mode::ERROR_END || modestatus == ModeCtrl::Mode::UNDEFINED) {

		if (errorstatus == ModeCtrl::Error::NOT_ENOUGH_ARGUMENTS) {
			std::cout << "引数が足りません。2以上を指定すること。ReadMeをよく読みなさい。" << std::endl;
			return 1;
		}

		if (errorstatus == ModeCtrl::Error::INVALID_ARGUMENT) {
			std::cout << "不正な引数。ReadMeをよく読みなさい。" << std::endl;
			return 1;
		}

		std::cout << "何かが不正。どっかでコーディングミスってるごめんね。" << std::endl;
		return 1;

	}


	FT232Ctrl ft232;
	ft232.Open();

	//読み込み　ファイルに出力
	if (modestatus == ModeCtrl::Mode::READROM) {
		std::string outputfilename = argv[1];

		std::vector<unsigned char> EEPData;
		ft232.ReadEEPROM(EEPData);
		FileUtil::WriteBinary(outputfilename, EEPData);
	}

	//書き込み
	if (modestatus == ModeCtrl::Mode::WRITE) {
		std::string inputfilename = argv[1];

		std::vector<unsigned char> fileData;
		if (!FileUtil::ReadBinary(inputfilename, fileData)) {
			ft232.WriteEEPROM(fileData);
		}
		else {
			modestatus = ModeCtrl::Mode::ERROR_END;
		}
		
	}

	//書き込み with checksum
	if (modestatus == ModeCtrl::Mode::WRITE_WITH_CHECKSAM) {
		std::string inputfilename = argv[1];

		std::vector<unsigned char> fileData;
		if (!FileUtil::ReadBinary(inputfilename, fileData)) {
			ft232.WriteEEPROMwithChecksum(fileData);
		}
		else {
			modestatus = ModeCtrl::Mode::ERROR_END;
		}
		
	}

	ft232.Close();

	if (modestatus != ModeCtrl::Mode::ERROR_END) {
		std::cout << "正常に終了しました。" << std::endl;
	}
	else {
		std::cout << "異常終了しました。" << std::endl;
	}


	return 0;
}
