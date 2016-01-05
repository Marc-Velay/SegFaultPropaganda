#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdint.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"



#define SCREEN_WIDTH 1280		//Defini la taille de la fenetre
#define SCREEN_HEIGHT 720

#define PATH_TOP_Y 170			//Coordonne en y de la limite du terrain
#define PATH_BOTTOM_Y 500
#define GRID_STEP 64			//Taille des carres de la grille sur le terrain

#define MAX_OFFICERS 100		//Nombre arbitraire du nb max d'ennemis
#define MAX_TOURELLES 20		//Nombre arbitraire du nb max de tourelles

typedef struct Input			//structure utilisée pour récuperer les touches clavier/ sourie appuyé
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
        char quit;
} Input;

typedef struct game			//toutes les variables du rungame, utilisee pour faire tourner le jeu
{
  int stade;
  int countdown;
  int timer;
  int nbEnnemiWave;
  int nbEnnemiCreated;
  int nbEnnemiAlive;
  int nbTourelleCreated;
  int nbWave;
} game;

typedef struct player			// structure de Stephen
{
  int x, y;
  SDL_Surface *sprite;
} player;

typedef struct tourelle
{
  int x, y;
  int alive;
  SDL_Surface *sprite;
} tourelle;

typedef struct laser
{
  int x, y;
  int direction;
  struct laser* suivant;
  SDL_Surface *sprite;
} laser;

typedef struct officer
{
  int x, y;
  int alive;
  SDL_Surface *sprite;
} officer;

typedef struct Sprites			
{
	SDL_Surface *image;
} Sprites;

enum						//Contient les numéros des cases du tableau sprite contenant chaque image correspondant au nom
{
	PLAYER_SPRITE=0,
	BACKGROUND_SPRITE=1,
	OFFICER_SPRITE=2,
	TOURELLE_SPRITE=3,
	LASER_SPRITE=4,
	MAX_SPRITES=5
};

SDL_Surface *screen, *Background, *Text;  //initialise les surfaces de la fenetre, fond et où on affiche le texte
TTF_Font *Font; 						//la police du texte
player Player;							
officer Officer[MAX_OFFICERS];			//Tableau contenant les ennemis cree
tourelle Tourelle[MAX_TOURELLES];
game Game;
Sprites sprite[MAX_SPRITES];
laser Laser;


// ************** graphics.c
SDL_Surface *loadImage(char *name);
TTF_Font *loadFont(char *name, int size);
void drawImage(SDL_Surface *image, int x, int y);
void drawString(char *text, int x, int y, TTF_Font *Font);
void drawMenu(char *text, int x, int y, TTF_Font *Font);
void loadSprite(int index, char *name);
SDL_Surface *getSprite(int index);
void freeSprites();
void loadAllSprites();
void updateScreen();

// ************** init.c
void init(char *title);
void cleanup();



// ************** input.c
void getInput(/*game *Game*/);
void UpdateEvents(Input* in);


// ************** main.c
int main(int argc, char *argv[]);

// ************** player.c
void drawPlayer();
void initPlayer();

// ************** ennemi.c
void initOfficer(int n, int lane);
void drawOfficer();
void createWave();
void createOfficers();
void moveOfficers();
void doEnnemi();

// ************** tourelle.c
void initTourelle(int n, int lane);
void drawTourelle();
void doTourelle();

// ************** projectile.c
void initLaser();
void updateLaser();
void shoot();