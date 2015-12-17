#include "AL_ttf_fonts.h"

char* itoa(int num, char* str, int base);
void reverse(char str[]);

SDL_Texture* AL_renderText(const char * message, TTF_Font *fontFile, SDL_Color color, SDL_Renderer *renderer) {
    
    SDL_Surface *surf = TTF_RenderText_Blended(fontFile, message, color);
    if (surf == NULL){
        TTF_CloseFont(fontFile);
        fprintf(stderr, "Failed to render text to the surface.\n");
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == NULL){
        fprintf(stderr, "Failed to create texture from surface\n");
        return NULL;
    }

    SDL_FreeSurface(surf);
    return texture;
}

int AL_openFontFile (TTF_Font **fontFile, const char *fontFileName, int fontSize){
    *fontFile = TTF_OpenFont(fontFileName, fontSize);
    if (*fontFile == NULL){
        fprintf(stderr, "Failed to open font file %s.\n", fontFileName);
        return 0;
    }
    return 1;
    
}

int AL_initialiseTTF(){
    if(TTF_Init() != 0){
        fprintf(stderr, "Failed to initialise ttf fonts.\n");
        return 0;
    }
    return 1;
}

void AL_renderFont(SDL_Renderer *mainRenderer, SDL_Color color, TTF_Font *fontFile, int xCor, int yCor, const char *stringToPrint){
    SDL_Texture *font = AL_renderText(stringToPrint, fontFile, color, mainRenderer);
    SDL_Rect destination;
    destination.x = xCor;
    destination.y = yCor;
    
    int w, h;
    
    SDL_QueryTexture(font, NULL, NULL, &w, &h);
    destination.h = h;
    destination.w = w;
    
    SDL_RenderCopy(mainRenderer, font, NULL, &destination);
}

void AL_renderUIStats(SDL_Renderer *mainRender){
    char *statString = (char *)malloc(sizeof(char)*30);
    char *numberString = (char *)malloc(sizeof(char)*5);
    SDL_Color color = {83,62,0, 0};
    
    int xCor = 40;
    int yCor = 48;
    int xOffset = 100;
    int yOffset = 40;
    TTF_Font *fontFile;
    
    AL_openFontFile(&fontFile, FONT_NAME_2, 20);
    
    strcpy(statString, "HULL: ");
    numberString = itoa(player.health, numberString, 10);
    AL_renderFont(mainRender, color, fontFile, xCor, yCor, statString);
    AL_renderFont(mainRender, color, fontFile, xCor + xOffset, yCor ,numberString);
    
    strcpy(statString, "SPEED: ");
    numberString = itoa(player.speed, numberString, 10);
    AL_renderFont(mainRender, color, fontFile, xCor, yCor + yOffset, statString);
    AL_renderFont(mainRender, color, fontFile, xCor + xOffset, yCor + yOffset, numberString);
    
    strcpy(statString, "CANNONS: ");
    numberString = itoa(player.weaponNumber, numberString, 10);
    AL_renderFont(mainRender, color, fontFile, xCor, yCor + yOffset*2, statString);
    AL_renderFont(mainRender, color, fontFile, xCor + xOffset, yCor + yOffset*2, numberString);
    
    strcpy(statString, "CREW: ");
    numberString = itoa(player.crew, numberString, 10);
    AL_renderFont(mainRender, color, fontFile, xCor, yCor + yOffset*3, statString);
    AL_renderFont(mainRender, color, fontFile, xCor + xOffset, yCor + yOffset*3, numberString);
    
    TTF_CloseFont(fontFile);
    AL_openFontFile(&fontFile, FONT_NAME_2, 60);
    
    
    SDL_Color colorGold = {227, 149, 52, 0};
    numberString = itoa(player.gold, numberString, 10);
    AL_renderFont(mainRender, colorGold, fontFile, 1120, -2, numberString);
    
    TTF_CloseFont(fontFile);
    free(statString);
    free(numberString);
}

void AL_renderEnemyStats(SDL_Renderer *mainRenderer, Encounter *encounter){
    char *stringToRender = (char *)malloc(sizeof(char)*30);
    SDL_Color color = {255, 255, 255, 0};
    TTF_Font *fontFile;
    int x = 850, y = 250;
    
    AL_openFontFile(&fontFile, FONT_NAME_2, 50);
    stringToRender = itoa(encounter->health, stringToRender, 10);
    strcat(stringToRender, "%");
    AL_renderFont( mainRenderer, color, fontFile, x, y, stringToRender);
    
}

char* itoa(int num, char* str, int base){
    int i = 0;
    bool isNegative = false;
    
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
    
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
    
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
    
    str[i] = '\0'; // Append string terminator
    
    // Reverse the string
    reverse(str);
    
    return str;
}

void reverse(char *p)
{
    char *q = p;
    while(q && *q) ++q;
    for(--q; p < q; ++p, --q)
        *p = *p ^ *q,
        *q = *p ^ *q,
        *p = *p ^ *q;
}