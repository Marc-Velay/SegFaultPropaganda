#include "fonctions.h"

void initOfficer(int n, int lane)
{		
		Officer[n].sprite = getSprite(OFFICER_SPRITE);
		Officer[n].x =0;
		Officer[n].y =lane*GRID_STEP+PATH_TOP_Y;
		Officer[n].alive =1;
		printf("Officer %d at: %d,%d\n", n, Officer[n].x, Officer[n].y);
}

void createWave(){
	
	time_t t;
	srand((unsigned) time(&t));
	Game.nbEnnemiWave = rand() %Game.nbWave +100+Game.nbWave;
	if(Game.nbEnnemiWave >= MAX_OFFICERS){
		Game.nbEnnemiWave = MAX_OFFICERS-1;
	}
	
}

void createOfficers(){
	int lane;
	
	if( Game.nbEnnemiCreated<=Game.nbEnnemiWave){
		lane = rand()%5;
		initOfficer(Game.nbEnnemiCreated, lane);
		Game.nbEnnemiCreated++;
	}
}

void drawOfficer()
{
	int i;
	for(i=0; i<Game.nbEnnemiCreated; i++){
		if(Officer[i].alive == 1){
		drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);
		}
	}	
}

void moveOfficers() {
	int i;
	
	for(i=0; i<=Game.nbEnnemiCreated;i++){
		if(Officer[i].alive == 1){
			Officer[i].x +=2;
		}		
	}
}

void doEnnemi(){
	int tick = Game.timer %25;
	if(Game.countdown ==0){
		createWave();
	}
	if(tick ==0){	
		createOfficers();
	}
	moveOfficers();
}