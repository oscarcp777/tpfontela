/*
 * Componente.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Componente.h"



Componente::Componente(int tamanio) {
	// TODO Auto-generated constructor stub
	this->tamanio = tamanio;

}

Componente::~Componente() {
	// TODO Auto-generated destructor stub
}

int Componente::getTamanio(){
    return this->tamanio;
}

void Componente::setTamanio(int tamanio)
{
    this->tamanio = tamanio;
}

