#ifndef AL_ttf_fonts_h
#define AL_ttf_fonts_h

#include <stdio.h>
#include "state_data.h"
#include "AL_encounters.h"

#define FONT_NAME "fonts/Primitive.ttf"
#define FONT_NAME_2 "fonts/PixelMusketeer.ttf"

SDL_Texture* AL_renderText(const char * message, TTF_Font *fontFile, SDL_Color color, SDL_Renderer *renderer);
int AL_openFontFile (TTF_Font **fontFile, const char *fontFileName, int fontSize);
int AL_initialiseTTF();
void AL_renderFont(SDL_Renderer *mainRenderer, SDL_Color color, TTF_Font *fontFile, int xCor, int yCor, const char *stringToPrint);
void AL_renderUIStats(SDL_Renderer *mainRender);
char* itoa(int num, char* str, int base);
void AL_renderEnemyStats(SDL_Renderer *mainRenderer, Encounter *encounter);
void AL_renderNumbers(SDL_Renderer *mainRender, int value);
void AL_renderDescription(SDL_Renderer *mainRenderer, char *stringToRender);
void stringsplit (char *test, char string[100][100]);
#endif
