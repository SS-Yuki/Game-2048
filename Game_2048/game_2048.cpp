#include "gameManager.h"

int main(int argc, char *const argv[]) {
	GameManager gm(argc, argv);
	if (gm.fileMode()) {
		gm.fileIn();
    	gm.fileOut();
		return 0;
	}
	gm.modeChoosing();
	if (gm.modeGet() == 1)
		gm.gameExecute();
	else if (gm.modeGet() == 2)
		gm.gameExecute(2);
	return 0;
}