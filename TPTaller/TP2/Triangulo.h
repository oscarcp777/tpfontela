#ifndef __TRIANGULO_H__
#define __TRIANGULO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Triangulo: public Figura {


	public: 
		Triangulo();
		Triangulo(std::string id,Posicion *ver1,Posicion *ver2, Posicion *ver3);
		Posicion* getVertice1();
		Posicion* getVertice2();
		Posicion* getVertice3();
		int dibujar(SDL_Surface *screen);

	private:
		Posicion *vertice1;
		Posicion *vertice2;
		Posicion *vertice3;
		void graficarPixel(SDL_Surface *screen, int i, int j, Posicion* ejeDeCoordenadas);



};

#endif