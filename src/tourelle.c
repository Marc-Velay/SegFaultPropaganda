#include "fonctions.h"

void initTourelle(int n, int lane)
{		
		Tourelle[n].sprite = getSprite(TOURELLE_SPRITE);
		Tourelle[n].x =SCREEN_WIDTH -500;
		Tourelle[n].y =lane*GRID_STEP+PATH_TOP_Y;
		Tourelle[n].alive =1;
		Game.nbTourelleCreated++;
		printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
}

void drawTourelle()
{
	int i;
	for(i=0; i<Game.nbTourelleCreated; i++){
		if(Tourelle[i].alive == 1){
		drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
		}
	}	
}

void createTourelle(int moux, int mouy){
	
}

void doTourelle(){
	if(Game.countdown ==0){
		initTourelle(0, 2);
		shoot();
		Game.countdown ++;
	}
}

