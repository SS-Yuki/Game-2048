#pragma once
#include "playerAction.h"
#include <ctime>
class ActionObserver {
public:
	virtual void actionPerformed(PlayerAction* action) = 0;
};