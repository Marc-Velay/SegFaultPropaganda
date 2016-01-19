#include "fonctions.h"


SDL_Surface *loadImage(char *name)
{
    /* Load the image using SDL Image */

    SDL_Surface *temp = IMG_Load(name);
    SDL_Surface *image=  NULL;

    if (temp == NULL)
    {
        printf("Failed to load image %s\n", name);
        return NULL;
    }

    image = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    if (image == NULL)
    {
        printf("Failed to convert image %s to native format\n", name);

        return NULL;
    }

    if( image != NULL )
    {
        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        Uint32 colorkey = SDL_MapRGB( (*image).format, 0xFF, 0xFF, 0xFF );
        SDL_SetColorKey( image, SDL_SRCCOLORKEY, colorkey );
    }


    /* Return the processed image */
    return image;
}

SDL_Surface *loadImageFULL(char *name)
{
    /* Load the image using SDL Image */

    SDL_Surface *temp = IMG_Load(name);
    SDL_Surface *image=  NULL;

    if (temp == NULL)
    {
        printf("Failed to load image %s\n", name);
        return NULL;
    }

    image = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    if (image == NULL)
    {
        printf("Failed to convert image %s to native format\n", name);

        return NULL;
    }

    /*if( image != NULL )
    {
        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        Uint32 colorkey = SDL_MapRGB( (*image).format, 0xFF, 0xFF, 0xFF );
        SDL_SetColorKey( image, SDL_SRCCOLORKEY, colorkey );
    }*/


    /* Return the processed image */
    return image;
}

TTF_Font *loadFont(char *name, int size)
{
    /* Use SDL_TTF to load the font at the specified size */

    TTF_Font *Font = TTF_OpenFont(name, size);

    if (Font == NULL)
    {
        printf("Failed to open Font %s: %s\n", name, TTF_GetError());

        exit(1);
    }

    return Font;
}

void drawAbout()
{
    drawMenu("Il y a fort pas longtemps dans notre galaxie, enfin sur la Terre pour être plus précis,",0,-150,compteurFont);
    drawMenu("s’est échoué un extraterrestre tout gris et tout moche : Stephen.",0,-70,compteurFont);
    drawMenu("Il fut très vite poursuivit par des agents de la CIA qui voulaient le trouver",00,10,compteurFont);
    drawMenu("car il était le seul de son espèce présent sur notre planète",0,90,compteurFont);
    drawMenu("(bon c’est aussi parce qu’il n’a pas d’amis mais ça c’est une autre histoire …).",0,170,compteurFont);
    drawMenu("Il savait que ceux qui le poursuivaient feraient tout pour l’attraper.",0,250,compteurFont);
    drawMenu("Là démarra son combat : Stephen VS Langley Falls.",0,330,compteurFont);



}

void drawImage(SDL_Surface *image, int x, int y)
{
    SDL_Rect dest;

    /* Set the blitting rectangle to the size of the src image */

    dest.x = x;
    dest.y = y;
    dest.w = (*image).w;
    dest.h = (*image).h;

    /* Blit the entire image onto the screen at coordinates x and y */

    SDL_BlitSurface(image, NULL, screen, &dest);
}


void drawString(char *text, int x, int y, TTF_Font *Font)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor, backgroundColor;

    /* White text on a black background */

    foregroundColor.r = 0;
    foregroundColor.g = 0;
    foregroundColor.b = 0;

    backgroundColor.r = 255;
    backgroundColor.g = 255;
    backgroundColor.b = 255;

    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Shaded(Font, text, foregroundColor, backgroundColor);

    if( surface != NULL )
    {
        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        Uint32 colorkey = SDL_MapRGB( (*surface).format, 0, 0, 0 );
        SDL_SetColorKey( surface, SDL_SRCCOLORKEY, colorkey );
    }

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = x - (*surface).w / 2;
    dest.y = y - (*surface).h / 2;
    dest.w = (*surface).w;
    dest.h = (*surface).h;

    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}



void drawMenu(char *text, int x, int y, TTF_Font *Font)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor, backgroundColor;

    /* White text on a black background */

    foregroundColor.r = 0;
    foregroundColor.g = 150;
    foregroundColor.b = 200;

    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;

    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Shaded(Font, text, foregroundColor, backgroundColor);

    if( surface != NULL )
    {

        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        // Uint32 colorkey = SDL_MapRGB( (*surface).format, 0, 0, 0 );
        // SDL_SetColorKey( surface, SDL_SRCCOLORKEY, colorkey );
    }

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = ((*screen).w - (*surface).w )/ 2 + x;
    dest.y = ((*screen).h - (*surface).h) / 3 + y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}


void drawText(char *text, int x, int y, TTF_Font *textFont, int r, int g, int b)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor, backgroundColor;

    /* White text on a black background */

    foregroundColor.r = 250;
    foregroundColor.g = 250;
    foregroundColor.b = 250;

    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;

    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Shaded(textFont, text, foregroundColor, backgroundColor);

    if( surface != NULL )
    {
        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        // Uint32 colorkey = SDL_MapRGB( (*surface).format, 0, 0, 0 );
        // SDL_SetColorKey( surface, SDL_SRCCOLORKEY, colorkey );
    }

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = x;
    dest.y = y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}

void drawText2(char *text, int x, int y, TTF_Font *textFont, int r, int g, int b)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor, backgroundColor;

    /* White text on a black background */

    foregroundColor.r = 0;
    foregroundColor.g = 0;
    foregroundColor.b = 0;

    backgroundColor.r = r;
    backgroundColor.g = g;
    backgroundColor.b = b;

    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Shaded(textFont, text, foregroundColor, backgroundColor);

    if( surface != NULL )
    {
        //Map the color key, 3* 0xFF pour transparent, sans font blanc
        // Uint32 colorkey = SDL_MapRGB( (*surface).format, 0, 0, 0 );
        // SDL_SetColorKey( surface, SDL_SRCCOLORKEY, colorkey );
    }

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = x;
    dest.y = y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}

void drawCompteur(char *text, int x, int y, TTF_Font *compteurFont)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor;

    /* White text on a black background */

    foregroundColor.r = 250;
    foregroundColor.g = 250;
    foregroundColor.b = 250;

    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Solid(compteurFont, text, foregroundColor);
    if( surface != NULL )
    {

        //Map the color key, 3* 0xFF pour transparent, sans font blanc
    }

    else
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = x;
    dest.y = y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}



void loadSprite(int index, char *name)
{
    /* Load the image into the next slot in the sprite bank */
    if (index >= MAX_SPRITES || index < 0)
    {
        printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);

        exit(1);
    }

    sprite[index].image = loadImage(name);

    if (sprite[index].image == NULL)
    {
        exit(1);
    }
}

void loadSpriteFULL(int index, char *name)
{
    /* Load the image into the next slot in the sprite bank */
    if (index >= MAX_SPRITES || index < 0)
    {
        printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);

        exit(1);
    }

    sprite[index].image = loadImageFULL(name);

    if (sprite[index].image == NULL)
    {
        exit(1);
    }
}


SDL_Surface *getSprite(int index)
{
    if (index >= MAX_SPRITES || index < 0)
    {
        printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);

        exit(1);
    }

    return sprite[index].image;
}

void freeSprites()
{
    int i;

    /* Loop through the sprite bank and clear the images */

    for (i=0; i<MAX_SPRITES; i++)
    {
        if (sprite[i].image != NULL)
        {
            SDL_FreeSurface(sprite[i].image);
        }
    }
}

void loadAllSprites()
{
    TitleFont = loadFont("sfd/PIXEL.ttf", 90);
    SubTitleFont = loadFont("sfd/PIXEL.ttf", 50);
    textFont = loadFont("sfd/FreeSans.ttf", 15);
    compteurFont = loadFont("sfd/PIXEL.ttf", 30);
    ClassicFont = loadFont("sfd/PIXEL.ttf", 40);

    loadSprite(PLAYER_R_SPRITE, "gfx/Roger_CleanR.png");
    loadSprite(PLAYER_R1_SPRITE, "gfx/Roger_CleanR_Walking1.png");
    loadSprite(PLAYER_R2_SPRITE, "gfx/Roger_CleanR_Walking2.png");
    loadSprite(PLAYER_R3_SPRITE, "gfx/Roger_CleanR_Walking3.png");
    loadSprite(PLAYER_R4_SPRITE, "gfx/Roger_CleanR_Walking4.png");
    loadSprite(PLAYER_R5_SPRITE, "gfx/Roger_CleanR_Walking15.png");

    loadSprite(PLAYER_L_SPRITE, "gfx/Roger_CleanL.png");
    loadSprite(PLAYER_L1_SPRITE, "gfx/Roger_CleanL_Walking1.png");
    loadSprite(PLAYER_L2_SPRITE, "gfx/Roger_CleanL_Walking2.png");
    loadSprite(PLAYER_L3_SPRITE, "gfx/Roger_CleanL_Walking3.png");
    loadSprite(PLAYER_L4_SPRITE, "gfx/Roger_CleanL_Walking4.png");
    loadSprite(PLAYER_L5_SPRITE, "gfx/Roger_CleanL_Walking5.png");

    loadSprite(BACKGROUND_LAUNCH_SPRITE, "gfx/Menu.png");
    loadSprite(BACKGROUND_END_SPRITE, "gfx/TerrainV2.png");
    loadSprite(BACKGROUND_SPRITE, "gfx/TerrainV4.png");
    loadSprite(BACKGROUND2_SPRITE, "gfx/TerrainV5.png");

    loadSprite(OFFICER_SPRITE, "gfx/Agent_Clean.png");
    loadSprite(OFFICER1_SPRITE, "gfx/Agent_Segway_Clean1.png");
    loadSprite(OFFICER2_SPRITE, "gfx/Agent_Segway_Clean2.png");
    loadSprite(OFFICER3_SPRITE, "gfx/Agent_Segway_Clean3.png");

    loadSprite(OFFICER_ATTACK1_SPRITE, "gfx/Agent_Segway_Cut_Clean1.png");
    loadSprite(OFFICER_ATTACK2_SPRITE, "gfx/Agent_Segway_Cut_Clean2.png");

    loadSprite(OFFICER_BLACK_SPRITE, "gfx/AgentBlack_Clean.png");
    loadSprite(OFFICER_BLACK1_SPRITE, "gfx/AgentBlack_Segway_Clean1.png");
    loadSprite(OFFICER_BLACK2_SPRITE, "gfx/AgentBlack_Segway_Clean2.png");
    loadSprite(OFFICER_BLACK3_SPRITE, "gfx/AgentBlack_Segway_Clean3.png");

    loadSprite(OFFICER_BLACK_ATTACK_SPRITE, "gfx/AgentBlack_Segway_Cut_Clean1.png");
    loadSprite(OFFICER_BLACK_ATTACK1_SPRITE, "gfx/AgentBlack_Segway_Cut_Clean2.png");
    loadSprite(OFFICER_BLACK_ATTACK2_SPRITE, "gfx/AgentBlack_Segway_Cut_Clean3.png");

    loadSprite(TOURELLE_1_SPRITE, "gfx/Tourelle_Clean.png");
    loadSprite(TOURELLE_2_SPRITE, "gfx/TourelleTriple.png");
    loadSprite(TOURELLE_3_SPRITE, "gfx/Tourelle_Clean2.png");

    loadSprite(BASE_HEALTH_0_SPRITE, "gfx/FullHPBar.png");
    loadSprite(BASE_HEALTH_1_SPRITE, "gfx/HPBar-1.png");
    loadSprite(BASE_HEALTH_2_SPRITE, "gfx/HPBar-2.png");
    loadSprite(BASE_HEALTH_3_SPRITE, "gfx/HPBar-3.png");
    loadSprite(BASE_HEALTH_4_SPRITE, "gfx/HPBar-4.png");
    loadSprite(BASE_HEALTH_5_SPRITE, "gfx/HPBar-5.png");
    loadSprite(BASE_HEALTH_6_SPRITE, "gfx/HPBar-6.png");
    loadSprite(BASE_HEALTH_7_SPRITE, "gfx/HPBar-7.png");
    loadSprite(BASE_HEALTH_8_SPRITE, "gfx/HPBar-8.png");
    loadSprite(BASE_HEALTH_9_SPRITE, "gfx/HPBar-9.png");
    loadSprite(LIFE_SPRITE, "gfx/Life.png");

    loadSprite(LASER_R_SPRITE, "gfx/Laser_R_Clean.png");
    loadSprite(LASER_L_SPRITE, "gfx/Laser_L_Clean.png");

    loadSprite(UPGRADE_1_SPRITE,"gfx/Upgrade1.png");
    loadSprite(UPGRADE_2_SPRITE,"gfx/Upgrade2.png");
    loadSprite(UPGRADE_3_SPRITE,"gfx/Upgrade3.png");
    loadSprite(UPGRADE_PUNCH_SPRITE,"gfx/Upgrade_Punch.png");
    loadSprite(UPGRADE_DOUBLE_SPRITE,"gfx/Upgrade_Double.png");
    loadSprite(UPGRADE_AOE_SPRITE,"gfx/Upgrade_AOE.png");

    loadSprite(TUTO_1_SPRITE,"gfx/Tuto1.png");
    loadSprite(TUTO_2_SPRITE,"gfx/Tuto2.png");
    loadSpriteFULL(CONTROLE_SPRITE,"gfx/Menu2.png");
}

void doOption()
{

        if(Game.drawOption >= 1)
        {
            drawText("Upgrade", Game.xOp+3, Game.yOp+10, textFont,240,240,0);
            drawText("Vendre  ", Game.xOp+4, Game.yOp+32, textFont,240,240,0);

            if(Game.drawOption == 2)
            {
            drawText("PUSH      ", Game.xOp+57, Game.yOp+10, textFont,240,240,0);
            drawText("DOUBLE ", Game.xOp+57, Game.yOp+32, textFont,240,240,0);
            drawText("AOE         ", Game.xOp+56, Game.yOp+54, textFont,240,240,0);
            }
        }

}


void doInterface() {
	char string[20] ;
if(Game.nbWave <= 10){
	drawText("Prix: ", 10, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_1_PRICE);
        drawText(string, 50, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_2_PRICE + 10*(Game.nbWave-1));
        drawText(string, 180, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_3_PRICE + 10*(Game.nbWave-1));
        drawText(string, 310, 685, textFont,97,117,18);

        drawText("Coins: ", 950, 685, textFont,97,117,18);
        sprintf(string,"%d", Player.coins);	//prints the integer Player.coins into a string to enable drawText to show value
        drawText(string, 1000, 685, textFont,97,117,18);

        sprintf(string,"%d", Game.nbWave);
        drawText("Vague: ", 410, 600, textFont,97,117,18);
        drawText(string, 470, 600, textFont,97,117,18);

        sprintf(string,"%d", Game.nbEnnemiKilled);
        drawText("Nombre d'ennemis tués: ", 410, 660, textFont,97,117,18);
        drawText(string, 580, 660, textFont,97,117,18);
}else{
        drawText2("Prix: ", 10, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_1_PRICE);
        drawText2(string, 50, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_2_PRICE + 10*(Game.nbWave-1));
        drawText2(string, 180, 685, textFont,97,117,18);

        sprintf(string,"%d", TOURELLE_3_PRICE + 10*(Game.nbWave-1));
        drawText2(string, 310, 685, textFont,97,117,18);

        drawText2("Coins: ", 950, 685, textFont,97,117,18);
        sprintf(string,"%d", Player.coins);	//prints the integer Player.coins into a string to enable drawText to show value
        drawText2(string, 1000, 685, textFont,97,117,18);

        sprintf(string,"%d", Game.nbWave);
        drawText2("Vague: ", 410, 600, textFont,97,117,18);
        drawText2(string, 470, 600, textFont,97,117,18);

        sprintf(string,"%d", Game.nbEnnemiKilled);
        drawText2("Nombre d'ennemis tués: ", 410, 660, textFont,97,117,18);
        drawText2(string, 580, 660, textFont,97,117,18);
}
	drawImage(getSprite(TOURELLE_1_SPRITE), 35, 617);
	drawImage(getSprite(TOURELLE_2_SPRITE), 162, 617);
	drawImage(getSprite(TOURELLE_3_SPRITE), 292, 617);
    Compteur();

    }

void Compteur()
{
    char string[20] ;

     if(Game.countdown - Game.timer > 0 && Game.countdown - Game.timer < 280 &&  Game.nbEnnemiAlive == 0 )
            {
            sprintf(string,"Assault dans %d !", (Game.countdown+1 - Game.timer)/30 );
            drawCompteur(string, SCREEN_WIDTH/3 + 12*GRID_STEP/10 ,  5*GRID_STEP/2, compteurFont);
            }
}

void doBaseHealth() {
	if(Game.stade == 1 ) {
	switch(Game.hpBase%11) {
		case 0:
			printf("BASE DIED\n");
			break;
		case 1:
			drawImage(getSprite(BASE_HEALTH_9_SPRITE), 723, 600);
			break;
		case 2:
			drawImage(getSprite(BASE_HEALTH_8_SPRITE), 723, 600);
			break;
		case 3:
			drawImage(getSprite(BASE_HEALTH_7_SPRITE), 723, 600);
			break;
		case 4:
			drawImage(getSprite(BASE_HEALTH_6_SPRITE), 723, 600);
			break;
		case 5:
			drawImage(getSprite(BASE_HEALTH_5_SPRITE), 723, 600);
			break;
		case 6:
			drawImage(getSprite(BASE_HEALTH_4_SPRITE), 723, 600);
			break;
		case 7:
			drawImage(getSprite(BASE_HEALTH_3_SPRITE), 723, 600);
			break;
		case 8:
			drawImage(getSprite(BASE_HEALTH_2_SPRITE), 723, 600);
			break;
		case 9:
			drawImage(getSprite(BASE_HEALTH_1_SPRITE), 723, 600);
			break;
		case 10:
			drawImage(getSprite(BASE_HEALTH_0_SPRITE), 723, 600);
			break;
	}
	}
}


void drawMenuPointer() {
        drawImage(getSprite(PLAYER_R_SPRITE), 380, Game.MenuPointer);
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

void updateScreen()
{
    SDL_FillRect(screen, NULL, 0);

    switch(Game.stade)
    {
    case 0:
        drawImage(getSprite(BACKGROUND_LAUNCH_SPRITE), 0, 0);
        drawMenu("Stephen VS Langley Falls", 0, -120, TitleFont);
        drawMenu("Start Game", 0, 50, SubTitleFont);
        drawMenu("Tutorial", 0, 150, SubTitleFont);
        drawMenu("about", 0, 250, SubTitleFont);
        drawMenu("Quit", 0, 350, SubTitleFont);
	drawMenuPointer();
        break;

    case -1:
        drawMenu("Entrez votre nom:",-450,120,ClassicFont);
        drawMenu(Player.name,-160,120,ClassicFont);
        break;
    case 1:
        doEnnemi();
        doTourelle();
        if(Game.nbWave%20 <= 10){drawImage(getSprite(BACKGROUND2_SPRITE), 0, 0);}
        else{drawImage(getSprite(BACKGROUND_SPRITE), 0, 0);}
	doInterface();
	if(Game.hpBase >0 ) {doBaseHealth();}
        drawOfficer();
        drawTourelle();
        drawPlayer();
        doOption();
        updateTir();
        collision();
        break;


    case 2:
        drawImage(getSprite(BACKGROUND_LAUNCH_SPRITE), 0, 0);
        drawMenu("HIGHSCORE",0,20, SubTitleFont);
        drawMenu("Play again?", 0, 120, SubTitleFont);
        drawMenu("Quit", 0, 220, SubTitleFont);
        drawMenuPointer();
        break;
    case 3:
        drawImage(getSprite(BACKGROUND_LAUNCH_SPRITE), 0, 0);
        drawMenu("HIGHSCORE", 0, -210, SubTitleFont);
        drawMenu("Joueur",-450 , -140 , ClassicFont);
        drawMenu("Vague atteinte",0 , -140 , ClassicFont);
        drawMenu("Ennemies abbatus",450 , -140 , ClassicFont);
        drawHighscore();
        drawMenu("Return menu", 0, 420, ClassicFont);
        break;

    case 4:
        drawImage(getSprite(TUTO_1_SPRITE), 0, 0);
        break;

    case 5:
        drawImage(getSprite(TUTO_2_SPRITE), 0, 0);
        break;

    case 6:
	    drawImage(getSprite(CONTROLE_SPRITE), 0, 0);
        break;

    case 7:
         drawImage(getSprite(BACKGROUND_LAUNCH_SPRITE), 0, 0);
         drawAbout();
	 break;
    }


    SDL_Flip(screen);
}
