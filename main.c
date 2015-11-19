#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "event_handler.h"




int main(int argc, const char * argv[]) {
    SDL_Window *mainWindow = NULL;
    SDL_Renderer *mainRenderer = NULL;
    AL_initWindowAndRenderer(&mainWindow, &mainRenderer);
    AL_initImage();
    
    GameState StateOfGame = MAIN_MENU;
    SDL_Event event;
    AL_LoadMainMenuState(mainRenderer, &StateOfGame, event);

    for (bool isRunning = true; isRunning; isRunning = AL_checkForQuit(event)){
        
        event = AL_checkForPress(StateOfGame);
        AL_callCorrectState(&StateOfGame, mainRenderer, event);
        
        
        SDL_RenderPresent(mainRenderer);
        

    }
    
    
    
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    IMG_Quit();
    SDL_Quit();
    
}
