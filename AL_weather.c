# include "AL_weather.h"

void AL_weatherCombat(Encounter *enemy, GameState *StateOfGame){
    static int initialised = 0;
    static int oldTime = 0;
    if (!initialised){
        
        oldTime = SDL_GetTicks();

    }
    
    
  int stormDuration= 20000 - player.speed*1000;
  int damage = enemy->locale.weatherseverity;
  int healthDamage = 0;
  int crewDamage=0;
  if(oldTime + stormDuration > SDL_GetTicks()){
    if(damage>25 && damage <50){
      healthDamage=rand()%5;
    }
    if(damage>49 && damage<75){
      healthDamage=rand()%10;
    }
    if(damage>74){
      healthDamage=rand()%20;
      crewDamage=damage/(player.luck*10);
    }
    AL_decreaseHealth(&player, healthDamage);
    AL_decreaseCrew(&player, crewDamage);
  }
  
}
