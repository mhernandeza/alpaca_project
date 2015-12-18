# include "AL_weather.h"

void AL_weatherCombat(Encounter *enemy, GameState *StateOfGame){
  static int stormDuration=10;
  static int damage= enemy.Environment->weatherseverity;
  int healthDamage;
  int crewDamage=0;
  if(stormDuration>0){
    if(damage>25 && damage <50){
      healthDamage=rand()%5;
    }
    if(damage>49 && damage<75){
      healthDamage=rand()%10;
    }
    if(damage>74){
      healtDamage=rand()%20;
      crewDamage=damage/(player.luck*10);
    }
    AL_decreaseHealth(&player, healthDamage);
    AL_decreaseCrew(&player, crewDamage);
    stormDuration-=player.speed;
  }
  else{
    *StateOfGame=MAIN_MENU;
  }
}
