//
//  event_handler.c
//  ALKrakenMain
//
//  Created by Lee's Mac on 11/19/15.
//  Copyright © 2015 Walid Beydoun. All rights reserved.
//

#include "event_handler.h"

//Checks if the quit button was pressed and returns a boolean for the value. Note funct returns false if quit was pressed.
bool AL_checkForQuit(SDL_Event event){
    if(event.type == SDL_QUIT){
        return false;
    }
    return true;
}

void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event event){
    switch (*StateOfGame) {
        case MAIN_MENU:
            AL_LoadMainMenuState(mainRenderer, StateOfGame, event);
            break;
        case PLAY_GAME:
            AL_LoadPlayGameState(mainRenderer, StateOfGame, event);
            break;
        default:
            break;
    }
    
}

SDL_Event AL_checkForPress(GameState StateOfGame){
    SDL_Event event;
    if(StateOfGame == MAIN_MENU){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                    case SDLK_w:
                        return event;
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        return event;
                        break;
                    case SDLK_RETURN:
                        return event;
                        break;
                    default:
                        event.key.keysym.sym = SDLK_0;
                        return event;
                        break;
                }
            }
        }
    }
    if (StateOfGame == PLAY_GAME){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE:
                        return event;
                        break;
                    default:
                        event.key.keysym.sym = SDLK_0;
                        return event;
                        break;
                }
            }
        }
    }
    event.key.keysym.sym = SDLK_0;
    return event;
}