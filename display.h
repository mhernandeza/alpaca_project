//
//  display.h
//  ALKrakenMain
//
//  Created by Lee's Mac on 11/12/15.
//  Copyright © 2015 Walid Beydoun. All rights reserved.
//

#ifndef display_h
#define display_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

typedef int bool;
#define true 1
#define false 0

struct AL_Sprite {
    SDL_Texture *image;
    SDL_Rect source;
    SDL_Rect destination;
    Uint32 oldTime;
    Uint32 speed;
    
    int numberOfFrames;
    int textureWidth;
    int textureHeight;
    int frameWidth, frameHeight;
};
typedef struct AL_Sprite AL_Sprite;

void AL_getNextFrame(AL_Sprite *spriteSheet);
void AL_setSpriteSheetData(AL_Sprite *spriteSheet, unsigned int frameRate, unsigned int numOfCols, int numOfRows);
void AL_setSpriteSizeAndLocation(AL_Sprite *spriteSheet, int xLocation, int yLocation, int width, int height);
bool AL_initWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderTarget);
bool AL_initImage();
bool checkForQuit();
SDL_Texture *AL_loadTexture(char *path, SDL_Renderer *renderTarget);

#endif /* display_h */
