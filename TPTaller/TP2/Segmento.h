#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Segmento:public Figura {

	public:
			Segmento(Posicion *inicio, Posicion* fin);
			int dibujar();
			Posicion* getInicio();
			Posicion* getFin();
	private:
			Posicion *inicio;
			Posicion *fin;

};