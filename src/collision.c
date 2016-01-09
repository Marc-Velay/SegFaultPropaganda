#include "fonctions.h"

void collision()
{
    collisionTirR_Ennemi();
    collisionEnnemi_Tourelle();
}

void collisionTirR_Ennemi()
{
	int i;
	tir *newTir = Tir;
	for(i=0; i<=Game.nbEnnemiCreated;i++){
		 while(newTir != NULL){
			 if( ( ( (Officer[i].x <= (*newTir).x) && ( (Officer[i].x + (GRID_STEP/5)) >= (*newTir).x) ) || ( (Officer[i].x <= (*newTir).x + 3*GRID_STEP/4) && ( (Officer[i].x + (GRID_STEP/5) ) >= (*newTir).x + GRID_STEP/2) ) ) && ((Officer[i].y - GRID_STEP/2) <= (*newTir).y) && ((Officer[i].y + GRID_STEP) >= (*newTir).y)) {
				Officer[i].hpOfficer -=1;
				if(Officer[i].hpOfficer <=0){
					Officer[i].alive = 0;
					Officer[i].x = Officer[i].y = 0;
				}
				(*newTir).on = (*newTir).x = (*newTir).y = 0;
			}
			newTir = (*newTir).suivant;
		 }
    newTir = Tir;
	}

}
void collisionEnnemi_Tourelle()
{

	int i,j;
	for(i=0; i<=Game.nbEnnemiCreated;i++)
        {
            for(j=0;j<=Game.nbTourelleCreated;j++)
            {
                if(Officer[i].x >= Tourelle[j].x - GRID_STEP/2 && Officer[i].lane == Tourelle[j].lane && Tourelle[j].alive == 1 /*&& Officer[i].reload >= 25*/)
                {
                    Officer[i].attack = 1;
                    Tourelle[i].hpTourelle --;
                    Officer[i].reload = 0;
                }
            }
        }
}
