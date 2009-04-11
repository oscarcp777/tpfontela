
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
	SDL_Surface *screen, *imagen, *circulo, *circulo_key;
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

	//Cargo las imagenes
	imagen = IMG_Load("don.png");
	if (imagen == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		return 1;
	}
	
	circulo = IMG_Load("circulo.png");
	if (circulo == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		//Libero la estructura
		SDL_FreeSurface(imagen);
		return 1;
	}

	circulo_key = IMG_Load("circulo.png");
	if (circulo_key == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		//Libero la estructura
		SDL_FreeSurface(imagen);
		SDL_FreeSurface(circulo);
		return 1;
	}	

	SDL_SetColorKey (circulo_key, SDL_SRCCOLORKEY, SDL_MapRGB(circulo_key->format, 0, 0, 0));

	//Quiero toda la imagen
	ori.x = 0;
	ori.y = 0;
	ori.w = imagen->w;
	ori.h = imagen->h;

	dest.x = 0;
	dest.y = 0;

	SDL_BlitSurface(imagen, &ori, screen, &dest);

	//dibujo el circulo sin color_key y otro con
	ori.w = circulo->w;
	ori.h = circulo->h;

	dest.x = 30;
	dest.y = 280;

	SDL_BlitSurface(circulo, &ori, screen, &dest);

	dest.x = 140;
	dest.y = 280;

	SDL_BlitSurface(circulo_key, &ori, screen, &dest);

	//Realmente lo muestra.
	SDL_Flip(screen);

	SDL_Delay(5000); 

	//Liberamos todo
	SDL_FreeSurface(imagen);
	SDL_FreeSurface(circulo);
	SDL_FreeSurface(circulo_key);

}

