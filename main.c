#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "display.h"



int main(int argc, const char * argv[]) {
    SDL_Window *mainWindow = NULL;
    SDL_Renderer *mainRenderer = NULL;
    AL_initWindowAndRenderer(&mainWindow, &mainRenderer);
    AL_initImage();
    
    
    AL_Sprite lightning;
    lightning.image = AL_loadTexture("images/storm.png", mainRenderer);
    AL_setSpriteSheetData(&lightning, 150, 13, 1);
    AL_setSpriteSizeAndLocation(&lightning, 0, 0, lightning.frameWidth, lightning.frameHeight);
    
    for (bool isRunning = true; isRunning; isRunning = checkForQuit()){
        
        AL_getNextFrame(&lightning);
        
        
        SDL_RenderClear(mainRenderer);
        SDL_RenderCopy(mainRenderer, lightning.image, &lightning.source, &lightning.destination);
        SDL_RenderPresent(mainRenderer);

    }
    
    
    
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    IMG_Quit();
    SDL_Quit();
    
}

