#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"


//Récupère les highscore stocké dans le .txt et le met dans les tableaux de score
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

    highscore = fopen("save/highscore.txt","r+"); // Ouvre le fichier en mode lecture+

    if(highscore == NULL)
    {

         highscore = fopen("save/highscore.txt","w+"); //Ouvre et créer en mode écriture+ si le fichier n'existe pas encore

         for(i=0;i<10;i++) // Et rempli avec des scores nuls
         {

             fprintf(highscore,"XXXXXXXXXX 0 0 ");
         }
    }

    fseek(highscore,0,SEEK_SET); // Remet le curseur au début avant de commencer à récuperer les scores

        for(i=0;i<10;i++)//Récupère les scores et inclus le score du joueur actuel si il bat un record
        {
		temp1 = Game.Joueur[i];
		temp2 = &Game.nbWaveScore[i];
		temp3 = &Game.nbKilledScore[i];
            fscanf(highscore,"%s %d %d", temp1, temp2,temp3);

            if(Game.nbKilledScore[i] < Game.nbEnnemiKilled)//Insére le score et décale les suivant
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
                else //dans le cas du dernier score on remplace juste
                {
                    strcpy (Game.Joueur[i], nomTemp);
                    Game.nbKilledScore[i] = Game.nbEnnemiKilled;
                    Game.nbWaveScore[i] = Game.nbWave;
                }
            }
        }
        fclose(highscore);

        highscore = fopen("save/highscore.txt","w+");
        //Ferme le fichier et le réouvres en écriture+ pour tout effacer et mettre le nouveau tableau des scores
         for(i=0;i<10;i++)
         {

             fprintf(highscore,"%s %d %d ", Game.Joueur[i],Game.nbWaveScore[i], Game.nbKilledScore[i]);
         }

         fclose(highscore);//Ferme le fichier a la fin de son utilisation


}

//Affiche le highscore stockée dans les tableaux récupérés par getScore();
void drawHighscore()
{
     char Joueur[14],nbWaveScore[20],nbKilledScore[20],compteur[3] ;
     int i;

    getScore();//Appelle getScore;

        for(i=0;i<10;i++)//Stocke les valeurs dans des string et les affiche au bon endroit
        {
            sprintf(compteur,"%d", i+1);
            sprintf(Joueur,"%s", Game.Joueur[i]);
            sprintf(nbWaveScore,"%d", Game.nbWaveScore[i]);
            sprintf(nbKilledScore,"%d", Game.nbKilledScore[i]);

            drawMenu(compteur,-550, -80 + 50*i, compteurFont);
            drawMenu(Joueur,-445, -80 + 50*i, compteurFont);
            drawMenu(nbWaveScore,0, -80 + 50*i, compteurFont);
            drawMenu(nbKilledScore,450 , -80 +  50*i , compteurFont);
        }

}


