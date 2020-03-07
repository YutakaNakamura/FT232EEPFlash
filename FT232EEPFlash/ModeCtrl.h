#pragma once
class ModeCtrl
{
public:
	enum Mode {
		UNDEFINED,
		READROM,
		WRITE,
		WRITE_WITH_CHECKSAM,
		ERROR_END,
	};

	enum Error {
		NORMAL,
		NOT_ENOUGH_ARGUMENTS,
		INVALID_ARGUMENT,

	};


private:
	Error mError = NORMAL;
	Mode mMode = UNDEFINED;


public:
	ModeCtrl();
	~ModeCtrl();

	Mode GetMode(void);
	Error GetError(void);

	void CheckMode(int argc, _TCHAR* argv[]);

};

