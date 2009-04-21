#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Cuadrado: public Figura{

	public: 
		Cuadrado(std::string id,int lado,Posicion *pos);
		int getLado();
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();

	private:
		int lado;
		Posicion *pos;


};