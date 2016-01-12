#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "AL_event_handler.h"





int main(int argc, const char * argv[]) {
    SDL_Window *mainWindow = NULL;
    SDL_Renderer *mainRenderer = NULL;
    AL_initWindowAndRenderer(&mainWindow, &mainRenderer);
    AL_initImage();
    AL_initSound();
    srand(time(NULL));
    
    
    
    AL_initializePlayer(&player);
    Encounter encounterArray[8];
    Encounter encounter;
    
    SDL_Event event;
    GameState StateOfGame = LOGO_STATE;
    int prevTime = 0;
    int currentTime = 0;
    double deltaTime = 0;
    static int gettingEncounter = 1;
    
    AL_getEncounter(encounterArray);
    
    
    AL_initialiseTTF();
    
    for (bool isRunning = true; isRunning; isRunning = AL_checkForQuit(event)){
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime)/1000.0;
        
        if (event.key.keysym.sym == SDLK_m){
            if(Mix_PausedMusic() == 1){
                Mix_ResumeMusic();
            } else {
                Mix_PauseMusic();
            }
        }
        
        
        if(gettingEncounter == 1 && StateOfGame == WORLD_STATE){
            AL_getEncounter(encounterArray);
            gettingEncounter = 0;
        }
        
        if(StateOfGame == COMBAT_STATE || StateOfGame == WEATHER_STATE){
            gettingEncounter = 1;
        }
        
        
        
        event = AL_checkForPress(StateOfGame);
        AL_callCorrectState(&StateOfGame, mainRenderer, &event, deltaTime, &encounter, encounterArray);
        
        
        SDL_RenderPresent(mainRenderer);
    }
    
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    IMG_Quit();
    SDL_Quit();
    
}
