#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define BOOL int
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TURNTIME 750
int tick (void);
int shoot (int pcharge);
int winner (int playerhull, int  enemyhull, int enemycannon);
int reload (int cannons, int pcharge, char* player);
int retreat_test (int retreat, int Hull);
int Rules (void);
int retreat_condiition (void);
BOOL loadmedia (SDL_Surface **image);
BOOL init (SDL_Window **window, SDL_Surface **image);
void clear (void);
int damage (int charge, int health);
int Loot_drop (int enemyhull);
int HitMiss (void);
int critical (void);
int fire_handle (int player1, int playerfire);



struct player {
  int Hull;
  int weaponNumber;
  int WeaponDamage;
  char *weapontype;
  char *descriptor;
  char *name;
  int Speed;
  int Loot;
  int fire;
};

int main (void)
{
  SDL_Surface *windowsurface;
  SDL_Surface *image;
  SDL_Window *window = NULL;
  /*All of this needs to be included in the main database struct*/
  struct player player1; struct player player2;
  player1.Hull = 100; player1.weaponNumber = 20; player1.descriptor = "Your"; player1.Loot = 0, player1.WeaponDamage = 1;
  player2.Hull = 110; player2.weaponNumber = 22; player2.descriptor = "Enemy", player2.WeaponDamage = 1;
  int retreat = 0, retreat_counter = 0;
  /*the following stats need to be passed from the player struct and
  enemy databas*/
  int pcharge = 0, echarge = 0, i, j, playerfire = 0, enemyfire = 0;
  BOOL isRunning = TRUE;
  SDL_Event ev;
  init(&window, &windowsurface);
  loadmedia(&image);
  srand(time(NULL));
  while (isRunning){
    while (SDL_PollEvent(&ev) != 0){
      if (ev.type == SDL_QUIT){
        isRunning = FALSE;
      }
    }
    SDL_BlitSurface(image, NULL, windowsurface, NULL);
    SDL_UpdateWindowSurface(window);
    retreat = Rules();
    while ((player1.Hull > 0 && player2.Hull > 0 && retreat_counter < 3) ) {
      printf("\nEngaged in Combat\n");
      if (tick() == 1){
        player1.Hull = fire_handle (player1.Hull, playerfire);
        player2.Hull = fire_handle (player2.Hull, enemyfire);
      }
/*if after a critical hit a fire starts, every turn the fire burns for
the ship takes a point of damage per fire untill it is put out on the roll of
a 6. one role per fire*/
        if (retreat_test(retreat, player1.Hull) == 1){
          retreat_counter++;
          printf("%d turns till escape\n", 10 - retreat_counter);
        }
        pcharge = reload(player1.weaponNumber, pcharge, player1.descriptor);
        echarge = reload(player2.weaponNumber, echarge, player2.descriptor);
        if (retreat_counter > 0) {
          printf("Retreating!\n");
          if (shoot(echarge) == 1){
        }
        else {
          if (shoot(pcharge) == 1){
            pcharge -= 100;
            for (i = 0 ; i < player1.weaponNumber ; i++ ){
              if (HitMiss() == 1){
                player2.Hull = damage(player1.WeaponDamage, player2.Hull);
                printf("Enemy ship takes %d Damage\n", player1.weaponNumber);
                printf("Enemy ship currently at %d hull strength\n", player2.Hull);
              }
              if (HitMiss() == 2) {
                playerfire += 1;
                printf("\nYour ship is on fire!!\n");
              }
              if (HitMiss() == 3) {
                player2.weaponNumber -= 1;
              }
            }
          }
            echarge -= 100;
            for (j = 0 ; j < player2.weaponNumber ; j++){
              if (HitMiss()){
                player1.Hull = damage(player2.WeaponDamage, player1.Hull);
                printf("Your ship takes %d Damage\n", player2.weaponNumber);
                printf("Your ship currently at %d Hull strength\n", player1.Hull);
              }
            }
            if (HitMiss() == 2) {
              enemyfire += 1;
              printf("\nEnemy Ship on Fire!!\n");
            }
            if (HitMiss() == 3) {
              player1.weaponNumber -= 1;
            }
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
  }
  SDL_Quit();
  return 0;
}

int shoot (int pcharge)
{
  if (pcharge >= 100){
    int x;
    printf("Ready to Fire!\n");
    pcharge -= 100;
    x = rand() % 3;
    if (x == 0 ){
      printf("\n               BANG!\n\n");
    }
    if (x == 1) {
      printf("\n               WOOSH!\n\n");
    }
    if (x == 2) {
      printf("                 KERPOW!\n\n");
    }
    return 1;
  }
  return 0;
}

int tick (void)
{
  SDL_Delay(TURNTIME);
  return 1;
}

int reload (int cannons, int pcharge, char* player)
{
  pcharge = cannons + pcharge;
  printf("%s cannons loading, currently at %d\n", player,  pcharge);
  return pcharge;
}

int winner (int playerhull, int  enemyhull, int enemycannon)
{
  if (playerhull > enemyhull) {
    printf("You sunk the enemy Ship!!\nCollect your spoils\n");
    return Loot_drop(enemycannon);
  }
  else {
    printf("Your ship has been sunk\n Captain goes down with the ship\n");
  }
  return 0;
}


int Rules (void)
{
  int retreat;
  printf("At what health would you retreat on?\n");
  if (scanf("%d", &retreat) == 1) {
    clear();
    return retreat;
  }
  return 0;
}

int retreat_test (int retreat, int Hull)
{
  if (retreat > Hull){
    printf("retreating from combat!\n");
    return 1;
  }
  return 0;
}

int retreat_condiition (void)
{
  printf("you managed to escape with your life!\n");
  return 0;
}

BOOL init (SDL_Window **window, SDL_Surface **surface)
{
  BOOL success = TRUE;

  if (SDL_Init(SDL_INIT_VIDEO)< 0){
    printf("Failed to initialse window. Error: %s\n", SDL_GetError());
    success = FALSE;
  }
  else {
    *window = SDL_CreateWindow("ALKraken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  }
  *surface = SDL_GetWindowSurface (*window);
  return success;
}


BOOL loadmedia (SDL_Surface **image)
{
  *image = SDL_LoadBMP ("images/test.bmp");
  return TRUE;
}

void clear (void)
{
  while ( getchar() != '\n' );
}

int damage (int cannon, int health)
{
  health -= cannon;
  return health;
}

int Loot_drop (int enemycannon)
{
  return rand()%enemycannon;
}

int HitMiss (void)
{
  int x;
  x = rand()%6;
  if (x > 1 && x < 5) {
    printf("Hit %d", x);
    return 1;
  }
  if (x == 5) {
    printf("\nIts Super Effective!\n");
    return critical();
  }
  else {
    printf("Miss %d", x);
    return 0;
  }
  return 0;
}

/*after a cannon shot, there is potential for critical damage.
in the event of a critical 1 of three events can take place.
1 - double damage, 2 - dammage an enemy cannon, 3, start a fire*/
int critical (void)
{
  int x;
  x = rand()%3;
  if (x == 0) {
    return 1;
  }
  if (x == 1) {
    return 2;
  }
  if (x == 2 ) {
    return 3;
  }
  return 0;
}

int fire_handle (int player1, int playerfire)
{
  int k = 0;
  if (playerfire > 0) {
    player1 -= 1;
    for (k = 0 ; k < playerfire ; k++){
      if (rand()%6 == 5) {
      playerfire -= 1;
      }
    }
  }
  return player1;
}