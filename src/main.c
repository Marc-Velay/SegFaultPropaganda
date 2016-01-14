#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png



int main(int argc, char *argv[])
{
	int go;
	unsigned int frameLimit = SDL_GetTicks() + 60;
	go = 1;

    while(go == 1){

           Game.restart = 0;

        init("Tower Defense: Stephen VS Langley Falls");
        atexit(cleanup);


        while (Game.restart != 1)
        {
		doWave();
		getInput();
		updateScreen();
		Game.timer +=1;
		Player.reload++;
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 60;
        }

    }

	exit(0);
}
