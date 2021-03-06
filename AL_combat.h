#include "AL_state_data.h"
#include "AL_player.h"
#include <SDL2/SDL.h>


#define TURNTIME 5000
#define ENEMY_TURN_TIME 6000
int tickPlayer (void);
int tickEnemy(Encounter *encounter);
int AL_playCombat(User *player, Encounter *player2, GameState *StateOfGame);
int AL_damageHandle (int WeaponNum, int weapondamage);
int AL_criticalDamageHandle(int weaponNum, int weaponDamage);
int AL_collectLoot();