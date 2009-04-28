#ifndef __CIRCULO_H__
#define __CIRCULO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Circulo: public Figura{
	
	public: 
		Circulo(void);
		Circulo(std::string id,int radio,Posicion *pos);
		int getRadio();
		void setRadio(int radio);
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();
		~Circulo();
	private:
		int radio;
		Posicion *pos;

};

#endif