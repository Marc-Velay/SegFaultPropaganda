#include "fonctions.h"

void initTir(int x, int y, int dir,int tireur, int degat )
{
    tir *newTir =Tir;
    tir *addTir = Tir;
    int created=0;

	printf("entrer dans initTir\n");
    if(newTir == NULL)
    {
	printf("cas 1: création du 1er maillon\n");
        Mix_PlayMusic(musiqueLaser, 1);
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
    else
    {
	printf("cas 2: création d'un maillon en fin de liste\n");
        newTir=(*Tir).suivant;

        while(created !=1 )
        {
            if(newTir == NULL)
            {
                Mix_PlayMusic(musiqueLaser, 1);
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
            addTir=newTir;
            newTir=(*newTir).suivant;
        }
    }
}

void showLink(tir* debut) {
  if(debut != NULL) {
    printf("[%d]->", (*debut).x);
    debut = (*debut).suivant;
    if(debut != NULL) {
      showLink((*debut).suivant);
    }else { printf("X\n"); }
  } else { printf("X\n"); }
}


tir* supprimerTir(tir *prec) {
	tir *temp;
	
	printf("entrer dans supprimerTir\n");
	if(prec != NULL) {
	printf("not null\n");
	
		
		if(prec == Tir || (*prec).suivant == NULL) { 				//maillon unique
			printf("cas 1: maillon seul\n");
			free(prec); 
			Tir = NULL;
			printf("cas 1: post free \n");
			temp = NULL;
			
					
			
		}else if((*prec).suivant == NULL){					//le dernier maillon
			if((*(*prec).suivant).suivant == NULL) {
				printf("cas 2: maillon en fin de liste\n");
	SDL_Delay(500);
				free((*prec).suivant);
				printf("cas 2: post free \n");
	SDL_Delay(500);
				(*prec).suivant = NULL;
				printf("cas 2: prec suivant = null \n");
	SDL_Delay(500);
				temp = NULL;	
			}
		
			
			
			
		} else if((*(*prec).suivant).suivant != NULL) {				//maillon au milieu de la lsc
	printf("cas 3: maillon en milieu de liste\n");
			temp = (*(*prec).suivant).suivant;
			printf("cas 3: temp alouer");
			free((*prec).suivant);
			printf("cas 3: post free \n");
			(*prec).suivant =  temp;
			printf("cas 3: pre return");
			temp = (*prec).suivant;
		}
	}
	
	
	return temp;
}


void updateTir()
{
    int i;
    tir *newTir= Tir;
    tir *prec = Tir;
    
    while(newTir !=NULL)
    {
        if((*newTir).on == 1)
        {
            drawImage((*newTir).sprite, (*newTir).x, (*newTir).y);

            if((*newTir).dir==0)
            {
                for(i=0; i<5; i++)
                {
			    
                    collisionTir_Ennemi();
                    if((*newTir).on == 1) {
				 (*newTir).x +=10;
			}
                    if((*newTir).x >= SCREEN_WIDTH)
                    {
			    printf("sortie droite\n");
			    showLink(Tir);
	                    newTir = supprimerTir(prec); 
			    i =5;
                    }
                }
            }

            if((*newTir).dir==1)
            {         
                for(i=0; i<5; i++)
                {
			collisionTir_Ennemi();
			if((*newTir).on == 1) {
				 (*newTir).x -=10;
			}
                   
                    if((*newTir).x <= 0 && (*newTir).on == 1)
                    {
			    showLink(Tir);
			    if((*newTir).on != 0) {
				    printf("entre gauche\n");
		                    newTir = supprimerTir(prec); 
				    printf("sortie gauche\n");	
				    i =5;
			    }
                    }
                }
            }
        }       
	if(newTir != NULL) {
		prec = newTir;
	        newTir = (*newTir).suivant;
	}
    }

            SDL_Delay(1);
}

void freeTir(tir *aTir) {
	if(aTir != NULL){ freeTir(aTir = (*aTir).suivant); }
	free(aTir);
	free(Tir);
}



