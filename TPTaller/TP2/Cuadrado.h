#include "Figura.h"
#include "Posicion.h"

class Cuadrado: public Figura{

	public: 
		Cuadrado(int lado,Posicion *pos);
		int getLado();

	private:
		int lado;
		Posicion *pos;


};