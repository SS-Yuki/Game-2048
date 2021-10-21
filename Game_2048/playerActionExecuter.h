#pragma once
#include <list>
#include "Subject.h"
class PlayerActionExecuter : public Subject {
public:
	PlayerActionExecuter(Player* pl);
	void executeAction(PlayerAction* action);
	int Undo();

	Player* pl;
private:
	vector <list <PlayerAction*>> actions;
	const int stateNum;
};
