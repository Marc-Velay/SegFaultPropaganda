#include "fonctions.h"

void initTir(int x, int y, int dir){
	Tir.sprite = getSprite(LASER_SPRITE);
	Tir.dir = dir;
	if(Tir.dir==0)Tir.x = x + (GRID_STEP/2);
	if(Tir.dir==1)Tir.x = x - GRID_STEP;
	Tir.y = y;
	Tir.on = 1;
	Tir.reload = 0;
<<<<<<< HEAD

=======
	//drawImage(Tir.sprite, Tir.x, Tir.y);
>>>>>>> romain

}

void updateTir(){
	if(Tir.on == 1) drawImage(Tir.sprite, Tir.x, Tir.y);
	if(Tir.dir==0) Tir.x +=50;
	if(Tir.dir==1) Tir.x -=50;
<<<<<<< HEAD
=======
	Game.timer +=1;
>>>>>>> romain
	SDL_Delay(16);

}

void Tirer(int x, int y, int dir){
	if(Game.countdown == 0){
		initTir(x,y,dir);
	}
}

