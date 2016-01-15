#include "fonctions.h"

void loadAllMusic(){

    musiqueLaser = Mix_LoadMUS("sde/Laser.aiff");
    musiqueMenu = Mix_LoadMUS("sde/Menu.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
}

