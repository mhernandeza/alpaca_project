#include "SDL2/SDL.h"
#include "SDL/SDL_mixer.h"
#include <string.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The event structure
SDL_Event event;
SDL_Window *screen = NULL;
//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

void clean_up();

int main( int argc, char* args[] )
{
    //Quit flag
    int quit = 0;

    //Initialize
    if( init() == 0 )
    {
        return 1;
    }

    //Load the files
    if( load_files() == 0 )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == 0 )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //If 1 was pressed
                if( event.key.keysym.sym == SDLK_1 )
                {
                    //Play the scratch effect
                    if( Mix_PlayChannel( -1, scratch, 0 ) == -1 )
                    {
                        return 1;
                    }
                }
                //If 2 was pressed
                else if( event.key.keysym.sym == SDLK_2 )
                {
                    //Play the high hit effect
                    if( Mix_PlayChannel( -1, high, 0 ) == -1 )
                    {
                        return 1;
                    }
                }
                //If 3 was pressed
                else if( event.key.keysym.sym == SDLK_3 )
                {
                    //Play the medium hit effect
                    if( Mix_PlayChannel( -1, med, 0 ) == -1 )
                    {
                        return 1;
                    }
                }
                //If 4 was pressed
                else if( event.key.keysym.sym == SDLK_4 )
                {
                    //Play the low hit effect
                    if( Mix_PlayChannel( -1, low, 0 ) == -1 )
                    {
                        return 1;
                    }
                }
                //If 9 was pressed
                else if( event.key.keysym.sym == SDLK_9 )
                {
                    //If there is no music playing
                    if( Mix_PlayingMusic() == 0 )
                    {
                        //Play the music
                        if( Mix_PlayMusic( music, -1 ) == -1 )
                        {
                            return 1;
                        }
                    }
                    //If music is being played
                    else
                    {
                        //If the music is paused
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                            //Pause the music
                            Mix_PauseMusic();
                        }
                    }
                }
                //If 0 was pressed
                else if( event.key.keysym.sym == SDLK_0 )
                {
                    //Stop the music
                    Mix_HaltMusic();
                }
            }
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = 1;
            }
        }
    }

    //Free surfaces, fonts and sounds
    //then quit SDL_mixer, SDL_ttf and SDL
    clean_up();

    return 0;
}

int init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 0;
    }

    //Set up the screen
    screen = SDL_CreateWindow("ALKraken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 0;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 0;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Monitor Music", NULL );

    //If everything initialized fine
    return 1;
}

int load_files()
{
    //Load the music
    music = Mix_LoadMUS( "beat.wav" );

    //If there was a problem loading the music
    if( music == NULL )
    {
        return 0;
    }

    //Load the sound effects
    scratch = Mix_LoadWAV( "scratch.wav" );
    high = Mix_LoadWAV( "high.wav" );
    med = Mix_LoadWAV( "medium.wav" );
    low = Mix_LoadWAV( "low.wav" );

    //If there was a problem loading the sound effects
    if( ( scratch == NULL ) || ( high == NULL ) || ( med == NULL ) || ( low == NULL ) )
    {
        return 0;
    }

    //If everything loaded fine
    return 1;
}

void clean_up()
{
    //Free the sound effects
    Mix_FreeChunk( scratch );
    Mix_FreeChunk( high );
    Mix_FreeChunk( med );
    Mix_FreeChunk( low );

    //Free the music
    Mix_FreeMusic( music );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}
