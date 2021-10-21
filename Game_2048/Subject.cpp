#include "Subject.h"

void Subject::addActionObserver(ActionObserver* observer) {
	actionObservers.push_back(observer);
}
void Subject::removeObserver(ActionObserver* observer) {
	actionObservers.erase(
		find(actionObservers.begin(), actionObservers.end(), observer)
	);
}
void Subject::Notify(PlayerAction* action) {
	for (auto o : actionObservers)
		o->actionPerformed(action);
}
