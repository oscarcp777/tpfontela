#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
int main(int argc, char *argv[])
{
	SDL_Surface *screen, *imagen;
	SDL_Rect ori, dest;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error al iniciar SDL\n");
		return 1;
	}

	atexit(SDL_Quit);
	
	screen = SDL_SetVideoMode(640, 480, 16, 0);

	if (screen == NULL) {
		printf("Error al setear video:%s\n", SDL_GetError());
		return 1;
	}

	//Cargo la imagen
	imagen = IMG_Load("Fondo de escritorio.bmp");
	if (imagen == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		return 1;
	}

	//Quiero toda la imagen
	ori.x = 0;
	ori.y = 0;
	ori.w = imagen->w;
	ori.h = imagen->h;

	dest.x = 0;
	dest.y = 0;

	SDL_BlitSurface(imagen, &ori, screen, &dest);

	//Realmente lo muestra.
	SDL_Flip(screen);

	SDL_Delay(5000); 
}
