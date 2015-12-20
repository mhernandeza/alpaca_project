#include "state_data.h"
#include "AL_player.h"
#include <SDL2/SDL.h>


#define TURNTIME 5000
#define ENEMY_TURN_TIME 6000
int tickPlayer (void);
int tickEnemy(Encounter *encounter);
int retreat_condition (void);
int AL_damageHandle (int WeaponNum, int weapondamage, int defender, User *player1, Encounter *player2);
int AL_reloadCannons (int Weapon_Number);
int AL_shoot_cannons (int Player_charge);
int AL_playCombat(User *player, Encounter *player2, GameState *StateOfGame);
int AL_GhostShip (User *player,Encounter *player2, GameState *StateOfGame);
int AL_surrender (User *player,Encounter *player2, GameState *StateOfGame);
int AL_critical_Damage  (User *player, Encounter *player2, int attacker);
int AL_damageHandle (int WeaponNum, int weapondamage, int defender, User *player1, Encounter *player2);