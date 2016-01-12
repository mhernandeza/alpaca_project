#ifndef event_handler_h
#define event_handler_h

#include <SDL2/SDL.h>
#include "AL_display.h"
#include "AL_combat.h"
#include "AL_ttf_fonts.h"
#include "AL_encounters.h"
#include "AL_weather.h"
#include "AL_sound.h"

bool AL_checkForQuit(SDL_Event event);
SDL_Event AL_checkForPress(GameState StateOfGame);
void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event *event, double deltaTime, Encounter *encounter, Encounter encounterArray[8]);
#endif /* event_handler_h */
