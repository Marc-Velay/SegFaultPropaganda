#include "fonctions.h"

void collision()
{
    int i;
    for(i=0; i<=Game.nbEnnemiCreated;i++){
		if((Officer[i].x <= Tir.x) && ((Officer[i].x + GRID_STEP) >= Tir.x) && (Officer[i].y <= Tir.y) && ((Officer[i].y + GRID_STEP) >= Tir.y))
            {
			Officer[i].alive = 0;
            Tir.on = 0;
		}
	}

}
