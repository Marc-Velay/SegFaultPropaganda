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
        if(((moux > 555 && moux < 883) && (mouy >240 && mouy <279)) && Game.stade ==0)
        {
            printf("START GAME CLICKED\n");
            Game.stade = 1;
        }
        printf("LEFT BUTTON PRESSED in: %d, %d\n", moux, mouy);
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 554 && moux < 737) && (mouy >366 && mouy <405)) && Game.stade ==0)
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

            Game.restart = 1;

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
    if ((in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 30 && moux < 100) && (mouy >615 && mouy <682) ) || in.key[SDLK_1] )
    {

        if( Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP  && Player.coins >= TOURELLE_1_PRICE)
        {
            printf("CREATE TOURELLE 1 CLICKED\n");
            createTourelle(1);
            printf("TOURELLE 1 CREATED\n");
        }
    }

    // bouton Tourelle du centre
    if ( (in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 160 && moux < 226) && (mouy >615 && mouy <682)) || in.key[SDLK_2]  )
    {

        if(Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP && Player.coins >= (TOURELLE_2_PRICE + 10*(Game.nbWave-1)))
        {
            printf("CREATE TOURELLE 2 CLICKED\n");
            createTourelle(2);
            printf("TOURELLE 2 CREATED\n");
        }
    }

    // bouton Tourelle de droite
    if ((in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 283 && moux < 355) && (mouy >615 && mouy <682)) || in.key[SDLK_3] )
    {

        if(Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP &&  Player.coins >= (TOURELLE_3_PRICE + 10*(Game.nbWave-1)))
        {
            printf("CREATE TOURELLE 3 CLICKED\n");
            createTourelle(3);
            printf("TOURELLE 3 CREATED\n");
        }
    }

    if ((in.mousebuttons[SDL_BUTTON_RIGHT] && (moux < SCREEN_WIDTH - 3*GRID_STEP) && (mouy >PATH_TOP_Y && mouy < PATH_BOTTOM_Y)) && Game.stade ==1 )
        {


            for(i=0;i<MAX_TOURELLES;i++)
            {
                if(Tourelle[i].x < moux && Tourelle[i].x + 60 > moux  && Tourelle[i].y < mouy && Tourelle[i].y + 50 > mouy && Tourelle[i].alive == 1)
                {
                    Game.drawOption = 1;
                    Game.xOp = Tourelle[i].x ;
                    Game.yOp = Tourelle[i].y ;
                }

            }
        }

        if(in.mousebuttons[SDL_BUTTON_LEFT] && Game.drawOption == 1 )
        {
            if((moux > Game.xOp && moux < Game.xOp+60) && (mouy > Game.yOp && mouy < Game.yOp+35))
            {
                UpgradeTourelle(Game.xOp,Game.yOp);
                Game.drawOption = 0;
            }

            else if((moux > Game.xOp && moux < Game.xOp+60) && (mouy > Game.yOp +35 && mouy < Game.yOp+55))
            {
                SellTourelle(Game.xOp,Game.yOp);
                Game.drawOption = 0;
            }
            else
            {
                Game.drawOption = 0;
            }
        }

        if(in.key[SDLK_4] && Game.stade == 1)
        {
            if(Game.pushBack != 1){Game.pushBack = 1;}
            else{Game.pushBack = 0;}
        }

       if(in.key[SDLK_5] && Game.stade == 1)
        {
            if(Game.doubleShot != 1){Game.doubleShot = 1;}
            else{Game.doubleShot = 0;}

        }
        if(in.key[SDLK_6] && Game.stade == 1)
        {
            if(Game.deadAIM != 1){Game.deadAIM = 1;}
            else{Game.deadAIM = 0;}
        }

        if(in.key[SDLK_7] && Game.stade == 1)
        {
            if(Game.AOE != 1){Game.AOE = 1;}
            else{Game.AOE = 0;}
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




