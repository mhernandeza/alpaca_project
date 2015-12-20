#ifndef display_h
#define display_h

#include <stdio.h>

#include "state_data.h"
#include "AL_combat.h"

typedef int bool;
#define true 1
#define false 0

struct AL_Sprite {
    SDL_Texture *image;
    SDL_Rect source;
    SDL_Rect destination;
    Uint32 oldTime;
    Uint32 speed;
    
    int numberOfFrames;
    int textureWidth;
    int textureHeight;
    int frameWidth, frameHeight;
};
typedef struct AL_Sprite AL_Sprite;

void AL_getNextFrame(AL_Sprite *spriteSheet);
void AL_setSpriteSheetData(AL_Sprite *spriteSheet, unsigned int frameRate, unsigned int numOfCols, int numOfRows);
void AL_setSpriteSizeAndLocation(AL_Sprite *spriteSheet, int xLocation, int yLocation, int width, int height);
bool AL_initWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderTarget);
bool AL_initImage();
SDL_Texture *AL_loadTexture(char *path, SDL_Renderer *renderTarget);


void AL_LoadMainMenuState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event);
void AL_LoadOptionState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event);
void AL_LoadPlayGameState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event, double deltaTime);
void AL_LoadCombatState(SDL_Renderer *mainRenderer, GameState *StateofGame, SDL_Event *event, double deltaTime, Encounter *encounter);
void AL_LoadGameOverState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event);
void AL_LoadLogoState(SDL_Renderer *mainRenderer, GameState *StateOfGame);
void AL_LoadBehaviourState(SDL_Renderer *mainRender, GameState *StateOfGame, SDL_Event *event);
void AL_LoadWorldState(SDL_Renderer *mainRender, GameState *StateOfGame, SDL_Event *event, Encounter *encounter, Encounter encounterArray[8]);
void AL_LoadRetreatScene(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame);

void AL_LoadWeatherState(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame, Encounter *encounter);
void AL_LoadSurrenderScene(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame);
#endif /* display_h */

