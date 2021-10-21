#pragma once
#include "playerAction.h"
#include "playerActionExecuter.h"

class UndoAction : public PlayerAction {
public:
	UndoAction(PlayerActionExecuter* aExe);
	virtual void execute();
	virtual void undo();
	int getUndoNum();
private:
	PlayerActionExecuter* aExe;
	int undoNum;
};

