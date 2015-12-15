#include "event_handler.h"

//Checks if the quit button was pressed and returns a boolean for the value. Note funct returns false if quit was pressed.
bool AL_checkForQuit(SDL_Event event){
    if(event.type == SDL_QUIT){
        return false;
    }
    return true;
}

void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event *event, double deltaTime, Encounter *encounter){
    switch (*StateOfGame) {
        case MAIN_MENU:
            AL_LoadMainMenuState(mainRenderer, StateOfGame, event);
            break;
        case PLAY_GAME:
            AL_LoadPlayGameState(mainRenderer, StateOfGame, event, deltaTime);
            break;
        case OPTIONS_MENU:
            AL_LoadOptionState(mainRenderer, StateOfGame, event);
            break;
        case COMBAT_STATE:
            AL_playCombat(&player, encounter);
            AL_LoadCombatState(mainRenderer, StateOfGame, event, deltaTime, encounter);
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
                    case SDLK_DOWN:
                    case SDLK_s:
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
    if (StateOfGame == PLAY_GAME || StateOfGame == COMBAT_STATE || StateOfGame == OPTIONS_MENU){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE:
                    case SDLK_a:
                    case SDLK_s:
                    case SDLK_d:
                    case SDLK_w:
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