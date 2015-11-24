# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>
# define WORDL 20

struct user_ship{
  char playerName[WORDL];
  char shipName[WORDL];
  char weaponType[WORDL];
  int weaponNumber; /*Mandar*/
  int weaponDamage; /*Mandar*/
  int health; /*Mandar*/
  int speed;
  int luck;
  int gold; /*Mandar*/
  int retreatHealt;/*Mandar*/
  int retreatWeapons;/*Mandar*/
};
typedef struct user_ship User;

void AL_presentStats(User *player1); /*Replace by SDL*/
void AL_initializePlayer(User *player1); /*Called by the driver*/
void AL_programReaction(User *player1); /*Called by the driver*/
int AL_getHealth(User *player);/*For combat*/
int AL_getWeaponNumber(User *player);/*For combat*/
int AL_getWeaponDamage(User *player);/*For combat*/
int AL_getGold(User *player);/*For combat*/
int AL_decreaseHealth(User *player);/*For combat*/
int AL_increaseGold(User *player);/*For combat*/
int AL_getRetreatHealth(User *player);/*For combat*/
int AL_getRetreatWeapons(User *player);/*For combat*/
