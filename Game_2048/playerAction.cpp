#include "playerAction.h"
#include <ctime>
PlayerAction::PlayerAction() : player(NULL), score(0), actionType(-1) {}

string PlayerAction::getName() {
	return player->getName();
}
struct tm* PlayerAction::getTime() {
	time_t second = time(NULL);
	struct tm* nowTime = localtime(&second);
	return nowTime;
}
int PlayerAction::getScore() {
	return score;
}
size_t PlayerAction::getType() {
	return actionType;
}

