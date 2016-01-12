#include "fonctions.h"

void initPlayer()
{
    Player.sprite = getSprite(PLAYER_L_SPRITE);

    Player.x = 3*SCREEN_WIDTH / 4;
    Player.y = SCREEN_HEIGHT / 4;
    Player.coins =3000;
    Player.stun = 0;
    Player.stuntime =  0;
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
