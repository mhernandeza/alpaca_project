#include "AL_ttf_fonts.h"

char* itoa(int num, char* str, int base);
void reverse(char str[]);

SDL_Texture* AL_renderText(const char * message, TTF_Font *fontFile, SDL_Color color, SDL_Renderer *renderer) {
    if(fontFile == NULL){
        fontFile = TTF_OpenFont(FONT_NAME_2, 60);
    }
    char message2[300];
    strcpy(message2, message);
    SDL_Surface *surf = TTF_RenderText_Blended(fontFile, message2, color);
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
    
    SDL_DestroyTexture(font);
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

    AL_renderFont(mainRenderer, color, fontFile, 500, 0, encounter->name);

    free(stringToRender);
    TTF_CloseFont(fontFile);

}

void AL_renderNumbers(SDL_Renderer *mainRender, int value) {
    char *stringToRender = (char *)malloc(sizeof(char) * 10);
    SDL_Color color = {0x58, 0x31, 0x01, 0};
    TTF_Font *fontFile;
    int x = 575, y = 525;

    AL_openFontFile(&fontFile, FONT_NAME_2, 120);
    stringToRender = itoa(value, stringToRender, 10);
    if(value < 10){
        AL_renderFont(mainRender, color, fontFile, x + 63, y, stringToRender);
        AL_renderFont(mainRender, color, fontFile, x, y, "0");
    } else  if (value < 20){
        AL_renderFont(mainRender, color, fontFile, x + 20, y, stringToRender);
    } else {
        AL_renderFont(mainRender, color, fontFile, x , y, stringToRender);

    }


    free(stringToRender);
    TTF_CloseFont(fontFile);
}

void AL_renderDescription(SDL_Renderer *mainRenderer, char *stringToRender){
    SDL_Color color = {0x57, 0x30, 0, 0};
    TTF_Font *fontFile;
    int x = 150, y = 275;

    AL_openFontFile(&fontFile, FONT_NAME_2, 30);

    AL_renderFont(mainRenderer, color, fontFile, x, y, stringToRender);
    TTF_CloseFont(fontFile);

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

/*splits string onto miultiple lines to prevent overflow of text boxes
requires the test string, (string to be split) and string, array of strings*/
void stringsplit (char *test, char string[4][60])
{
  int x = 0, z = 0, y = 0;
  while (test[x] != '\0') {
    string[y][z] = test[x];
    x++;
    z++;
    if (z >= 50 && test[x] == ' '){
        string[y][z] = '\0';
        
        y++;
        z = 0;
    }
  }
    string[y][z] = '\0';
    string[y+1][0] = ' ';
    string[y+1][1] = '\0';
  return;
}

void AL_renderInfo(char *str, SDL_Renderer *mainRenderer){
    SDL_Color color = {0x57, 0x30, 0x00, 0xff};
    char stringArray[4][60];
    TTF_Font *fontFile;
    int x = 250, y = 570;
    
    stringsplit(str, stringArray);
    
    AL_openFontFile(&fontFile, FONT_NAME_2, 25);

    int i;
    AL_renderFont(mainRenderer, color, fontFile, x + 12, y + i * 30, stringArray[0]);

    for (i = 1; i < 3; i++){
        AL_renderFont(mainRenderer, color, fontFile, x, y + i * 30, stringArray[i]);
    }
    
    TTF_CloseFont(fontFile);
    
}

void AL_renderLootValues(SDL_Renderer *mainRenderer, int startGold, int startCrew, int startCannon, int startHealth){
    SDL_Color color = {0x71, 0x49, 0x0E, 0xff};
    TTF_Font *fontFile;
    int x = 600, y = 270;
    
    AL_openFontFile(&fontFile, FONT_NAME_2, 60);
    char stringToRender[20];
    itoa(startCrew, stringToRender, 10);
    
    AL_renderFont(mainRenderer, color, fontFile, x, y, stringToRender);
    itoa(startGold, stringToRender, 10);
    AL_renderFont(mainRenderer, color, fontFile, x, y + 80, stringToRender);
    itoa(startHealth, stringToRender, 10);
    AL_renderFont(mainRenderer, color, fontFile, x, y + 180, stringToRender);
    itoa(startCannon, stringToRender, 10);
    AL_renderFont(mainRenderer, color, fontFile, x+90, y + 260, stringToRender);
    
    TTF_CloseFont(fontFile);
    
}

void AL_renderWeatherValues(SDL_Renderer *mainRenderer, int health, int crew){
    SDL_Color color = {0x71, 0x49, 0x0E, 0xff};
    TTF_Font *fontFile;
    int x = 800, y = 400;
    
    AL_openFontFile(&fontFile, FONT_NAME_2, 80);
    
    char stringToRender[50];
    health *= -1;
    crew *= -1;
    
    itoa(health, stringToRender, 10);
    AL_renderFont(mainRenderer, color, fontFile, x, y, stringToRender);
    itoa(crew, stringToRender, 10);
    AL_renderFont(mainRenderer, color, fontFile, x, y+100, stringToRender);
    
    TTF_CloseFont(fontFile);
}