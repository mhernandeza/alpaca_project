# include "AL_driver.h"

int main (void){
  User player;
  Encounter test;
  int result;
  srand(time(NULL));
  AL_initializePlayer(&player);
  AL_presentStats(&player);
  /*do{*/
    do{
      AL_getEncounter(&test);
      AL_programReaction(&player, &test);
    }while(player.retreatHealth==100);
    result=AL_playCombat(&player, &test);
    if(result){
      printf("\n");
      printf("Well done keep playing!\n");
      printf("\n");
    }
    else{
      printf("\n");
      printf("Oh no!\n");
      printf("\n");
    }
  /*}while(AL_getHealth(&player));*/
  printf("Game over!\n");
  return 0;
}
