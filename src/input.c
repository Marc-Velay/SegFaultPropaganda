#include "fonctions.h"


void UpdateEvents(Input* in)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            (*in).key[event.key.keysym.sym]=1;
            break;
        case SDL_KEYUP:
            (*in).key[event.key.keysym.sym]=0;
            break;
        case SDL_MOUSEMOTION:
            (*in).mousex=event.motion.x;
            (*in).mousey=event.motion.y;
            (*in).mousexrel=event.motion.xrel;
            (*in).mouseyrel=event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
            (*in).mousebuttons[event.button.button]=1;
            break;
        case SDL_MOUSEBUTTONUP:
            (*in).mousebuttons[event.button.button]=0;
            break;
        case SDL_QUIT:
            (*in).quit = 1;
            break;
        default:
            break;
        }
    }
}




void getInput()
{
    Input in;
    memset(&in,0,sizeof(in));
    int i;
    UpdateEvents(&in);
    int moux;
    int mouy;
    SDL_GetMouseState(&moux,&mouy);

    if(in.key[SDLK_ESCAPE] || in.quit)
    {
        exit(0);
    }
    /************************************MENU*********************************/
    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 543 && moux < 737) && (mouy >223 && mouy <256)) && Game.stade ==0)
        {
            printf("START GAME CLICKED\n");
            Game.stade = 1;
        }
        printf("LEFT BUTTON PRESSED in: %d, %d\n", moux, mouy);
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 588 && moux < 689) && (mouy >353 && mouy <401)) && Game.stade ==0)
        {
            printf("ABOUT PRESSED\n");
            Game.stade = 2;
        }
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 602 && moux < 673) && (mouy >480 && mouy <530)) && Game.stade ==0)
        {
            printf("QUIT PRESSED\n");
            SDL_Quit();
            exit(0);
        }
    }

      if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 540 && moux < 737) && (mouy >223 && mouy <273)) && Game.stade ==2)
        {
            printf("QUIT PRESSED\n");
            SDL_Quit();
            exit(0);
        }
    }

    /************************************MENU*********************************/


    /************************************LAST SCREEN*********************************/


    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 556 && moux < 724) && (mouy >423 && mouy <472)) && Game.stade ==2)
        {
            printf("Restart PRESSED\n");

            restart = 1;

           // main(0, NULL);



        }
    }
    /************************************LAST SCREEN*********************************/

    /************************************TOURELLES*********************************/
    // bouton Tourelle de gauche

    while(in.key[SDLK_p])
    {
           updateScreen();
            Game.timer +=1;
            Player.reload++;
            SDL_Delay(1);
            UpdateEvents(&in);
    }

   if( Player.stun  == 0){
    if (in.mousebuttons[SDL_BUTTON_LEFT] )
    {

        if(((moux > 30 && moux < 100) && (mouy >615 && mouy <682)) && Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP  && Player.coins >= TOURELLE_1_PRICE)
        {
            printf("CREATE TOURELLE 1 CLICKED\n");
            createTourelle(1);
            printf("TOURELLE 1 CREATED\n");
        }
    }

    // bouton Tourelle du centre
    if (in.mousebuttons[SDL_BUTTON_LEFT] )
    {

        if(((moux > 160 && moux < 226) && (mouy >615 && mouy <682)) && Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP && Player.coins >= (TOURELLE_2_PRICE + 10*(Game.nbWave-1)))
        {
            printf("CREATE TOURELLE 2 CLICKED\n");
            createTourelle(2);
            printf("TOURELLE 2 CREATED\n");
        }
    }

    // bouton Tourelle de droite
    if (in.mousebuttons[SDL_BUTTON_LEFT] )
    {

        if(((moux > 283 && moux < 355) && (mouy >615 && mouy <682)) && Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP &&  Player.coins >= TOURELLE_3_PRICE)
        {
            printf("CREATE TOURELLE 3 CLICKED\n");
            createTourelle(3);
            printf("TOURELLE 3 CREATED\n");
        }
    }

    /************************************TOURELLES*********************************/



    if(in.key[SDLK_SPACE])
    {
        if(Player.sprite == getSprite(PLAYER_R_SPRITE) && Player.reload > 20)
        {
            initTir(Player.x,Player.y,0);
            Player.reload = 0;
        }
        if(Player.sprite == getSprite(PLAYER_L_SPRITE) && Player.reload > 20)
        {
            initTir(Player.x,Player.y,1);
            Player.reload = 0;
        }
    }


        while((in.key[SDLK_d] || in.key[SDLK_s] || in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_DOWN] || in.key[SDLK_UP] || in.key[SDLK_LEFT] || in.key[SDLK_RIGHT]) && Player.stun ==0)
        {
            if(in.key[SDLK_d] || in.key[SDLK_RIGHT])
            {
                Player.sprite = getSprite(PLAYER_R_SPRITE);
                Player.x +=10;
                if(Player.x > SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH)
                {
                    Player.x = SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH;
                }

            }
            if(in.key[SDLK_s] || in.key[SDLK_DOWN])
            {
                Player.y +=10;
                if(Player.y > SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT)
                {
                    Player.y = SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT;
                }
            }
            if(in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_LEFT])
            {
                Player.sprite = getSprite(PLAYER_L_SPRITE);
                Player.x -=10;
                if(Player.x < 0)
                {
                    Player.x =0;
                }

            }
            if(in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_UP])
            {
                Player.y -=10;
                if(Player.y < 0)
                {
                    Player.y =0;
                }
            }
            if(in.key[SDLK_SPACE])
            {
                if(Player.sprite == getSprite(PLAYER_R_SPRITE) && Player.reload > 20)
                {
                    initTir(Player.x,Player.y,0);
                    Player.reload = 0;
                }
                if(Player.sprite == getSprite(PLAYER_L_SPRITE) && Player.reload > 20)
                {
                    initTir(Player.x,Player.y,1);
                    Player.reload = 0;
                }
            }

            updateScreen();
            Game.timer +=1;
            Player.reload++;
            SDL_Delay(16);
            UpdateEvents(&in);
        }
    }
}




