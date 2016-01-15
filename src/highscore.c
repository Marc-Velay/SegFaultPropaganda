#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"

void highscore()
{
    FILE* highscore = NULL;

    highscore = fopen("save/highscore.txt","w+");

    if(highscore != NULL)
    {
        fprintf(highscore,"Meilleur score vagues: %d   ennemies abbatus: %d",Game.nbWave,Game.nbEnnemiKilled);
        fclose(highscore);
    }
}
