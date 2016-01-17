#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png



int main(int argc, char *argv[])
{
	int go;
	unsigned int frameLimit = SDL_GetTicks() + 45;
	go = 1;

    while(go == 1){

           Game.restart = 0;
           Game.stade=0;

        init("Tower Defense: Stephen VS Langley Falls");
        atexit(cleanup);


        while (Game.restart != 1)
        {
        updateScreen();
        getInput();
		Game.timer +=1;
		doWave();
		Player.reload++;
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 45;
        }

    }

	exit(0);
}
