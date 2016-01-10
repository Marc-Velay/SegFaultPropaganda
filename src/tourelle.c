#include "fonctions.h"

void initTourelle(int n, int colonne, int lane, int choixTourelle)
{
    int i;
    int recycled = 0;


    for(i=0;i<Game.nbTourelleCreated;i++)
    {
        if(Tourelle[i].alive == 0 && recycled == 0)
        {
           switch ( choixTourelle ) {
            case 1:
                Game.nbTourelleCreated++;
                Tourelle[n].sprite = getSprite(TOURELLE_SPRITE);
                Tourelle[n].x = colonne*GRID_STEP;
                Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y+30;
                Tourelle[n].alive =1;
                Tourelle[n].hpTourelle=5;
                Tourelle[n].lane = lane;
                Tourelle[n].reloadrate=20;
                recycled = 1;
                printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
                break;

            default:
                printf("Tourelle type does not exist\n");
                break;
            }
        }
    }
    if(recycled==0)
    {
    switch ( choixTourelle ) {
    case 1:
        Game.nbTourelleCreated++;
		Tourelle[n].sprite = getSprite(TOURELLE_SPRITE);
		Tourelle[n].x = colonne*GRID_STEP;
		Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y+30;
		Tourelle[n].alive =1;
		Tourelle[n].hpTourelle=5;
		Tourelle[n].lane = lane;
		Tourelle[n].reloadrate=20;
		printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);

    break;
    default:
        printf("Tourelle type does not exist\n");
        break;
        }
    }
}

void drawTourelle()
{
	int i;
	for(i=0; i<=Game.nbTourelleCreated; i++){
		if(Tourelle[i].alive == 1){
		drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
		}
	}
}

void createTourelle(int choixTourelle){
	int lane=0;
	int colonne=0;
	int temp=0;
	int empty =0;

	while(temp<Player.x -GRID_STEP + STEPHEN_ACTUAL_WIDTH /2){
		temp += GRID_STEP;
		colonne++;
	}
	temp =0;
	while(temp <= Player.y - PATH_TOP_Y -GRID_STEP + STEPHEN_ACTUAL_HEIGHT /4){
		temp += GRID_STEP;
		lane++;
	}
	if(lane > 4){lane =4;}
	for(temp=0; temp<=Game.nbTourelleCreated; temp++){
		    if(Tourelle[temp].x == colonne*GRID_STEP && Tourelle[temp].y == (lane)*GRID_STEP+PATH_TOP_Y+30) { empty =1;}
	    }
	    if(empty ==0) {
		    Game.nbTourelle++;
		    initTourelle(Game.nbTourelle,colonne,lane,choixTourelle);
		    Player.coins -=100;
	    } else { printf("La case est déjà occupé\n"); }



}

void doTourelle(){
	/*if(Game.countdown ==0){
		shoot();
		Game.countdown ++;
	}*/
	int i,j;



	for(i=0; i<=Game.nbTourelleCreated; i++)
        {
            for(j=0; j<Game.nbEnnemiCreated; j++)
            {
                if(Tourelle[i].alive == 1 && Game.timer % Tourelle[i].reloadrate == 0 && Tourelle[i].lane == Officer[j].lane && Officer[j].alive == 1)
                {
                initTir(Tourelle[i].x,Tourelle[i].y,1);
                }
            }
        }

}

