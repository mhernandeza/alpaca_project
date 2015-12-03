# include "AL_player.h"
# include <SDL2/SDL.h>

#define BOOL int
#define TRUE 1
#define FALSE 0
#define TURNTIME 800
int tick (void);
int retreat_condition (void);
int AL_damageHandle (int WeaponNum, int weapondamage, int defender, User *player1, Encounter *player2);
/*player = human player struct/Encounter player 2. 1 and 2 indicate damaged player*/
int AL_reloadCannons (int Weapon_Number);
int AL_shoot_cannons (int Player_charge);
int Critical_Damage  (User *player, Encounter *player2, int attacker);
int AL_playCombat(User *player, Encounter *player2);
int AL_collectLoot (User *player, Encounter *player2);
