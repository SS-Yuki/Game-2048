#pragma once
#include "actionObserver.h"
#include <algorithm>
#include <vector>

class Subject {
public:
	void addActionObserver(ActionObserver* observer);
	void removeObserver(ActionObserver* observer);
	void Notify(PlayerAction* action);
private:
	vector <ActionObserver*> actionObservers;
};

