#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Segmento:public Figura {

	public:
			Segmento(std::string id,Posicion *inicio, Posicion* fin);
			int dibujar();
			Posicion* getInicio();
			Posicion* getFin();
	private:
			Posicion *inicio;
			Posicion *fin;

};