#include "fonctions.h"

void loadAllMusic(){                // Chargement de toutes les musiques utilisées dans le programme
    /*** Effets sonores ***/
    musiqueKick = Mix_LoadWAV("sde/Kick.wav");
    musiqueLaser = Mix_LoadWAV("sde/Laser.aiff");
    /*** Effets sonores ***/

    /*** Musiques ***/
    musiqueMenu = Mix_LoadMUS("sde/Menu.mp3");
    musiqueGame = Mix_LoadMUS("sde/Game.mp3");
    /*** Musiques ***/

    Mix_AllocateChannels(2);                // Création de deux canaux audio (superposition des effets sonores)
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);      // Réglage du volume de la musique
}


void freeMusic(){              // Libère la musique chargée en mémoire

    Mix_FreeChunk(musiqueKick);
    Mix_FreeChunk(musiqueLaser);
    Mix_FreeMusic(musiqueGame);
    Mix_FreeMusic(musiqueMenu);
}
