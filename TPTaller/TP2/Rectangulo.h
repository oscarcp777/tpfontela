#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Rectangulo: public Figura {


	public: 
		Rectangulo(int base,int altura, Posicion *pos);
		int getBase();
		int getAltura();
		int dibujar();
		Posicion* getPosicion();

	private:
		int base;
		int altura;
		Posicion *pos;



};