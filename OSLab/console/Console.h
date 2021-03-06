#pragma once

#include "../memory/PageMemoryPool.h"
#include "../filesystem/disk.h"
#include "../displayWindow/DisplayWindow.h"
#include "../ProcManage/PM.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>


using namespace std;

class Console
{
private:
	void Console::InputAnalyse(vector<string> cuttedString);
	string trim(string str);
	void InputCut(string input);
	string workingDir;

	PM procM;

	bool cat(string filename);
	bool ls();
	bool mkfile(string filename);
	bool mkexec(string filename);
	bool ps();
public:
	bool isExit;

	PageMemoryPool memPool;
	DisplayWindow disWin;

	Console();
	~Console();
	void waitForInput();
	void inputThread();
};

