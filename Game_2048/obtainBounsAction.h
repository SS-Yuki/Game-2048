#pragma once
#include "playerAction.h"

class ObtainBounsAction : public PlayerAction {
public:
	ObtainBounsAction(Player* pl, double timeDur);
	virtual void execute();
	virtual void undo();
	double getTimeDur();
private:
	double timeDuration;
};