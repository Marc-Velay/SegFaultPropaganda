#include "fonctions.h"


void init(char *title)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE);

    if (screen == NULL)
    {
        printf("Couldn't set screen mode to 1280 x 720: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_WM_SetCaption(title, NULL);

    Game.stade=0;
    Game.countdown =300;
    Game.timer =0;
    Game.nbWave=1;
    Game.nbTourelleCreated=0;
    Game.nbTourelle=0;
    Game.nbEnnemiAlive=0;
    Game.hpBase=10;
    Tir = NULL;
    loadAllSprites();
    initPlayer();
}





void cleanup()
{
    freeSprites();

    TTF_Quit();

    SDL_Quit();
}
