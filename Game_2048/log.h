#pragma once
#include "actionObserver.h"
#include "playerActionExecuter.h"
#include "performMoveAction.h"
#include "obtainBounsAction.h"
#include <fstream>

class Log : public ActionObserver {
public:
	Log(PlayerActionExecuter* aExe);

	~Log();
	void actionPerformed(PlayerAction* action);
private:
	PlayerActionExecuter* aExe;
	string logName;
	string dirE(const char& dir);
};
