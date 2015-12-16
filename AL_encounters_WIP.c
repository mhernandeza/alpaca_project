#include "AL_encounters.h"

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
    fscanf(fp,"%d\n%d\n%d\n%d\n%d\n\n",&list[i].weaponnumber,&list[i].weapondamage,&list[i].crew,&list[i].health,&list[i].speed);
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

/* is sent an 8 cell Environment array signifying the player's surrounding cells, and fills them with random weather */
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
  int choicenumber,random_encounter1,random_encounter2,random_direction1,random_direction2,chosen;
  char c,tempstring1[INFOTEXT],tempstring2[INFOTEXT];
  Encounter* list;
  Environment* surroundings;
  Encounter current;
  list = (Encounter*)malloc(sizeof(Encounter)*TOTALENCOUNTERS);
  surroundings = (Environment*)malloc(sizeof(Environment)*COMPASSPOINTS);
  readfile(list);
  generate_environment(surroundings);
  random_encounter1 = rand()%TOTALENCOUNTERS;
  do{
    random_encounter2 = rand()%TOTALENCOUNTERS;
  }while(random_encounter2 == random_encounter1);
  random_direction1 = rand()%COMPASSPOINTS;
  do{
    random_direction2 = rand()%COMPASSPOINTS;
  }while(random_direction2 == random_direction1);
  list[random_encounter1].locale = surroundings[random_direction1];
  list[random_encounter2].locale = surroundings[random_direction2];
  current = list[random_encounter1];
  for(choicenumber = 1;choicenumber<3;choicenumber++){
    printf("\nEncounter %d: %s!\nYou see %s on the horizon to the %s; %s is armed with %d %s.\nThe weather looks %s.\n\n",
    choicenumber,current.name,current.description,current.locale.direction,current.pronoun,current.weaponnumber,current.weapontype,current.locale.weatherdescription);
    current = list[random_encounter2];
  }
  strcpy(tempstring1,list[random_encounter1].locale.direction);
  strcpy(tempstring2,list[random_encounter2].locale.direction);
  toupper(tempstring1[0]);
  toupper(tempstring2[0]);
  printf("In which direction do you choose to travel?\n1: %s\n2: %s\n\n",tempstring1,tempstring2);
  chosen = -1;
  do{
    if((c = getchar()) == '1'){
      chosen = random_encounter1;
    }
    else if(c == '2'){
      chosen = random_encounter2;
    }
    else{
      printf("Please enter 1 or 2:\n");
    }
  }while(chosen == -1);
  copyencounter(e,&list[chosen]);
  free(list);
  free(surroundings);
}


void AL_chooseDirection(STUFF){

}

void AL_getEncounter(Encounter* e){
  Encounter* list;
  Encounter current;
  list = (Encounter*)malloc(sizeof(Encounter)*TOTALENCOUNTERS);
  readfile(list);

}

/* this function will fill the world with the initial state: sea, land and enemies to fight */
void generateWorld(Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2]){
  int i,y,x,landcells,landseedX,landseedY;
  for(y=0;y<WORLDSIZE+2;y++){
    for(x=0;x<WORLDSIZE+2;x++){
      wipe_encounter(&worldMap[y][x]);
    }
  }
  // CREATION OF LAND. 10-20% of world to be land cells
  landcells = (WORLDSIZE*WORLDSIZE)/((rand()%6)+5);
  landseedX = (rand()%WORLDSIZE)+1;
  landseedY = (rand()%WORLDSIZE)+1;
  worldMap[landseedY][landseedX].locale.land = 1;
  for(i=1;i<landcells;i++){

  }
  player.locationX = STUFF;
  player.locationY = STUFF:
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

void updateWorld(Encounter worldMap[WORLDSIZE+2][WORLDSIZE+2]){

}


void copyencounter(Encounter* remote, Encounter* local){
  remote->ID = local->ID;
  strcpy(remote->name,local->name);
  strcpy(remote->description,local->description);
  strcpy(remote->pronoun,local->pronoun);
  strcpy(remote->weapontype,local->weapontype);
  remote->weaponnumber = local->weaponnumber;
  remote->weapondamage = local->weapondamage;
  remote->crew = local->crew;
  remote->health = local->health;
  remote->speed = local->speed;
  remote->locale.land = local->locale.land;
  strcpy(remote->locale.direction,local->locale.direction);
  strcpy(remote->locale.weatherdescription,local->locale.weatherdescription);
  remote->locale.weatherseverity = local->locale.weatherseverity;
  remote->oldTime = SDL_GetTicks();
}