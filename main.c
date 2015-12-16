#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "event_handler.h"

#define WORLDSIZE 5

int main(int argc, const char * argv[]) {
    SDL_Window *mainWindow = NULL;
    SDL_Renderer *mainRenderer = NULL;
    AL_initWindowAndRenderer(&mainWindow, &mainRenderer);
    AL_initImage();
    AL_initializePlayer(&player);
    AL_presentStats(&player);
    Encounter testEncounter;
    Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2];
    SDL_Event event;
    GameState StateOfGame = MAIN_MENU;
    int prevTime = 0;
    int currentTime = 0;
    double deltaTime = 0;

   /* temporary encounter creation */
    strcpy(testEncounter.name, "Test");
    testEncounter.weapondamage = 1;
    testEncounter.weaponnumber = 20;
    testEncounter.crew = 60;
    testEncounter.health = 100;
    testEncounter.speed = 5;
    testEncounter.oldTime = SDL_GetTicks();
    /* DELETE AFTER ENCOUNTER STUFF FINAL */


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
