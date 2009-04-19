#include <SDL.h>

int main_old(int argc, char* argv[])
{
	SDL_Surface *screen;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("error al iniciar SDL: %s\n", SDL_GetError());
		exit(1);
	}

	//Antes de salir de la aplicacion, llama al SDL_Quit
	atexit(SDL_Quit);
	
	screen = SDL_SetVideoMode(400, 400, 16, 0);
	if (screen == NULL)
	{
		printf("error al setear el modo de video: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption("Hola mundo!", "Hola Mundo!");

	SDL_Event ev;
	while(true) {
		while(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT){
				printf(">El usuario quiere salir.\n");
				printf(">SDL Terminado.\n");

				return 0;
			}
		}
	}

	return 0;
}


