#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"

void highscore()
{
    FILE* highscore = NULL;
    FILE* highscoreTemp = NULL;

    int nbWaveScore, nbKilledScore, nbWaveScoreTemp, nbKilledScoreTemp;
    int written, i, d;

    highscore = fopen("save/highscore.txt","r+");

    if(highscore == NULL)
    {
         highscore = fopen("save/highscore.txt","w+");
         for(i=0;i<10;i++)
         {
             fprintf(highscore,"0 0\n");
         }
    }

    d = -3;
    i = 10;
    fseek(highscore,0,SEEK_SET);
    while(fscanf(highscore, "%d %d", &nbWaveScore, &nbKilledScore) != EOF)
        {
            if(written !=1)
            {
                if(Game.nbEnnemiKilled > nbKilledScore)
                {

                    while(Game.nbEnnemiKilled/i > 0)
                    {
                        if(Game.nbEnnemiKilled/i != 0){d--;}
                        if(Game.nbWave/i != 0){d--;}
                        i*=10;
                    }
                    fseek(highscore,d,SEEK_CUR);
                    fprintf(highscore,"%d %d",Game.nbWave,Game.nbEnnemiKilled);
                    written = 1;
                }
            }
            else
            {

            }
        }

    fclose(highscore);
}
