#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdint.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

//caca

#define SCREEN_WIDTH 1280		//Defini la taille de la fenetre
#define SCREEN_HEIGHT 720
#define STEPHEN_ACTUAL_HEIGHT 65
#define STEPHEN_ACTUAL_WIDTH 35
#define MENU_HEIGHT 145


#define PATH_TOP_Y 192			//Coordonne en y de la limite du terrain
#define PATH_BOTTOM_Y 500
#define GRID_STEP 64			//Taille des carres de la grille sur le terrain

#define MAX_OFFICERS 500		//Nombre arbitraire du nb max d'ennemis
#define MAX_TOURELLES 41		//Nombre arbitraire du nb max de tourelles

#define TOURELLE_1_HP 4
#define TOURELLE_1_RELOADRATE 40
#define TOURELLE_1_PRICE 100

#define TOURELLE_2_HP 5
#define TOURELLE_2_RELOADRATE 60
#define TOURELLE_2_PRICE 125

#define TOURELLE_3_HP 3
#define TOURELLE_3_RELOADRATE 20
#define TOURELLE_3_PRICE 200

#define UPGRADE_PRICE 20

#define OFFICIER_1_HP 5
#define OFFICIER_1_RELOADRATE 20



typedef struct Input			//structure utilisée pour récuperer les touches clavier/ sourie appuyées
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
    int nbEnnemiKilled;
    int nbTourelleCreated;
    int nbWave;
    int nbTourelle;
    int hpBase;
    float restart;
    int drawOption,xOp,yOp,iOp;
    int nbWaveScore[10], nbKilledScore[10];
    char Joueur[10][14];
    int MenuPointer;
} game;

typedef struct player			// structure de Stephen
{
    char name[14];
    int nameInd;
    int x, y;
    int direction;
    int reload;
    int coins;
    int stun, stuntime;
    int level;
    SDL_Surface *sprite;
} player;

typedef struct tourelle
{
    int x, y;
    int alive;
    float hpTourelle;
    int lane;
    int reloadrate;
    int type;
    int degat, effet;
    int level;
    SDL_Surface *sprite;
} tourelle;

typedef struct tir
{
    int x, y;
    int dir;
    int on;
    int tireur;
    int degat;
    struct tir* suivant;
    SDL_Surface *sprite;

} tir;

typedef struct officer
{
    int x, y;
    int alive;
    int lane;
    int hpOfficer;
    int attack;
    int reloadrate;
    SDL_Surface *sprite;
} officer;

typedef struct Sprites
{
    SDL_Surface *image;
} Sprites;

enum						//Contient les numéros des cases du tableau sprite contenant chaque image correspondant au nom
{
    PLAYER_R_SPRITE,
    PLAYER_R1_SPRITE,
    PLAYER_R2_SPRITE,
    PLAYER_R3_SPRITE,
    PLAYER_R4_SPRITE,
    PLAYER_R5_SPRITE,
    PLAYER_L_SPRITE,
    PLAYER_L1_SPRITE,
    PLAYER_L2_SPRITE,
    PLAYER_L3_SPRITE,
    PLAYER_L4_SPRITE,
    PLAYER_L5_SPRITE,
    BACKGROUND_LAUNCH_SPRITE,
    BACKGROUND_END_SPRITE,
    BACKGROUND_SPRITE,
    OFFICER_SPRITE,
    OFFICER1_SPRITE,
    OFFICER2_SPRITE,
    OFFICER3_SPRITE,
    OFFICER_ATTACK1_SPRITE,
    OFFICER_ATTACK2_SPRITE,
    OFFICER_BLACK_SPRITE,
    OFFICER_BLACK1_SPRITE,
    OFFICER_BLACK2_SPRITE,
    OFFICER_BLACK3_SPRITE,
    OFFICER_BLACK_ATTACK_SPRITE,
    OFFICER_BLACK_ATTACK1_SPRITE,
    OFFICER_BLACK_ATTACK2_SPRITE,
    TOURELLE_1_SPRITE,
    TOURELLE_2_SPRITE,
    TOURELLE_3_SPRITE,
    BASE_HEALTH_0_SPRITE,
    BASE_HEALTH_1_SPRITE,
    BASE_HEALTH_2_SPRITE,
    BASE_HEALTH_3_SPRITE,
    BASE_HEALTH_4_SPRITE,
    BASE_HEALTH_5_SPRITE,
    BASE_HEALTH_6_SPRITE,
    BASE_HEALTH_7_SPRITE,
    BASE_HEALTH_8_SPRITE,
    BASE_HEALTH_9_SPRITE,
    LIFE_SPRITE,
    LASER_L_SPRITE,
    LASER_R_SPRITE,
    UPGRADE_1_SPRITE,
    UPGRADE_2_SPRITE,
    UPGRADE_3_SPRITE,
    UPGRADE_PUNCH_SPRITE,
    UPGRADE_DOUBLE_SPRITE,
    UPGRADE_AOE_SPRITE,
    MAX_SPRITES
};



SDL_Surface *screen, *Background, *Text, *health;  //initialise les surfaces de la fenetre, fond et où on affiche le texte
TTF_Font *TitleFont; 						//la police du texte
TTF_Font *SubTitleFont;
TTF_Font *textFont;
TTF_Font *ClassicFont;
TTF_Font *compteurFont;
player Player;
officer Officer[MAX_OFFICERS];			//Tableau contenant les ennemis cree
tourelle Tourelle[MAX_TOURELLES];
game Game;
Sprites sprite[MAX_SPRITES];
tir *Tir;
Mix_Music *musiqueMenu;
Mix_Music *musiqueLaser;

// ************** graphics.c
SDL_Surface *loadImage(char *name);		//fct pour recup les images à partir du disk
TTF_Font *loadFont(char *name, int size);	// recup la police à partir du disk
void drawImage(SDL_Surface *image, int x, int y);	//affiche une image à l'écran, en x,y
void drawString(char *text, int x, int y, TTF_Font *Font);	//affiche du texte sur une surface
void drawMenu(char *text, int x, int y, TTF_Font *Font); //affiche le menu du 1er ecran
void drawText(char *text, int x, int y, TTF_Font *textFontn, int r, int g, int b);
void loadSprite(int index, char *name);	//recup les sprite grace à loadimage, et les place dans un tableau d'images
SDL_Surface *getSprite(int index);	//recup l'image dans la case index du tableau cree dans loadAllSprite
void freeSprites();		//libere toutes les images du tableau
void loadAllSprites();		//liste des sprites a lister
void updateScreen();	//fonction utilisee pour refresh l'ecran avec les nouvelles positions des images, apres avoir mis a jour chaque elem du jeu
void doInterface();
void doOption();
void doBaseHealth();
void drawMenuPointer();
void delay(unsigned int frameLimit);
void Compteur();

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
int getLanePlayer();
int getColPlayer();

// ************** ennemi.c
void initOfficer(int n, int lane);
void drawOfficer();
void createWave();
void doWave();		//cree le nombre d'ennemis dans cette vague
void createOfficers();		//cree les nouveaux officiers jusqu'à la limite de createWave
void moveOfficers();			//gestion des colisions
void doEnnemi();			//appel permettant de gerer la creation et le deplacement des ennemis
void getEnnemiAlive();

// ************** tourelle.c
void creerTourelle1(int n,int colonne, int lane);
void creerTourelle2(int n,int colonne, int lane);
void creerTourelle3(int n,int colonne, int lane);
void initTourelle(int n, int colonne, int lane, int type);
void drawTourelle();
void doTourelle();			//appel permettant de gerer la creation et le deplacement des tourelles
void createTourelle(int type);
void SellTourelle(int i);
void UpgradeTourelle(int i);
void UpTourelle1(int i);
void UpTourelle2(int i);
void UpTourelle3(int i);
// ************** tir.c
void initTir(int x, int y, int dir, int tireur, int degat);
void updateTir();
void Tirer(int x, int y, int dir);

// ************** collision.c
void collision();
void collisionTir_Ennemi();
void collisionEnnemi_Tourelle();
void collisionEnnemi_Base();
void collisionEnnemi_Roger();
void freeTir(tir *Tir);
void Jeu();

//*************** sound.c
void loadAllMusic();

//*************** highscore.c
void getScore();
void drawHighscore();
