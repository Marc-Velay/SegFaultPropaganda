#include "fonctions.h"

//Initialise une tourelle 1
void creerTourelle1(int n,int colonne, int lane)
{
    Tourelle[n].type = 1;
    Tourelle[n].sprite = getSprite(TOURELLE_1_SPRITE);
    Tourelle[n].x = colonne*GRID_STEP  +8;
    Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
    Tourelle[n].alive =1;
    Tourelle[n].hpTourelle=TOURELLE_1_HP;
    Tourelle[n].inithpTourelle = TOURELLE_1_HP;
    Tourelle[n].lane = lane;
    Tourelle[n].effet = 0;
    Tourelle[n].level = 0;
    Tourelle[n].degat = 1;
    Tourelle[n].reloadrate=TOURELLE_1_RELOADRATE;
    Player.coins -= TOURELLE_1_PRICE;
}

//Initialise une tourelle 2
void creerTourelle2(int n,int colonne, int lane)
{
    Tourelle[n].type = 2;
    Tourelle[n].sprite = getSprite(TOURELLE_2_SPRITE);
    Tourelle[n].x = colonne*GRID_STEP  +8;
    Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
    Tourelle[n].alive =1;
    Tourelle[n].hpTourelle = TOURELLE_2_HP;
    Tourelle[n].inithpTourelle = TOURELLE_2_HP;
    Tourelle[n].lane = lane;
    Tourelle[n].effet = 0;
    Tourelle[n].level = 0;
    Tourelle[n].degat = 1;
    Tourelle[n].reloadrate = TOURELLE_2_RELOADRATE;
    Player.coins -= (TOURELLE_2_PRICE );
}

//Initialise une tourelle 3
void creerTourelle3(int n,int colonne, int lane)
{
    Tourelle[n].type = 3;
    Tourelle[n].sprite = getSprite(TOURELLE_3_SPRITE);
    Tourelle[n].x = colonne*GRID_STEP +8;
    Tourelle[n].y =(lane*GRID_STEP)+PATH_TOP_Y;
    Tourelle[n].alive =1;
    Tourelle[n].hpTourelle = TOURELLE_3_HP;
    Tourelle[n].inithpTourelle = TOURELLE_3_HP;
    Tourelle[n].lane = lane;
    Tourelle[n].effet = 0;
    Tourelle[n].level = 0;
    Tourelle[n].degat = 1;
    Tourelle[n].reloadrate = TOURELLE_3_RELOADRATE;
    Player.coins -= (TOURELLE_3_PRICE );
}

//Initialise les valeurs de la tourelle (position, degats, points de vie...) et la pose en fonction du type choisi
void initTourelle(int n, int colonne, int lane, int choixTourelle)
{
    int i;
    int created = 0;

    for(i=0; i<MAX_TOURELLES; i++)
    {
        if(Tourelle[i].alive == 0 && created ==0)
        {
            switch ( choixTourelle )
            {
            case 1:
                creerTourelle1(i, colonne, lane);
                break;

            case 2:
                creerTourelle2(i, colonne, lane);
                break;

            case 3:
                creerTourelle3(i, colonne, lane);
                break;

            default:
                printf("Tourelle type does not exist\n");
                break;
            }
            created = 1;
        }
    }
    if(created == 0)
    {
        switch ( choixTourelle )
        {
        case 1:
            creerTourelle1(n, colonne, lane);
            created =1;
            break;


        case 2:
            creerTourelle2(n, colonne, lane);
            created =1;
            break;

        case 3:
            creerTourelle3(n, colonne, lane);
            created=1;
            break;
        default:
            printf("Tourelle type does not exist\n");
            break;
        }
        Game.nbTourelleCreated++;
    }
}

//Dessine la tourelle, avec son upgrade, son buff et ses points de vies
void drawTourelle()
{
    int i;
    float Tourellehp;

    for(i=0; i<=MAX_TOURELLES; i++)
    {
        if(Tourelle[i].alive == 1)
        {
            if(Tourelle[i].level == 1) //Tourelle upgrade 1
            {
                drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                drawImage(getSprite(UPGRADE_1_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
            }

            else if(Tourelle[i].level == 2)//Tourelle upgrade 2
            {
                drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                drawImage(getSprite(UPGRADE_2_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
            }

            else if(Tourelle[i].level == 3)//Tourelle upgrade 3
            {

                drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                drawImage(getSprite(UPGRADE_3_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
            }

            else if(Tourelle[i].level == 4)//Tourelle upgrade 4
            {

                if(Tourelle[i].effet == 1)//Tourelle Buff 1
                {
                    drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                    drawImage(getSprite(UPGRADE_PUNCH_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
                }

                else if(Tourelle[i].effet == 2)//Tourelle Buff 2
                {
                    drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                    drawImage(getSprite(UPGRADE_DOUBLE_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
                }

                else if(Tourelle[i].effet == 3)//Tourelle Buff 3
                {
                    drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
                    drawImage(getSprite(UPGRADE_AOE_SPRITE),Tourelle[i].x-5, Tourelle[i].y-10);
                }

            }
            else // Tourelle sans upgrade
            {
                drawImage(Tourelle[i].sprite, Tourelle[i].x, Tourelle[i].y);
            }

            Tourellehp = Tourelle[i].inithpTourelle;

            //Affiche les points de vies
            if(Tourelle[i].hpTourelle < Tourellehp) {
		if (Tourelle[i].hpTourelle >= 0) {
			drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x +10  , Tourelle[i].y - 10 );

			if(Tourelle[i].hpTourelle > (Tourellehp/5)) {//Affiche 1/5 de la vie totale
			drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x +10  +11, Tourelle[i].y - 10 );

				if(Tourelle[i].hpTourelle >= (2*Tourellehp/5)) {//Affiche 2/5 de la vie totale
					drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x +10  +22, Tourelle[i].y - 10 );

						if(Tourelle[i].hpTourelle >= (3*Tourellehp/5) ) {//Affiche 3/5 de la vie totale
							drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x +10 +33, Tourelle[i].y - 10 );

							if(Tourelle[i].hpTourelle >= (4*Tourellehp/5)) {//Affiche 4/5 de la vie totale
								drawImage(getSprite(LIFE_SPRITE), Tourelle[i].x +10  +44, Tourelle[i].y - 10 );

							}
						}
					}
				}
			}
		}
        }
    }
}


//Créer la tourelle à la position du joueur
void createTourelle(int choixTourelle)
{
    int lane=0;
    int colonne=0;
    int temp=0;
    int empty =0;

    //Trouve la colonne et la ligne du joueur
    colonne = getColPlayer(Player.x);
    lane = getLanePlayer(Player.y);


    for(temp=0; temp<=MAX_TOURELLES; temp++)//Test si une tourelle est déjà à cette position
    {
        //Cas où une tourelle est déjà présente
        if(Tourelle[temp].x == colonne*GRID_STEP+8 && Tourelle[temp].y == (lane)*GRID_STEP+PATH_TOP_Y && Tourelle[temp].alive == 1)
        {
            empty =1;
        }
    }

    if(empty ==0)//si non, poser une tourelle
    {
        Game.nbTourelle++;
        initTourelle(Game.nbTourelle,colonne,lane,choixTourelle);
    }
    else
    {
        printf("La case est déjà occupé\n");
    }



}

//Fait tirer les tourelles posées
void doTourelle()
{
    int i,j;



    for(i=0; i<=MAX_TOURELLES; i++)//Test les tourelles et les ennemies
    {
        for(j=0; j<=Game.nbEnnemiWave; j++)
        {
            if(Tourelle[i].alive == 1 && Game.timer % Tourelle[i].reloadrate == 0 && Tourelle[i].lane == Officer[j].lane && Officer[j].alive == 1)
            { // Cas si il y a une tourelle sur la meme ligne qu'un ennemi, si oui tirer

                if(Tourelle[i].type == 2)
                {//Cas tourelle 3 tirs
                    initTir(Tourelle[i].x,Tourelle[i].y - GRID_STEP,1,i,Tourelle[i].degat);
                    initTir(Tourelle[i].x,Tourelle[i].y,1,i,Tourelle[i].degat);
                    initTir(Tourelle[i].x,Tourelle[i].y + GRID_STEP,1,i,Tourelle[i].degat);
                }
                else//Cas tourelle 1 tir
                {
                    initTir(Tourelle[i].x,Tourelle[i].y,1,i,Tourelle[i].degat);
                }
            }
        }
    }

}


//Upgrade les tourelles de type 1
void UpTourelle1(int i)
{
    Tourelle[i].hpTourelle += 2 + Tourelle[i].level;
    Tourelle[i].inithpTourelle = Tourelle[i].hpTourelle;
    Tourelle[i].reloadrate -= 3;
    Tourelle[i].degat += 1 + (Tourelle[i].level-1) ;
}

//Upgrade les tourelles de type 2
void UpTourelle2(int i)
{
    Tourelle[i].hpTourelle += 2 + Tourelle[i].level;
    Tourelle[i].inithpTourelle = Tourelle[i].hpTourelle;
    Tourelle[i].reloadrate -= 3;
    Tourelle[i].degat += 1 + (Tourelle[i].level-1) ;

}
//Upgrade les tourelles de type 3
void UpTourelle3(int i)
{
    Tourelle[i].hpTourelle += 2 + Tourelle[i].level;
    Tourelle[i].inithpTourelle = Tourelle[i].hpTourelle;
    Tourelle[i].reloadrate -= 2;
    Tourelle[i].degat += (Tourelle[i].level)/2 ;
}

//Upgrade la tourelle en fonction de son type et soustrait l'argent du joueur
void UpgradeTourelle(int i)
{

    switch(Tourelle[i].type)
    {
    case 1:
        UpTourelle1(i);
        break;

    case 2:
        UpTourelle2(i);
        break;

    case 3:
        UpTourelle3(i);
        break;

    }

    Player.coins -= UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level) + UPGRADE_PRICE;
    Tourelle[i].level ++;
}

//Vends la tourelle choisie en fonction de son type et de son niveau d'upgrade
void SellTourelle(int i)
{

    Tourelle[i].alive = 0;
    Game.nbTourelle--;

    switch(Tourelle[i].type)
    {
    case 1:
        Player.coins += TOURELLE_1_PRICE + UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level);
        break;
    case 2:
        Player.coins += TOURELLE_2_PRICE  + UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level);
        break;
    case 3:
        Player.coins += TOURELLE_3_PRICE + UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level);
        break;


    }
}
