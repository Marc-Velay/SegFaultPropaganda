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

	//SDL_Event event;
	UpdateEvents(&in);
	int moux;
	int mouy;
	SDL_GetMouseState(&moux,&mouy);

	if(in.key[SDLK_ESCAPE] || in.quit) {
	  exit(0);
	}

	if (in.mousebuttons[SDL_BUTTON_LEFT]) {
	  if(((moux > 543 && moux < 737) && (mouy >223 && mouy <256)) && Game.stade ==0) {
	    printf("START GAME CLICKED\n");
	    Game.stade = 1;
	  }
	printf("LEFT BUTTON PRESSED in: %d, %d\n", moux, mouy);
	}

	if (in.mousebuttons[SDL_BUTTON_LEFT] ) {

	  if(((moux > 30 && moux < 100) && (mouy >615 && mouy <690)) && Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y && Player.y < PATH_BOTTOM_Y ) {
	    printf("CREATE TOURELLE CLICKED\n");
	    createTourelle(moux, mouy);
	    printf("TOURELLE CREATED\n");
	  }
	}



    if(in.key[SDLK_SPACE])
    {
        if((Player.sprite == getSprite(PLAYER_R_SPRITE))&& (Player.reload >= 25)) initTir(Player.x,Player.y,0);
        if((Player.sprite == getSprite(PLAYER_L_SPRITE))&& (Player.reload >= 25)) initTir(Player.x,Player.y,1);
    }

    while(in.key[SDLK_d] || in.key[SDLK_s] || in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_DOWN] || in.key[SDLK_UP] || in.key[SDLK_LEFT] || in.key[SDLK_RIGHT])
    {
        if(in.key[SDLK_d] || in.key[SDLK_RIGHT])
        {
            Player.sprite = getSprite(PLAYER_R_SPRITE);
            Player.x +=10;
	    if(Player.x > SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH) { Player.x = SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH;}

        }
        if(in.key[SDLK_s] || in.key[SDLK_DOWN])
        {
            Player.y +=10;
	     if(Player.y > SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT) { Player.y = SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT;}
        }
        if(in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_LEFT])
        {
            Player.sprite = getSprite(PLAYER_L_SPRITE);
            Player.x -=10;
	    if(Player.x < 0) {Player.x =0;}

        }
        if(in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_UP])
        {
            Player.y -=10;
	    if(Player.y < 0) {Player.y =0;}
        }
        if(in.key[SDLK_SPACE])
    {
        if((Player.sprite == getSprite(PLAYER_R_SPRITE))&& (Player.reload >= 25)) initTir(Player.x,Player.y,0) ;
        if((Player.sprite == getSprite(PLAYER_L_SPRITE))&& (Player.reload >= 25)) initTir(Player.x,Player.y,1);
    }
/*
         if(in.key[SDLK_SPACE])
    {
        if((Player.sprite == getSprite(PLAYER_R_SPRITE)) && Tir.reload >= 25) initTir(Player.x,Player.y,0);
        if((Player.sprite == getSprite(PLAYER_L_SPRITE)) && Tir.reload >= 25) initTir(Player.x,Player.y,1);
    }
*/
	updateScreen();
	Game.timer +=1;
	Player.reload +=1;
	SDL_Delay(16);
        UpdateEvents(&in);
    }
}


