#include "Cuadrado.h"

Cuadrado::Cuadrado(int l,Posicion *p){//,std::string i):Figura(i){
	
	lado = l;
	pos = p;
	
}
int Cuadrado::dibujar(){

	return 0;
}
int Cuadrado::getLado(){

	return lado;
	
}

