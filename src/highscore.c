#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"

void swapScore(int* a, int* b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;


}

int nbChiffres(int i)
{

	int nb = 0;

	do
    {
		nb++;

	}while((i /= 10) > 0);

	return nb;
}

void highscore()
{
    FILE* highscore = NULL;

    char noms[10][14];
    char nomTemp[14] = "sauce";

    int nbWaveScore[10], nbKilledScore[10];
    int nbWaveScoreTemp, nbKilledScoreTemp;
    int i;

    nbWaveScoreTemp = Game.nbWave;
    nbKilledScoreTemp = Game.nbEnnemiKilled;

    highscore = fopen("save/highscore.txt","r+");

    if(highscore == NULL)
    {
         highscore = fopen("save/highscore.txt","w+");

         for(i=0;i<10;i++)
         {
             fprintf(highscore,"XXXXXXXXXXXXX 0 0 ");
         }
    }

    fseek(highscore,0,SEEK_SET);

        for(i=0;i<10;i++)
        {
            fscanf(highscore, "%s", &noms[i]);
            fscanf(highscore, "%d %d", &nbWaveScore[i], &nbKilledScore[i]);

            if(nbKilledScore[i] < Game.nbEnnemiKilled)
            {
                if(i != 9)
                {
                    strcpy (noms[i+1], noms[i]);
                    nbKilledScore[i+1] = nbKilledScore[i];
                    nbWaveScore[i+1] = nbWaveScore[i];

                    strcpy (noms[i], nomTemp);
                    nbKilledScore[i] = nbKilledScoreTemp;
                    nbWaveScore[i] = nbWaveScoreTemp;
                    Game.nbEnnemiKilled = 0;
                    i++;
                }
                else
                {
                    strcpy (noms[i], nomTemp);
                    nbKilledScore[i] = Game.nbEnnemiKilled;
                    nbWaveScore[i] = Game.nbWave;
                }
            }
        }
        fclose(highscore);

        highscore = fopen("save/highscore.txt","w+");

         for(i=0;i<10;i++)
         {

             fprintf(highscore, "%s ", noms[i]);
             fprintf(highscore,"%d %d ",nbWaveScore[i], nbKilledScore[i]);
         }

         fclose(highscore);


}
