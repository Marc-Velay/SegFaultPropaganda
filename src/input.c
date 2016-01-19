#include "fonctions.h"


//Capture toutes les entrées utilisateur (clavier et souris)
void UpdateEvents(Input* in)
{	//remplis un tableau, où chaque case correspond à une touche par des 1 si la case a été appuyé.
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
        case SDL_MOUSEMOTION:		//Les entrees de la souris.
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



//Gère les intéractions du joueur avec le jeu (navigation dans le menu, poser tourelle, tirer, ecrire son nom...)
void getInput()
{
    Input in;
    memset(&in,0,sizeof(in));
    int i;
    UpdateEvents(&in);
    int moux;
    int mouy;	// coordonnées de la souris
    unsigned int frameLimit = SDL_GetTicks() + 45;
    SDL_GetMouseState(&moux,&mouy);	// rentre les coord en x et y de la souris dans les deux entiers moux et mouy
    int annimationFrame = Game.timer % 15;

    if(in.key[SDLK_ESCAPE] || in.quit)
    {
	    SDL_Quit();
	    exit(0);
    }


        //Gère les entrées dans le tutoriel
    /************************************TUTORIAL*********************************/
    //Il suffit de clic gauche avec la souris pour défiler le tutoriel en jeu
    if(Game.stade == 6 && in.mousebuttons[SDL_BUTTON_LEFT])
    {
        Game.stade = 0;
	moux = mouy =0;//Remet la position de la souris à zéro pour eviter de cliquer sur une touche du menu
    }

    if(Game.stade == 5 && in.mousebuttons[SDL_BUTTON_LEFT])
    {
        Game.stade = 6;
    }

    if(Game.stade == 4 && in.mousebuttons[SDL_BUTTON_LEFT])
    {
        Game.stade = 5;
    }

    /************************************TUTORIAL*********************************/

    //Passe le about par un clic gauche
    /************************************ABOUT*********************************/
    if(Game.stade == 7 && in.mousebuttons[SDL_BUTTON_LEFT] )
    {
        Game.stade = 0;
	moux = mouy =0;//Remet la position de la souris à zéro pour eviter de cliquer sur une touche du menu
    }
    /************************************ABOUT*********************************/

    //Gère les entrées dans le menu
    /************************************MENU*********************************/
    if (in.mousebuttons[SDL_BUTTON_LEFT])//Si le joueur clic sur start game
    {
        if(((moux > 521 && moux < 760) && (mouy >277 && mouy <319)) && Game.stade ==0)
        {
            printf("START GAME PRESSED\n");
            memset(&Player.name,0,sizeof(Player.name));//Met le nom du joueur à zéro avant le début de la partie
            Game.stade = -1;
        }
        printf("LEFT BUTTON PRESSED in: %d, %d\n", moux, mouy);
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])//Si le joueur clic sur tutorel
    {
        if(((moux > 550 && moux < 726) && (mouy >379 && mouy <416)) && Game.stade ==0)
        {
            printf("TUTORIAL PRESSED\n");
            Game.stade = 4;
        }
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])//Si le joueur clic sur le about
    {
        if(((moux > 581 && moux < 696) && (mouy >477 && mouy <518)) && Game.stade ==0)
        {
            printf("ABOUT PRESSED\n");
            Game.stade = 7;
        }
    }

    if (in.mousebuttons[SDL_BUTTON_LEFT])//Si le joueur clic sur quitter
    {
        if(((moux > 595 && moux < 684) && (mouy >580 && mouy <620)) && Game.stade == 0)
        {
            printf("QUIT PRESSED\n");
            SDL_Quit();
            exit(0);
        }
    }

    if (Game.stade == 0) // Place le pointeur dans le menu en fonction de la position de la souris
    {			// Annimation Stephen sur le menu
        if((mouy >277 && mouy <319))
        {
            Game.MenuPointer = 260;
        }


        if((mouy >379 && mouy <416) )
        {
            Game.MenuPointer = 360;
        }

        if((mouy >477 && mouy <518))
        {
            Game.MenuPointer = 460;
        }

        if((mouy >580 && mouy <620))
        {
            Game.MenuPointer = 560;
        }
    }

    /************************************MENU*********************************/


    //Gère la saisie du nom de joueur
    /************************************GET NAME*********************************/

        //strlen (const char *cs);
        if(Game.stade == -1)
        {
            if(Player.nameInd < 13)//Si le nom comporte moins de 13 lettres, ajouter lettre préssée
            {
                if(in.key[SDLK_a])
                {
                    Player.name[Player.nameInd] = 'A';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_b])
                {
                    Player.name[Player.nameInd] = 'B';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_c])
                {
                    Player.name[Player.nameInd] = 'C';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_d])
                {
                    Player.name[Player.nameInd] = 'D';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_e])
                {
                    Player.name[Player.nameInd] = 'E';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_f])
                {
                    Player.name[Player.nameInd] = 'F';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_g])
                {
                    Player.name[Player.nameInd] = 'G';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_h])
                {
                    Player.name[Player.nameInd] = 'H';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_i])
                {
                    Player.name[Player.nameInd] = 'I';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_j])
                {
                    Player.name[Player.nameInd] = 'J';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_k])
                {
                    Player.name[Player.nameInd] = 'K';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_l])
                {
                    Player.name[Player.nameInd] = 'L';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_m])
                {
                    Player.name[Player.nameInd] = 'M';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_n])
                {
                    Player.name[Player.nameInd] = 'N';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_o])
                {
                    Player.name[Player.nameInd] = 'O';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_p])
                {
                    Player.name[Player.nameInd] = 'P';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_q])
                {
                    Player.name[Player.nameInd] = 'Q';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_r])
                {
                    Player.name[Player.nameInd] = 'R';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_s])
                {
                    Player.name[Player.nameInd] = 'S';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_t])
                {
                    Player.name[Player.nameInd] = 'T';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_u])
                {
                    Player.name[Player.nameInd] = 'U';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_v])
                {
                    Player.name[Player.nameInd] = 'V';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_w])
                {
                    Player.name[Player.nameInd] = 'W';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_x])
                {
                    Player.name[Player.nameInd] = 'X';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_y])
                {
                    Player.name[Player.nameInd] = 'Y';
                    Player.nameInd++;
                }
                else if(in.key[SDLK_z])
                {
                    Player.name[Player.nameInd] = 'Z';
                    Player.nameInd++;
                }
            }       //Si la touche retour est préssé, effacer lettre et décrémenter indice chaine
                if(in.key[SDLK_BACKSPACE] && Player.nameInd > 0)
                {
                    Player.name[Player.nameInd-1] = ' ' ;
                    Player.nameInd--;
                } //Si touche entrée pressé, lancer la partie et la musique de jeu
                else if(in.key[SDLK_RETURN])
                {
                    Game.stade = 1;
                    Mix_HaltMusic();
                    Mix_VolumeChunk(musiqueLaser, 5);
                    Mix_PlayChannel(0, musiqueLaser, 0);
                    Mix_PlayMusic(musiqueGame, -1);
                }


        }

    /************************************GET NAME*********************************/



    //Gères les entrées sur l'écran de fin de jeu
    /************************************LAST SCREEN*********************************/


      if (in.mousebuttons[SDL_BUTTON_LEFT])//Cas highscore cliquée
    {
        if(((moux > 540 && moux < 735) && (mouy >250 && mouy <290)) && Game.stade ==2)
        {
            printf("HIGHSCORE PRESSED\n");
           Game.stade = 3;
        }
    }


    if (in.mousebuttons[SDL_BUTTON_LEFT])//Cas quitter cliquée
    {
        if(((moux > 595 && moux < 679) && (mouy >449 && mouy <489)) && Game.stade ==2)
        {
            printf("QUIT PRESSED\n");
            SDL_Quit();
            exit(0);
        }
    }


    if (in.mousebuttons[SDL_BUTTON_LEFT])//Cas restart cliquée
    {
        if(((moux > 518 && moux < 758) && (mouy >349 && mouy <389)) && Game.stade ==2)
        {

            printf("Restart PRESSED\n");
            Game.restart = 1;
        }
    }

    //Place le pointeur en fonction de la position de la souris
    if( (mouy >449 && mouy <489) && Game.stade ==2)
    {
        Game.MenuPointer = 440;
    }

    if( (mouy >349 && mouy <389) && Game.stade ==2)
    {
        Game.MenuPointer = 340;
    }

     if( (mouy >250 && mouy <290) && Game.stade ==2)
    {
        Game.MenuPointer = 240;
    }

    /************************************LAST SCREEN*********************************/




    /************************************HIGHSCORE SCREEN*********************************/

        //Test si le bouton quitter du highscore et pressé

    if (in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(((moux > 600 && moux < 675) && (mouy >650 && mouy <690)) && Game.stade ==3)
        {
            printf("RETURN MENU PRESSED\n");
            Game.restart = 1;
        }
    }





    /************************************HIGHSCORE SCREEN*********************************/


    //Gères les demande de création de tourelles de l'utilisateur

    /************************************TOURELLES*********************************/


    while(in.key[SDLK_p])
    {
        updateScreen();
        doWave();
        Game.timer +=1;
        Player.reload++;
        SDL_Delay(1);
        UpdateEvents(&in);
    }

    if( Player.stun  == 0)
    {
        if ((in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 30 && moux < 100) && (mouy >615 && mouy <682) ) || in.key[SDLK_1] )
        {

            if( Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y + STEPHEN_ACTUAL_HEIGHT>PATH_TOP_Y && Player.y - STEPHEN_ACTUAL_HEIGHT< PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH -  3*GRID_STEP  && Player.coins >= TOURELLE_1_PRICE)
            {// bouton Tourelle de gauche
                printf("CREATE TOURELLE 1 CLICKED\n");
                createTourelle(1);
                printf("TOURELLE 1 CREATED\n");
            }
        }

        // bouton Tourelle du centre
        if ( (in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 160 && moux < 226) && (mouy >615 && mouy <682)) || in.key[SDLK_2]  )
        {

            if(Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y -STEPHEN_ACTUAL_HEIGHT/2 && Player.y < PATH_BOTTOM_Y && Player.x < SCREEN_WIDTH - 3*GRID_STEP -STEPHEN_ACTUAL_WIDTH && Player.coins >= (TOURELLE_2_PRICE + 10*(Game.nbWave-1)))
            {
                printf("CREATE TOURELLE 2 CLICKED\n");
                createTourelle(2);
                printf("TOURELLE 2 CREATED\n");
            }
        }

        // bouton Tourelle de droite
        if ((in.mousebuttons[SDL_BUTTON_LEFT] && (moux > 283 && moux < 355) && (mouy >615 && mouy <682)) || in.key[SDLK_3] )
        {

            if(Game.stade ==1 && Game.nbTourelle+1 < MAX_TOURELLES && Player.y >PATH_TOP_Y-STEPHEN_ACTUAL_HEIGHT/2 && Player.y < PATH_BOTTOM_Y  && Player.x < SCREEN_WIDTH - 3*GRID_STEP -STEPHEN_ACTUAL_WIDTH &&  Player.coins >= (TOURELLE_3_PRICE + 10*(Game.nbWave-1)))
            {
                printf("CREATE TOURELLE 3 CLICKED\n");
                createTourelle(3);
                printf("TOURELLE 3 CREATED\n");
            }
        }

        if ((in.mousebuttons[SDL_BUTTON_RIGHT] && (moux < SCREEN_WIDTH - 3*GRID_STEP) && (mouy >PATH_TOP_Y && mouy < PATH_BOTTOM_Y)) && Game.stade ==1 )
        {

            //Gères le menu d'upgrade et de vente des tourelles
            for(i=0; i<MAX_TOURELLES; i++)
            {
                if(Tourelle[i].x < moux && Tourelle[i].x + 60 > moux  && Tourelle[i].y < mouy && Tourelle[i].y + 50 > mouy && Tourelle[i].alive == 1)
                {//Si un clic droit est effectué sur la tourelle, ouvrir le menu
                    Game.drawOption = 1;
                    Game.xOp = Tourelle[i].x ;
                    Game.yOp = Tourelle[i].y ;
                    Game.iOp = i;
                }

            }
        }

        //Gères les intéractions avec le menu des tourelles
        if(in.mousebuttons[SDL_BUTTON_LEFT] && Game.drawOption == 2 )
        {

            if((!(moux > Game.xOp +57 && moux < Game.xOp+107) && !(mouy > Game.yOp +10 && mouy < Game.yOp+85)) || Player.coins < UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level) + UPGRADE_PRICE)
            {//Quitte le menu si cliquée en dehors
                Game.drawOption = 0;
            }
        }

        if(in.mousebuttons[SDL_BUTTON_LEFT] && Game.drawOption == 1 )
        {
            if((moux > Game.xOp && moux < Game.xOp+60) && (mouy > Game.yOp && mouy < Game.yOp+35))
            {
                if(Tourelle[Game.iOp].level >= 3)
                {//Ouvre le menu des buff si tourelle level de base max
                    Game.drawOption = 2;
                }
                else if(Player.coins >= UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level) + UPGRADE_PRICE)
                {//Sinon et assez d'argent, upgrade la tourelle et ferme le menu

                    UpgradeTourelle(Game.iOp);
                    Game.drawOption = 0;
                }

                else
                {//Si pas assez d'argent quitte le menu sans upgrade
                    Game.drawOption = 0;
                }

            }

            else if((moux > Game.xOp && moux < Game.xOp+60) && (mouy > Game.yOp +35 && mouy < Game.yOp+55))
            {//Vend la tourelle si cliquée sur vendre
                SellTourelle(Game.iOp);
                Game.drawOption = 0;
            }
            else
            {//Quitte si cliquée en dehors du menu
                Game.drawOption = 0;
            }
        }


        //Cas du menu des buff ouvert
        if(in.mousebuttons[SDL_BUTTON_LEFT] && Game.drawOption == 2 )
        {

            if((moux > Game.xOp +57 && moux < Game.xOp+107) && (mouy > Game.yOp +10 && mouy < Game.yOp+85) && Player.coins >= UPGRADE_PRICE * (Tourelle[Game.iOp].level * Tourelle[Game.iOp].level) + UPGRADE_PRICE)
            {//Cas buff 1 choisi
                if((moux > Game.xOp +57 && moux < Game.xOp+107) && mouy < Game.yOp+35 )
                {
                    Tourelle[Game.iOp].level = 4;
                    Tourelle[Game.iOp].effet = 1;
                    Game.drawOption = 0;
                }
                else if((moux > Game.xOp +57 && moux < Game.xOp+107) && mouy < Game.yOp+60)
                {//Cas buff 2 choisi
                    Tourelle[Game.iOp].level = 4;
                    Tourelle[Game.iOp].effet = 2;
                    Game.drawOption = 0;
                }
                else if((moux > Game.xOp +57 && moux < Game.xOp+107) && mouy < Game.yOp+85)
                {//Cas buff 3 choisi
                    Tourelle[Game.iOp].level = 4;
                    Tourelle[Game.iOp].effet = 3;
                    Game.drawOption = 0;
                }
                //Soustraie l'argent du joueur du prix de l'upgrade
                Player.coins -= UPGRADE_PRICE * (3*3)  + UPGRADE_PRICE;

            }

        }


        /************************************TOURELLES*********************************/



        //Gères les déplacements et tirs de roger
        /************************************DEPLACEMENTS*********************************/


        //Tir si barre espace pressée
        if(in.key[SDLK_SPACE] && Game.stade == 1)
        {
            //A gauche ou a droite en fonction du sens du joueur
            if(Player.sprite == getSprite(PLAYER_R_SPRITE) && Player.reload > 20)
            {
                initTir(Player.x,Player.y+19,0,-1,1);
                Player.reload = 0;
            }
            if(Player.sprite == getSprite(PLAYER_L_SPRITE) && Player.reload > 20)
            {
                initTir(Player.x,Player.y+19,1,-1,1);
                Player.reload = 0;
            }
        }

        //Tant qu'une touche de déplacement est préssé, se déplacer
        while((in.key[SDLK_d] || in.key[SDLK_s] || in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_DOWN] || in.key[SDLK_UP] || in.key[SDLK_LEFT] || in.key[SDLK_RIGHT]) && Player.stun ==0  && Game.stade == 1)
        {
            if(in.key[SDLK_d] || in.key[SDLK_RIGHT])
            {//Si droite pressée

                //Player.sprite = getSprite(PLAYER_R_SPRITE);
		    Player.direction =0;
                Player.x +=5;
                if(Player.x > SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH)
                {
                    Player.x = SCREEN_WIDTH - STEPHEN_ACTUAL_WIDTH;
                }

            }
            if(in.key[SDLK_s] || in.key[SDLK_DOWN])
            {//Si bas pressée
                Player.y +=5;
                if(Player.y > SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT)
                {
                    Player.y = SCREEN_HEIGHT - STEPHEN_ACTUAL_HEIGHT - MENU_HEIGHT;
                }
            }
            if(in.key[SDLK_q] || in.key[SDLK_a] || in.key[SDLK_LEFT])
            {//Si gauche pressée
                Player.sprite = getSprite(PLAYER_L_SPRITE);
		    Player.direction = 1;
                Player.x -=5;
                if(Player.x < 0)
                {
                    Player.x =0;
                }

            }
            if(in.key[SDLK_z] || in.key[SDLK_w] || in.key[SDLK_UP])
            {//Si haut pressée
                Player.y -=5;
                if(Player.y < 0)
                {
                    Player.y = 0;
                }
            }
            if(in.key[SDLK_SPACE])
            {//Si tir pressé pendant un déplacement
                if(Player.direction == 0 && Player.reload > 20)
                {
                    initTir(Player.x,Player.y+19,0,-1,1);
                    Player.reload = 0;
                }
                if(Player.direction == 1 && Player.reload > 20)
                {
                    initTir(Player.x,Player.y+19,1,-1,1);
                    Player.reload = 0;
                }
            }

            if(Player.direction ==0){
                    //Animation en cas de déplacement de roger vers la droite
		    if(annimationFrame <3){
			    Player.sprite = getSprite(PLAYER_R1_SPRITE);
		    } else if(annimationFrame <6){
			    Player.sprite = getSprite(PLAYER_R2_SPRITE);

		    }else if(annimationFrame <9){
			    Player.sprite = getSprite(PLAYER_R4_SPRITE);

		    }else if(annimationFrame <12){
			    Player.sprite = getSprite(PLAYER_R3_SPRITE);

		    } else if(annimationFrame <15){
			    Player.sprite = getSprite(PLAYER_R5_SPRITE);
		    }
            }else if(Player.direction == 1) {
                 //Animation en cas de déplacement de roger vers la gauche
		    if(annimationFrame <3){
			    Player.sprite = getSprite(PLAYER_L1_SPRITE);
		    } else if(annimationFrame <6){
			    Player.sprite = getSprite(PLAYER_L2_SPRITE);

		    }else if(annimationFrame <9){
			    Player.sprite = getSprite(PLAYER_L4_SPRITE);

		    }else if(annimationFrame <12){
			    Player.sprite = getSprite(PLAYER_L3_SPRITE);

		    } else if(annimationFrame <15){
			    Player.sprite = getSprite(PLAYER_L5_SPRITE);
		    }
            }

        /************************************DEPLACEMENTS*********************************/
        //Boucle le jeu aussi pour ne pas avoir de désynchronisation des frames
        updateScreen();
	doWave();
        Game.timer +=1;
        Player.reload++;
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 45;
         UpdateEvents(&in);
	 annimationFrame = Game.timer % 15;

        }
                if(Player.direction == 1) {
			Player.sprite = getSprite(PLAYER_L_SPRITE);
		} else {Player.sprite = getSprite(PLAYER_R_SPRITE);}
    }
}




