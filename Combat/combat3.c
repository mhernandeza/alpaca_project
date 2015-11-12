#include <stdio.h>
#include <SDL2/SDL.h>

#define BOOL int
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int tick (void);
int shoot (int pcharge);
int winner (int playerh, int  enemyh);
int reload (int Playercan, int pcharge, char* player);
int retreat_test (int retreat, int playerH);
int Rules (void);
int retreat_condiition (void);
BOOL loadmedia (SDL_Surface **image);
BOOL init (SDL_Window **window, SDL_Surface **image);
void clear (void);
int damage (int charge, int health);

struct player {
  int playerH = 100;
  int Playercan = 40;
}

struct enemy {
  int EnemyH = 80;
  int Playercan = 30
}

int main (void)
{
  SDL_Surface *windowsurface;
  SDL_Surface *image;
  SDL_Window *window = NULL;
  /*All of this needs to be included in the main database struct*/
  char* player1 = "Your";
  char* player2 = "Enemy";
  int retreat, retreat_counter = 0;
  /*the following stats need to be passed from the player struct and
  enemy databas*/
  int Playercan = 40,  enemyCan = 25, playerH = 100, enemyH = 90;
  int pcharge = 0, echarge = 0;
  BOOL isRunning = TRUE;
  SDL_Event ev;
  init(&window, &windowsurface);
  loadmedia(&image);
  while (isRunning){
    while (SDL_PollEvent(&ev) != 0){
      if (ev.type == SDL_QUIT){
        isRunning = FALSE;
      }
    }
    SDL_BlitSurface(image, NULL, windowsurface, NULL);
    SDL_UpdateWindowSurface(window);
    retreat = Rules();
    while ((playerH > 0 && enemyH > 0 && retreat_counter < 3) ) {
      printf("Engaging in Combat press 1 and Enter to continue\n\n");
      if (tick() == 1){
        if (retreat_test(retreat, playerH) == 1){
          retreat_counter++;
          printf("%d turns till escape\n", 3 - retreat_counter);
        }
        pcharge = reload(Playercan, pcharge, player1);
        echarge = reload(enemyCan, echarge, player2);
        if (retreat_counter > 0) {
          printf("Retreating!\n");
        }
        else {
          if (shoot(pcharge) == 1){
            enemyH = damage(Playercan, enemyH);
            pcharge -= 100;
            printf("enemy ship takes %d Damage\n", Playercan);
            printf("Currently at %d Hull strength\n", enemyH);
          }
          if (shoot(echarge) == 1){
            playerH = damage(enemyCan, playerH);
            echarge -= 100;
            printf("Your ship takes %d Damage\n", enemyCan);
            printf("Currently at %d Hull strength\n", playerH);
          }
        }
      }
    }
    if (enemyH <= 0 || playerH <= 0) {
      winner(playerH, enemyH);
    }
    if (retreat_counter == 3){
      retreat_condiition();
    }
  }

  SDL_Quit();
  return 0;
}

int shoot (int pcharge)
{
  if (pcharge >= 100){
    printf("Ready to Fire!\n");
    pcharge -= 100;
    printf("BANG!\n");
    return 1;
  }
  return 0;
}

int tick (void)
{
  int i;
  scanf("%d", &i);
  if ( i == 1){
    clear();
    return 1;
  }
  return 1;
}

int reload (int Playercan, int pcharge, char* player)
{
  pcharge = Playercan + pcharge;
  printf("%s cannons loading, currently at %d\n", player,  pcharge);
  return pcharge;
}

int winner (int playerh, int  enemyh)
{
  if (playerh > enemyh) {
    printf("You sunk the enemy Ship!!\nCollect your spoils");
  }
  else {
    printf("Your ship has been sunk\n Captain goes down with the ship");
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

int retreat_test (int retreat, int playerH)
{
  if (retreat > playerH){
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
