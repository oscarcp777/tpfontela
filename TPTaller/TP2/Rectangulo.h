#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Rectangulo: public Figura {


	public: 
		Rectangulo(std::string id, int base,int altura, Posicion *pos);
		int getBase();
		int getAltura();
		int dibujar(SDL_Surface *screen);
		Posicion* getPosicion();

	private:
		int base;
		int altura;
		Posicion *pos;



};