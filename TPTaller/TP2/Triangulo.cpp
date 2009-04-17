#include "Triangulo.h"

Triangulo::Triangulo(Posicion *ver1,Posicion *ver2,Posicion *ver3){
	this->vertice1 = ver1;
	this->vertice2 = ver2;
	this->vertice3 = ver3;
	
}
int Triangulo::dibujar(){
	std::cout<<"se dibujo un triangulo \n";
	return 0;
}

Posicion* Triangulo::getVertice1(){
		
	return this->vertice1;
}

Posicion* Triangulo::getVertice2(){
		
	return this->vertice2;
}

Posicion* Triangulo::getVertice3(){
		
	return this->vertice3;
}