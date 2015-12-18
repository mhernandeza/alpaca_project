#include "display.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void playFireCannonAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite);
void playEnemyFireAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter);

//Call this function to initialise the SDL_Window and renderer. It takes pointers to the pointers of the window
//and renderer. It returns true if both the window and the renderer were initialised.
bool AL_initWindowAndRenderer(SDL_Window **window, SDL_Renderer ** renderTarget){
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO)< 0){
        printf("Failed to initialse window. Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        *window = SDL_CreateWindow("ALKraken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*window == NULL){
            printf("Failed to create a window. Error == %s\n", SDL_GetError());
        }
    }
    
    *renderTarget = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderTarget == NULL){
        printf("Failed to create a renderer: %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

//Call this function to initialise the IMG_extension of SDL. It will initialise the subsystems for PNG and JPG image formats only.
//Returns false if it failed to initialise extension.
bool AL_initImage(){
    int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF;
    if (!(IMG_Init(imgFlags)& imgFlags)){
        printf("SDL_Image initialisation failed: %s", IMG_GetError());
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
        printf("Faild to create an SDL Surface. %s\n", SDL_GetError());
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL){
            printf("Failed to create a texture from a surface. %s\n", SDL_GetError());
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
            *StateOfGame = BEHAVIOUR_STATE;
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
    static AL_Sprite HUD;
    static int intialised = 0;
    
    if(intialised == 0){
       // storm.image = AL_loadTexture("images/mockCombatSprites/storm.jpg", mainRenderer);
       // AL_setSpriteSheetData(&storm, 200, 9, 3);
        background.image = AL_loadTexture("images/mockCombatSprites/combatBackground.jpg", mainRenderer);

        playerShip.image = AL_loadTexture("images/mockCombatSprites/playerShip.png", mainRenderer);
        AL_setSpriteSheetData(&playerShip, 150, 9, 1);
        AL_setSpriteSizeAndLocation(&playerShip, 200, 280, 250, 250);

        enemyShip.image = AL_loadTexture("images/mockCombatSprites/enemyShip.png", mainRenderer);
        AL_setSpriteSheetData(&enemyShip, 120, 10, 1);
        AL_setSpriteSizeAndLocation(&enemyShip, 760, 270, 250, 250);

        
        cannonSprite.image = AL_loadTexture("images/mockCombatSprites/cannon6.png", mainRenderer);
        AL_setSpriteSheetData(&cannonSprite, 40, 2, 35);
        AL_setSpriteSizeAndLocation(&cannonSprite, 300, 260, 600, 300);
        
        cannonSpriteEnemy.image = AL_loadTexture("images/mockCombatSprites/cannon6.png", mainRenderer);
        AL_setSpriteSheetData(&cannonSpriteEnemy, 40, 2, 35);
        AL_setSpriteSizeAndLocation(&cannonSpriteEnemy, 300, 260, 600, 300);
        
       /* cannonSprite.image = AL_loadTexture("images/mockCombatSprites/cannon8.png", mainRenderer);
        AL_setSpriteSheetData(&cannonSprite, 100, 5, 22);
        AL_setSpriteSizeAndLocation(&cannonSprite, 280, 270, 600, 200); */
        
        HUD.image = AL_loadTexture("images/mockCombatSprites/HUD2.png", mainRenderer);
    
        
        intialised = 1;
    }
    
    AL_getNextFrame(&playerShip);
    AL_getNextFrame(&enemyShip);
   
    
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, background.image, NULL, NULL);
    
    
    playEnemyFireAnimation(mainRenderer, &cannonSpriteEnemy, encounter);
    SDL_RenderCopy(mainRenderer, enemyShip.image, &enemyShip.source, &enemyShip.destination);
    playFireCannonAnimation(mainRenderer, &cannonSprite);
    SDL_RenderCopy(mainRenderer, playerShip.image, &playerShip.source, &playerShip.destination);
    SDL_RenderCopy(mainRenderer, HUD.image, NULL, NULL);
    
    if (event->key.keysym.sym == SDLK_BACKSPACE){
        *StateofGame = MAIN_MENU;
        SDL_DestroyTexture(background.image);
        SDL_DestroyTexture(playerShip.image);
        SDL_DestroyTexture(enemyShip.image);
        SDL_DestroyTexture(cannonSprite.image);
        background.image = NULL; playerShip.image = NULL;
        enemyShip.image = NULL; cannonSprite.image = NULL;
        intialised = 0;
    } else if (event->key.keysym.sym == SDLK_w){
        //TODO when event happens play animation
    }
    
}

void playFireCannonAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite){
    if(player.isFiring){
        AL_getNextFrame(cannonSprite);
        SDL_RenderCopy(mainRenderer, cannonSprite->image, &cannonSprite->source, &cannonSprite->destination);
        if(cannonSprite->source.y + cannonSprite->frameHeight >= cannonSprite->textureHeight){
            player.isFiring = false;
        }
    }
}

void playEnemyFireAnimation(SDL_Renderer *mainRenderer, AL_Sprite *cannonSprite, Encounter *encounter){
    if(encounter->isFiring){
        AL_getNextFrame(cannonSprite);
        SDL_RenderCopyEx(mainRenderer, cannonSprite->image, &cannonSprite->source, &cannonSprite->destination, 0.0, NULL, true);
        if(cannonSprite->source.y + cannonSprite->frameHeight >= cannonSprite->textureHeight){
            encounter->isFiring = false;
        }
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
        printf("%d\n", SDL_SetTextureAlphaMod(logo, alpha));
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
            printf("%d\n", alpha);
        }
        SDL_SetTextureAlphaMod(logo, alpha);

        
    }
    
}

void AL_LoadBehaviourState(SDL_Renderer *mainRender, GameState *StateOfGame, SDL_Event *event){
    enum currentScene { yesScene, noScene, numScene};
    
    static AL_Sprite behaviourYes;
    static AL_Sprite behaviourNo;
    static AL_Sprite behaviourNum;
    static AL_Sprite numbers;
    static int scene = yesScene;
    static int initialised = 0;
    
    if(!initialised){
        behaviourYes.image = AL_loadTexture("images/behaviourSprites/behaviourYes.jpg", mainRender);
        behaviourNo.image = AL_loadTexture("images/behaviourSprites/behaviourNo.jpg", mainRender);
        behaviourNum.image = AL_loadTexture("images/behaviourSprites/behaviourNum.png", mainRender);
        
        numbers.image = AL_loadTexture("images/behaviourSprites/numbers.png", mainRender);
        AL_setSpriteSheetData(&numbers, 20, 2, 5);
        AL_setSpriteSizeAndLocation(&numbers, 500, 500, 50, 50);
        
        SDL_RenderCopy(mainRender, behaviourYes.image, NULL, NULL);
        scene = yesScene;
        initialised = 1;
    }
    
    SDL_RenderClear(mainRender);
    if(event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT){
        if(scene == yesScene && scene != numScene){
            scene = noScene;
        } else if (scene == noScene && scene != numScene) {
            scene = yesScene;
        }
    }
    
    if(event->key.keysym.sym == SDLK_w){
        player.retreatHealth++;
        if(player.retreatHealth > 99){
            player.retreatHealth = 0;
        }
    }
    if (event->key.keysym.sym == SDLK_s){
        player.retreatHealth--;
        if(player.retreatHealth < 0){
            player.retreatHealth = 99;
        }
    }
    
    if (scene == yesScene){
        SDL_RenderCopy(mainRender, behaviourYes.image, NULL, NULL);
    } else if (scene == noScene) {
        SDL_RenderCopy(mainRender, behaviourNo.image, NULL, NULL);
    } else if (scene == numScene){
        SDL_RenderCopy(mainRender, behaviourNum.image, NULL, NULL);
        AL_renderNumbers(mainRender, player.retreatHealth);
    }
    
    if(scene != numScene){
       // AL_renderDescription(mainRender, "Would you like to retreat based on your hull.");
    } else if (scene == numScene){
        AL_renderDescription(mainRender, "At what health would you like to retreat at?");
    }
    
    
    if(event->key.keysym.sym == SDLK_RETURN){
        if (scene == noScene){
            SDL_DestroyTexture(behaviourYes.image);
            SDL_DestroyTexture(behaviourNo.image);
            SDL_DestroyTexture(behaviourNum.image);
            SDL_DestroyTexture(numbers.image);
            player.retreatHealth = 0;
            initialised = 0;
            *StateOfGame = COMBAT_STATE;
        }
        if (scene == numScene){
            *StateOfGame = COMBAT_STATE;
            initialised = 0;
        }
        if (scene == yesScene){
            scene = numScene;
            
        }
        
    }
    
}