#ifndef __RECTANGULO_H__
#define __RECTANGULO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Rectangulo: public Figura {


	public:
		Rectangulo();
		~Rectangulo();
		Rectangulo(std::string id, int base,int altura, Posicion *pos);
		int getBase();
		void setBase(int base);
		int getAltura();
		void setAltura(int altura);
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();
		void setPosicion(Posicion *posicion);
		void calcularRadioDeInfluencia();
		int getX();
		int getY();
	private:
		int base;
		int altura;
		Posicion *pos;
		SDL_Surface *imagenAuxiliar;



};

#endif
