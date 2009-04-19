#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
	SDL_Surface *screen, *imagen, *lente, *circulo_key;
	SDL_Rect ori, dest;
	int lente_x, lente_y, circulo_x, circulo_y;
	
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
	imagen = IMG_Load("Fondo de escritorio.bmp");
	if (imagen == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		return 1;
	}
	
	lente = IMG_Load("lente.png");
	if (lente == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		//Libero la estructura
		SDL_FreeSurface(imagen);
		return 1;
	}
	SDL_SetAlpha(lente, SDL_SRCALPHA, 0);

	circulo_key = IMG_Load("circulo.png");
	if (circulo_key == NULL) {
		printf("error al cargar imagen:%s\n", SDL_GetError());
		//Libero la estructura
		SDL_FreeSurface(imagen);
		SDL_FreeSurface(lente);
		return 1;
	}	

	SDL_SetColorKey (circulo_key, SDL_SRCCOLORKEY, SDL_MapRGB(circulo_key->format, 0, 0, 0));
	SDL_SetAlpha(circulo_key, SDL_SRCALPHA, 128);

	//Quiero toda la imagen
	ori.x = 0;
	ori.y = 0;
	ori.w = imagen->w;
	ori.h = imagen->h;

	dest.x = 0;
	dest.y = 0;

	SDL_BlitSurface(imagen, &ori, screen, &dest);

	ori.w = lente->w;
	ori.h = lente->h;

	dest.x = lente_x = 30;
	dest.y = lente_y = 280;

	SDL_BlitSurface(lente, &ori, screen, &dest);

	dest.x = circulo_x = 140;
	dest.y = circulo_y = 280;

	SDL_BlitSurface(circulo_key, &ori, screen, &dest);

	for(int i=0; i<1000; i++) {
		ori.w = imagen->w;
		ori.h = imagen->h;

		dest.x = 0;
		dest.y = 0;
		SDL_BlitSurface(imagen, &ori, screen, &dest);
		
		ori.w = lente->w;
		ori.h = lente->h;

		lente_x++;
		lente_y++;
		
		dest.x = lente_x % 640;
		dest.y = lente_y % 480;

		SDL_BlitSurface(lente, &ori, screen, &dest);

		circulo_x++;
		circulo_y++;
		dest.x = circulo_x % 640;
		dest.y = circulo_y % 480;

		SDL_BlitSurface(circulo_key, &ori, screen, &dest);
				
		//Realmente lo muestra.
		SDL_Flip(screen);
	}


	//Liberamos todo
	SDL_FreeSurface(imagen);
	SDL_FreeSurface(lente);
	SDL_FreeSurface(circulo_key);

}

