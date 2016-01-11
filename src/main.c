#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png

int main(int argc, char *argv[])
{
	int go;


	init("Tower Defense: Stephen VS Langley Falls");
	atexit(cleanup);
	go = 1;

	while (go == 1)
	{
		if(Game.nbEnnemiAlive==0 && Game.stade == 1){
			Game.nbWave+=1;
			Game.nbEnnemiCreated =0;
			Game.countdown =0;
			doEnnemi();
		}
		getInput();
		updateScreen();
		Game.timer +=1;
		Player.reload++;
		SDL_Delay(16);
	}

	exit(0);
}
