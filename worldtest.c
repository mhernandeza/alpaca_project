# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>
# include <ctype.h>

#define INFOTEXT 100
#define WORLDSIZE 5

struct environment{
  int land;
  char direction[INFOTEXT];
  char weatherdescription[INFOTEXT];
  int weatherseverity;
};

typedef struct environment Environment;

struct encounter{
  int ID;
  char name[INFOTEXT]; /* eg: Queen Anne's Revenge */
  char description[INFOTEXT]; /* eg: a frigate with black sails */
  char pronoun[INFOTEXT]; /* eg: it, she, he, they */
  char weapontype[INFOTEXT];
  int weaponnumber;
  int weapondamage;
  int crew;
  int health;
  int speed;
  int oldTime;
  int isFiring;
  Environment locale;
};

typedef struct encounter Encounter;

void generateWorld(Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2]);
void printWorld(Encounter worldMap[][WORLDSIZE+2]);
void wipe_encounter(Encounter *e);

int main(void){
  Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2];
  srand(time(NULL));
  generateWorld(worldMap);
  printWorld(worldMap);
  return 0;
}

/* this function will fill the world with the initial state: sea, land and enemies to fight */
void generateWorld(Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2]){
  int i,y,x,landcells,landseedX,landseedY;
  for(y=0;y<WORLDSIZE+2;y++){
    for(x=0;x<WORLDSIZE+2;x++){
      wipe_encounter(&worldMap[y][x]);
    }
  }
  /* CREATION OF LAND. 10-20% of world to be land cells */
  landcells = (WORLDSIZE*WORLDSIZE)/((rand()%6)+5);
  landseedX = (rand()%WORLDSIZE)+1;
  landseedY = (rand()%WORLDSIZE)+1;
  worldMap[landseedY][landseedX].locale.land = 1;
  for(i=1;i<=landcells;){
    for(y=1;y<WORLDSIZE+2;y++){
      for(x=1;x<WORLDSIZE+2;x++){
        /* 20% chance of sea becoming land */
        if((((rand()%10)+1) > 8) && (worldMap[y][x].locale.land == 0){
          worldMap[y][x].locale.land = 1;
          i++;
        }
        else if(worldMap[y][x].locale.land == 1){

        }
      }
    }
  }
/*  player.locationX = STUFF;
  player.locationY = STUFF:*/
}

void printWorld(Encounter worldMap[][WORLDSIZE+2]){
  int y,x;
  for(y=0;y<=WORLDSIZE+2;y++){
    for(x=0;x<=WORLDSIZE+2;x++){
      if((y == 0) || (y == (WORLDSIZE+2))){
        printf("-");
      }
      else if((x == 0) || (x == (WORLDSIZE+2))){
        printf("|");
      }
      else if(worldMap[y][x].locale.land == 1){
        printf("#");
      }
      else{
        printf(" ");
      }
    }
    printf("\n");
  }
}

void wipe_encounter(Encounter *e){
  e->ID = -1;
  e->name[0] = 0;
  e->description[0] = 0;
  e->pronoun[0] = 0;
  e->weapontype[0] = 0;
  e->weaponnumber = 0;
  e->weapondamage = 0;
  e->crew = 0;
  e->health = 0;
  e->speed = 0;
  e->oldTime = 0;
  e->isFiring = 0;
  e->locale.land = 0;
  e->locale.direction[0] = 0;
  e->locale.weatherdescription[0] = 0;
  e->locale.weatherseverity = 0;
}
