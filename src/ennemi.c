#include "fonctions.h"

void initOfficer(int n, int lane)
{
    Officer[n].sprite = getSprite(OFFICER_SPRITE);
    Officer[n].x = 0;
    Officer[n].y = lane*GRID_STEP+PATH_TOP_Y;
    Officer[n].alive = 1;
    Officer[n].hpOfficer = OFFICIER_1_HP + 3*Game.nbWave/2;
    Officer[n].lane = lane;
    Officer[n].attack = 0;
    Officer[n].reloadrate = OFFICIER_1_RELOADRATE - Game.nbWave;
    if(Officer[n].reloadrate < 2)
    {
        Officer[n].reloadrate = 2;
    }
}

int pow(int nb, int pui)
{
    int i;

    for(i=0;i<pui;i++)
    {
        nb *= nb;
    }
    return nb;
}

void createWave()
{

    time_t t;
    Game.countdown=1;
    srand((unsigned) time(&t));

    Game.nbEnnemiWave = (rand() %Game.nbWave) + 4*Game.nbWave;
    if(Game.nbEnnemiWave >= MAX_OFFICERS)
    {
        Game.nbEnnemiWave = MAX_OFFICERS-1;
    }
    printf("nombre d'ennemis pour la vague %d: %d\n", Game.nbWave, Game.nbEnnemiWave);
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
                    Officer[i].x += 1 + Game.nbWave;
            }

            else
            {
                if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP))
                    Officer[i].x += 1 + Game.nbWave;
            }
        }
    }
}

void doEnnemi()
{
    int tick = Game.timer % (25-Game.nbWave/4);

    if(Game.nbWave >=24){tick = Game.timer % 2;}
    else{tick = Game.timer % (25-Game.nbWave);}
    getEnnemiAlive();
    if(Game.countdown ==0)
    {
        createWave();
        createOfficers();
        tick++;
    }
    if(tick == 0)
    {
        createOfficers();
    }
    moveOfficers();
}
