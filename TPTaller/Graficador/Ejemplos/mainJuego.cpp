#include <stdlib.h>
#include <string.h>
#include <math.h>
#if defined(_MSC_VER)
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif
#include "gp.h"

// Screen surface
SDL_Surface *gScreen;
// Surface that contains the tiles
SDL_Surface *gTiles;
// Surface that contains the font
SDL_Surface *gFont;
// Texture surface
SDL_Surface *gTexture;

// Look-up table
unsigned short *gLut;
// Distance mask
unsigned int *gMask; 

// Pointer to the joystick interface
SDL_Joystick *gJoystick = NULL;

// Total number of collectibles
int gCollectibleCount;
// Number of collectibles taken
int gCollectiblesTaken;
// Array of collectibles
collectible *gCollectible;

// Last iteration's tick value
int gLastTick;
// Level start tick
int gLevelStartTick;
// Current level
int gCurrentLevel;

// Player's position
float gXPos;
float gYPos;

// Player's motion vector
float gXMov;
float gYMov;

// Player's start position
float gStartX;
float gStartY;

// Player's roll vector
float gXRoll;
float gYRoll;

// Player's ball's roll value
float gRoll;

// Player's key status
int gKeyLeft;
int gKeyRight;
int gKeyUp;
int gKeyDown;

// Player's score
int gScore;

// Camera position
float gCameraX;
float gCameraY;

// Level data
unsigned char *gLevel;  
// Level collision data
unsigned char *gColliders; 

// Level name string
char *gLevelName;
// Level time limit
int gLevelTime;

// Dynamic level width and height, in tiles
int gLevelWidth;
int gLevelHeight;

// Offset of character data per character
int gFontOfs[256];
// Width of character data per character
int gFontWidth[256];

// Original vertices
vertex *gVtx;
// Transformed vertices
vertex *gRVtx;

// Scheduled game state
int gNextState;
// Current game state
int gGameState;
// State start tick
int gStateStartTick;

void init()
{
  SDL_Surface *temp = SDL_LoadBMP("texture17.bmp");
  gTexture = SDL_ConvertSurface(temp, gScreen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  gLut = new unsigned short[WIDTH * HEIGHT * 4];
  gMask = new unsigned int[WIDTH * HEIGHT * 4];

  int i, j, k;
  for (i = 0; i < HEIGHT * 2; i++)
  {
    for (j = 0; j < WIDTH * 2; j++)
    {
      int xdist = j - (WIDTH);
      int ydist = i - (HEIGHT);
     
      // round
      int distance = (int)sqrt((float)(xdist * xdist + ydist * ydist));
  
      // square
      //int distance = (abs(xdist) > abs(ydist)) ? abs(xdist) : abs(ydist);
  
      // diamond
      //int distance = (abs(xdist) + abs(ydist)) / 2;
     
      // flower
      //distance += (int)(sin(atan2((float)xdist, (float)ydist) * 5) * 8);
     
      if (distance <= 0) distance = 1;
  
      int d = distance;
      if (d > 255) d = 255;
      gMask[i * WIDTH * 2 + j] = d * 0x010101;
     
      distance = (64 * 256 / distance) & 0xff;
  
      int angle = (int)(((atan2((float)xdist, (float)ydist) / PI) + 1.0f) * 128);
  
      gLut[i * WIDTH * 2 + j] = (distance << 8) + angle;
    }
  }
  gVtx = new vertex[BALLVTXCOUNT];
  gRVtx = new vertex[BALLVTXCOUNT];

  for (i = 0; i < BALLVTXCOUNT; i++)
  {
    gVtx[i].x = (rand() % 32768) - 16384.0f;
    gVtx[i].y = (rand() % 32768) - 16384.0f;
    gVtx[i].z = (rand() % 32768) - 16384.0f;
    float len = (float)sqrt(gVtx[i].x * gVtx[i].x + 
                            gVtx[i].y * gVtx[i].y + 
                            gVtx[i].z * gVtx[i].z);
    if (len != 0)
    {
      gVtx[i].x /= len;
      gVtx[i].y /= len;
      gVtx[i].z /= len;
    }
  }

  if (SDL_NumJoysticks() > 0)
  {
    gJoystick = SDL_JoystickOpen(0);    
    if (SDL_JoystickNumAxes(gJoystick) < 2)
    {
      // Not enough axes for our use; don't use the joystick.
      SDL_JoystickClose(gJoystick);
      gJoystick = NULL;
    }
  }

  gCollectible = NULL;
  gLevel = NULL;
  gColliders = NULL;
  gLevelName = NULL;
  gScore = 0;
  gCurrentLevel = 0;
  gGameState = STATE_NONE;
  gNextState = STATE_ENTRY;

  temp = SDL_LoadBMP("tiles2.bmp");
  gTiles = SDL_ConvertSurface(temp, gScreen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("font.bmp");
  gFont = SDL_ConvertSurface(temp, gScreen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  if (SDL_MUSTLOCK(gFont))
    if (SDL_LockSurface(gFont) < 0) 
      return;

  for (k = 0; k < gFont->h / gFont->w; k++)
  {
    gFontOfs[k] = gFont->w;
    gFontWidth[k] = 0;
    for (i = 0; i < gFont->w; i++)
    {
      for (j = 0; j < gFont->w; j++)
      {
        if (((unsigned int*)gFont->pixels)[(i + k * gFont->w) * 
                                           (gFont->pitch / 4) + j] != 0) 
        {
          if (j < gFontOfs[k])
            gFontOfs[k] = j;

          if (j > gFontWidth[k])
            gFontWidth[k] = j;
        }
      }
    }
    gFontWidth[k] -= gFontOfs[k];
  }

  // Unlock if needed
  if (SDL_MUSTLOCK(gFont)) 
    SDL_UnlockSurface(gFont);
}

void deinit()
{
  if (gJoystick)
    SDL_JoystickClose(gJoystick);
}

void changestate()
{
    // Things that need to be done when leaving a state
    switch (gGameState)
    {
    case STATE_ENDLEVEL: 
        gCurrentLevel++;
        break;
    }

    // Switch state
    gGameState = gNextState;

    // Things that need to be done when entering a state
    switch (gGameState)
    {
    case STATE_ENTRY: 
        reset();
        break;
    case STATE_INGAME:
        gLastTick = SDL_GetTicks(); 
        gLevelStartTick = SDL_GetTicks(); 
        break;
    }
    
    gStateStartTick = SDL_GetTicks();
}

void render()
{
    while (gNextState != gGameState)
        changestate();
    switch (gGameState)
    {
    case STATE_ENTRY:
    case STATE_READY:
    case STATE_INGAME:
    case STATE_FALLOFF:
    case STATE_ENDLEVEL:
        rendergame();
        break;
    }
}

// Entry point
int main(int argc, char *argv[])
{
  // Initialize SDL's subsystems
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) 
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // make sure our deinit gets called at shutdown.
  atexit(deinit);
    
  // Attempt to create a WIDTHxHEIGHT window with 32bit pixels.
  gScreen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
  
  init();

  // If we fail, return error.
  if (gScreen == NULL) 
  {
    fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
    exit(1);
  }

  // Main loop: loop forever.
  while (1)
  {
    // Render stuff
    render();

    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
      switch (event.type) 
      {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          gKeyLeft = 1;
          break;
        case SDLK_RIGHT:
          gKeyRight = 1;
          break;
        case SDLK_UP:
          gKeyUp = 1;
          break;
        case SDLK_DOWN:
          gKeyDown = 1;
          break;
        }
        break;
      case SDL_KEYUP:                  
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          // If escape is pressed, return (and thus, quit)
          return 0;
        case SDLK_LEFT:
          gKeyLeft = 0;
          break;
        case SDLK_RIGHT:
          gKeyRight = 0;
          break;
        case SDLK_UP:
          gKeyUp = 0;
          break;
        case SDLK_DOWN:
          gKeyDown = 0;
          break;
        case SDLK_RETURN:
        case SDLK_SPACE:
          if (gGameState == STATE_ENDLEVEL)
          {
            gNextState = STATE_ENTRY;
          }
          break;
        }
        break;
      case SDL_QUIT:
          return(0);
      }
    }
  }
  return 0;
}
