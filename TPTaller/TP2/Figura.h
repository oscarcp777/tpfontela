#ifndef _FIGURA_H_
#define _FIGURA_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include "Color.h"

class Figura{

	public:
		 virtual int dibujar(SDL_Surface *screen)=0; //metodo virtual puro

		 std::string getId();
		 std::string getIdTextura();
		 void setIdTextura(std::string idTextura);
		 static SDL_Surface* ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
		 static void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		 static Uint32 ReadPixel(SDL_Surface *surface, int x, int y);
         Color* getColorLinea();
         void setColorLinea(Color *colorLinea);
         Color* Figura::getColorFigura();
          void Figura::setColorFigura(Color *colorFigura);


protected:
		std::string id;
		std::string idTextura;
		SDL_Color color;
		Color* colorFigura;
		Color* colorLinea;
		SDL_Surface *imagen; //donde se guarda la imagen en caso de tenerla


		void putpixel(SDL_Surface *screen, int x, int y, SDL_Color color);
		SDL_Color getpixel(SDL_Surface *imagen, int x, int y);
		void dibujarLinea(SDL_Color color,SDL_Surface *screen ,int x1, int y1, int x2, int y2);
		void plot( SDL_Surface* surface, int x, int y, SDL_Color color);

};
#endif
