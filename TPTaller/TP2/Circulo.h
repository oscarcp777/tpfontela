#include "Figura.h"
#include "Posicion.h"

class Circulo: public Figura{
	
	public: 
		//Circulo(int radio,Posicion *pos,std::string i);
		Circulo(int radio,Posicion *pos);
		int getRadio();
		

	private:
		int radio;
		Posicion *pos;

};