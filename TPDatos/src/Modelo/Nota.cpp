/*
 * Nota.cpp
 *
 *  Created on: 11/10/2009
 *      Author: richy
 */

#include "Nota.h"

Nota::Nota(int n):Registro(10) {
	// TODO Auto-generated constructor stub
	this->nota = n;
}

Nota::~Nota() {
	// TODO Auto-generated destructor stub
}


void Nota::serializar(){
	std::stringstream flujo;
	flujo<<this->nota;
	this->setAtributo("Nota",flujo.str());
}

void Nota::hidratar(){

}
