#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "event_handler.h"





int main(int argc, const char * argv[]) {
    SDL_Window *mainWindow = NULL;
    SDL_Renderer *mainRenderer = NULL;
    AL_initWindowAndRenderer(&mainWindow, &mainRenderer);
    AL_initImage();
    srand(time(NULL));
    
    
    AL_initializePlayer(&player);
    AL_presentStats(&player);
    Encounter testEncounter;
    
    SDL_Event event;
    GameState StateOfGame = MAIN_MENU;
    int prevTime = 0;
    int currentTime = 0;
    double deltaTime = 0;
   
    
   /* //This can be removed----------------------
    strcpy(testEncounter.name, "Test");
    testEncounter.weapondamage = 1;
    testEncounter.weaponnumber = 20;
    testEncounter.crew = 60;
    testEncounter.health = 100;
    testEncounter.speed = 5;
    testEncounter.oldTime = SDL_GetTicks();
    //----------------------------------------- */
    
    AL_getEncounter(&testEncounter);
    
    AL_initialiseTTF();
    
    for (bool isRunning = true; isRunning; isRunning = AL_checkForQuit(event)){
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime)/1000.0;
        
        
        event = AL_checkForPress(StateOfGame);
        AL_callCorrectState(&StateOfGame, mainRenderer, &event, deltaTime, &testEncounter);

        
        SDL_RenderPresent(mainRenderer);
    }
    
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    IMG_Quit();
    SDL_Quit();
    
}
