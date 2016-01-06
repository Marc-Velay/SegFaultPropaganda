#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png

int main(int argc, char *argv[])
{
	int go;
	Game.stade=0;
	Game.countdown =0;
	Game.timer =0;
	Game.nbWave=1;
	Game.nbTourelleCreated=0;
	Game.nbTourelle=0;

	init("Tower Defense: Stephen VS Langley Falls");
	atexit(cleanup);
	go = 1;
	loadAllSprites();
	initPlayer();

	while (go == 1)
	{
		getInput();
		updateScreen();
		Game.timer +=1 ;
		Tir.reload +=1;
		SDL_Delay(16);
	}

	exit(0);
}
