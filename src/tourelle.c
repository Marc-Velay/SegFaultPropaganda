#include "fonctions.h"

void initTourelle(int n, int colonne, int lane)
{		
		Tourelle[n].sprite = getSprite(TOURELLE_SPRITE);
		Tourelle[n].x = colonne*GRID_STEP;
		Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y+30;
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
	int lane=0;
	int colonne=0;
	int temp=0;
	while(temp<Player.x -GRID_STEP + STEPHEN_ACTUAL_WIDTH){
		temp += GRID_STEP;
		colonne++;
	}
	temp =0;
	while(temp <= Player.y - PATH_TOP_Y -GRID_STEP + STEPHEN_ACTUAL_HEIGHT){
		temp += GRID_STEP;
		lane++;
	}
	Game.nbTourelle++;
	if(lane > 5){lane =5;}
	initTourelle(Game.nbTourelle,colonne,lane-1);
}

void doTourelle(){
	if(Game.countdown ==0){
		shoot();
		Game.countdown ++;
	}
}

