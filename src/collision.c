#include "fonctions.h"

void collision()
{
	int i;
	tir *newTir =Tir;
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
		 }
		
	}

}
