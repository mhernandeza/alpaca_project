#include "AL_sound.h"

int AL_initSound(){
    if (SDL_Init(SDL_INIT_AUDIO) != 0){
        fprintf(stderr, "SDL_Mixer could not be initialised! SDL_mixer Error: %s\n", SDL_GetError());
        return false;
    }
    
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fprintf(stderr, "SDL_Mixer could not be initialised! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    return true;
}