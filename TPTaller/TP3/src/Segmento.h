#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Segmento:public Figura {

	public:
			Segmento(std::string id,Posicion *inicio, Posicion* fin);
			~Segmento();
			int dibujar(SDL_Surface *screen);
			Posicion* getInicio();
			Posicion* getFin();
		    void calcularRadioDeInfluencia();
	private:
			Posicion *inicio;
			Posicion *fin;

};
