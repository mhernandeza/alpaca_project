# include "AL_combat.h"

int AL_playCombat(User *player, Encounter *player2)
{
  int Player_charge = 0, Enemy_charge = 0, retreat_Counter = 10, playerfire = 0, enemyfire = 0;
  if (tick() == 1){
    if ((AL_getRetreatHealth(player) < AL_getHealth(player) )||
    ((AL_getRetreatWeapons(player) == 1) &&
    (AL_getEnemyRetreatWeapon(player2) > AL_getWeaponNumber(player))) {
      retreat_counter++;
      printf("%d turns till escape\n", 10 - retreat_counter);
    }
    Player_charge += AL_reloadCannons(AL_getWeaponNumber(player));
    Enemy_charge += AL_reloadCannons(player2->weaponnumber);
    if (retreat_counter >= 0) {
      printf("Retreating!\n");
    }
    else {
      if (AL_shoot_cannons(Player_charge) == 1){
        Player_charge -= 100;
        player2->health -= AL_damageHandle(AL_getWeaponNumber(player), AL_getWeaponDamage(player));
      }
      if (AL_shoot_cannons(Enemy_charge) == 1){
        AL_decreaseHealth(damageHandle(player2->weaponnumber, player2->weapondamage));
        Enemy_charge -= 100;
      }
    }
  }
  if (player2->Hull <= 0){
    return 1;
  }
  if(AL_getHealth(player) <= 0){
    return 0;
  }
  if (retreat_counter == 10){
    retreat_condition();
    return 1;
  }
  return 0;
}

int AL_reloadCannons (int Weapon_Number)
{
  return (AL_getWeaponNumber(player));
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
  for (x = 0 ; x < WeaponNumber ; x++) {
    y = rand()%6
    if (y <= 1) {
      miss++;
    }
    if (y >= 2 && y<= 4) {
      hits++;
    }
    if (y == 5) {
      hits+=2;
      critical++;
    }
  }
  printf("%d Shots hit the target, %d critical hits were dealt,
  %d Damage Dealt\n%d shots missed\n", hits, critical, hits*weapondamage, miss);
  return hits*weaponDamage
}

int retreat_condition (void)
{
  printf("you managed to escape with your life!\n");
  return 0;
}

int tick (void)
{
  if (time()%TURNTIME == 0){
    return 1;
  }
  return 0;
}
