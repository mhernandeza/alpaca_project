# include "AL_encounters.h"
#include "AL_state_data.h"
#include "AL_event_handler.h" //Change this later. We just need SDL
# define WORDL 20

void AL_presentStats(User *player); /*Replace by SDL*/
void AL_initializePlayer(User *player); /*Called by the driver*/
void AL_programReaction(User *player, Encounter *test);/*Called by the driver*/
void AL_askHealth(User *player);/*Local*/
int AL_setupRetreathealth(int x, int h);/*Local*/
void AL_askWeapons(User *player);/*Local*/
void AL_askKraken(User *player);/*Local*/

/*For combat*/
int AL_getHealth(User *player);
/*Returns the user's current health*/
int AL_getWeaponNumber(User *player);
/*Returns the user ammount of weapons*/
int AL_getWeaponDamage(User *player);
/*Returns the user's weapon damage*/
int AL_getGold(User *player);
/*Returns the user's current gold*/
int AL_decreaseHealth(User *player, int amount);
/*Modifies the user's current health by a fixed amount, returns the resulting health*/
int AL_increaseHealth(User *player, int amount);
/*Modifies the user's current health by a fixed amount, returns the resulting health*/
int AL_decreaseWeapons(User *player, int amount);
/*Modifies the user's number of weapons by a fixed amount, returns the resulting number*/
int AL_increaseWeapons(User *player, int amount);
/*Modifies the user's number of weapons by a fixed amount, returns the resulting number*/
int AL_increaseGold(User *player, int amount);
/*Modifies the user's current gold by a fixed amount, returns the resulting gold*/
int AL_getRetreatHealth(User *player);
/*Returns retreat health programmed by the user*/
int AL_getRetreatWeapons(User *player);
/*Returns 1 if the user decided to retreat when having less cannons than the enemy*/
int AL_getSpeed(User *player);
/*Returns players reloading speed*/
int AL_getCrew(User *player);
/*Returns players crew number*/
int AL_increaseCrew(User *player, int amount);
/*Modifies crew number by an amount and returns the result*/
int AL_decreaseCrew(User *player, int amount);
/*Modifies crew number by an amount and returns the result*/
