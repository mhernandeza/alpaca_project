#include "AL_event_handler.h"

//Checks if the quit button was pressed and returns a boolean for the value. Note funct returns false if quit was pressed.
bool AL_checkForQuit(SDL_Event event){
    if(event.type == SDL_QUIT){
        return false;
    }
    return true;
}

void AL_callCorrectState(GameState *StateOfGame, SDL_Renderer *mainRenderer, SDL_Event *event, double deltaTime, Encounter *encounter, Encounter encounterArray[8]){
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
            AL_playCombat(&player, encounter, StateOfGame);
            AL_LoadCombatState(mainRenderer, StateOfGame, event, deltaTime, encounter);
            AL_renderUIStats(mainRenderer);
            AL_renderEnemyStats(mainRenderer, encounter);
            if((player.health <= player.retreatHealth && player.health >= 0) || (player.weaponNumber <= player.retreatWeapons && player.weaponNumber > 0)){
                AL_LoadRetreatScene(deltaTime, mainRenderer, StateOfGame);
            } else if ((encounter->weaponnumber <= 0 || encounter->health <= 0) && encounter->ID != 0){
                AL_LoadSurrenderScene(deltaTime, mainRenderer, StateOfGame);
            }
            break;
        case GAME_OVER:
            AL_LoadGameOverState(mainRenderer, StateOfGame, event);
            AL_renderHighScore(mainRenderer);
            break;
        case LOGO_STATE:
            AL_LoadLogoState(mainRenderer, StateOfGame);
            break;
        case BEHAVIOUR_STATE:
            AL_LoadBehaviourState(mainRenderer, StateOfGame, event);
            AL_renderUIStats(mainRenderer);
            break;
        case WORLD_STATE:
            AL_LoadWorldState(mainRenderer, StateOfGame, event, encounter, encounterArray);
            break;
        case WEATHER_STATE:
            AL_LoadWeatherState(deltaTime, mainRenderer, StateOfGame, encounter);
            AL_renderUIStats(mainRenderer);
            break;
        default:
            break;
    }
}

SDL_Event AL_checkForPress(GameState StateOfGame){
    SDL_Event event;
    if(StateOfGame == MAIN_MENU || StateOfGame == GAME_OVER){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                    case SDLK_w:
                    case SDLK_DOWN:
                    case SDLK_s:
                    case SDLK_m:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuHover.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
                        return event;
                        break;
                    case SDLK_RETURN:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuSelect.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
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
    if (StateOfGame == PLAY_GAME || StateOfGame == OPTIONS_MENU || StateOfGame == LOGO_STATE){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE:
                    case SDLK_a:
                    case SDLK_s:
                    case SDLK_d:
                    case SDLK_w:
                    case SDLK_m:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuHover.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
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
    if (StateOfGame == COMBAT_STATE || StateOfGame == WEATHER_STATE){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE:
                    case SDLK_a:
                    case SDLK_s:
                    case SDLK_d:
                    case SDLK_w:
                    case SDLK_m:
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

    if (StateOfGame == BEHAVIOUR_STATE){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_a:
                    case SDLK_d:
                    case SDLK_w:
                    case SDLK_s:
                    case SDLK_m:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuHover.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
                        return event;
                        break;
                        
                    case SDLK_RETURN:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuSelect.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
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
    if (StateOfGame == WORLD_STATE){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_a:
                    case SDLK_d:
                    case SDLK_m:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuHover.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
                        return event;
                        break;
                        
                    case SDLK_RETURN:
                        if(player.soundFX != NULL){
                            Mix_FreeChunk(player.soundFX);
                        }
                        player.soundFX = Mix_LoadWAV("sounds/mainMenuSelect.wav");
                        Mix_PlayChannel(-1, player.soundFX, 0);
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