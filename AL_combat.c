# include "AL_combat.h"

int AL_playCombat(User *player, Encounter *player2)
{
  int Player_charge = 0, Enemy_charge = 0, retreat_Counter = 0, newloot = 0, healing = 0;
  do {
    if (tick() == 1){
      if ((AL_getRetreatHealth(player) > AL_getHealth(player) )/*||
      ((AL_getRetreatWeapons(player) == 1)  &&
      (AL_getEnemyRetreatWeapon(player2) > AL_getWeaponNumber(player)))*/) {
      retreat_Counter++;
      printf("%d turns till escape\n", 3 - retreat_Counter);
    }
    Player_charge += ((float)AL_getCrew(player)/(float)AL_getWeaponNumber(player))*100;
    Enemy_charge += ((float)player2->crew/(float)player2->weaponnumber)*100;
    if (retreat_Counter > 0) {
      printf("Retreating!\n");
    }
      if (AL_shoot_cannons(Player_charge) == 1){
        Player_charge = 0;
        printf("You take a shot at the enemy!\n");
        player2->health -= AL_damageHandle(AL_getWeaponNumber(player), AL_getWeaponDamage(player));
      }
      if (AL_shoot_cannons(Enemy_charge) == 1){
        Enemy_charge = 0;
        printf("The enemy takes a shot at you!\n");
        AL_decreaseHealth(player, AL_damageHandle(player2->weaponnumber, player2->weapondamage));

      }
    if (player2->health <= 0){
      newloot = rand()%(player2->weaponnumber);
      healing = ((100-AL_getHealth(player))/10);
      printf("You sank the Enemy ship\nYour carpenter repaired the ship from %d to %d\n", AL_getHealth(player), AL_increaseHealth(player, healing));
      printf("You salvaged %d worth of gold from the wreck, you now have %d gold pieces\n", newloot,(AL_increaseGold(player, newloot)));
      return 1;
    }
    if(AL_getHealth(player) <= 0){
      printf("Your ship was sunk by the enemy ship\n");
      return 0;
    }
    if (retreat_Counter==3){
      retreat_condition();
      return 1;
    }
  }
}
while (AL_getHealth(player) >= 0 && player2->health >= 0);
return 0;
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
  int x, y = 0, hits = 0, miss = 0;
  for (x = 0 ; x < WeaponNum ; x++) {
    y = rand()%6;
    if (y <= 2) {
      miss++;
    }
    if (y >= 3 && y<= 4) {
      hits++;
    }
    if (y == 5) {
      hits++;
    }
  }
  printf("%d Shots hit the target, %d Damage Dealt\n%d shots missed\n", hits, hits*weapondamage, miss);
  return (hits*weapondamage);
}

int retreat_condition (void)
{
  printf("you managed to escape with your life!\n");
  return 0;
}

int tick (void)
{
  SDL_Delay(TURNTIME);
  return 1;
}

int Critical_Damage  (void)
{
  int y;
    y = rand() % 6;
    if (y <= 3 ){
      return 1;
/*double damage*/
    }
    if (y == 4) {
      return 2;
/*start a fire on ship*/
    }
    if (y == 5) {
      return 3;
/*destroy a cannon*/
    }
  return 0;
}
