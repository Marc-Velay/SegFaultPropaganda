#include "fonctions.h"

void initTir(int x, int y, int dir){
	tir *newTir;
	int created=0;
	
	if(Tir == NULL){
		Tir = (tir*)malloc(sizeof(tir));
		(*Tir).suivant =NULL;
		(*Tir).sprite = getSprite(LASER_SPRITE);
		(*Tir).dir = dir;
		if((*Tir).dir==0) {(*Tir).x = x + (GRID_STEP/2);}
		if((*Tir).dir==1) {(*Tir).x = x - GRID_STEP;}
		(*Tir).y = y;
		(*Tir).on = 1;
		(*Tir).reload = 0;
	}
	else {
		newTir=(*Tir).suivant;
		
		while(created !=1 ){
			if(newTir == NULL) {
				newTir = (tir*)malloc(sizeof(tir));
				(*newTir).suivant =NULL;
				(*newTir).sprite = getSprite(LASER_SPRITE);
				(*newTir).dir = dir;
				if((*newTir).dir==0) {(*newTir).x = x + (GRID_STEP/2);}
				if((*newTir).dir==1) {(*newTir).x = x - GRID_STEP;}
				(*newTir).y = y;
				(*newTir).on = 1;
				(*newTir).reload = 0;
				created =1;
			}
			newTir= (*newTir).suivant;
			if((*newTir).on ==0){
				newTir = (tir*)malloc(sizeof(tir));
				(*newTir).suivant =NULL;
				(*newTir).sprite = getSprite(LASER_SPRITE);
				(*newTir).dir = dir;
				if((*newTir).dir==0) {(*newTir).x = x + (GRID_STEP/2);}
				if((*newTir).dir==1) {(*newTir).x = x - GRID_STEP;}
				(*newTir).y = y;
				(*newTir).on = 1;
				(*newTir).reload = 0;
				created =1;
			}
			newTir=(*newTir).suivant;
		}	
	}
}

void updateTir(){
    int i;
    tir *newTir= Tir;
	while(newTir !=NULL){
		if((*newTir).on == 1) {
		    drawImage((*newTir).sprite, (*newTir).x, (*newTir).y);
		    
			if((*newTir).dir==0) {
			        for(i=0;i<50;i++) {
			            (*newTir).x +=1;
			            collision();
			        }
			}

			if((*newTir).dir==1) {
			        for(i=0;i<50;i++) {
			            (*newTir).x -=1;
			            collision();
			        }
			}
		 }
		 newTir = (*newTir).suivant;
	}
}

void Tirer(int x, int y, int dir){
	if(Game.countdown == 0){
		initTir(x,y,dir);
	}
}

