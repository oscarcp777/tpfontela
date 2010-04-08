#include "HashChange.h"

HashChange::HashChange(unsigned long int clave, unsigned int bloqAnterior, unsigned int bloqActual){
	this->clave = clave;
	this->bloqueAnterior = bloqAnterior;
	this->bloqueActual = bloqActual;
}

HashChange::~HashChange(){
	
}

unsigned long int HashChange::getClave(){
	return this->clave;
}

unsigned int HashChange::getBloqueAnterior(){
	return this->bloqueAnterior;
}

unsigned int HashChange::getBloqueActual(){
	return this->bloqueActual;
}

void HashChange::imprimir(){
	cout << "Clave: " << this->getClave() 
		 << " Bloque Anterior: " << this->getBloqueAnterior()
		 << " Bloque Actual: " << this->getBloqueActual() << endl;
}

