#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

struct player {
  int Hull;
  int weaponNumber;
  int WeaponDamage;
  char *weapontype;
  char *descriptor;
  char *pronoun;
  char *name;
  int Speed;
  int Loot;
  int fire;
};

int main (void)
{
  struct player player1; struct player player2;
  int retreat = 0, retreat_counter = 0, pcharge = 0, echarge = 0, playerfire = 0, enemyfire = 0;
  srand(time(NULL));
  retreat = Rules();
  player1.Hull = 100; player1.weaponNumber = 20; player1.descriptor = "Your"; player1.Loot = 0, player1.WeaponDamage = 1;
  player2.Hull = 110; player2.weaponNumber = 22; player2.descriptor = "Enemy", player2.WeaponDamage = 1;
  while ((player1.Hull > 0 && player2.Hull > 0 && retreat_counter < 3) ) {
    printf("\nEngaged in Combat\n");
    if (tick() == 1){
      fire_handle(player1.Hull, playerfire);
      fire_handle(player2.Hull, enemyfire);
      if (retreat_test(retreat, player1.Hull) == 1){
        retreat_counter++;
        printf("%d turns till escape\n", 3 - retreat_counter);
      }
      pcharge = reload(player1.weaponNumber, pcharge, player1.descriptor);
      echarge = reload(player2.weaponNumber, echarge, player2.descriptor);
      if (retreat_counter > 0) {
        printf("Retreating!\n");
      }
      else {
        if (shoot(pcharge) == 1){
          pcharge -= 100;
          enemyfire = damage_handle(player1, player2, enemyfire);
        }
        if (shoot(echarge) == 1){
          echarge -= 100;
          playerfire = damage_handle(player1, player2, playerfire);
        }
      }
    }
  }
  if (player2.Hull <= 0 || player1.Hull <= 0) {
    player1.Loot = player1.Loot + winner(player1.Hull, player2.Hull, player2.weaponNumber);
    printf("You have %d Gold coins\n", player1.Loot);
    return 0;
  }
  if (retreat_counter == 10){
    retreat_condiition();
    return 0;
  }
return 0;
}
