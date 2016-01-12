#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png

int main(int argc, char *argv[])
{
	int go;
    go = 1;

    while(go == 1){

           restart = 0;

        init("Tower Defense: Stephen VS Langley Falls");
        atexit(cleanup);


        while (restart != 1)
        {
            doWave();
            getInput();
            updateScreen();
            Game.timer +=1;
            Player.reload++;
            SDL_Delay(16);
        }
    }

	exit(0);
}
