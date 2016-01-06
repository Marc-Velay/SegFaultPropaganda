#include "fonctions.h"

void collision()
{
    int i;
    for(i=0; i<=Game.nbEnnemiCreated;i++){
		if(Officer[i].x <= Tir.x && Officer[i].x <= Tir.x){
			Officer[i].x +=2;
		}
	}

}
