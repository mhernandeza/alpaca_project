# include "AL_driver.h"

int main (void){
  User player;
  Encounter test;
  AL_initializePlayer(&player);
  AL_presentStats(&player);
  do{
    AL_getEncounter(&test);
    AL_playCombat(&player, &test);
  }while(AL_getHealth(&player));
  return 0;
}
