#include "fonctions.h"


//Initialise le tir (position, degats, direction, tireur,...)
void initTir(int x, int y, int dir,int tireur, int degat )
{
    tir *newTir =Tir;
    tir *addTir = Tir;
    int created=0;

    if(newTir == NULL)//Cas premier tir de la liste
    {
        Mix_VolumeChunk(musiqueLaser, 15);
        Mix_PlayChannel(0, musiqueLaser, 0);
        newTir = (tir*)malloc(sizeof(tir));
        (*newTir).suivant =NULL;
        (*newTir).dir = dir;
        (*newTir).tireur = tireur;
        (*newTir).degat = degat;
        if((*newTir).dir==0)
        {
            (*newTir).x = x + (GRID_STEP/2);
            (*newTir).sprite = getSprite(LASER_R_SPRITE);
        }
        if((*newTir).dir==1)
        {
            (*newTir).x = x - GRID_STEP;
            (*newTir).sprite = getSprite(LASER_L_SPRITE);
        }
        (*newTir).y = y;
        (*newTir).on = 1;
        Tir =newTir;
    }
    else //Cas classique (hors tete de liste)
    {
        newTir=(*Tir).suivant;

        while(created !=1 )
        {
            if(newTir == NULL) //Cas queue de liste
            {
                Mix_VolumeChunk(musiqueLaser, 15);
                Mix_PlayChannel(0, musiqueLaser, 0);
                newTir = (tir*)malloc(sizeof(tir));
                (*newTir).suivant =NULL;
                (*newTir).dir = dir;
                (*newTir).tireur = tireur;
                (*newTir).degat = degat;
                if((*newTir).dir==0)
                {
                    (*newTir).x = x + (GRID_STEP/2);
                    (*newTir).sprite = getSprite(LASER_R_SPRITE);

                }
                if((*newTir).dir==1)
                {
                    (*newTir).x = x - GRID_STEP;
                    (*newTir).sprite = getSprite(LASER_L_SPRITE);
                }
                (*newTir).y = y;
                (*newTir).on = 1;
                (*addTir).suivant = newTir;
                created =1;
                break;
            }
            if((*newTir).on ==0) // Cas tir désactivé au milieu, on le remplace
            {
                Mix_VolumeChunk(musiqueLaser, 15);
                Mix_PlayChannel(0, musiqueLaser, 0);
                (*newTir).dir = dir;
                (*newTir).tireur = tireur;
                (*newTir).degat = degat;
                if((*newTir).dir==0)
                {
                    (*newTir).x = x + (GRID_STEP/2);
                }
                if((*newTir).dir==1)
                {
                    (*newTir).x = x - GRID_STEP;
                }

                (*newTir).y = y;
                (*newTir).on = 1;
                created =1;
            }
            addTir=newTir;
            newTir=(*newTir).suivant;
        }
    }
}


//Actualise la position des tirs
void updateTir()
{
    int i;
    tir *newTir= Tir;
    while(newTir !=NULL)
    {
        if((*newTir).on == 1)// Les faits avancer si activé
        {
            drawImage((*newTir).sprite, (*newTir).x, (*newTir).y);

            if((*newTir).dir==0) // Cas tir vers la droite
            {
                for(i=0; i<5; i++)
                {
                    (*newTir).x +=10;
                    if((*newTir).x >= SCREEN_WIDTH || (*newTir).x < 0)
                    {
                        (*newTir).x = (*newTir).y = (*newTir).on =0;
                    }
                    collisionTir_Ennemi();
                }
            }

            if((*newTir).dir==1) // Cas tir vers la gauche
            {
                for(i=0; i<5; i++)
                {
                    (*newTir).x -=10;
                    if((*newTir).x <= 0)
                    {
                        (*newTir).x = (*newTir).y = (*newTir).on =0;
                    }
                    collisionTir_Ennemi();
                }
            }
        }
        newTir = (*newTir).suivant;
    }

            SDL_Delay(1);
}

//Libère la liste complète des tirs, utilisé entre les vagues
void freeTir(tir *Tir) {
	if(Tir != NULL){ freeTir(Tir = (*Tir).suivant); }
	free(Tir);
}



