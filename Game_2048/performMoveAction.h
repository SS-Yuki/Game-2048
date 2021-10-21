#pragma once
#include "playerAction.h"
#include "map.h"
class PerformMoveAction : public PlayerAction
{
public:
	PerformMoveAction(Player* pl, Map* fmap, char dir);
	virtual void execute();
	virtual void undo();
	char getDir();
private:
	char direction;
	Map mapCopy;
	Map* map;
};

