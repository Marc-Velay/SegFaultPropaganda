#include "fonctions.h"

void collision()
{
    int i;
    for(i=0; i<=Game.nbEnnemiCreated;i++){
		if( ( ( (Officer[i].x <= Tir.x) && ( (Officer[i].x + (GRID_STEP/5)) >= Tir.x) ) || ( (Officer[i].x <= Tir.x + 3*GRID_STEP/4) && ( (Officer[i].x + (GRID_STEP/5) ) >= Tir.x + GRID_STEP/2) ) ) && ((Officer[i].y - GRID_STEP/2) <= Tir.y) && ((Officer[i].y + GRID_STEP) >= Tir.y))
	          {
			Officer[i].alive = 0;
			Game.nbEnnemiAlive-=1;
			Tir.on = Tir.x = Tir.y = Officer[i].x = Officer[i].y = 0;
		}
	}

}
