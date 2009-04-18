#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Triangulo: public Figura {


	public: 
		Triangulo(std::string id,Posicion *ver1,Posicion *ver2, Posicion *ver3);
		Posicion* getVertice1();
		Posicion* getVertice2();
		Posicion* getVertice3();
		int dibujar();

	private:
		Posicion *vertice1;
		Posicion *vertice2;
		Posicion *vertice3;



};