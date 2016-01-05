#include "fonctions.h"

void initLaser(){
	Laser.sprite = getSprite(LASER_SPRITE);
	Laser.x =SCREEN_WIDTH -600;
	Laser.y =2*GRID_STEP+PATH_TOP_Y+20;
}

void updateLaser(){
	drawImage(Laser.sprite, Laser.x, Laser.y);
}

void shoot(){
	if(Game.countdown == 0){
		initLaser();
	}	
}