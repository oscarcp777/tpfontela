#include "Figura.h"
#include "Posicion.h"

class Circulo: public Figura{
	
	public: 
		Circulo(int radio,Posicion *pos);
		int getRadio();
		int dibujar();

	private:
		int radio;
		Posicion *pos;

};