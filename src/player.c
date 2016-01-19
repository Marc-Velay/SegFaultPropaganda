#include "fonctions.h"

void initPlayer()   // Initialisation des variables du personnage (Stephen) au début du jeu (Start Game)
{
    Player.sprite = getSprite(PLAYER_L_SPRITE); // Chargement de l'image du personnage
	Player.direction = 0;               // Définit le sens de déplacement du personnage
    Player.x = 3*SCREEN_WIDTH / 4;      // Positionnement du personnage
    Player.y = SCREEN_HEIGHT / 4;
    Player.coins = 300;                 // Argent disponible
    Player.stun = 0;                    // Définit si le personnage est assommé lors de la collision avec un agent
    Player.stuntime =  0;               // Définit le temps pendant lequel le personnage est assommé

    Player.nameInd = 0;
}

void drawPlayer()   // Affichage du sprite de Stephen sur la carte
{
    if(Player.stuntime - Game.timer > 0 )
    {
        if( Game.timer % 2 == 0) // Fait clignoter le sprite du personnage lorsque celui-ci est touché par un Agent
        {
        drawImage(Player.sprite, Player.x, Player.y);
        }
    }
    else    // Affichage permanent du personnage
        {
            drawImage(Player.sprite, Player.x, Player.y);
        }
}

/********** Récupération de la position du personnage **********/
int getColPlayer()
{

    int colonne=0;
    int temp=0;


    while(temp<=Player.x -GRID_STEP + 3*STEPHEN_ACTUAL_WIDTH /4)
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


    while(temp <= Player.y - PATH_TOP_Y - GRID_STEP + STEPHEN_ACTUAL_HEIGHT/2 )
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
/********** Récupération de la position du personnage **********/


