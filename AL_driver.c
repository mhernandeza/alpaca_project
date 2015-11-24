# include "user_behaviour.h"

int main (void){
  User player;
  User *p;
  p=&player;
  AL_initializePlayer(p);
  AL_presentStats(p);
  p->health=AL_getHealth(p);
  printf("%d\n",p->health);
  return 0;
}
