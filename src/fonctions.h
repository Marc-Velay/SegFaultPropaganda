#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdint.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"



#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define PATH_TOP_Y 170
#define PATH_BOTTOM_Y 500
#define GRID_STEP 64

#define MAX_OFFICERS 100
#define MAX_TOURELLES 20

typedef struct Input
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
        char quit;
} Input;

typedef struct game
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

typedef struct player
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

enum
{
	PLAYER_SPRITE=0,
	BACKGROUND_SPRITE=1,
	OFFICER_SPRITE=2,
	TOURELLE_SPRITE=3,
	MAX_SPRITES=4
};

SDL_Surface *screen, *Background, *Officer1, *Text;  
TTF_Font *Font; 
player Player;
officer Officer[MAX_OFFICERS];
tourelle Tourelle[MAX_TOURELLES];
game Game;
Sprites sprite[MAX_SPRITES];



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