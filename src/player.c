#include "fonctions.h"

void initPlayer()
{
    int i;

    Player.sprite = getSprite(PLAYER_L_SPRITE);

    Player.x = 3*SCREEN_WIDTH / 4;
    Player.y = SCREEN_HEIGHT / 4;
    Player.coins =30000;
    Player.stun = 0;
    Player.stuntime =  0;

    for(i=0;i<13;i++)
    {
        Player.name[i] == ' ';
    }

    Player.nameInd = 0;
}

void drawPlayer()
{
    if(Player.stuntime - Game.timer > 0 )
    {
        if( Game.timer % 2 == 0)
        {
        drawImage(Player.sprite, Player.x, Player.y);
        }
    }
    else
        {
            drawImage(Player.sprite, Player.x, Player.y);
        }
}

int getColPlayer()
{

    int colonne=0;
    int temp=0;


    while(temp<=Player.x -GRID_STEP + STEPHEN_ACTUAL_WIDTH /2)
    {
        temp += GRID_STEP;
        colonne++;
    }
    return colonne;
}

int getLanePlayer()
{
     int lane=0;
    int temp=0;


    while(temp <= Player.y - PATH_TOP_Y - GRID_STEP + STEPHEN_ACTUAL_HEIGHT )
    {
        temp += GRID_STEP;
        lane++;
    }
    if(lane > 4)
    {
        lane =4;
    }

    return lane;
}


