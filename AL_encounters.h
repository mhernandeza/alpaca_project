# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>
# include <ctype.h>
# include <SDL2/SDL.h>
# include "AL_ttf_fonts.h"

#define INFOTEXT 100
#define LONGINFO 300

#ifndef AL_ENCOUNTER_H
#define AL_ENCOUNTER_H

struct environment{
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
  char longdescription[LONGINFO];
  Environment locale;
};

typedef struct encounter Encounter;

void AL_getEncounter(Encounter *e);

#endif
