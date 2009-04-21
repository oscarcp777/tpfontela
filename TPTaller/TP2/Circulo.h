#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Circulo: public Figura{
	
	public: 
		Circulo(std::string id,int radio,Posicion *pos);
		int getRadio();
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();
	private:
		int radio;
		Posicion *pos;

};