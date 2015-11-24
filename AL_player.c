# include "user_behaviour.h"
int AL_setupRetreathealth(int x);

void AL_presentStats(User *player){
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Welcome Capitain %s on board the %s, armed with %d %s.\n",
        player->player_name, player->ship_name, player->weaponnumber,
        player->weapontype);
  if(player->luck>5){
    printf("We're feeling lucky.\n");
  }
  printf("Starting with a hull of %d per cent and %d coins lets sail to the horizon!\n",
        player->health, player->gold);
   printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void AL_initializePlayer(User *player){
  char w[WORDL];
  printf("Input your name: ");
  scanf("%s",w);
  strcpy(player->playerName, w);
  strcpy(player->shipName,"Black Pearl");
  strcpy(player->weaponType,"Cannons");
  player->weaponNumber=(rand()%30)+20;
  player->weaponDamage=1;
  player->health=100;
  player->speed=1+(rand()%10);
  player->luck=1+(rand()%10);
  player->gold=1000;
}

void AL_programReaction(User *player){
  int x;
  printf("Initially you have a hull of %d per cent!\n", player->health);
  printf("Would you like to retreat based on your hull condition?\n"
         "1.Yes\n"
         "2.No\n");
  scanf("%d", &x);
  if(x==1){
    player->retreatHealth=AL_setupRetreathealth(rand()%2);
  }
  else{
    printf("Today is a good day to die Capitain!\n");
    p1->retreatHealth=-1;/*Flag for it not to be considered*/
  }
  printf("Your current ship is well equipped with %d cannons!\n", player1->weaponnumber);
  printf("Would you like to retreat if you have fewer cannons than the opponent ship?\n"
         "1.Yes\n"
         "2.No\n");
  scanf("%d", &x);
  if(x==1){
    p1->retreatWeapons=1;/*Flag, comparisson between number of cannons should be made*/
    printf("if(CANNONS<Enemy_Cannons){\n  retreat();\n}\n");
    printf("We will flee IF OUR CANNONS are FEWER THAN the ENEMY CANNONS.\n");
  }
  else{
    p1->retreatWeapons=0;/*Flag, doesn't matter*/
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
        printf("Your maximum health is 100, try again.\n");
      }
    }while(health>=100);
    if(health==0){
      printf("We shall not back down Capitain!\n");
      health=-1;/*Flag condition for never retreating*/
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
        printf("Your minimum health is 0, try again.\n");
      }
    }while(health<0);
    if(health==0){
      printf("We shall not back down Capitain!\n");
      health=-1;/*Flag condition for never retreating*/
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

int AL_getHealth(User *player){
/*Returns the user's current health*/
  return player->health;
}
int AL_getWeaponNumber(User *player){
/*Returns the user ammount of weapons*/
  return player->weaponNumber;
}

int AL_getWeaponDamage(User *player){
/*Returns the user's weapon damage*/
  return player->weaponDamage;
}

int AL_getGold(User *player){
/*Returns the user's current gold*/
  return player->gold;
}

int AL_decreaseHealth(User *player, int amount){
/*Modifies the user's current health by a fixed amount, returns the resulting health*/
  player->health-=amount;
  if(player->health<0){
    player->health=0;
  }
  return player->health;
}

int AL_increaseGold(User *player, int amount){
/*Modifies the user's current gold by a fixed amount, returns the resulting gold*/
  player->gold+=amount;
  return player->gold;
}

int AL_getRetreatHealth(User *player){
/*Returns retreat health programmed by the user*/
  return player->retreatHealth;
}
int AL_getRetreatWeapons(User *player){
/*Returns 1 if the user decided to retreat when having less cannons than the enemy, returns 0 otherwise*/
  return player->retreatWeapons;
}
