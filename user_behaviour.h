# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>
# define WORDL 20

struct user_ship{
  char player_name[WORDL];
  char ship_name[WORDL];
  char weapontype[WORDL];
  int weaponnumber;
  int weapondamage;
  int health;
  int speed;
  int luck;
  int gold;
};
typedef struct user_ship User;

struct retreat{
  int retreat_health;
  int retreat_weapons;
};
typedef struct retreat Retreat;

void AL_presentStats(User *player1);
void AL_initializePlayer(User *player1);
void AL_programReaction(Retreat *p1, User *player1);
int AL_setupRetreathealth(int x);
