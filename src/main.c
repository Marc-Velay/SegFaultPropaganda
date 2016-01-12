#include "fonctions.h"

// Strip images using		 pngcrush -rem allb RogerShadeClean_64x64.png Roger_Clean.png

void Jeu()
{
    doWave();
            getInput();
            updateScreen();
            Game.timer +=1;
            Player.reload++;
            SDL_Delay(16);
}

int main(int argc, char *argv[])
{
	int go;
    go = 1;

    while(go == 1){

           Game.restart = 0;

        init("Tower Defense: Stephen VS Langley Falls");
        atexit(cleanup);


        while (Game.restart != 1)
        {
            Jeu();
        }

    }

	exit(0);
}
