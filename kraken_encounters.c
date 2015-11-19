#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INFOTEXT 100
#define TOTALENCOUNTERS 4
#define COMPASSPOINTS 8

struct encounter{
  char name[INFOTEXT]; /* eg: Queen Anne's Revenge */
  char description[INFOTEXT]; /* eg: a frigate with black sails */
  char weapontype[INFOTEXT];
  int weaponnumber;
  int weapondamage;
  int health;
  int speed;
  int weatherseverity;
};

typedef struct encounter Encounter;

struct environment{
  char direction[INFOTEXT];
  char weatherdescription[INFOTEXT];
  int weatherseverity;
};

typedef struct environment Environment;

int readfile(Encounter* list);
void read_in_string(char s[],FILE *fp);
int generate_environment(Environment* surroundings);

int main(void){
  int encounter1,encounter2,direction1,direction2;
  Encounter* list;
  Environment* surroundings;
  list = (Encounter*)malloc(sizeof(Encounter)*TOTALENCOUNTERS);
  surroundings = (Environment*)malloc(sizeof(Environment)*COMPASSPOINTS);
  srand(time(NULL));
  readfile(list);
  generate_environment(surroundings);
  encounter1 = rand()%TOTALENCOUNTERS;
  do{
    encounter2 = rand()%TOTALENCOUNTERS;
  }while(encounter1 == encounter2);
  direction1 = rand()%COMPASSPOINTS;
  do{
    direction2 = rand()%COMPASSPOINTS;
  }while(direction1 == direction2);
  printf("You see %s on the horizon to the %s. It is armed with %d %ss. The weather looks %s.\nLooking to the %s, you also see %s, armed with %d %ss. The weather looks %s.\n",
  list[encounter1].description,surroundings[direction1].direction,list[encounter1].weaponnumber,list[encounter1].weapontype,surroundings[direction1].weatherdescription,
  surroundings[direction2].direction,list[encounter2].description,list[encounter2].weaponnumber,list[encounter2].weapontype,surroundings[direction2].weatherdescription); /* stick direction in later */
  /* now send info to combat module etc */
  free(list);
  free(surroundings);
  return 0;
}

int readfile(Encounter* list){
  int i;
  FILE *fp;
  fp = fopen("encounters.txt","r");
  if(fp == NULL){
    printf("ERROR: encounters.txt not found\n");
    exit(1);
  }
  for(i=0;i<TOTALENCOUNTERS;i++){
    read_in_string(list[i].name,fp);
    read_in_string(list[i].description,fp);
    read_in_string(list[i].weapontype,fp);
    fscanf(fp,"%d\n%d\n%d\n%d\n\n",&list[i].weaponnumber,&list[i].weapondamage,&list[i].health,&list[i].speed);
  }
  fclose(fp);
  return 0;
}

void read_in_string(char s[],FILE *fp){
  char c;
  int i = 0;
  while((c = fgetc(fp)) != EOF && c != '\n'){
    s[i++] = c;
  }
  s[i] = '\0';
}

int generate_environment(Environment* surroundings){
  int i;
  strcpy(surroundings[0].direction,"north");
  strcpy(surroundings[1].direction,"northeast");
  strcpy(surroundings[2].direction,"east");
  strcpy(surroundings[3].direction,"southeast");
  strcpy(surroundings[4].direction,"south");
  strcpy(surroundings[5].direction,"southwest");
  strcpy(surroundings[6].direction,"west");
  strcpy(surroundings[7].direction,"northwest");
  for(i=0;i<COMPASSPOINTS;i++){
    surroundings[i].weatherseverity = rand()%100;
    if(surroundings[i].weatherseverity > 74){
      strcpy(surroundings[i].weatherdescription,"severe");
    }
    else if(surroundings[i].weatherseverity > 49){
      strcpy(surroundings[i].weatherdescription,"rough");
    }
    else if(surroundings[i].weatherseverity > 24){
      strcpy(surroundings[i].weatherdescription,"choppy");
    }
    else{
      strcpy(surroundings[i].weatherdescription,"calm");
    }
  }
  return 0;
}

/*
int shift_location(Environment* surroundings,int lastmove){

}

*/
