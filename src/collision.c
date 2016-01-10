#include "fonctions.h"

void collision()
{
    collisionTir_Ennemi();
    collisionEnnemi_Tourelle();
    collisionEnnemi_Base();
}

void collisionTir_Ennemi()
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
                if(Officer[i].x >= Tourelle[j].x - GRID_STEP/2 && Officer[i].lane == Tourelle[j].lane  /*&& Officer[i].reload >= 25*/)
                {

                    if(Tourelle[j].alive == 1 )
                    {

                        if( Game.timer % Officer[i].reloadrate == 0 )
                        {
                        Tourelle[j].hpTourelle --;
                        if(Tourelle[j].hpTourelle == 0)
                            {
                                Tourelle[j].alive = 0;
                                Tourelle[j].x = 0;
                                Tourelle[j].y = 0;
                            }
                        }
                        Officer[i].attack = 1;
                    }
                    else
                    {
                        Officer[i].attack = 0;
                    }
                }



            }
        }
}

void collisionEnnemi_Base()
{
    int i;
        for(i=0;i<Game.nbEnnemiCreated;i++)
        {
             if( Officer[i].lane == 0 || Officer[i].lane == 4 )
                {
                    if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP/2))
                    {

                        if( Game.timer % Officer[i].reloadrate == 0 )
                        {

                        Game.hpBase --;

                        if(Game.hpBase == 0)
                            {
                               Game.stade = 2;
                            }
                        }
                    }
                }

                else
                {
                    if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP))
                       {

                        if( Game.timer % Officer[i].reloadrate == 0 )
                        {

                        Game.hpBase --;

                        if(Game.hpBase == 0)
                            {
                               Game.stade = 2;
                            }
                        }
                    }
                }
        }
}
