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
	//in.mousebuttons[SDL_BUTTON_LEFT] = 0;
	printf("LEFT BUTTON PRESSED in: %d, %d\n", moux, mouy);
	}

    while(in.key[SDLK_d] || in.key[SDLK_s] || in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_z] || in.key[SDLK_w])
    {
        if(in.key[SDLK_d])
        {
            Player.x +=10;
        }
        if(in.key[SDLK_s])
        {
            Player.y +=10;
        }
        if(in.key[SDLK_q] || in.key[SDLK_a])
        {
            Player.x -=10;
        }
        if(in.key[SDLK_z] || in.key[SDLK_w])
        {
            Player.y -=10;
        }

			updateScreen();
			SDL_Delay(16);
            UpdateEvents(&in);
    }

	/*if(in.key[SDLK_d]) {
		while(in.key[SDLK_d] && in.key[SDLK_a]==0 && in.key[SDLK_q]==0 && in.key[SDLK_z]==0 && in.key[SDLK_w]==0 && in.key[SDLK_s]==0){
			UpdateEvents(&in);
			Player.x +=10;
			updateScreen();
			SDL_Delay(16);
		}
		getInput();
	}
	if(in.key[SDLK_q] || in.key[SDLK_a]){
		while((in.key[SDLK_q] || in.key[SDLK_a])&& in.key[SDLK_s]==0 && in.key[SDLK_d]==0 && in.key[SDLK_z]==0 && in.key[SDLK_w]==0){
			UpdateEvents(&in);
			Player.x -=10;
			updateScreen();
            SDL_Delay(16);
		}
		getInput();
	}
	if(in.key[SDLK_z] || in.key[SDLK_w]) {
		while((in.key[SDLK_z] || in.key[SDLK_w])&& in.key[SDLK_s]==0 && in.key[SDLK_d]==0 && in.key[SDLK_q]==0 && in.key[SDLK_a]==0){
			UpdateEvents(&in);
			Player.y -=10;
			updateScreen();
            SDL_Delay(16);
		}
		getInput();
	}
	if(in.key[SDLK_s]){
		while(in.key[SDLK_s] && in.key[SDLK_q]==0 && in.key[SDLK_a]==0 && in.key[SDLK_d]==0 && in.key[SDLK_z]==0 && in.key[SDLK_w]==0){
			UpdateEvents(&in);
			Player.y +=10;
			updateScreen();
            SDL_Delay(16);
		}
		getInput();
	}*/

}


