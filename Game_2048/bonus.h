#pragma once
#include "actionObserver.h"
#include "playerActionExecuter.h"
#include "obtainBounsAction.h"
class Bonus : public ActionObserver {
public:
	Bonus(PlayerActionExecuter* aExe);
	~Bonus();
	void actionPerformed(PlayerAction* action);
	static clock_t lastTime;
private:
	PlayerActionExecuter* aExe;
};
