
#ifndef state_data_h
#define state_data_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "AL_encounters.h"

typedef int bool;
#define true 1
#define false 0

#define WORD_LEN 30

struct playerShip {
    char playerName[WORD_LEN];
    char shipName[WORD_LEN];
    char weaponType[WORD_LEN];
    int weaponNumber;/*From 20 to 50*/
    int weaponDamage;/*1 or 2*/
    int health; /*0 to 100*/
    int speed;/*From 1 to 10*/
    int luck;/*From 1 to 10*/
    int gold;/*Starting with 1000*/
    int crew;/*From 1 to 100*/
    int retreatHealth;
    int retreatWeapons;
    int oldTime;
    bool isFiring;
};
typedef struct playerShip User;

enum GameState { LOGO_STATE, MAIN_MENU, OPTIONS_MENU, PLAY_GAME, BEHAVIOUR_STATE, COMBAT_STATE, GAME_OVER};
typedef enum GameState GameState;

void AL_initialisePlayerShip();

extern User player;



#endif /* state_data_h */
