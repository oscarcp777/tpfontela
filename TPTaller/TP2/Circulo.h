#include "Figura.h"

class Circulo: public Figura{
	
	public: 
		Circulo(int radio);
		int getRadio();

	private:
		int radio;

};