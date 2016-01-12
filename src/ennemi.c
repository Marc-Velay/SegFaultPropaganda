#include "fonctions.h"

void initOfficer(int n, int lane)
{
    Officer[n].sprite = getSprite(OFFICER_SPRITE);
    Officer[n].x = 0;
    Officer[n].y = lane*GRID_STEP+PATH_TOP_Y;
    Officer[n].alive = 1;
    Officer[n].hpOfficer = OFFICIER_1_HP + (Game.nbWave*Game.nbWave/2) - Game.nbWave;
    Officer[n].lane = lane;
    Officer[n].attack = 0;
    Officer[n].reloadrate = OFFICIER_1_RELOADRATE - Game.nbWave;
    if(Officer[n].reloadrate < 2)
    {
        Officer[n].reloadrate = 2;
    }
}



void createWave()
{

    Game.nbWave+=1;
    time_t t;
    //Game.countdown=1;
    srand((unsigned) time(&t));

    Game.nbEnnemiWave = (rand() %Game.nbWave) + 2+ (Game.nbWave*Game.nbWave/2);
    if(Game.nbEnnemiWave >= MAX_OFFICERS)
    {
        Game.nbEnnemiWave = MAX_OFFICERS-1;
    }
    printf("nombre d'ennemis pour la vague %d: %d\n", Game.nbWave, Game.nbEnnemiWave);
}

void doWave()
{
     if(Game.nbEnnemiAlive==0 && Game.stade == 1 ){

            if(Game.countdown - Game.timer < 0 ){
                Game.countdown = Game.timer + 120;
            }
                else if(Game.countdown - Game.timer == 0)
                {
                Game.nbEnnemiCreated = 0;
                createWave();
                freeTir((*Tir).suivant);
                (*Tir).suivant = NULL;
                }

	    }
}

void createOfficers()
{
    int lane;

    if( Game.nbEnnemiCreated<=Game.nbEnnemiWave)
    {
        lane = rand()%5;
        Game.nbEnnemiAlive++;
        initOfficer(Game.nbEnnemiCreated, lane);
        Game.nbEnnemiCreated++;

    }
}

void drawOfficer()
{
    int i,j;

    for(j=0; j<5; j++)
    {
        for(i=0; i<Game.nbEnnemiCreated; i++)
        {

            if(Officer[i].alive == 1 && Officer[i].lane == j)
            {

                drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);
            }
        }
    }

}

void getEnnemiAlive()
{
    int i;
    int alive=0;
    for(i=0; i<Game.nbEnnemiCreated; i++)
    {
        if(Officer[i].alive == 1)
        {
            alive +=1;
        }
    }
    Game.nbEnnemiAlive= alive;
}

void moveOfficers()
{
    int i;

    for(i=0; i<=Game.nbEnnemiCreated; i++)
    {
        if(Officer[i].alive == 1 && Officer[i].attack != 1)
        {

            if( Officer[i].lane == 0 || Officer[i].lane == 4 )
            {
                if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP/2))
                    Officer[i].x += 2 + Game.nbWave/2;
            }

            else

            {
                if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP))
                    Officer[i].x += 2 + Game.nbWave/2;
            }
        }
    }
}

void doEnnemi()
{
    int tick = Game.timer % (25-Game.nbWave);

    if(Game.nbWave >=24){tick = Game.timer % 2;}
    else{tick = Game.timer % (25-Game.nbWave);}
    getEnnemiAlive();

    /*if(Game.countdown == 0)
    {
        Game.nbWave+=1;
        createWave();
        createOfficers();
        tick++;
        //Game.countdown++;
    }*/
    if(tick == 0)
    {
        createOfficers();
    }
    moveOfficers();
}
