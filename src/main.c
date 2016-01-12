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
	    if(Game.nbEnnemiAlive==0 && Game.stade == 1 ){

            if(Game.countdown - Game.timer < 0 ){
                Game.countdown = Game.timer + 150;
            }
                else if(Game.countdown - Game.timer == 0)
                {
                Game.nbEnnemiCreated =0;
                createWave();
                }

	    }
		getInput();
		updateScreen();
		Game.timer +=1;
		Player.reload++;
		SDL_Delay(16);
	}

	exit(0);
}
