#include "undoAction.h"


UndoAction::UndoAction(PlayerActionExecuter* aExe) : aExe(aExe), undoNum(3) {
	player = aExe->pl;
	score = 0;
	actionType = 0;
}

void UndoAction::execute() {
	score = aExe->Undo();
	undoNum--;
}
void UndoAction::undo() {}
int UndoAction::getUndoNum() {
	return undoNum;
}

