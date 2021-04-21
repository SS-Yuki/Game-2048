#include "gameManager.h"

int main() {
	GameManager gm;
	gm.difficultySettings();
	gm.modeChoosing();

	if (gm.modeGet() == 1)
		gm.gameExecute();
	else if (gm.modeGet() == 2)
		gm.gameExecute(2);

	system("pause");
	return 0;
}