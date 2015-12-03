# include "AL_combat.h"

int AL_playCombat(User *player, Encounter *player2)
{
  int  Player_charge = 0, Enemy_charge = 0, retreat_Counter = 0, surrender;
  do {
    if (tick() == 1){
      if (AL_getRetreatHealth(player) > AL_getHealth(player) ) {
        retreat_Counter++;
        printf("%d turns till escape\n", 10 - retreat_Counter);
      }
      if (player2->weaponnumber == 0 ) {
        printf("The enemy is defenseless, do you accept their surrender?\n1: Yes\n2: No\n");
        if (scanf("%d", &surrender) == 1) {
          if (surrender == 1) {
            printf("They give you a token of their appreciation\n");
            AL_collectLoot(player, player2);
            return 1;
          }
        }
        else {
          printf("Send them to a watery grave");
          AL_collectLoot (player, player2);
          return 1;
        }
        }
        if (player2->crew <= 0 ){
          printf("The enemy ship is a ghost ship? We collect what is left");
          AL_collectLoot(player, player2);
        }
      Player_charge += ((float)AL_getCrew(player)/(float)AL_getWeaponNumber(player))*10;
      Enemy_charge += ((float)player2->crew/(float)player2->weaponnumber)*10;
      if (retreat_Counter > 0) {
        printf("Retreating!\n");
      }
      if (AL_shoot_cannons(Player_charge) == 1){
        Player_charge = Player_charge % 100;
        printf("You take a shot at the enemy!\n");
        player2->health -= AL_damageHandle(AL_getWeaponNumber(player), AL_getWeaponDamage(player), 2, player, player2);
        SDL_Delay(400);
      }
      if (AL_shoot_cannons(Enemy_charge) == 1){
        Enemy_charge = Enemy_charge % 100;
        printf("The enemy takes a shot at you!\n");
        AL_decreaseHealth(player, AL_damageHandle(player2->weaponnumber, player2->weapondamage, 1, player, player2));
        SDL_Delay(400);
      }
      if (player2->health <= 0){
        AL_collectLoot (player, player2);
      }
      if(AL_getHealth(player) <= 0){
        printf("Your ship was sunk by the enemy ship\n");
        return 0;
      }
      if (retreat_Counter==10){
        retreat_condition();
        return 1;
      }
  }
}
  while (AL_getHealth(player) >= 0 && player2->health >= 0);
  return 1;
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
      printf("\n               KERPOW!\n\n");
    }
    return 1;
  }
  return 0;
}

int AL_damageHandle (int WeaponNum, int weapondamage, int defender, User *player1, Encounter *player2)
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
      if (defender == 1){
        AL_decreaseHealth(player1 ,Critical_Damage(player1, player2, 2));
      }
      if (defender == 2) {

        player2->health -= Critical_Damage(player1, player2, 1);
      }
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

int Critical_Damage  (User *player, Encounter *player2, int attacker)
{
  int y;
  y = rand() % 6;
  if (player2->ID == 3) {
//the Kracken exception
      player2->health -= 5;
      printf("The cannon ball hits the kracken's eye!");
  }
  printf("The shot was super effective! ");
  if (y <= 1 ){
    printf("It did aditional damage\n");
    if (attacker == 1) {
      player2->health -= 1;
    }
    else {
      AL_decreaseHealth(player, 1);
    }
  }
  if (y == 2 || y == 3 ) {
    printf("It took out a cannon!\n");
    if (attacker == 1) {
      player2->weaponnumber -= 1;
      if(player2->weaponnumber < 0){
        player2->weaponnumber=0;
      }

      }
    }
    else {
      AL_decreaseWeapons(player, 1);
    }
  /*destroy a cannon*/
  if (y == 4 || y == 5) {
    printf("It killed a crew member\n");
    if (attacker == 1) {
      player2->crew -= 1;
    }
    else {
      AL_decreaseCrew(player, 1);
    }
  }
  return 0;
}

int AL_collectLoot (User *player, Encounter *player2)
{
  int newloot, healing, Newcrew, takecrew;
  newloot = 100 + rand()%(player2->weaponnumber + 1);
  healing = ((100-AL_getHealth(player))/10);
  Newcrew = rand()%(player2->crew/10);
  printf("You sank the Enemy ship\nYour carpenter repaired the ship by %d to %d\n", healing, AL_increaseHealth(player, healing));
  printf("You salvaged %d worth of gold from the wreck, you now have %d gold pieces\n", newloot,(AL_increaseGold(player, newloot)));
  if (Newcrew > 0 ) {
    printf("You find %d survivors, would you like to offer them a place on your crew?\n1: Yes\n2: No\n", Newcrew);
    if (scanf("%d", &takecrew) == 1){
      if (takecrew == 1) {
        printf("You give them refuge, they are happy to be alive and dry!\n");
        AL_increaseCrew(player, Newcrew);
      }
    }
    else {
      printf("Send the scurvy dogs to Davey Jones' locker\n");
    }
  }
  return 1;
}
/*
float AL_weatherMod (void)
{
if (surroundings.weatherseverity > 75) {
return 0.5;
}
else if (surroundings.weatherseverity > 50) {
return 0.25;
}
else if (surroundings.weatherseverity > 25) {
return 0.1;
}
return 0;
}
*/
