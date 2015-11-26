#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "encounter.h"

#define TOTALENCOUNTERS 4
#define COMPASSPOINTS 8

int readfile(Encounter* list);
void read_in_string(char s[],FILE *fp);
int generate_environment(Environment* surroundings);
void copyencounter(Encounter* remote, Encounter* local);

int readfile(Encounter* list){
  int i;
  FILE *fp;
  fp = fopen("encounters.txt","r");
  if(fp == NULL){
    printf("ERROR: encounters.txt not found\n");
    exit(1);
  }
  for(i=0;i<TOTALENCOUNTERS;i++){
    fscanf(fp,"%d\n",&list[i].ID);
    read_in_string(list[i].name,fp);
    read_in_string(list[i].description,fp);
    read_in_string(list[i].pronoun,fp);
    read_in_string(list[i].weapontype,fp);
    fscanf(fp,"%d\n%d\n%d\n%d\n\n",&list[i].weaponnumber,&list[i].weapondamage,&list[i].health,&list[i].speed);
    if((list[i].weaponnumber == 1) && (list[i].weapontype[strlen(list[i].weapontype)-1] == 's')){
      list[i].weapontype[strlen(list[i].weapontype)-1]='\0';
    }
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

/* Below: Create small functions to send information from the struct to other modules, etc */

/* this needs to take in a encounter pointer and fill it */
void AL_getEncounter(Encounter *e){
  int random_encounter,random_direction;
  Encounter* list;
  Environment* surroundings;
  list = (Encounter*)malloc(sizeof(Encounter)*TOTALENCOUNTERS);
  surroundings = (Environment*)malloc(sizeof(Environment)*COMPASSPOINTS);
  readfile(list);
  generate_environment(surroundings);
  random_encounter = rand()%TOTALENCOUNTERS;
  random_direction = rand()%COMPASSPOINTS;
  list[random_encounter].locale = surroundings[random_direction];
  copyencounter(e,&list[random_encounter]);
  free(list);
  free(surroundings);
}

void copyencounter(Encounter* remote, Encounter* local){
  remote->ID = local->ID;
  strcpy(remote->name,local->name);
  strcpy(remote->description,local->description);
  strcpy(remote->pronoun,local->pronoun);
  strcpy(remote->weapontype,local->weapontype);
  remote->weaponnumber = local->weaponnumber;
  remote->weapondamage = local->weapondamage;
  remote->health = local->health;
  remote->speed = local->speed;
  strcpy(remote->locale.direction,local->locale.direction);
  strcpy(remote->locale.weatherdescription,local->locale.weatherdescription);
  remote->locale.weatherseverity = local->locale.weatherseverity;
}
