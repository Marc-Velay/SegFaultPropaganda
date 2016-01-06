#include "fonctions.h"

void collision()
{
    int i;
    for(i=0; i<=Game.nbEnnemiCreated;i++){
		if((Officer[i].x <= Tir.x) && ((Officer[i].x + (2*GRID_STEP/3)) >= Tir.x) && ((Officer[i].y - GRID_STEP/2) <= Tir.y) && ((Officer[i].y + GRID_STEP) >= Tir.y))
            {
			Officer[i].alive = 0;
            Tir.on = Tir.x = Tir.y = Officer[i].x = Officer[i].y = 0;
		}
	}

}
