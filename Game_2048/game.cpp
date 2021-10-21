#include "gameManager.h"

int main(int argc, char* const argv[]) {
	GameManager gm(argc, argv);

	gm.fileTest();

	gm.gameInit();
	if (gm.modeGet() == 1)
		gm.gameExecute();
	else if (gm.modeGet() == 2)
		gm.gameExecute(2);
	
	getchar();
	return 0;
}
 