#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
int main_old(int argc, char *argv[]) {
SDL_Event event;
SDL_Surface *screen;
SDL_Surface *imagen;

SDL_Rect rect;
int done = 0;
screen = SDL_SetVideoMode(300,350,16, SDL_SWSURFACE | SDL_DOUBLEBUF );
if(!screen){
printf("No se pudo iniciar la pantalla: %s\n", SDL_GetError());
SDL_Quit();
exit(-1);
}
SDL_WM_SetCaption("Graficador", "Graficador");
imagen = IMG_Load("don.png");
if(!imagen) {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
}

rect.x = 10;
rect.y = 10;
rect.w = imagen->w;
rect.h = imagen->h;
SDL_BlitSurface(imagen, NULL, screen, &rect);
while (done == 0) {
SDL_Flip (screen);
// Comprobando teclas para opciones
while (SDL_PollEvent(&event)) {
// Cerrar la ventana
if (event.type == SDL_QUIT) { done = 1; }
// Pulsando una tecla
if (event.type == SDL_KEYDOWN) {
done = 1;
}
}
}


SDL_FreeSurface(imagen);
SDL_FreeSurface(screen);
SDL_Quit();
printf("\nTodo ha salido bien.\n");
return 0;
}