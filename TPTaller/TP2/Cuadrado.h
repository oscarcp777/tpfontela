#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Cuadrado: public Figura{

	public: 
		Cuadrado(int lado,Posicion *pos);
		int getLado();
		int dibujar();
		Posicion* getPosicion();

	private:
		int lado;
		Posicion *pos;


};