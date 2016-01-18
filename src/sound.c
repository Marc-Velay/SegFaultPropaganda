#include "fonctions.h"

void loadAllMusic(){
    musiqueKick = Mix_LoadWAV("sde/Kick.wav");
    musiqueLaser = Mix_LoadWAV("sde/Laser.aiff");
    musiqueMenu = Mix_LoadMUS("sde/Menu.mp3");
    musiqueGame = Mix_LoadMUS("sde/Game.mp3");

    Mix_AllocateChannels(2);
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
}
