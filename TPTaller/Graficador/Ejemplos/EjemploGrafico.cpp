#include "SDL.h"
/*
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";
int main2(int argc, char **argv)
{
SDL_Init( SDL_INIT_VIDEO );
SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH,
WINDOW_HEIGHT, 0,
SDL_HWSURFACE | SDL_DOUBLEBUF );
SDL_WM_SetCaption( WINDOW_TITLE, 0 );
SDL_Surface* bitmap = SDL_LoadBMP("bat.bmp");
// Part of the bitmap that we want to draw
SDL_Rect source;
source.x = 24;
source.y = 63;
source.w = 265;
source.h = 244;
// Part of the screen we want to draw the sprite to
SDL_Rect destination;
destination.x = 300;
destination.y = 300;
destination.w = 665;
destination.h = 644;
SDL_Event event;
bool gameRunning = true;
while (gameRunning)
{
if (SDL_PollEvent(&event))
{
if (event.type == SDL_QUIT)
{
gameRunning = false;
}
}
SDL_BlitSurface(bitmap, &source, screen, &destination);
SDL_Flip(screen);
}
SDL_FreeSurface(bitmap);
SDL_Quit();
return 0;
}*/