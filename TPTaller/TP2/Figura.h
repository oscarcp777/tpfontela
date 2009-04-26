#ifndef _FIGURA_H_
#define _FIGURA_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_main.h>

class Figura{

	public:
		 virtual int dibujar(SDL_Surface *screen)=0; //metodo virtual puro 
		 
		 std::string getId();
		 std::string getIdTextura();
		 void setIdTextura(std::string idTextura);
	protected:
		std::string id;
		std::string idTextura;
		SDL_Color color;
		SDL_Surface *imagen; //donde se guarda la imagen en caso de tenerla
	
		
		void putpixel(SDL_Surface *screen, int x, int y, SDL_Color color);
		SDL_Color getpixel(SDL_Surface *imagen, int x, int y);

};
#endif