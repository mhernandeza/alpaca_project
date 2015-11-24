# include "combat.h"

int main (void){
  User player;
  Encounter test;
  AL_initializePlayer(&player);
  AL_presentStats(&player);
  AL_getEncounter(&test);
  AL_playCombat(&player, &test);
  return 0;
}
