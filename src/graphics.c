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
        // Uint32 colorkey = SDL_MapRGB( (*surface).format, 0, 0, 0 );
        // SDL_SetColorKey( surface, SDL_SRCCOLORKEY, colorkey );
    }

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = ((*screen).w - (*surface).w )/ 2 +x;
    dest.y = ((*screen).h - (*surface).h) / 3 + y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}


void drawText(char *text, int x, int y, TTF_Font *textFontn, int r, int g, int b)
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
    Font = loadFont("sfd/FreeSans.ttf", 30);
    textFont = loadFont("sfd/FreeSans.ttf", 15);
    loadSprite(PLAYER_R_SPRITE, "gfx/Roger_CleanR.png");
    loadSprite(PLAYER_L_SPRITE, "gfx/Roger_CleanL.png");
    loadSprite(BACKGROUND_LAUNCH_SPRITE, "gfx/Menu.png");
    loadSprite(BACKGROUND_END_SPRITE, "gfx/TerrainV2.png");
    loadSprite(BACKGROUND_SPRITE, "gfx/TerrainV4.png");
    loadSprite(OFFICER_SPRITE, "gfx/Agent_Clean.png");
    loadSprite(TOURELLE_1_SPRITE, "gfx/Tourelle_Clean.png");
    loadSprite(TOURELLE_2_SPRITE, "gfx/Tourelle_Clean2.png");
    loadSprite(TOURELLE_3_SPRITE, "gfx/Tourelle_Clean.png");    
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
    loadSprite(LASER_SPRITE, "gfx/Laser_Clean.png");
}

void doOption()
{

        if(Game.drawOption == 1)
        {
            drawText("Upgrade", Game.xOp+4, Game.yOp+10, textFont,240,240,0);
            drawText("Vendre  ", Game.xOp+5, Game.yOp+32, textFont,240,240,0);

        }
}


void doInterface() {
	char string[20] ;
    
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
		       

        if(Game.countdown - Game.timer > 0 && Game.nbEnnemiAlive == 0 )
            {
            sprintf(string,"%d", (Game.countdown+1 - Game.timer)/30 );
            drawMenu(string, 500, 250, Font);
            }
}


void doBaseHealth() {
	switch(Game.hpBase) {
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
			
		default:			
			drawImage(getSprite(BASE_HEALTH_9_SPRITE), 723, 600);
			break;
			
	}
}


void updateScreen()
{
    /* Blank the screen */
    SDL_FillRect(screen, NULL, 0);

    switch(Game.stade)
    {
    case 0:
        drawImage(getSprite(BACKGROUND_LAUNCH_SPRITE), 0, 0);
        drawMenu("QUIT", 0, 260, Font);
        break;


    case 1:
        doEnnemi();
        doTourelle();
        drawImage(getSprite(BACKGROUND_SPRITE), 0, 0);
	
	doInterface();
        drawOfficer();
        drawTourelle();
        drawPlayer();
        doOption();
        updateTir();
	doBaseHealth();
        collision();
        break;


    case 2:
        drawImage(getSprite(BACKGROUND_END_SPRITE), 0, 0);
        drawMenu("GAME OVER !", 0, 0, Font);
        drawMenu("Play again?", 0, 200, Font);
        break;
    }


    SDL_Flip(screen);
}
