/*
 * Nota.cpp
 *
 *  Created on: 11/10/2009
 *      Author: richy
 */

#include "Nota.h"

Nota::Nota(int n) {
	// TODO Auto-generated constructor stub
	this->nota = n;
}

Nota::~Nota() {
	// TODO Auto-generated destructor stub
}


void Nota::serializar(){

	this->setAtributo("Nota",&this->nota,sizeof(this->nota));
}

void Nota::hidratar(){

}
