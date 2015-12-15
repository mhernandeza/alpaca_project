#ifndef event_handler_h
#define event_handler_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.h"
#include "AL_combat.h"


bool AL_checkForQuit(SDL_Event event);
SDL_Event AL_checkForPress(GameState StateOfGame);
void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event *event, double deltaTime, Encounter *encounter);
#endif /* event_handler_h */
