#include "display.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


void playFireCannonAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter);
void playEnemyFireAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter);

//Call this function to initialise the SDL_Window and renderer. It takes pointers to the pointers of the window
//and renderer. It returns true if both the window and the renderer were initialised.
bool AL_initWindowAndRenderer(SDL_Window **window, SDL_Renderer ** renderTarget){
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO)< 0){
        fprintf(stderr, "Failed to initialse window. Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        *window = SDL_CreateWindow("ALKraken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*window == NULL){
            fprintf(stderr, "Failed to create a window. Error == %s\n", SDL_GetError());
        }
    }
    
    *renderTarget = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderTarget == NULL){
        fprintf(stderr, "Failed to create a renderer: %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

//Call this function to initialise the IMG_extension of SDL. It will initialise the subsystems for PNG and JPG image formats only.
//Returns false if it failed to initialise extension.
bool AL_initImage(){
    int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF;
    if (!(IMG_Init(imgFlags)& imgFlags)){
        fprintf(stderr, "SDL_Image initialisation failed: %s", IMG_GetError());
        return false;
    }
    else {
        return true;
    }
}

//Function loads texture from the given path. Requires a SDL_Renderer
SDL_Texture *AL_loadTexture(char *path, SDL_Renderer *renderTarget){
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL){
        fprintf(stderr,"Faild to create an SDL Surface. %s\n", SDL_GetError());
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL){
            fprintf(stderr, "Failed to create a texture from a surface. %s\n", SDL_GetError());
        }
    }
    
    SDL_FreeSurface(surface);
    return texture;
}

//Function sets the sprite sheet data needed to initialise a AL_Sprite variables
void AL_setSpriteSheetData(AL_Sprite *spriteSheet, unsigned int speed, unsigned int numOfCols, int numOfRows){
    spriteSheet->speed = speed;
    spriteSheet->numberOfFrames = numOfRows;
    spriteSheet->oldTime = SDL_GetTicks();
    
    SDL_QueryTexture(spriteSheet->image, NULL, NULL, &spriteSheet->textureWidth, &spriteSheet->textureHeight);
    spriteSheet->frameWidth = spriteSheet->textureWidth/numOfCols;
    spriteSheet->frameHeight = spriteSheet->textureHeight/numOfRows;
    
    spriteSheet->source.x = 0;
    spriteSheet->source.y = 0;
    spriteSheet->source.w = spriteSheet->frameWidth;
    spriteSheet->source.h = spriteSheet->frameHeight;
    
    
}

//Gets the next frame in an animation. All the information needed for it to process this data is in the AL_Sprite variable.
void AL_getNextFrame(AL_Sprite *spriteSheet){
    if (spriteSheet->oldTime + spriteSheet->speed > SDL_GetTicks()){
        return;
    }
    
    spriteSheet->oldTime = SDL_GetTicks();
    
    spriteSheet->source.x += spriteSheet->frameWidth;
    if (spriteSheet->source.x >= spriteSheet->textureWidth){
        spriteSheet->source.x = 0;
    }
    spriteSheet->source.y += spriteSheet->frameHeight;
    if(spriteSheet->source.y >= spriteSheet->textureHeight){
        spriteSheet->source.y = 0;
    }
}

//Sets the size and location of the sprite sheet. All values are in pixels.
void AL_setSpriteSizeAndLocation(AL_Sprite *spriteSheet, int xLocation, int yLocation, int width, int height){
    spriteSheet->destination.x = xLocation;
    spriteSheet->destination.y = yLocation;
    spriteSheet->destination.w = width;
    spriteSheet->destination.h = height;
    
}


void playFireCannonAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter){
    if(player.isFiring){
        AL_getNextFrame(cannonSprite);
        SDL_RenderCopy(mainRenderer, cannonSprite->image, &cannonSprite->source, &cannonSprite->destination);
        if(cannonSprite->source.y + cannonSprite->frameHeight >= cannonSprite->textureHeight){
            player.isFiring = false;
            encounter->health -= AL_damageHandle(encounter->weaponnumber, encounter->weapondamage, 1, &player, encounter);
        }
    }
}

void playEnemyFireAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter){
    if(encounter->isFiring){
        AL_getNextFrame(cannonSprite);
        SDL_RenderCopyEx(mainRenderer, cannonSprite->image, &cannonSprite->source, &cannonSprite->destination, 0.0, NULL, true);
        if(cannonSprite->source.y + cannonSprite->frameHeight >= cannonSprite->textureHeight){
            encounter->isFiring = false;
            player.health -= AL_damageHandle(AL_getWeaponNumber(&player), AL_getWeaponDamage(&player), 2, &player, encounter);
        }
    }
}

void copyEncounter(Encounter *encounter, Encounter encounterFromArr){
    if(encounter == NULL){
        return;
    }
    encounter->ID = encounterFromArr.ID;
    encounter->crew = encounterFromArr.crew;
    encounter->health = encounterFromArr.health;
    encounter->oldTime = encounterFromArr.oldTime;
    encounter->isFiring = encounterFromArr.isFiring;
    encounter->weaponnumber = encounterFromArr.weaponnumber;
    encounter->weapondamage = encounterFromArr.weapondamage;
    encounter->locale.weatherseverity = encounterFromArr.locale.weatherseverity;
    strcpy(encounter->description, encounterFromArr.description);
    strcpy(encounter->name, encounterFromArr.name);
    strcpy(encounter->locale.direction, encounterFromArr.locale.direction);
    strcpy(encounter->locale.weatherdescription, encounterFromArr.locale.weatherdescription);
    strcpy(encounter->longdescription, encounterFromArr.longdescription);
}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void AL_LoadMainMenuState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event){
    const int startPosition = 340;
    const int nextMenuElement = 125;
    const int optionPosition = startPosition + nextMenuElement;
    const int exitPosition = optionPosition + nextMenuElement;
    
    static AL_Sprite skullSprite;
    static SDL_Texture *mainMenuTexture;
    static int initialised = 0;
    if(initialised == 0){
        mainMenuTexture = AL_loadTexture("images/mainMenuSprites/mainMenu.jpg", mainRenderer);
        skullSprite.image = AL_loadTexture("images/mainMenuSprites/skullSprite.png", mainRenderer);
        AL_setSpriteSheetData(&skullSprite, 120, 2, 1);
        AL_getNextFrame(&skullSprite);
        AL_setSpriteSizeAndLocation(&skullSprite, 720, 340, 70, 70);
        initialised = 1;
    }
    
    AL_getNextFrame(&skullSprite);
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, mainMenuTexture, NULL, NULL);
    SDL_RenderCopy(mainRenderer, skullSprite.image, &skullSprite.source, &skullSprite.destination);
    

    if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_w){
        skullSprite.destination.y -= nextMenuElement;
        if(skullSprite.destination.y < startPosition){
            skullSprite.destination.y = exitPosition;
        }
    }
    if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
        skullSprite.destination.y += nextMenuElement;
        if(skullSprite.destination.y > exitPosition){
            skullSprite.destination.y = startPosition;
        }
    }
    
    if (event->key.keysym.sym == SDLK_RETURN){
        if (skullSprite.destination.y == startPosition){
            initialised = 0;
            *StateOfGame = WORLD_STATE;
        } else if (skullSprite.destination.y == exitPosition){
            initialised = 0;
            event->type = SDL_QUIT;
        } else if (skullSprite.destination.y == optionPosition){
            initialised = 0;
            *StateOfGame = OPTIONS_MENU;
        }
    }
}

void AL_LoadOptionState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event){
    static SDL_Texture *optionMenuTexture;
    static int initialised = 0;
    if(initialised == 0){
        optionMenuTexture = AL_loadTexture("images/mainMenuSprites/optionsMenu.jpg", mainRenderer);
        initialised = 1;
    }
    
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, optionMenuTexture, NULL, NULL);
    
    if (event->key.keysym.sym == SDLK_BACKSPACE){
        *StateOfGame = MAIN_MENU;
        SDL_DestroyTexture(optionMenuTexture);
        initialised = 0;
    }

}

void AL_LoadPlayGameState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event, double deltaTime){
    static AL_Sprite worldMap;
    static AL_Sprite playerShip;
    int playerShipSize = 250;
    static int initialised = 0;
    if(initialised == 0){
        
        playerShip.image = AL_loadTexture("images/worldMapSprites/playerShip.png", mainRenderer);
        AL_setSpriteSheetData(&playerShip, 120, 9, 1);
        AL_setSpriteSizeAndLocation(&playerShip, 0, 220, playerShipSize, playerShipSize);
        
        worldMap.image = AL_loadTexture("images/worldMapSprites/worldMap.png", mainRenderer);
        AL_setSpriteSheetData(&worldMap, 120, 8, 1);
        AL_setSpriteSizeAndLocation(&worldMap, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        
        initialised = 1;
    }
    
    AL_getNextFrame(&playerShip);
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, worldMap.image, &worldMap.source, &worldMap.destination);
    SDL_RenderCopy(mainRenderer, playerShip.image, &playerShip.source, &playerShip.destination);
    
    int speed = 1000;
    int leftScreenMargin = 16;
    int topScreenMargin = -15;
    int bottomScreenMargin = 230;
  
    if(event->key.keysym.sym == SDLK_BACKSPACE){
        *StateOfGame = MAIN_MENU;
        SDL_DestroyTexture(worldMap.image);
        worldMap.image = NULL;
        SDL_DestroyTexture(playerShip.image);
        playerShip.image = NULL;
        initialised = 0;
    } else if (event->key.keysym.sym == SDLK_w){
        if (!((playerShip.destination.y - speed*deltaTime) < topScreenMargin)){
            playerShip.destination.y -= speed*deltaTime;
        }
    } else if (event->key.keysym.sym == SDLK_s){
        if (!((playerShip.destination.y + speed*deltaTime) > SCREEN_HEIGHT - bottomScreenMargin)){
            playerShip.destination.y += speed*deltaTime;
        }
        
    } else if (event->key.keysym.sym == SDLK_d){
        playerShip.destination.x += speed*deltaTime;
        if (playerShip.destination.x >= SCREEN_WIDTH){
            AL_getNextFrame(&worldMap);
            AL_setSpriteSizeAndLocation(&playerShip, 0, 220, playerShipSize, playerShipSize);
        }
    } else if (event->key.keysym.sym == SDLK_a){
        if (!((playerShip.destination.x + speed*deltaTime) < leftScreenMargin)){
            playerShip.destination.x -= speed*deltaTime;
        }
    }
    
}

void AL_LoadCombatState(SDL_Renderer *mainRenderer, GameState *StateofGame, SDL_Event *event, double deltaTime, Encounter *encounter){
    static AL_Sprite background;
    static AL_Sprite playerShip;
    static AL_Sprite enemyShip;
    static AL_Sprite cannonSprite;
    static AL_Sprite cannonSpriteEnemy;
    static AL_Sprite HUD1;
    static AL_Sprite HUD2;
    static int intialised = 0;
    static int oldTime;
    static int swap = 1;
    int swapRate = 3500;
    char shipType[50];
    char backgroundType[50];
    char number[20];
    TTF_Font *fontFile = NULL;
    SDL_Color color = {0,0, 0};
    
    if (encounter->ID == 0){
        strcpy(shipType, "images/mockCombatSprites/krakenBody2.png");
    } else if (encounter->ID == 1){
        strcpy(shipType, "images/mockCombatSprites/whiteShip.png");
    } else if (encounter->ID == 2){
        strcpy(shipType, "images/mockCombatSprites/redShip.png");
    } else if (encounter->ID == 3){
        strcpy(shipType, "images/mockCombatSprites/blackShip.png");
    }
    int backIndex = rand()%4;
    if(backIndex == 0){
        strcpy(backgroundType, "images/mockCombatSprites/combatBackground.jpg");
    } else if (backIndex == 1){
        strcpy(backgroundType, "images/mockCombatSprites/day.jpg");
    } else if (backIndex == 2){
        strcpy(backgroundType, "images/mockCombatSprites/nightNoMoon.jpg");
    } else {
        strcpy(backgroundType, "images/mockCombatSprites/sunset.jpg");
    }
    
    
    if(intialised == 0){
       
        background.image = AL_loadTexture(backgroundType, mainRenderer);

        playerShip.image = AL_loadTexture("images/mockCombatSprites/ourShipCombat2.png", mainRenderer);
        AL_setSpriteSheetData(&playerShip, 150, 8, 1);
        AL_setSpriteSizeAndLocation(&playerShip, 250, 280, 250, 250);
        
        enemyShip.image = AL_loadTexture(shipType, mainRenderer);
        
        if(encounter->ID == 0){
            AL_setSpriteSheetData(&enemyShip, 120, 5, 1);
            AL_setSpriteSizeAndLocation(&enemyShip, 760, 270, 350, 250);
            
            cannonSpriteEnemy.image = AL_loadTexture("images/mockCombatSprites/attack.png", mainRenderer);
            AL_setSpriteSheetData(&cannonSpriteEnemy, 90, 10, 19);
            AL_setSpriteSizeAndLocation(&cannonSpriteEnemy, 140, 370,180, 180);
        } else {
            
            AL_setSpriteSheetData(&enemyShip, 120, 10, 1);
            AL_setSpriteSizeAndLocation(&enemyShip, 760, 270, 350, 250);
            
            cannonSpriteEnemy.image = AL_loadTexture("images/mockCombatSprites/cannon6.png", mainRenderer);
            AL_setSpriteSheetData(&cannonSpriteEnemy, 40, 2, 35);
            AL_setSpriteSizeAndLocation(&cannonSpriteEnemy, 300, 260, 600, 300);
        }
        
        cannonSprite.image = AL_loadTexture("images/mockCombatSprites/cannon6.png", mainRenderer);
        AL_setSpriteSheetData(&cannonSprite, 40, 2, 35);
        AL_setSpriteSizeAndLocation(&cannonSprite, 300, 260, 600, 300);
  
        HUD1.image = AL_loadTexture("images/mockCombatSprites/HudHealth.png", mainRenderer);
        HUD2.image = AL_loadTexture("images/mockCombatSprites/HudCannons.png", mainRenderer);
        intialised = 1;
    }
    
    AL_getNextFrame(&playerShip);
    AL_getNextFrame(&enemyShip);
   
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, background.image, NULL, NULL);
    
    playEnemyFireAnimation(mainRenderer, &cannonSpriteEnemy, encounter);
    SDL_RenderCopy(mainRenderer, enemyShip.image, &enemyShip.source, &enemyShip.destination);
    playFireCannonAnimation(mainRenderer, &cannonSprite, encounter);
    SDL_RenderCopy(mainRenderer, playerShip.image, &playerShip.source, &playerShip.destination);
    
    if (oldTime + swapRate < SDL_GetTicks()){
        oldTime = SDL_GetTicks();
        swap++;
    }
    
   
    if(swap % 2 == 1){
        SDL_RenderCopy(mainRenderer, HUD1.image, NULL, NULL);
        AL_renderFont(mainRenderer, color, fontFile, 900, 530, itoa(player.retreatHealth, number, 10));
    } else {
        SDL_RenderCopy(mainRenderer, HUD2.image, NULL, NULL);
        AL_renderFont(mainRenderer, color, fontFile, 850, 530, itoa(player.retreatWeapons, number, 10));
    }
    
    
    
    
    if (event->key.keysym.sym == SDLK_BACKSPACE){
        *StateofGame = MAIN_MENU;
        SDL_DestroyTexture(background.image);
        SDL_DestroyTexture(playerShip.image);
        SDL_DestroyTexture(enemyShip.image);
        SDL_DestroyTexture(cannonSprite.image);
        background.image = NULL; playerShip.image = NULL;
        enemyShip.image = NULL; cannonSprite.image = NULL;
        intialised = 0;
    }
    
}

void AL_LoadGameOverState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event *event){
    static AL_Sprite gameOverSprite;
    static int initialised = 0;
    
    if(!initialised){
        gameOverSprite.image = AL_loadTexture("images/gameOverSprites/gameOver.png", mainRenderer);
    }
    
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, gameOverSprite.image, NULL, NULL);
    
    if(event->key.keysym.sym == SDLK_RETURN){
        SDL_DestroyTexture(gameOverSprite.image);
        *StateOfGame = MAIN_MENU;
    }
    
}

void AL_LoadLogoState(SDL_Renderer *mainRenderer, GameState *StateOfGame){
    static SDL_Texture *logo;
    static int oldTime;
    static int initialised = 0;
    static int alpha = 0;
    if(!initialised){
        logo = AL_loadTexture("images/logo.png", mainRenderer);
        SDL_SetTextureAlphaMod(logo, alpha);
        initialised = 1;
        oldTime = SDL_GetTicks();
    }
    
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, logo, NULL, NULL);
    
    if(oldTime + 6000 < SDL_GetTicks()){
        *StateOfGame = MAIN_MENU;
    }
    if(oldTime + 4500 > SDL_GetTicks()){
        if(alpha < 255){
            alpha = alpha + 1;
        }
        SDL_SetTextureAlphaMod(logo, alpha);
        
    }
    
}

void AL_LoadBehaviourState(SDL_Renderer *mainRender, GameState *StateOfGame, SDL_Event *event){
    enum currentScene { healthYes, healthNo, healthNum, cannonNo, cannonYes, cannonNum};
    
    static AL_Sprite behHealthYes;
    static AL_Sprite behHealthNo;
    static AL_Sprite behHealthNum;
    static AL_Sprite behCannonYes;
    static AL_Sprite behCannonNo;
    static AL_Sprite behCannonNum;
    
    static int scene = healthYes;
    static int initialised = 0;
    
    if(!initialised){
        behHealthYes.image = AL_loadTexture("images/behSprites/healthYes.png", mainRender);
        behHealthNo.image = AL_loadTexture("images/behSprites/healthNo.png", mainRender);
        behHealthNum.image = AL_loadTexture("images/behSprites/retreatHealthNum.png", mainRender);
        behCannonNo.image = AL_loadTexture("images/behSprites/cannonsNo.png", mainRender);
        behCannonYes.image = AL_loadTexture("images/behSprites/cannonsYes.png", mainRender);
        behCannonNum.image = AL_loadTexture("images/behSprites/retreatCannonsNum.png", mainRender);
        
        SDL_RenderCopy(mainRender, behHealthYes.image, NULL, NULL);
        scene = healthYes;
        initialised = 1;
    }
    
    SDL_RenderClear(mainRender);
    if(event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT){
        if(scene == healthYes && scene != healthNum){
            scene = healthNo;
        } else if (scene == healthNo && scene != healthNum) {
            scene = healthYes;
        } else if (scene == cannonNo && scene != cannonNum){
            scene = cannonYes;
        } else if (scene == cannonYes && scene != cannonNum){
            scene = cannonNo;
        }
    }
    
    if(scene == healthNum && event->key.keysym.sym == SDLK_w){
        player.retreatHealth++;
        if(player.retreatHealth > 99){
            player.retreatHealth = 0;
        }
    }
    if (scene == healthNum && event->key.keysym.sym == SDLK_s){
        player.retreatHealth--;
        if(player.retreatHealth < 0){
            player.retreatHealth = 99;
        }
    }
    
    if(scene == cannonNum && event->key.keysym.sym == SDLK_w){
        player.retreatWeapons++;
        if(player.retreatWeapons > player.weaponNumber){
            player.retreatWeapons = 0;
        }
    }
    if (scene == cannonNum && event->key.keysym.sym == SDLK_s){
        player.retreatWeapons--;
        if(player.retreatWeapons < 0){
            player.retreatWeapons = player.weaponNumber;
        }
    }
    
    if (scene == healthYes){
        SDL_RenderCopy(mainRender, behHealthYes.image, NULL, NULL);
    } else if (scene == healthNo) {
        SDL_RenderCopy(mainRender, behHealthNo.image, NULL, NULL);
    } else if (scene == healthNum){
        SDL_RenderCopy(mainRender, behHealthNum.image, NULL, NULL);
        AL_renderNumbers(mainRender, player.retreatHealth);
    } else if (scene == cannonYes){
        SDL_RenderCopy(mainRender, behCannonYes.image, NULL, NULL);
    } else if (scene == cannonNo){
        SDL_RenderCopy(mainRender, behCannonNo.image, NULL, NULL);
    } else if (scene == cannonNum){
        SDL_RenderCopy(mainRender, behCannonNum.image, NULL, NULL);
        AL_renderNumbers(mainRender, player.retreatWeapons);
    }
    
   /* if(scene != numScene){
       // AL_renderDescription(mainRender, "Would you like to retreat based on your hull.");
    } else if (scene == numScene){
        AL_renderDescription(mainRender, "At what health would you like to retreat at?");
    } */
    
    
    if(event->key.keysym.sym == SDLK_RETURN){
        if (scene == healthNo){
            player.retreatHealth = 0;
            scene = cannonYes;
        }
        else if (scene == healthYes){
            scene = healthNum;
        }
        else if (scene == healthNum){
            scene = cannonYes;
        }
        else if (scene == cannonYes){
            scene = cannonNum;
        }
        else if (scene == cannonNo){
            player.retreatWeapons = 0;
            SDL_DestroyTexture(behCannonNo.image);
            SDL_DestroyTexture(behCannonYes.image);
            SDL_DestroyTexture(behCannonNum.image);
            SDL_DestroyTexture(behHealthNo.image);
            SDL_DestroyTexture(behHealthNum.image);
            SDL_DestroyTexture(behHealthYes.image);
            initialised = 0;
            *StateOfGame = COMBAT_STATE;
        }
        else if (scene == cannonNum){
            SDL_DestroyTexture(behCannonNo.image);
            SDL_DestroyTexture(behCannonYes.image);
            SDL_DestroyTexture(behCannonNum.image);
            SDL_DestroyTexture(behHealthNo.image);
            SDL_DestroyTexture(behHealthNum.image);
            SDL_DestroyTexture(behHealthYes.image);
            initialised = 0;
            *StateOfGame = COMBAT_STATE;
        }
    }
}

void AL_LoadWorldState(SDL_Renderer *mainRender, GameState *StateOfGame, SDL_Event *event, Encounter *encounter, Encounter encounterArray[8]){
    enum currentScene { neScene, nnScene, nwScene};
    
    static AL_Sprite compassNE;
    static AL_Sprite compassNW;
    static AL_Sprite compassNN;
    static int scene = nnScene;
    static int initialised = 0;
    if(!initialised){
        compassNE.image = AL_loadTexture("images/worldStateSprites/northEast.jpg", mainRender);
        compassNW.image = AL_loadTexture("images/worldStateSprites/northWest.jpg", mainRender);
        compassNN.image = AL_loadTexture("images/worldStateSprites/north.jpg", mainRender);
        
        
        SDL_RenderCopy(mainRender, compassNN.image, NULL, NULL);
        scene = nnScene;
        initialised = 1;
    }

    if(event->key.keysym.sym == SDLK_a){
        if(scene == nnScene){
            scene = nwScene;
        } else if (scene == nwScene){
            scene = neScene;
        } else if (scene == neScene){
            scene = nnScene;
        }
    } else if (event->key.keysym.sym == SDLK_d){
        if(scene == nnScene){
            scene = neScene;
        } else if (scene == neScene){
            scene = nwScene;
        } else if (scene == nwScene){
            scene = nnScene;
        }
    }
    
    SDL_RenderClear(mainRender);
    if (scene == nnScene){
        SDL_RenderCopy(mainRender, compassNN.image, NULL, NULL);
        AL_renderInfo(encounterArray[0].longdescription, mainRender);
    } else if (scene == neScene){
        SDL_RenderCopy(mainRender, compassNE.image, NULL, NULL);
        AL_renderInfo(encounterArray[1].longdescription, mainRender);

    } else if (scene == nwScene){
        SDL_RenderCopy(mainRender, compassNW.image, NULL, NULL);
        AL_renderInfo(encounterArray[7].longdescription, mainRender);

    }
    
    
    if(event->key.keysym.sym == SDLK_RETURN){
        if(scene == nnScene){
            copyEncounter(encounter, encounterArray[0]);
            if(encounter->ID != 4){
                *StateOfGame = BEHAVIOUR_STATE;
                
            } else {
                *StateOfGame = WEATHER_STATE;
            }
        }
        if(scene == nwScene){
            copyEncounter(encounter, encounterArray[7]);
            if(encounter->ID != 4){
                *StateOfGame = BEHAVIOUR_STATE;
            } else {
                *StateOfGame = WEATHER_STATE;
            }
        }
        if(scene == neScene){
            copyEncounter(encounter, encounterArray[1]);
            if(encounter->ID != 4){
                *StateOfGame = BEHAVIOUR_STATE;
            } else {
                *StateOfGame = WEATHER_STATE;
            }
        }
    }
    AL_renderUIStats(mainRender);
    
}

void AL_LoadRetreatScene(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame){
    SDL_Texture *retreat = AL_loadTexture("images/playerRetreat.png", mainRenderer);
    static double oldTime = 0;
    SDL_RenderCopy(mainRenderer, retreat, NULL, NULL);
    if (oldTime > 5){
        SDL_DestroyTexture(retreat);
        *StateOfGame = WORLD_STATE;
    } else {
        oldTime += deltaTime;
    }
    
    SDL_DestroyTexture(retreat);
}

void AL_LoadSurrenderScene(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame){
    SDL_Texture *retreat = AL_loadTexture("images/enemySurrender.png", mainRenderer);
    static double oldTime = 0;
    SDL_RenderCopy(mainRenderer, retreat, NULL, NULL);
    if (oldTime > 3){
        SDL_DestroyTexture(retreat);
        oldTime = 0;
        player.health += (rand() % 30) + 1;
        player.crew += (rand() % 10) + 1;
        player.gold += (rand() % 100) + 1;
        
        *StateOfGame = WORLD_STATE;
    } else {
        oldTime += deltaTime;
    }
    
    SDL_DestroyTexture(retreat);
}



void AL_LoadWeatherState(double deltaTime, SDL_Renderer *mainRenderer, GameState *StateOfGame, Encounter *encounter){
    static AL_Sprite storm;
    static AL_Sprite playerShip;
    static AL_Sprite effectImage;
    static AL_Sprite HUD;
    static int oldTime = 0;
    static int initialised = 0;
    static int xLocaton = 150;
    static int xCorBird = 1200;
    int shipMove = 6000;
    
    encounter->locale.weatherseverity = 23;
    
    if(!initialised){
        
        playerShip.image = AL_loadTexture("images/mockCombatSprites/ourShipCombat2.png", mainRenderer);
        AL_setSpriteSheetData(&playerShip, 150, 8, 1);
        AL_setSpriteSizeAndLocation(&playerShip, xLocaton, 280, 250, 250);
        xLocaton = 150;
        xCorBird = 1200;
        
        if (encounter->locale.weatherseverity < 25){
            storm.image = AL_loadTexture("images/mockCombatSprites/sunset.jpg", mainRenderer);
            effectImage.image = AL_loadTexture("images/weatherSprites/clear.png", mainRenderer);
            AL_setSpriteSheetData(&effectImage, 120, 2, 1);
            AL_setSpriteSizeAndLocation(&effectImage, xCorBird, 100, 200, 200);
            HUD.image = AL_loadTexture("images/weatherSprites/hudClear.png", mainRenderer);
            
        } else if (encounter->locale.weatherseverity < 50){
            storm.image = AL_loadTexture("images/mockCombatSprites/day.jpg", mainRenderer);
            effectImage.image = AL_loadTexture("images/weatherSprites/wind.png", mainRenderer);
            AL_setSpriteSheetData(&effectImage, 120, 30, 1);
            AL_setSpriteSizeAndLocation(&effectImage, 100, 200, 50, 50);
            HUD.image = AL_loadTexture("images/weatherSprites/hudWindy.png", mainRenderer);
            
        } else if (encounter->locale.weatherseverity < 75){
            storm.image = AL_loadTexture("images/mockCombatSprites/nightNoMoon.jpg", mainRenderer);
            effectImage.image = AL_loadTexture("images/weatherSprites/rain.png", mainRenderer);
            AL_setSpriteSheetData(&effectImage,120, 2, 1);
            HUD.image = AL_loadTexture("images/weatherSprites/hudRain.png", mainRenderer);
        } else {
            storm.image = AL_loadTexture("images/weatherSprites/storm.jpg", mainRenderer);
            AL_setSpriteSheetData(&storm, 200, 9, 3);
            HUD.image = AL_loadTexture("images/weatherSprites/hudStorm.png", mainRenderer);
        }
        
        oldTime = SDL_GetTicks();
        
        initialised = 1;
    }
    
    SDL_RenderClear(mainRenderer);
    if(oldTime + shipMove > SDL_GetTicks()){
        xLocaton += 3;
        AL_setSpriteSizeAndLocation(&playerShip, xLocaton, 280, 250, 250);
        
        if(encounter->locale.weatherseverity < 25){
            xCorBird -= 4;
            AL_setSpriteSizeAndLocation(&effectImage, xCorBird, 100, 200, 200);
        }
        
        if(encounter->locale.weatherseverity < 75){
            SDL_RenderCopy(mainRenderer, storm.image, NULL, NULL);
        } else {
            SDL_RenderCopy(mainRenderer, storm.image, &storm.source, NULL);
        }
        
        if(encounter->locale.weatherseverity >= 75){
            AL_getNextFrame(&storm);
        } else {
            AL_getNextFrame(&effectImage);
        }
        
        AL_getNextFrame(&playerShip);
        SDL_RenderCopy(mainRenderer, playerShip.image, &playerShip.source, &playerShip.destination);
        if (encounter->locale.weatherseverity > 50 && encounter->locale.weatherseverity < 75){
            SDL_RenderCopy(mainRenderer, effectImage.image, &effectImage.source, NULL);
        } else if (encounter->locale.weatherseverity < 50){
            SDL_RenderCopy(mainRenderer, effectImage.image, &effectImage.source, &effectImage.destination);
        }
        
        SDL_RenderCopy(mainRenderer, HUD.image, NULL, NULL);

    } else {
        oldTime = 0;
        initialised = 0;
        *StateOfGame = WORLD_STATE;
    }
    
    
    
}
