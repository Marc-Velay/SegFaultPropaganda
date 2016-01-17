#include "fonctions.h"


void init(char *title)
{
    int i;

     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)  //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }

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

    for(i=0; i<=MAX_OFFICERS; i++)
            {
                Officer[i].alive = 0;
                Officer[i].x=Officer[i].y=-3*SCREEN_WIDTH;
            }
            for(i=0; i<=MAX_TOURELLES; i++)
            {
                Tourelle[i].alive = 0;
                Tourelle[i].x=Tourelle[i].y=SCREEN_WIDTH*2;
            }

    getScore();
    Game.countdown =300;
    Game.timer =0;
    Game.nbWave=1;
    Game.nbTourelleCreated=0;
    Game.nbTourelle=0;
    Game.nbEnnemiAlive=0;
    Game.nbEnnemiKilled=0;
    Game.nbEnnemiWave=0;
    Game.hpBase=10;
    Game.MenuPointer =260;
    Tir = NULL;
    loadAllSprites();
    loadAllMusic();
    initPlayer();

}





void cleanup()
{
    freeSprites();

    TTF_Quit();

    SDL_Quit();
}
