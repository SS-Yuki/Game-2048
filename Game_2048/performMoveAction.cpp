#include "performMoveAction.h"

PerformMoveAction::PerformMoveAction(Player* pl, Map* fmap, char dir) : mapCopy(*fmap), map(fmap), direction(dir) {
	player = pl;
	score = 0;
	actionType = 1;
}
void PerformMoveAction::execute() {
	map->moveResult(direction);
	score = map->getScore();
	player->changeScore(score);
}
void PerformMoveAction::undo() {
	*map = mapCopy;
	player->changeScore(-score);
}
char PerformMoveAction::getDir() {
	return direction;
}

