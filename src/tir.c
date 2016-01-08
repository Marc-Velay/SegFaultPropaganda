#include "fonctions.h"

void initTir(int x, int y, int dir){
	Tir.sprite = getSprite(LASER_SPRITE);
	Tir.dir = dir;
	if(Tir.dir==0)Tir.x = x + (GRID_STEP/2);
	if(Tir.dir==1)Tir.x = x - GRID_STEP;
	Tir.y = y;
	Tir.on = 1;
	Tir.reload = 0;
}

void updateTir(){
    int i;

	if(Tir.on == 1)
    {
    drawImage(Tir.sprite, Tir.x, Tir.y);
	if(Tir.dir==0)
    {
        for(i=0;i<50;i++)
        {
            Tir.x +=1;
            collision();
        }
    }

	if(Tir.dir==1)
    {
        for(i=0;i<50;i++)
        {
            Tir.x -=1;
            collision();
        }
    }
    }
}

void Tirer(int x, int y, int dir){
	if(Game.countdown == 0){
		initTir(x,y,dir);
	}
}

