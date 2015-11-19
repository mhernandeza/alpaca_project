# include "user_behaviour.h"

int main (void){
  User player1;
  Retreat p1behaviour;
  User *p;
  Retreat *p1;
  p=&player1;
  p1=&p1behaviour;
  srand(time(NULL));
  AL_initializePlayer(p);
  AL_programReaction(p1, p);/*Depends on display*/
  AL_presentStats(p);/*Depends on display*/
  return 0;
}

void AL_initializePlayer(User *player1){
  char w[WORDL];
  printf("Input your name: ");
  scanf("%s",w);
  strcpy(player1->player_name, w);
  strcpy(player1->ship_name,"Black Pearl");
  strcpy(player1->weapontype,"Cannons");
  player1->weaponnumber=(rand()%30)+20;/*From 20 to 50*/
  player1->weapondamage=1;
  player1->health=100;
  player1->speed=rand()%10;
  player1->luck=rand()%10;
  player1->gold=1000;
}

void AL_presentStats(User *player1){
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Welcome Capitain %s on board the %s, armed with %d %s.\n",
        player1->player_name, player1->ship_name, player1->weaponnumber,
        player1->weapontype);
  if(player1->luck>5){
    printf("We're feeling lucky.\n");
  }
  printf("Starting with a hull of %d per cent and %d coins lets sail to the horizon!\n",
        player1->health, player1->gold);
   printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void AL_programReaction(Retreat *p1, User *player1){
  int x;
  printf("Initially you have a hull of %d per cent!\n", player1->health);
  printf("Would you like to retreat based on your hull condition?\n"
         "1.Yes\n"
         "2.No\n");
  scanf("%d", &x);
  if(x==1){
    p1->retreat_health=AL_setupRetreathealth(rand()%2);
  }
  else{
    printf("Today is a good day to die Capitain!\n");
    p1->retreat_health=-1;/*Flag for it not to be considered*/
  }
  printf("Your current ship is well equipped with %d cannons!\n", player1->weaponnumber);
  printf("Would you like to retreat if you have fewer cannons than the opponent ship?\n"
         "1.Yes\n"
         "2.No\n");
  scanf("%d", &x);
  if(x==1){
    p1->retreat_weapons=1;/*Flag, comparisson between number of cannons should be made*/
    printf("if(CANNONS<Enemy_Cannons){\n  retreat();\n}\n");
    printf("We will flee IF OUR CANNONS are FEWER THAN the ENEMY CANNONS.\n");
  }
  else{
    p1->retreat_weapons=0;/*Flag, doesn't matter*/
    printf("We shall fear no enemy Capitain!\n");
  }
}

int AL_setupRetreathealth(int x){
  int health;
  switch (x){
    case 0:
    do{
      printf("Flee if our health is not more than: ");
      scanf("%d", &health);
      if(health>=100){
        printf("Invalid condition, try again.\n");
      }
    }while(health>=100);
    if(health==0){
      printf("We shall not back down Capitain!\n");
      health=-1;
    }
    else{
      printf("if(!(HEALTH>%d)){\n  retreat();\n}\n",health);
      printf("We'll retreat IF our health is NOT MORE THAN %d.\n",health);
    }
    return health;
    break;
    case 1:
    do{
      printf("Flee if our health is fewer than: ");
      scanf("%d", &health);
      if(health<0){
        printf("Invalid condition, try again.\n");
      }
    }while(health<0);
    if(health==0){
      printf("We shall not back down Capitain!\n");
      health=-1;
    }
    else{
      printf("if(HEALTH<%d){\n  retreat();\n}\n",health);
      printf("We'll retreat IF our health is FEWER THAN %d.\n",health);
    }
    return health;
    break;/*
    case 2:
      printf("Would you like to flee if the enemies health is more than ours?\n"
            "1.Yes\n"
            "2.No\n");
      scanf("%d", health);
      if(health==1){
        health=-1;
        printf("if(ENEMY_HEALTH<OUR_HEALTH){\n  retreat();\n}\n");
        printf("We'll retreat IF the ENEMY'S HEALTH is FEWER THAN OURS.\n");
      }
      if(health==2){
        health=-2;
       printf("We'll keep fighting no matter what!\n");
      }
    return health;
    break;*/
    default:
      health=0;
      printf("ERROR!!!\n");
      exit(1);
  }
}
