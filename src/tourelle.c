#include "fonctions.h"

void initTourelle(int n, int colonne, int lane, int choixTourelle)
{
    int i;
    int created =0;

    for(i=0; i<MAX_TOURELLES; i++)
    {
        if(Tourelle[i].alive == 0 && created ==0)
        {
            switch ( choixTourelle )
            {
            case 1:
                Tourelle[i].type = 1;
                Tourelle[i].sprite = getSprite(TOURELLE_1_SPRITE);
                Tourelle[i].x = colonne*GRID_STEP  +8;
                Tourelle[i].y =(lane*GRID_STEP)+PATH_TOP_Y;
                Tourelle[i].alive =1;
                Tourelle[i].hpTourelle=TOURELLE_1_HP;
                Tourelle[i].lane = lane;
                Tourelle[i].effet = 0;
                Tourelle[i].level = 0;
                Tourelle[i].reloadrate=TOURELLE_1_RELOADRATE;
                Player.coins -= TOURELLE_1_PRICE;
                created = 1;
                printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
                break;

            case 2:
                Tourelle[i].type = 2;
                Tourelle[i].sprite = getSprite(TOURELLE_2_SPRITE);
                Tourelle[i].x = colonne*GRID_STEP  +8;
                Tourelle[i].y =(lane*GRID_STEP)+PATH_TOP_Y;
                Tourelle[i].alive =1;
                Tourelle[i].hpTourelle=TOURELLE_2_HP;
                Tourelle[i].lane = lane;
                Tourelle[i].effet = 0;
                Tourelle[i].level = 0;
                Tourelle[i].reloadrate=TOURELLE_2_RELOADRATE;
                Player.coins -= (TOURELLE_2_PRICE);
                created = 1;
                printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
                break;

            case 3:
                Tourelle[i].type = 3;
                Tourelle[i].sprite = getSprite(TOURELLE_3_SPRITE);
                Tourelle[i].x = colonne*GRID_STEP  +8;
                Tourelle[i].y =(lane*GRID_STEP)+PATH_TOP_Y;
                Tourelle[i].alive =1;
                Tourelle[i].hpTourelle=TOURELLE_3_HP;
                Tourelle[i].lane = lane;
                Tourelle[i].effet = 0;
                Tourelle[i].level = 0;
                Tourelle[i].reloadrate=TOURELLE_3_RELOADRATE;
                Player.coins -= (TOURELLE_3_PRICE);
                created = 1;
                printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
                break;

            default:
                printf("Tourelle type does not exist\n");
                break;
            }
        }
    }
    if(created==0)
    {
        switch ( choixTourelle )
        {
        case 1:
            Tourelle[n].type = 1;
            Game.nbTourelleCreated++;
            Tourelle[n].sprite = getSprite(TOURELLE_1_SPRITE);
            Tourelle[n].x = colonne*GRID_STEP  +8;
            Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
            Tourelle[n].alive =1;
            Tourelle[n].hpTourelle = TOURELLE_1_HP;
            Tourelle[n].lane = lane;
            Tourelle[n].effet = 0;
            Tourelle[n].level = 0;
            Tourelle[n].reloadrate = TOURELLE_1_RELOADRATE;
            Player.coins -= TOURELLE_1_PRICE;
            created =1;
            printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
            break;


        case 2:
            Tourelle[n].type = 2;
            Game.nbTourelleCreated++;
            Tourelle[n].sprite = getSprite(TOURELLE_2_SPRITE);
            Tourelle[n].x = colonne*GRID_STEP  +8;
            Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
            Tourelle[n].alive =1;
            Tourelle[n].hpTourelle = TOURELLE_2_HP;
            Tourelle[n].lane = lane;
            Tourelle[n].effet = 0;
            Tourelle[n].level = 0;
            Tourelle[n].reloadrate = TOURELLE_2_RELOADRATE;
            Player.coins -= (TOURELLE_2_PRICE );
            created =1;
            printf("Tourelle %d at: %d,%d\n", n, Tourelle[n].x, Tourelle[n].y);
            break;

        case 3:
            Tourelle[n].type = 3;
            Game.nbTourelleCreated++;
            Tourelle[n].sprite = getSprite(TOURELLE_3_SPRITE);
            Tourelle[n].x = colonne*GRID_STEP +8;
            Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
            Tourelle[n].alive =1;
            Tourelle[n].hpTourelle = TOURELLE_3_HP;
            Tourelle[n].lane = lane;
            Tourelle[n].effet = 0;
            Tourelle[n].level = 0;
            Tourelle[n].reloadrate = TOURELLE_3_RELOADRATE;
            Player.coins -= (TOURELLE_3_PRICE );
            created=1;
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
    float tourellehp;

    for(i=0; i<=MAX_TOURELLES; i++)
    {
        if(Tourelle[i].alive == 1)
        {
            if(Tourelle[i].level == 1){
            drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
            drawImage(getSprite(UPGRADE_1_SPRITE),Tourelle[i].x, Tourelle[i].y);
	    tourellehp = TOURELLE_1_HP;
            }

         else if(Tourelle[i].level == 2){
            drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
            drawImage(getSprite(UPGRADE_2_SPRITE),Tourelle[i].x, Tourelle[i].y);
	    tourellehp = TOURELLE_2_HP;
         }

        else if(Tourelle[i].level == 3){
            drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
            drawImage(getSprite(UPGRADE_3_SPRITE),Tourelle[i].x, Tourelle[i].y);
	    tourellehp = TOURELLE_3_HP;
            }
        else{
                drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
            }
            
             if(Tourelle[i].hpTourelle < tourellehp) {
			if(Tourelle[i].hpTourelle >= (tourellehp/5)) {					
				drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x -20 , Tourelle[i].y - 10 );	
				
				if(Tourelle[i].hpTourelle >= (2*tourellehp/5)) {							
					drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x -20 +11, Tourelle[i].y - 10 );			
					
					if(Tourelle[i].hpTourelle >= (3*tourellehp/5) ) {							
						drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x -20 +22, Tourelle[i].y - 10 );	
						
						if(Tourelle[i].hpTourelle >= (4*tourellehp/5)) {							
							drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x -20 +33, Tourelle[i].y - 10 );	
							
						}
					}
				}
			}
	        }
        }
    }
}



void createTourelle(int choixTourelle)
{
    int lane=0;
    int colonne=0;
    int temp=0;
    int empty =0;

   colonne = getColPlayer(Player.x);

    lane = getLanePlayer(Player.y);


    for(temp=0; temp<=MAX_TOURELLES; temp++)
    {
        if(Tourelle[temp].x == colonne*GRID_STEP+8 && Tourelle[temp].y == (lane)*GRID_STEP+PATH_TOP_Y && Tourelle[temp].alive == 1)
        {
            empty =1;
        }
    }
    if(empty ==0)
    {
        Game.nbTourelle++;
        initTourelle(Game.nbTourelle,colonne,lane,choixTourelle);
    }
    else
    {
        printf("La case est déjà occupé\n");
    }



}

void doTourelle()
{
    int i,j;



    for(i=0; i<=MAX_TOURELLES; i++)
    {
        for(j=0; j<=Game.nbEnnemiWave; j++)
        {
            if(Tourelle[i].alive == 1 && Game.timer % Tourelle[i].reloadrate == 0 && Tourelle[i].lane == Officer[j].lane && Officer[j].alive == 1)
            {
                if(Tourelle[i].reloadrate == TOURELLE_2_RELOADRATE)
                {
                 initTir(Tourelle[i].x,Tourelle[i].y - GRID_STEP/2,1,i,Tourelle[i].effet);
                 initTir(Tourelle[i].x,Tourelle[i].y,1,i,Tourelle[i].effet);
                 initTir(Tourelle[i].x,Tourelle[i].y + GRID_STEP/2,1,i,Tourelle[i].effet);
                }
                else
                {
                    initTir(Tourelle[i].x,Tourelle[i].y,1,i,Tourelle[i].effet);
                }
            }
        }
    }

}


void UpgradeTourelle(int x, int y)
{
    int i;

    for(i=0;i<MAX_TOURELLES;i++)
            {
                if(Tourelle[i].x == x && Tourelle[i].y == y)
                {
                    printf("hp avant:%lf reload avant:%d\n",Tourelle[i].hpTourelle,Tourelle[i].reloadrate);
                    Tourelle[i].hpTourelle += 2 + (Game.nbWave*Game.nbWave);
                    Tourelle[i].reloadrate -= 2 + Game.nbWave;
                    Tourelle[i].level ++;
                    Player.coins -= 20;
                    printf("hp aprés: %lf reload après: %d\n",Tourelle[i].hpTourelle,Tourelle[i].reloadrate);
                }
            }
}


void SellTourelle(int x, int y)
{
    int i;

    for(i=0;i<MAX_TOURELLES;i++)
            {
                if(Tourelle[i].x == x && Tourelle[i].y == y)
                {
                    Tourelle[i].alive = 0;
                    switch(Tourelle[i].type)
                    {
                    case 1:
                        Player.coins += TOURELLE_1_PRICE;
                        break;
                    case 2:
                        Player.coins += TOURELLE_2_PRICE + 5*Game.nbWave;
                        break;
                    case 3:
                        Player.coins += TOURELLE_3_PRICE + 5*Game.nbWave;
                        break;
                    }
                }
            }
}
