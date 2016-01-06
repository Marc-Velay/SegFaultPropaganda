#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdint.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//caca

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
  int direction;
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

typedef struct tir
{
  int x, y;
  int dir;
  int on;
  //struct tir* suivant;
  SDL_Surface *sprite;
} tir;

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
	PLAYER_R_SPRITE,
	PLAYER_L_SPRITE,
	BACKGROUND_SPRITE,
	OFFICER_SPRITE,
	TOURELLE_SPRITE,
	LASER_SPRITE,
	MAX_SPRITES
};

SDL_Surface *screen, *Background, *Text;  //initialise les surfaces de la fenetre, fond et où on affiche le texte
TTF_Font *Font; 						//la police du texte
player Player;
officer Officer[MAX_OFFICERS];			//Tableau contenant les ennemis cree
tourelle Tourelle[MAX_TOURELLES];
game Game;
Sprites sprite[MAX_SPRITES];
laser Laser;
tir Tir;

// ************** graphics.c
SDL_Surface *loadImage(char *name);		//fct pour recup les images à partir du disk
TTF_Font *loadFont(char *name, int size);	// recup la police à partir du disk
void drawImage(SDL_Surface *image, int x, int y);	//affiche une image à l'écran, en x,y
void drawString(char *text, int x, int y, TTF_Font *Font);	//affiche du texte sur une surface
void drawMenu(char *text, int x, int y, TTF_Font *Font); //affiche le menu du 1er ecran
void loadSprite(int index, char *name);	//recup les sprite grace à loadimage, et les place dans un tableau d'images
SDL_Surface *getSprite(int index);	//recup l'image dans la case index du tableau cree dans loadAllSprite
void freeSprites();		//libere toutes les images du tableau
void loadAllSprites();		//liste des sprites a lister
void updateScreen();	//fonction utilisee pour refresh l'ecran avec les nouvelles positions des images, apres avoir mis a jour chaque elem du jeu

// ************** init.c
void init(char *title);		//initialise les librairies et certains elements
void cleanup();			//supprime tous ce qui a ete initialise dans la fct au dessus et les sprites



// ************** input.c
void getInput();			//fct pour les actions du joueur
void UpdateEvents(Input* in);	//met à jour le tableau ayant une case par touche du clavier et de la sourie à partir des evenements


// ************** main.c
int main(int argc, char *argv[]);

// ************** player.c
void drawPlayer();
void initPlayer();

// ************** ennemi.c
void initOfficer(int n, int lane);
void drawOfficer();
void createWave();			//cree le nombre d'ennemis dans cette vague
void createOfficers();		//cree les nouveaux officiers jusqu'à la limite de createWave
void moveOfficers();			//gestion des colisions
void doEnnemi();			//appel permettant de gerer la creation et le deplacement des ennemis

// ************** tourelle.c
void initTourelle(int n, int lane);
void drawTourelle();
void doTourelle();			//appel permettant de gerer la creation et le deplacement des tourelles

// ************** projectile.c
void initLaser();
void updateLaser();
void shoot();

void initTir(int x, int y, int dir);
void updateTir();
void Tirer(int x, int y, int dir);

