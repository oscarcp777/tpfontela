/*
 * RegistroIndice.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "RegistroIndice.h"

RegistroIndice::RegistroIndice(){

}

	RegistroIndice::RegistroIndice(string termino, double pesoGlobal) {
		this->termino = termino;
		this->pesoGlobal = pesoGlobal;
	}

	double RegistroIndice::getPesoGlobal() {
		return pesoGlobal;
	}

	string RegistroIndice::getTermino() {
		return termino;
	}

	RegistroIndice::~RegistroIndice(){

	}
