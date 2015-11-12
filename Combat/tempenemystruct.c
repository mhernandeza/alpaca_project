#include <stdio.h>

struct player {
  int Hull;
  int cannons;
  char descriptor[100];
  char name[100];
  int Loot;
};

typedef struct player Ship;

struct *database (int ID)
{
  struct Ship player1, enemy1, enemy2;

  player1.Hull = 100;
  player1.cannons = 35 ;
  player1.descriptor = "Your";
  player1.name = "The Alpaca";
  player1.Loot = 0;

  Enemy1.Hull = 80;
  Enemy1.cannons = 30;
  Enemy1.descriptor = "Enemy";
  Enemy1.name = "The Black Sail";

  Enemy2.Hull = 50;
  Enemy2.cannons = 15;
  Enemy2.descriptor = "Civilian";
  Enemy2.name = "The Unlucky Trader";

  if (ID = 1){
    return &player1;
  }
  if (ID = 2) {
    return &enemy1;
  }
  if (ID = 3) {
    return &enemy2;
  }
}
