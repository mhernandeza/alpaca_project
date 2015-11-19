//
//  display.c
//  ALKrakenMain
//
//  Created by Lee's Mac on 11/12/15.
//  Copyright © 2015 Walid Beydoun. All rights reserved.
//

#include "display.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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
    
    *renderTarget = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
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

void AL_LoadMainMenuState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event event){
    const int startPosition = 340;
    const int nextMenuElement = 125;
    const int optionPosition = startPosition + nextMenuElement;
    const int exitPosition = optionPosition + nextMenuElement;
    
    static AL_Sprite skullSprite;
    static SDL_Texture *mainMenuTexture;
    static int initialised = 0;
    if(initialised == 0){
        mainMenuTexture = AL_loadTexture("images/mainMenu.jpg", mainRenderer);
        skullSprite.image = AL_loadTexture("images/skullSprite.png", mainRenderer);
        AL_setSpriteSheetData(&skullSprite, 120, 2, 1);
        AL_getNextFrame(&skullSprite);
        AL_setSpriteSizeAndLocation(&skullSprite, 720, 340, 70, 70);
        initialised = 1;
    }
    
    AL_getNextFrame(&skullSprite);
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, mainMenuTexture, NULL, NULL);
    SDL_RenderCopy(mainRenderer, skullSprite.image, &skullSprite.source, &skullSprite.destination);
    

    if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w){
        skullSprite.destination.y -= nextMenuElement;
        if(skullSprite.destination.y < startPosition){
            skullSprite.destination.y = exitPosition;
        }
    }
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s){
        skullSprite.destination.y += nextMenuElement;
        if(skullSprite.destination.y > exitPosition){
            skullSprite.destination.y = startPosition;
        }
    }
    
    if (event.key.keysym.sym == SDLK_RETURN){
        if (skullSprite.destination.y == startPosition){
            initialised = 0;
            *StateOfGame = PLAY_GAME;
        }
    }
}

void AL_LoadPlayGameState(SDL_Renderer *mainRenderer, GameState *StateOfGame, SDL_Event event){
    static AL_Sprite stormSprite;
    static int initialised = 0;
    if(initialised == 0){
        stormSprite.image = AL_loadTexture("images/storm.jpg", mainRenderer);
        AL_setSpriteSheetData(&stormSprite, 140, 9, 3);
        initialised = 1;
    }
    
    AL_getNextFrame(&stormSprite);
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, stormSprite.image, &stormSprite.source, NULL);
    
    if(event.key.keysym.sym == SDLK_BACKSPACE){
        *StateOfGame = MAIN_MENU;
        initialised = 0;
    }
    
}