#pragma once
#include "player.h"
class PlayerAction {
public:
	PlayerAction();
	virtual void execute() = 0;
	virtual void undo() = 0;

	string getName();
	struct tm* getTime();
	int getScore();
	size_t getType();
	Player* player;
protected:
	int score;
	int actionType;
};
