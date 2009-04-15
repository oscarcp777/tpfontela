#include "Figura.h"
#include "Posicion.h"

class Rectangulo: public Figura {


	public: 
		Rectangulo(int base,int altura, Posicion *pos);
		int getBase();
		int getAltura();
		int dibujar();

	private:
		int base;
		int altura;
		Posicion *pos;



};