#ifndef __CUADRADO_H__
#define __CUADRADO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Cuadrado: public Figura{

	public:
		Cuadrado(std::string id,int lado,Posicion *pos);
		~Cuadrado();
		Cuadrado();
		int getLado();
		void setLado(int lado);
		void setPosicion(Posicion * posicion);
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();

	private:
		int lado;
		Posicion *pos;


};

#endif
