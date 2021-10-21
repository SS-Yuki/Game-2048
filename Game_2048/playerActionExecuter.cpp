#include "playerActionExecuter.h"

PlayerActionExecuter::PlayerActionExecuter(Player* pl) : pl(pl), stateNum(5) {}

void PlayerActionExecuter::executeAction(PlayerAction* action) {
	if (action->getType() > actions.size())
		actions.resize(action->getType());
	action->execute();
	Notify(action);
	if (action->getType() > 0) {
		actions[action->getType() - 1].push_back(action);
		for (auto listVal : actions) {
			if (listVal.size() > stateNum)
				listVal.pop_front();
		}
	}
}

int PlayerActionExecuter::Undo() {
	int score = 0;
	for (auto listVal : actions) {
		score += listVal.back()->getScore();
		listVal.back()->undo();
		listVal.pop_back();
	}
	return score;
}

