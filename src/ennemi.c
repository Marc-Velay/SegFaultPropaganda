#include "fonctions.h"


void initOfficer(int n, int lane)                       // Création de l'unité "Agent de la CIA"
{
    Officer[n].sprite = getSprite(OFFICER_SPRITE);  // Récupération de l'image de l'Agent
    Officer[n].x = 0;
    Officer[n].y = lane*GRID_STEP+PATH_TOP_Y-36;    // Position d'apparition de l'Agent
    Officer[n].alive = 1;
    Officer[n].hpOfficer = 2*(Game.nbWave+1)/3 *( OFFICIER_1_HP ) + Game.nbWave/2;
    Officer[n].lane = lane;
    Officer[n].attack = 0;
    Officer[n].reloadrate = OFFICIER_1_RELOADRATE - Game.nbWave/5;  // Variables internes à l'unité (statistique, positionnement...)

    if(Officer[n].reloadrate < 2)
    {
        Officer[n].reloadrate = 2;
    }
}



void createWave()                                       // Création d'une vague d'Agents
{

    Game.nbWave+=1;
    time_t t;
    //Game.countdown=1;
    srand((unsigned) time(&t));

    Game.nbEnnemiWave = (rand() %Game.nbWave) + 2 * Game.nbWave ;   // Détermination du nombre d'ennemis de la Nème vague en fonction de N
    if(Game.nbEnnemiWave >= MAX_OFFICERS)
    {
        Game.nbEnnemiWave = MAX_OFFICERS-1;                         // Limitation du nombre d'ennemis pouvant apparaitre sur la carte par une variable globale
    }
    printf("nombre d'ennemis pour la vague %d: %d\n", Game.nbWave, Game.nbEnnemiWave);
}

void doWave()                                           // Lance la création d'une vague si la vague précédente est vaincue
{
    getEnnemiAlive();   // Récupère le nombre d'ennemis sur la carte

     if(Game.nbEnnemiAlive==0 && Game.stade == 1 )
        {

            if(Game.countdown - Game.timer < 0 )
            {

                Game.countdown = Game.timer + 300;  // Ajoute du temps avant la création de la prochaine vague

                if(Tir != NULL)                     // Annule les tirs lasers en cours d'éxécution
                        {
                        freeTir((*Tir).suivant);
                        (*Tir).suivant = NULL;
                        }
            }

            else if(Game.countdown - Game.timer == 0 )  // Lance la création d'une vague à la fin du temps imparti entre les deux vagues
            {
                    Game.nbEnnemiCreated = 0;
                    createWave();


            }

        }
}

void createOfficers()       // Attribue aléatoirement une lane à un ennemi et lance la création de cet ennemi
{
    int lane;

    if( Game.nbEnnemiCreated<=Game.nbEnnemiWave) // Tant que tous les ennemis de la vague ne sont pas créés
    {
        lane = rand()%5;                         // Détermine aléatoirement une valeur de lane
        Game.nbEnnemiAlive++;
        initOfficer(Game.nbEnnemiCreated, lane);    // Créé un "Agent de la CIA" sur la lane déterminée précédemment
        Game.nbEnnemiCreated++;

    }
}

void drawOfficer()      // Affichage d'un ennemi sur la carte
{
	int i,j;
	float officerhp;
	int annimationFrame = Game.timer%18;

	for(j=0; j<5; j++) {
		for(i=0; i<Game.nbEnnemiCreated; i++) {

			if(Officer[i].alive == 1 && Officer[i].lane == j) {
				officerhp = 2*(Game.nbWave+1)/3 *( OFFICIER_1_HP ) + Game.nbWave/2; // Nombre d'HP d'un Agent lors de sa création
			        drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);       // Affichage du sprite d'un Agent à sa position actuelle

				if(Officer[i].hpOfficer != officerhp) {
					if (Officer[i].hpOfficer >= 0) {                                // Si un ennemi perd de la vie, afficher sa barre de vie au dessus de lui
						drawImage(getSprite(LIFE_SPRITE), Officer[i].x +10  , Officer[i].y - 10 );

						if(Officer[i].hpOfficer > (officerhp/5)) {
							drawImage(getSprite(LIFE_SPRITE), Officer[i].x +10  +11, Officer[i].y - 10 );

							if(Officer[i].hpOfficer >= (2*officerhp/5)) {
								drawImage(getSprite(LIFE_SPRITE), Officer[i].x +10  +22, Officer[i].y - 10 );

								if(Officer[i].hpOfficer >= (3*officerhp/5) ) {
									drawImage(getSprite(LIFE_SPRITE), Officer[i].x +10 +33, Officer[i].y - 10 );

									if(Officer[i].hpOfficer >= (4*officerhp/5)) {       // Ajout d'une barre de vie pour chaque 1/5 de vie actuelle
										drawImage(getSprite(LIFE_SPRITE), Officer[i].x +10  +44, Officer[i].y - 10 );

									}
								}
							}
						}
					}

			        }
             if(Game.nbWave%20 <= 10) // Détermine le design des Agents pour la Nème vague en fonction de N.
            {
                if(Officer[i].attack == 0) {    // Animation gérée à la frame d'un AgentBlanc en déplacement
                    if(annimationFrame <6){
                        Officer[i].sprite = getSprite(OFFICER1_SPRITE);
                    }else if(annimationFrame <12){
                        Officer[i].sprite = getSprite(OFFICER2_SPRITE);
                    }else if(annimationFrame <18){
                        Officer[i].sprite = getSprite(OFFICER3_SPRITE);
                    }
                } else if(Officer[i].attack == 1) {  // Animation gérée à la frame d'un AgentBlanc en position d'attaque
                    if(annimationFrame <10){
                        Officer[i].sprite = getSprite(OFFICER_ATTACK1_SPRITE);
                    }else if(annimationFrame <18){
                        Officer[i].sprite = getSprite(OFFICER_ATTACK2_SPRITE);
                    }
                }
             }
             else
             {
                if(Officer[i].attack == 0) {    // Animation gérée à la frame d'un AgentNoir en déplacement
                    if(annimationFrame <6){
                        Officer[i].sprite = getSprite(OFFICER_BLACK1_SPRITE);
                    }else if(annimationFrame <12){
                        Officer[i].sprite = getSprite(OFFICER_BLACK2_SPRITE);
                    }else if(annimationFrame <18){
                        Officer[i].sprite = getSprite(OFFICER_BLACK3_SPRITE);
                    }
                } else if(Officer[i].attack == 1) { // Animation gérée à la frame d'un AgentNoir en position d'attaque
                    if(annimationFrame <6){
                        Officer[i].sprite = getSprite(OFFICER_BLACK_ATTACK_SPRITE);
                    }else if(annimationFrame <12){
                        Officer[i].sprite = getSprite(OFFICER_BLACK_ATTACK1_SPRITE);
                    }else if(annimationFrame <18){
                        Officer[i].sprite = getSprite(OFFICER_BLACK_ATTACK2_SPRITE);
                    }
                }
             }


			drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);   // Affichage dans la fenêtre du sprite actuel d'un Agent à sa position actuelle
			}
		}
	}
}

void getEnnemiAlive() // Récupère le nombre d'ennemis en vie sur la carte
{
    int i;
    int alive=0;
    for(i=0; i<Game.nbEnnemiCreated; i++)
    {
        if(Officer[i].alive == 1)
        {
            alive +=1;
        }
    }
    Game.nbEnnemiAlive= alive;
}

void moveOfficers() // Fonction gérant le déplacement des Agents
{
    int i;

    for(i=0; i<=Game.nbEnnemiCreated; i++)
    {
        if(Officer[i].alive == 1 && Officer[i].attack != 1) // Si un Agent est en vie et n'est pas en posture d'attaque
        {

            if( Officer[i].lane == 0 || Officer[i].lane == 4 )  // Sur la lane 0 et sur la lane 4, déplacement entre 0 et 1280-96 pixels sur la largeur
            {
                if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP/2))
                    Officer[i].x += 1 + Game.nbWave/8;          // Un Agent de la Nème vague parcoure 1+(N/8) pixels à chaque actualisation de position
            }

            else                                            // Sur les autres lanes, déplacement entre 0 et 1280-192 pixels sur la largeur

            {
                if(Officer[i].x < (SCREEN_WIDTH - 3*GRID_STEP))
                    Officer[i].x += 1 + Game.nbWave/8;      // Un Agent de la Nème vague parcoure 1+(N/8) pixels à chaque actualisation de position
            }
        }
    }
}

void doEnnemi()     // Lance la création d'un ennemi toutes les 20 frames et actualise le déplacement des Agents
{
    int tick = Game.timer % (20);

    if(tick == 0)
    {
        createOfficers();
    }
    moveOfficers();
}
