# include "AL_combat.h"

int AL_critical_Damage  (User *player, Encounter *player2, int attacker);

int AL_playCombat(User *player, Encounter *player2, GameState *StateOfGame)
{
  static int Player_charge = 0, Enemy_charge = 0, retreat_Counter = 0, newloot = 0, healing = 0;

    static int oldTime = 0;
    if (oldTime == 0){
        oldTime = SDL_GetTicks();
    }
    if((oldTime + 5000) > SDL_GetTicks()){
        return 1;
    }

    if (tickPlayer() == 1){
        //AL_surrender (player, player2, StateOfGame);
        AL_GhostShip (player, player2, StateOfGame);
      if ((AL_getRetreatHealth(player) > AL_getHealth(player) )) {
      retreat_Counter++;
      }
    Player_charge += ((float)AL_getCrew(player)/(float)AL_getWeaponNumber(player))*100;

    if (retreat_Counter > 0) {
    }
      if ((player->isFiring = (AL_shoot_cannons(Player_charge) == 1))){
        Player_charge = 0;
      }

    if (player2->health <= 0){
      newloot = rand()%(player2->weaponnumber);
      healing = ((100-AL_getHealth(player))/10);
        AL_increaseHealth(player, healing);
      AL_increaseGold(player, newloot);
      oldTime = 0;
      *StateOfGame = WORLD_STATE;
      return 1;
    }
    if(AL_getHealth(player) <= 0){
        oldTime = 0;
        *StateOfGame = GAME_OVER;
      return 0;
    }
    if (retreat_Counter==3){
      retreat_condition();
      return 1;
    }
  }
    if (tickEnemy(player2) && player2->weaponnumber != 0 ){
        Enemy_charge += ((float)player2->crew/(float)player2->weaponnumber)*100;
        player2->isFiring = AL_shoot_cannons(Enemy_charge);
        if ((player2->isFiring = (AL_shoot_cannons(Enemy_charge) == 1))){
            Enemy_charge = 0;
        }
    }

return 0;
}

int AL_shoot_cannons (int Player_charge)
{
  int x;
  if (Player_charge >= 100){
    x = rand() % 3;
    if (x == 0 ){
    }
    if (x == 1) {
    }
    if (x == 2) {
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
        AL_decreaseHealth(player1 ,AL_critical_Damage(player1, player2, 2));
      }
      if (defender == 2) {

        player2->health -= AL_critical_Damage(player1, player2, 1);
      }
    }
  }

  return (hits*weapondamage);
}

int retreat_condition (void)
{
  return 0;
}

int tickPlayer (void)
{
    if(player.oldTime + TURNTIME > SDL_GetTicks()){
        return 0;
    }
    player.oldTime = SDL_GetTicks();
    return 1;
}
int tickEnemy(Encounter *encounter){
    if(encounter->oldTime + ENEMY_TURN_TIME > SDL_GetTicks()){

        return 0;
    }
    encounter->oldTime = SDL_GetTicks();
    return 1;
}

int AL_critical_Damage  (User *player, Encounter *player2, int attacker)
{
  int y;
  y = rand() % 6;
  if (player2->ID == 0) {
    //the Kracken exception to critical hits
    player2->health -= 5;
  } else {

   if (y <= 1 ){
    if (attacker == 1) {
      player2->health -= 1;
    }
    else {
      AL_decreaseHealth(player, 1);
    }
  }
  if (y == 2 || y == 3 ) {
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
  if (y == 4 || y == 5) {
    if (attacker == 1) {
      player2->crew -= 1;
    }
    else {
      AL_decreaseCrew(player, 1);
    }
  }
  }return 0;
}

int AL_collectLoot(User *player, Encounter *player2){
    int newloot, healing, newcrew;
    newloot = 100 + rand()%(player2->weaponnumber + 1);
    healing = ((100 - AL_getHealth(player))/10);
    newcrew = rand()%(player2->crew/10);
    AL_increaseHealth(player, healing);
    AL_increaseCrew(player, newcrew);
    printf("%d\n", newloot);
    AL_increaseGold(player, newloot);
    if(newcrew > 0){

    }
    return 1;
}


int AL_surrender (User *player, Encounter *player2, GameState *StateOfGame)
{
  //int surrender;
  if (player2->weaponnumber == 0 ) {
    AL_collectLoot(player, player2);
    return 1;
    }
  return 0;
}

int AL_GhostShip (User *player, Encounter *player2, GameState *StateOfGame)
{
  if (player2->crew <= 0 ){
    AL_collectLoot(player, player2);
    return 1;
  }
  return 0;
}
