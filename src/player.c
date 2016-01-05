#include "fonctions.h"

void initPlayer()
{
	Player.sprite = getSprite(PLAYER_SPRITE);
	
	Player.x = 3*SCREEN_WIDTH / 4;
	Player.y = SCREEN_HEIGHT / 4;
}

void drawPlayer()
{
	drawImage(Player.sprite, Player.x, Player.y);
}