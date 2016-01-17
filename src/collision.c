#include "fonctions.h"

void collision()
{
    collisionTir_Ennemi();
    collisionEnnemi_Tourelle();
    collisionEnnemi_Base();
    collisionEnnemi_Roger();
}



void collisionTir_Ennemi()
{
    int i,j;
    tir *newTir = Tir;
    for(i=0; i<=Game.nbEnnemiCreated; i++)
    {
        while(newTir != NULL)
        {
            if( ( ( (Officer[i].x <= (*newTir).x) && ( (Officer[i].x + (GRID_STEP/5)) >= (*newTir).x) ) || ( (Officer[i].x <= (*newTir).x + 3*GRID_STEP/4) && ( (Officer[i].x + (GRID_STEP/5) ) >= (*newTir).x + GRID_STEP/2) ) )
                    && ((Officer[i].y - GRID_STEP/3) <= (*newTir).y) && ((Officer[i].y + GRID_STEP) >= (*newTir).y))
            {



                if((*newTir).tireur > -1 && Tourelle[(*newTir).tireur].level == 4)
                {
                    if(Tourelle[(*newTir).tireur].effet == 1)
                    {
                        Officer[i].x -= GRID_STEP/5;
                    }

                    else if(Tourelle[(*newTir).tireur].effet == 2 && (*newTir).degat > Officer[i].hpOfficer)
                    {
                        initTir((*newTir).x,(*newTir).y,(*newTir).dir,(*newTir).tireur,(*newTir).degat - Officer[i].hpOfficer);
                    }

                    else if(Tourelle[(*newTir).tireur].effet == 3)
                    {
                        for(j=0; j<MAX_OFFICERS; j++)
                        {
                            if((Officer[j].x > Officer[i].x - GRID_STEP && Officer[j].x < Officer[i].x + GRID_STEP ) && (Officer[j].y > Officer[i].y - GRID_STEP && Officer[j].y < Officer[i].y + GRID_STEP ))
                            {
                                Officer[j].hpOfficer -= (*newTir).degat;
                            }
                        }
                    }
                }

                Officer[i].hpOfficer -= (*newTir).degat;

                if(Officer[i].hpOfficer <=0)
                {
                    Officer[i].alive = 0;
                    Officer[i].x = Officer[i].y = -3 * SCREEN_HEIGHT;
                    Player.coins+=20 ;
                    Game.nbEnnemiKilled++;

                }
                (*newTir).on = 0;
                (*newTir).x = (*newTir).y = SCREEN_HEIGHT;
            }
            newTir = (*newTir).suivant;
        }
        newTir = Tir;
    }

}
void collisionEnnemi_Tourelle()
{

    int i,j;
    for(i=0; i<=Game.nbEnnemiCreated; i++)
    {
        for(j=0; j<=MAX_TOURELLES; j++)
        {
            if(Officer[i].x >= Tourelle[j].x - GRID_STEP && Officer[i].x  < Tourelle[j].x + GRID_STEP/2 && Officer[i].lane == Tourelle[j].lane )
            {


                if(Tourelle[j].alive == 1 )
                {

                    if( Game.timer % Officer[i].reloadrate == 0 )
                    {
                        Tourelle[j].hpTourelle --;
                        if(Tourelle[j].hpTourelle == 0)
                        {
                            Tourelle[j].alive = 0;
                            Game.nbTourelle --;
                        }
                    }
                    Officer[i].attack = 1;
                }
                else
                {
                    Officer[i].attack = 0;
                }
            }
        }
    }
}

void collisionEnnemi_Base()
{
    int i;
    for(i=0; i<Game.nbEnnemiCreated; i++)
    {
        if( Officer[i].lane == 0 || Officer[i].lane == 4 )
        {
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP/2) && Officer[i].alive == 1)
            {

                    Officer[i].attack = 1;
                if( Game.timer % Officer[i].reloadrate == 0 )
                {

                    Game.hpBase --;
                    if(Game.hpBase <= 0)
                    {
                        Game.hpBase =0;
                    }

                    if(Game.hpBase == 0)
                    {
                        Game.MenuPointer =350;
                        Game.stade = 2;

                    }
                }
            }
        }

        else
        {
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP))
            {

                    Officer[i].attack = 1;
                if( Game.timer % Officer[i].reloadrate == 0 )
                {

                    Game.hpBase --;
                    if(Game.hpBase <= 0)
                    {
                        Game.hpBase =0;
                    }

                    if(Game.hpBase <= 0)
                    {
                        Game.stade = 2;
                        Game.hpBase =0;
                    }
                }
            }
        }
    }
}


void collisionEnnemi_Roger()
{
    int i;


    if(Player.stun == 0 && Player.stuntime - Game.timer <= 0)
    {
        for(i=0; i<=Game.nbEnnemiCreated; i++)
        {


            if( ( (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y ) <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y + GRID_STEP/2 )
                    || (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y ) <  (Player.y + STEPHEN_ACTUAL_HEIGHT/3)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT/3) )
                    || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y + GRID_STEP/2 )
                    || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  (Player.y + STEPHEN_ACTUAL_HEIGHT/3)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT/3) )
                ) && Officer[i].alive == 1 )
            {

                Player.stun = 1;
                Player.stuntime = Game.timer + 200;

            }
        }

    }
    else
    {
        if(Player.stuntime - Game.timer <= 110)
        {
            Player.stun = 0;
        }


        if((Player.stuntime - Game.timer) > 170)
            drawText("3",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);

        else if((Player.stuntime - Game.timer) > 140)
            drawText("2",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);


        else if((Player.stuntime - Game.timer) > 110)
        {
            drawText("1",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);
        }

    }

}
