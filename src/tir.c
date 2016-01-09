#include "fonctions.h"

void initTir(int x, int y, int dir){
	tir *newTir =Tir;
	tir *addTir = Tir;
	int created=0;
	if(newTir == NULL){
		newTir = (tir*)malloc(sizeof(tir));
		(*newTir).suivant =NULL;
		(*newTir).sprite = getSprite(LASER_SPRITE);
		(*newTir).dir = dir;
		if((*newTir).dir==0) {(*newTir).x = x + (GRID_STEP/2);}
		if((*newTir).dir==1) {(*newTir).x = x - GRID_STEP;}
		(*newTir).y = y;
		(*newTir).on = 1;
		(*newTir).reload = 0;
		Tir =newTir;
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
				(*addTir).suivant = newTir;
				created =1;
				break;
			}
			if((*newTir).on ==0){
				(*newTir).dir = dir;
				if((*newTir).dir==0) {(*newTir).x = x + (GRID_STEP/2);}
				if((*newTir).dir==1) {(*newTir).x = x - GRID_STEP;}
				(*newTir).y = y;
				(*newTir).on = 1;
				(*newTir).reload = 0;
				created =1;
			}
			addTir=newTir;
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
				    if((*newTir).x >= SCREEN_WIDTH) {(*newTir).x = (*newTir).y = (*newTir).on =0; }
			            collision();
			        }
			}

			if((*newTir).dir==1) {
			        for(i=0;i<50;i++) {
			            (*newTir).x -=1;
				    if((*newTir).x <= 0) {(*newTir).x = (*newTir).y = (*newTir).on =0; }
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

