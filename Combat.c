#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "encounter.h"
#include <time.h>


#define BOOL int
#define TRUE 1
#define FALSE 0
#define TURNTIME 1000

int retreat_condiition (void);
int AL_damageHandle (int WeaponNum, int weapondamage);
int AL_reloadCannons (int Weapon_Number);
int AL_shoot_cannons (int Player_charge);
int tick (void);

struct user_fake {
  int Hull;
  int WeaponNumber;
  int WeaponDamage;
  char *weapontype;
  char *descriptor;
  char *pronoun;
  char *name;
  int Speed;
  int gold;
};

int main (void)
{
  struct player1, player2, test;
  main2(); /* when game controller ready, delete this and replace with srand(time(NULL)) at the highest level; */
  Encounter player2; /* move this to game controller module */
  AL_getEncounter(&test); /* move this to game controller module then pass yourself a pointer to the struct */
  printf("\nEncounter: %s!\nYou see %s on the horizon to the %s; %s is armed with %d %s.\nThe weather looks %s.\n\n",
  test.name,test.description,test.locale.direction,test.pronoun,test.weaponnumber,test.weapontype,test.locale.weatherdescription);
  int Player_charge = 0, Enemy_charge = 0, retreat_Counter = 10, playerfire = 0, enemyfire = 0;
  if (tick() == 1){
    if ((AL_getRetreatHealth(player1) < AL_getHealth(player1) )||
    ((AL_getRetreatWeapons(player1) == 1) &&
    (AL_getEnemyRetreatWeapon(player2) > AL_getWeaponNumber(player1))) {
      retreat_Counter++;
      printf("%d turns till escape\n", 10 - retreat_Counter);
    }
    Player_charge += AL_reloadCannons(AL_getWeaponNumber(player1));
    Enemy_charge += AL_reloadCannons(player2.weaponnumber);
    if (retreat_Counter >= 0) {
      printf("Retreating!\n");
    }
    if (AL_shoot_cannons(Player_charge) == 1){
      Player_charge -= 100;
      player2.health -= AL_damageHandle(AL_getWeaponNumber(player1), AL_getWeaponDamage(player1));
    }
    if (AL_shoot_cannons(Enemy_charge) == 1){
      AL_decreaseHealth(damageHandle(player2.weaponnumber, player2.weapondamage));
      Enemy_charge -= 100;
    }
  if (player2.Hull <= 0) {
    return 1;
  }
  if (AL_getHealth(player1) <= 0) {
    return 0;
  }
  if (retreat_Counter == 10){
    retreat_condiition();
    return 1;
  }
  }
  return 1;
}

int AL_reloadCannons (int Weapon_Number)
{
  return (AL_getWeaponNumber(player1));
}

int AL_shoot_cannons (int Player_charge)
{
  int x;
  if (Player_charge >= 100){
    printf("Ready to fire\n");
    x = rand() % 3;
    if (x == 0 ){
      printf("\n               BANG!\n\n");
    }
    if (x == 1) {
      printf("\n               WOOSH!\n\n");
    }
    if (x == 2) {
      printf("                 KERPOW!\n\n");
    }
    return 1;
  }
  return 0;
}

int AL_damageHandle (int WeaponNum, int weapondamage)
{
  int x, y = 0, hits = 0, critical = 0, miss = 0;
  for (x = 0 ; x < WeaponNum ; x++) {
    y = rand()%6;
    if (y <= 1) {
      miss++;
    }
    if (y >= 3 && y<= 4) {
      hits++;
    }
    if (y == 5) {
      hits+=2;
      critical++;
    }
  }
  printf("%d Shots hit the target, %d critical hits were dealt, %d Damage Dealt\n%d shots missed\n", hits, critical, (hits*weapondamage), miss);
  return hits*weaponDamage;
}

int retreat_condiition (void)
{
  printf("you managed to escape with your life!\n");
  return 0;
}

int tick (void)
{
  if (time(NULL)%TURNTIME == 0){
    return 1;
  }
  return 0;
}
