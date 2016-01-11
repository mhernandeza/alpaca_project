# include "AL_combat.h"

int AL_critical_Damage  (User *player, Encounter *player2, int attacker);

int AL_playCombat(User *player, Encounter *player2, GameState *StateOfGame)
{
    static int oldTime = 0;
    if (oldTime == 0){
        oldTime = SDL_GetTicks();
    }
    if((oldTime + 5000) > SDL_GetTicks()){
        return 1;
    }
    
    if(player->health <= 0){
        *StateOfGame = GAME_OVER;
    }
    
    if (tickPlayer() == 1){
        player->isFiring = true;
    }
    
    if (tickEnemy(player2) == 1){
        player2->isFiring = true;
    }
    return 0;
}

int AL_criticalDamageHandle(int weaponNum, int weaponDamage){
    int criticalDamageDealth = 0;
    if (rand()/(double)RAND_MAX < 0.5){
        criticalDamageDealth = AL_damageHandle(weaponNum, weaponDamage)/2;
    }
    return (criticalDamageDealth);
}


int AL_damageHandle (int WeaponNum, int weapondamage)
{
    int damageDealt;
    
    damageDealt = weapondamage * WeaponNum * (rand()/(double)RAND_MAX);
    
    return (damageDealt);
}

int tickPlayer (void)
{
    if(player.oldTime + TURNTIME > SDL_GetTicks()){
        return 0;
    }
    player.oldTime = SDL_GetTicks();
    return 1;
}
int tickEnemy(Encounter *encounter){
    if(encounter->oldTime + ENEMY_TURN_TIME > SDL_GetTicks()){

        return 0;
    }
    encounter->oldTime = SDL_GetTicks();
    return 1;
}

int AL_collectLoot(){
    int newloot, healing, newcrew, newcannons;
    
    newloot = 100 + rand()%100 + 1;
    healing = rand()%2;
    if (rand()%100 > 90){
        newcrew = 1;
    } else {
        newcrew = 0;
    }
    if (rand()%100 > 90){
        newcannons = 1;
    } else {
        newcannons = 0;
    }
    
    player.gold += newloot;
    player.health += healing;
    player.crew += newcrew;
    player.weaponNumber += newcannons;
    
    return 1;
}
