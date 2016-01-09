#include "fonctions.h"

void initLaserdef(int n, int colonne, int lane){

	Game.nbLaserdefCreated++;
		Laserdef[n].sprite = getSprite(LASER_SPRITE);
		Laserdef[n].x = colonne*GRID_STEP;
		Laserdef[n].y =(lane*GRID_STEP)+PATH_TOP_Y+30;
		printf("Laserdef %d at: %d,%d\n", n, Laserdef[n].x, Laserdef[n].y);
}

void updateLaser(int n, int colonne, int lane){
	drawImage(Laserdef[n].sprite, Laserdef[n].x, Laserdef[n].y);
}

void shoot(int n, int colonne, int lane){
	if(Game.countdown == 0){
		initLaserdef( n, colonne,  lane);
	}
}
