#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"



void getScore()
{
    FILE* highscore = NULL;

    char nomTemp[14] = "sauce";
    strcpy (nomTemp, Player.name);

    int nbWaveScoreTemp, nbKilledScoreTemp;
    int i;
    char *temp1;
    int *temp2;
    int *temp3;

    nbWaveScoreTemp = Game.nbWave;
    nbKilledScoreTemp = Game.nbEnnemiKilled;

    highscore = fopen("save/highscore.txt","r+");

    if(highscore == NULL)
    {

         highscore = fopen("save/highscore.txt","w+");

         for(i=0;i<10;i++)
         {

             fprintf(highscore,"XXXXXXXXXX 0 0 ");
         }
    }

    fseek(highscore,0,SEEK_SET);

        for(i=0;i<10;i++)
        {
		temp1 = Game.Joueur[i];
		temp2 = &Game.nbWaveScore[i];
		temp3 = &Game.nbKilledScore[i];
            fscanf(highscore,"%s %d %d", temp1, temp2,temp3);

            if(Game.nbKilledScore[i] < Game.nbEnnemiKilled)
            {
                if(i != 9)
                {
                    strcpy (Game.Joueur[i+1], Game.Joueur[i]);
                    Game.nbKilledScore[i+1] = Game.nbKilledScore[i];
                    Game.nbWaveScore[i+1] = Game.nbWaveScore[i];

                    strcpy (Game.Joueur[i], nomTemp);
                    Game.nbKilledScore[i] = nbKilledScoreTemp;
                    Game.nbWaveScore[i] = nbWaveScoreTemp;
                    Game.nbEnnemiKilled = 0;
                    i++;
                }
                else
                {
                    strcpy (Game.Joueur[i], nomTemp);
                    Game.nbKilledScore[i] = Game.nbEnnemiKilled;
                    Game.nbWaveScore[i] = Game.nbWave;
                }
            }
        }
        fclose(highscore);

        highscore = fopen("save/highscore.txt","w+");

         for(i=0;i<10;i++)
         {

             fprintf(highscore,"%s %d %d ", Game.Joueur[i],Game.nbWaveScore[i], Game.nbKilledScore[i]);
         }

         fclose(highscore);


}

void drawHighscore()
{
     char Joueur[14],nbWaveScore[20],nbKilledScore[20],compteur[3] ;
     int i;
     /*char *temp;
     int *temp1;
     int *temp2;
     FILE* highscore = NULL;*/

    getScore();
    //highscore = fopen("save/highscore.txt","r+");

        for(i=0;i<10;i++)
        {
		/*temp = Game.Joueur[i];
		temp1 =&Game.nbWaveScore[i];
		temp2 = &Game.nbKilledScore[i];*/
            sprintf(compteur,"%d", i+1);
            //fscanf(highscore,"%s %d %d", temp, temp1, temp2);
            sprintf(Joueur,"%s", Game.Joueur[i]);
            sprintf(nbWaveScore,"%d", Game.nbWaveScore[i]);
            sprintf(nbKilledScore,"%d", Game.nbKilledScore[i]);

            drawMenu(compteur,-550, -80 + 50*i, compteurFont);
            drawMenu(Joueur,-445, -80 + 50*i, compteurFont);
            drawMenu(nbWaveScore,0, -80 + 50*i, compteurFont);
            drawMenu(nbKilledScore,450 , -80 +  50*i , compteurFont);
        }

}


