#include "fonctions.h"

//Appelle toutes les collisions
void collision()
{
    collisionTir_Ennemi();
    collisionEnnemi_Tourelle();
    collisionEnnemi_Base();
    collisionEnnemi_Roger();
}


//Gere les collisions des tirs de tourelles et de Roger avec les ennemies
void collisionTir_Ennemi()
{
    int i,j;
    tir *newTir = Tir;
    for(i=0; i<=Game.nbEnnemiCreated; i++) /// Boucles qui testent tout les tirs avec tout les officiers
    {
        while(newTir != NULL)
        {
            if( ( ( (Officer[i].x <= (*newTir).x) && ( (Officer[i].x + (GRID_STEP/5)) >= (*newTir).x) ) || ( (Officer[i].x <= (*newTir).x + 3*GRID_STEP/4) && ( (Officer[i].x + (GRID_STEP/5) ) >= (*newTir).x + GRID_STEP/2) ) )
                    && ((Officer[i].y - GRID_STEP/3) <= (*newTir).y) && ((Officer[i].y + GRID_STEP) >= (*newTir).y))
            {



                if((*newTir).tireur > -1 && Tourelle[(*newTir).tireur].level == 4)
                    //Teste si c'est une tourelle avec une compétence qui a tiré
                {
                    if(Tourelle[(*newTir).tireur].effet == 1)//Test si c'est la compétence 1
                    {
                        Officer[i].x -= GRID_STEP/5;
                         Officer[i].attack = 0;
                   }

                    else if(Tourelle[(*newTir).tireur].effet == 2 && (*newTir).degat > Officer[i].hpOfficer) //Test si c'est la compétence 2
                    {
                        initTir((*newTir).x,(*newTir).y,(*newTir).dir,(*newTir).tireur,(*newTir).degat - Officer[i].hpOfficer);
                    }

                    else if(Tourelle[(*newTir).tireur].effet == 3)//Test si c'est la compétence 3
                    {
                        for(j=0; j<MAX_OFFICERS; j++)
                        {
                            if((Officer[j].x > Officer[i].x - GRID_STEP && Officer[j].x < Officer[i].x + GRID_STEP ) && (Officer[j].y > Officer[i].y - GRID_STEP && Officer[j].y < Officer[i].y + GRID_STEP ))
                            {
                                Officer[j].hpOfficer -= (*newTir).degat;
                            }
                        }
                    }
                }

                Officer[i].hpOfficer -= (*newTir).degat; //Applique les dégats sur l'ennemie

                if(Officer[i].hpOfficer <=0) //Cas si l'ennemi est mort
                {
                    Officer[i].alive = 0;
                    Officer[i].x = Officer[i].y = -3 * SCREEN_HEIGHT;
                    Player.coins+=20 ;
                    Game.nbEnnemiKilled++;

                }
                //Désactive le tir
                (*newTir).on = 0;
                (*newTir).x = (*newTir).y = SCREEN_HEIGHT;
            }
            newTir = (*newTir).suivant;
        }
        newTir = Tir;
    }

}

//Gère les attaques des ennemies sur les tourelles

void collisionEnnemi_Tourelle()
{

    int i,j;
    for(i=0; i<=Game.nbEnnemiCreated; i++) //Test tout les ennemies avec toutes les tourelles
    {
        for(j=0; j<=MAX_TOURELLES; j++)
        {
            if(Officer[i].x >= Tourelle[j].x - GRID_STEP && Officer[i].x  < Tourelle[j].x + GRID_STEP/2 && Officer[i].lane == Tourelle[j].lane )
            {


                if(Tourelle[j].alive == 1 )
                {

                    if( Game.timer % Officer[i].reloadrate == 0 ) //Cas ou l'ennemi est a portée et attaque
                    {
                        Mix_VolumeChunk(musiqueKick, 15);
                        Mix_PlayChannel(1, musiqueKick, 0);
                        Tourelle[j].hpTourelle --;

                        if(Tourelle[j].hpTourelle == 0) // Cas où la tourelle est détruite
                        {
                            Tourelle[j].alive = 0;
                            Game.nbTourelle --;
                        }
                    }
                    Officer[i].attack = 1;
                }
                else
                {
                    Officer[i].attack = 0; //Remet l'ennemi en route après avoir détruit la tourelle
                }
            }
        }
    }
}

//Gère la collision entre les ennemies et la base, elle gère donc aussi la fin d'une partie
void collisionEnnemi_Base()
{
    int i;
    for(i=0; i<Game.nbEnnemiCreated; i++)
    {
        if( Officer[i].lane == 0 || Officer[i].lane == 4 ) //Cas ennemies aux extrémités
        {
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP/2) && Officer[i].alive == 1)//Si un ennemi est à portée
            {

                    Officer[i].attack = 1;
                if( Game.timer % Officer[i].reloadrate == 0 )//Si l'ennemi peut attaquer
                {
                    Mix_VolumeChunk(musiqueKick, 15);
                    Mix_PlayChannel(1, musiqueKick, 0); //Son d'attaque
                    Game.hpBase --;
                    if(Game.hpBase <= 0)
                    {
                        Game.hpBase =0;
                    }

                    if(Game.hpBase == 0) //Si la base est détruite, fin du jeu => écran fin de jeu et musique menu
                    {
                        Game.MenuPointer =350;
                        Game.stade = 2;
                        Mix_HaltMusic();
                        Mix_PlayMusic(musiqueMenu, -1);
                    }
                }
            }
        }

        else //Cas ennemi au milieu
        {
            if(Officer[i].x >= (SCREEN_WIDTH - 3*GRID_STEP))
            {

                    Officer[i].attack = 1;
                if( Game.timer % Officer[i].reloadrate == 0 )
                {
                    Mix_VolumeChunk(musiqueKick, 15);
                    Mix_PlayChannel(1, musiqueKick, 0);
                    Game.hpBase --;
                    if(Game.hpBase <= 0)
                    {
                        Game.hpBase =0;
                    }

                    if(Game.hpBase <= 0)
                    {
                        Game.stade = 2;
                        Game.hpBase =0;
                        Mix_HaltMusic();
                        Mix_PlayMusic(musiqueMenu, -1);
                    }
                }
            }
        }
    }
}

//Gère les collision de Roger avec les ennemies

void collisionEnnemi_Roger()
{
    int i;


    if(Player.stun == 0 && Player.stuntime - Game.timer <= 0) // Si le joueur n'est pas déja étourdie ou qu'il ne l'a pas été recemment
    {
        for(i=0; i<=Game.nbEnnemiCreated; i++)
        {


            if( ( (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y ) <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y + GRID_STEP/2 )
                    || (Officer[i].x <  Player.x &&   (Officer[i].x + GRID_STEP/2) > Player.x    &&   (Officer[i].y ) <  (Player.y + STEPHEN_ACTUAL_HEIGHT/3)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT/3) )
                    || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  Player.y  && (Officer[i].y + 3*GRID_STEP/2) >  Player.y + GRID_STEP/2 )
                    || (Officer[i].x <  (Player.x + STEPHEN_ACTUAL_WIDTH) &&   (Officer[i].x + GRID_STEP/2) > (Player.x + STEPHEN_ACTUAL_WIDTH)    &&   Officer[i].y <  (Player.y + STEPHEN_ACTUAL_HEIGHT/3)  && (Officer[i].y + 3*GRID_STEP/2) >  (Player.y + STEPHEN_ACTUAL_HEIGHT/3) )
                ) && Officer[i].alive == 1 )
                //Cas de collision entre roger et un ennemie
            {
                Mix_VolumeChunk(musiqueKick, 15);
                Mix_PlayChannel(1, musiqueKick, 0);
                Player.stun = 1;
                Player.stuntime = Game.timer + 200;

            }
        }

    }
    else
    {
        if(Player.stuntime - Game.timer <= 110) //si il est stun depus suffisament longtemps on le libère
        {
            Player.stun = 0;
        }

        //sinon on affiche le compteur d'étourdissement
        if((Player.stuntime - Game.timer) > 170)
            drawText("3",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);

        else if((Player.stuntime - Game.timer) > 140)
            drawText("2",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);


        else if((Player.stuntime - Game.timer) > 110)
        {
            drawText("1",Player.x,Player.y - GRID_STEP/2,textFont,197,150,80);
        }

    }

}
