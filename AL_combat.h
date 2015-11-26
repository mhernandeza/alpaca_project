# include "AL_player.h"
#define BOOL int
#define TRUE 1
#define FALSE 0
#define TURNTIME 750
int tick (void);
int retreat_condition (void);
int AL_damageHandle (int WeaponNum, int weapondamage);
int AL_reloadCannons (int Weapon_Number);
int AL_shoot_cannons (int Player_charge);
int AL_playCombat(User *player, Encounter *player2);
