#include <stdio.h>

struct player {
  int Hull;
  int cannons;
  char* descriptor;
  char* name;
};

typedef struct player Ship;

int main (void)
{
  Ship player1;
  Ship Enemy1;
  Ship Enemy2;

  player1.Hull = 100;
  player1.cannons = 35 ;
  player1.descriptor = "Your";
  player1.name = "The Alpaca";

  Enemy1.Hull = 80;
  Enemy1.cannons = 30;
  Enemy1.descriptor = "Enemy";
  Enemy1.name = "The Black Sail";

  Enemy2.Hull = 50;
  Enemy2.cannons = 15;
  Enemy2.descriptor = "Civilian";
  Enemy2.name = "The Unlucky Trader";


}
