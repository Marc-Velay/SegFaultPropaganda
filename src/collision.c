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
    int i;
    tir *newTir = Tir;
    for(i=0; i<=Game.nbEnnemiCreated; i++)
    {
        while(newTir != NULL)
        {
            if( ( ( (Officer[i].x <= (*newTir).x) && ( (Officer[i].x + (GRID_STEP/5)) >= (*newTir).x) ) || ( (Officer[i].x <= (*newTir).x + 3*GRID_STEP/4) && ( (Officer[i].x + (GRID_STEP/5) ) >= (*newTir).x + GRID_STEP/2) ) )
                && ((Officer[i].y - GRID_STEP/2) <= (*newTir).y) && ((Officer[i].y + GRID_STEP) >= (*newTir).y))
            {
                Officer[i].hpOfficer -=1;
                if(Officer[i].hpOfficer <=0)
                {
                    Officer[i].alive = 0;
                    Officer[i].x = Officer[i].y = 0;
                    Player.coins+=20;
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
        for(j=0; j<=Game.nbTourelleCreated; j++)
        {
            if(Officer[i].x >= Tourelle[j].x - GRID_STEP/2 && Officer[i].x  < Tourelle[j].x + GRID_STEP/2 && Officer[i].lane == Tourelle[j].lane  )
            {


                if(Tourelle[j].alive == 1 )
                {

                    if( Game.timer % Officer[i].reloadrate == 0 )
                    {
                        Tourelle[j].hpTourelle --;
                        if(Tourelle[j].hpTourelle == 0)
                        {
                            Tourelle[j].alive = 0;
                            Tourelle[j].x = 2*SCREEN_WIDTH;
                            Tourelle[j].y = 2*SCREEN_HEIGHT;
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
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP/2))
            {

                if( Game.timer % Officer[i].reloadrate == 0 )
                {

                    Game.hpBase --;

                    if(Game.hpBase == 0)
                    {
                        Game.stade = 2;
                    }
                }
            }
        }

        else
        {
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP))
            {

                if( Game.timer % Officer[i].reloadrate == 0 )
                {

                    Game.hpBase --;

                    if(Game.hpBase <= 0)
                    {
                        Game.stade = 2;
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


            if( ( (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y - GRID_STEP/2) <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y )
               || (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y - GRID_STEP/2) <  (Player.y + STEPHEN_ACTUAL_HEIGHT)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT) )
               || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y )
               || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  (Player.y + STEPHEN_ACTUAL_HEIGHT)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT) )
                ) )
                {

                    Player.stun = 1;
                    Player.stuntime = Game.timer + 300;

                }
            }

    }
     else
        {
            if(Player.stuntime - Game.timer <= 120) {Player.stun = 0;}


                        if((Player.stuntime - Game.timer) > 240)
                        drawText("3",Player.x,Player.y - GRID_STEP/2,Font);

                        else if((Player.stuntime - Game.timer) > 180)
                        drawText("2",Player.x,Player.y - GRID_STEP/2,Font);


                        else if((Player.stuntime - Game.timer) > 120)
                        drawText("1",Player.x,Player.y - GRID_STEP/2,Font);


        }

}
