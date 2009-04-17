#include "Rectangulo.h"

Rectangulo::Rectangulo(int altura,int base,Posicion *p){
	
	this->altura = altura;
	this->base = base;
	this->pos = p;
	
}
int Rectangulo::dibujar(){
	std::cout<<"se dibujo un rectangulo \n";
	return 0;
}
int Rectangulo::getAltura(){

	return this->altura;
	
}
int Rectangulo::getBase(){

	return this->base;
	
}
Posicion* Rectangulo::getPosicion(){
	return this->pos;
}