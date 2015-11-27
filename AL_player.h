# include "encounter.h"
# define WORDL 20

struct user_ship{
  char playerName[WORDL];
  char shipName[WORDL];
  char weaponType[WORDL];
  int weaponNumber;/*From 20 to 50*/
  int weaponDamage;/*1 or 2*/
  int health; /*0 to 100*/
  int speed;/*From 1 to 10*/
  int luck;/*From 1 to 10*/
  int gold;/*Starting with 1000*/
  int retreatHealth;
  int retreatWeapons;
};
typedef struct user_ship User;

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
int AL_increaseGold(User *player, int amount);
/*Modifies the user's current gold by a fixed amount, returns the resulting gold*/
int AL_getRetreatHealth(User *player);
/*Returns retreat health programmed by the user*/
int AL_getRetreatWeapons(User *player);
/*Returns 1 if the user decided to retreat when having less cannons than the enemy*/
int AL_getSpeed(User *player);
/*Returns players reloading speed*/
