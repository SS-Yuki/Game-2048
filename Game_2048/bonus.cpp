#include "bonus.h"
clock_t Bonus::lastTime = clock();

Bonus::Bonus(PlayerActionExecuter* aExe) : aExe(aExe) {
	aExe->addActionObserver(this);
}
Bonus::~Bonus() {
	aExe->removeObserver(this);
}
void Bonus::actionPerformed(PlayerAction* action) {
	if (action->getType() == 1) {
		clock_t now = clock();
		double timeDuration = ((double)now - lastTime) / CLOCKS_PER_SEC;
		lastTime = now;
		aExe->executeAction(
			new ObtainBounsAction(action->player, timeDuration)
		);
	}
}


