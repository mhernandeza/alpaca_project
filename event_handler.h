//
//  event_handler.h
//  ALKrakenMain
//
//  Created by Lee's Mac on 11/19/15.
//  Copyright © 2015 Walid Beydoun. All rights reserved.
//

#ifndef event_handler_h
#define event_handler_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include "state_data.h"
#include "display.h"

typedef int bool;
#define true 1
#define false 0



bool AL_checkForQuit(SDL_Event event);
SDL_Event AL_checkForPress(GameState StateOfGame);
void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event event);
#endif /* event_handler_h */
