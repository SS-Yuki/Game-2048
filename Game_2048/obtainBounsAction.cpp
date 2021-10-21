#include "obtainBounsAction.h"

ObtainBounsAction::ObtainBounsAction(Player* pl, double timeDur) : timeDuration(timeDur) {
	player = pl;
	score = 0;
	actionType = 2;
}
void ObtainBounsAction::execute() {
	if (timeDuration < 1) {
		score = 1;
		player->changeScore(score);
	}
}
void ObtainBounsAction::undo() {
	player->changeScore(-score);
}
double ObtainBounsAction::getTimeDur() {
	return timeDuration;
}
