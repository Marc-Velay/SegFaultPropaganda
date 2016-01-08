#include "fonctions.h"

void initOfficer(int n, int lane)
{
		Officer[n].sprite = getSprite(OFFICER_SPRITE);
		Officer[n].x = 0;
		Officer[n].y = lane*GRID_STEP+PATH_TOP_Y;
		Officer[n].alive = 1;
		Officer[n].lane = lane;
}

void createWave(){

	time_t t;
	srand((unsigned) time(&t));
	Game.nbEnnemiWave = rand() %Game.nbWave +2;
	if(Game.nbEnnemiWave >= MAX_OFFICERS){
		Game.nbEnnemiWave = MAX_OFFICERS-1;
	}
	printf("nombre d'ennemis pour la vague: %d", Game.nbEnnemiWave);
}

void createOfficers(){
	int lane;

	if( Game.nbEnnemiCreated<=Game.nbEnnemiWave){
		lane = rand()%5;
		initOfficer(Game.nbEnnemiCreated, lane);
		Game.nbEnnemiCreated++;
		Game.nbEnnemiAlive++;
	}
}

void drawOfficer()
{
	int i,j;

    for(j=0;j<5;j++)
    {
        for(i=0; i<Game.nbEnnemiCreated; i++){

            if(Officer[i].alive == 1 && Officer[i].lane == j){

            drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);
            }
        }
    }

}


void moveOfficers() {
	int i;

	for(i=0; i<=Game.nbEnnemiCreated;i++){
		if(Officer[i].alive == 1){

                if( Officer[i].lane == 0 || Officer[i].lane == 4 )
                {
                    if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP/2))
                        Officer[i].x +=2;
                }

                else
                {
                    if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP))
                        Officer[i].x +=2;
                }
		}
	}
}

void doEnnemi(){
	int tick = Game.timer %25;
	if(Game.countdown ==0){
		createWave();
		printf("test\n");
		Game.countdown=1;
	}
	if(tick ==0){
		createOfficers();
	}
	moveOfficers();
}
