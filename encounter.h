#define INFOTEXT 100

struct environment{
  char direction[INFOTEXT];
  char weatherdescription[INFOTEXT];
  int weatherseverity;
};

typedef struct environment Environment;

struct encounter{
  char name[INFOTEXT]; /* eg: Queen Anne's Revenge */
  char description[INFOTEXT]; /* eg: a frigate with black sails */
  char pronoun[INFOTEXT]; /* eg: it, she, he, they */
  char weapontype[INFOTEXT];
  int weaponnumber;
  int weapondamage;
  int health;
  int speed;
  Environment locale;
};

typedef struct encounter Encounter;

void AL_getEncounter(Encounter *e);
