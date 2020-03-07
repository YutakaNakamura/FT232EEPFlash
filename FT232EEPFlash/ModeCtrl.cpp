#include "stdafx.h"
#include "ModeCtrl.h"

#include <vector>

ModeCtrl::ModeCtrl()
{
}


ModeCtrl::~ModeCtrl()
{
}

ModeCtrl::Mode ModeCtrl::GetMode(void) {
	return mMode;
}

ModeCtrl::Error ModeCtrl::GetError(void) {
	return mError;
}


void ModeCtrl::CheckMode(int argc, _TCHAR* argv[]) {

	//�����̐����`�F�b�N
	if (argc < 3) {
		mMode = ERROR_END;
		mError = NOT_ENOUGH_ARGUMENTS;
		return;
	}

	//������vector�ŊǗ�
	std::vector <std::string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	//WR�̃I�v�V�����m�F
	std::string RWoption = args.at(2);
	if (RWoption == "-R" || RWoption == "-r") {
		mMode = READROM;
	}
	else if (RWoption == "-W" || RWoption == "-w") {
		mMode = WRITE;
	}
	else {
		mMode = ERROR_END;
		mError = NOT_ENOUGH_ARGUMENTS;
	}

	//�ǉ��̃I�v�V�����������Ȃ�ΏI��
	if (args.size() < 4) {
		return;
	}

	std::string ADDoption = args.at(3);
	if (ADDoption == "--C" && mMode == WRITE) {
		mMode = WRITE_WITH_CHECKSAM;
	}

}