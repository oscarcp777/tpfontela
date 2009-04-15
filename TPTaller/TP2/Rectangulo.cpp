#include "Rectangulo.h"

Rectangulo::Rectangulo(int altura,int base,Posicion *p){
	
	altura = altura;
	base = base;
	pos = p;
	
}
int Rectangulo::dibujar(){

	return 0;
}
int Rectangulo::getAltura(){

	return altura;
	
}
int Rectangulo::getBase(){

	return base;
	
}