/*
 * Registro.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Registro.h"


Registro::Registro(int tamanio):Componente(tamanio) {


}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}




void Registro::setAtributo(std::string etiqueta, std::string valor){
	this->getMapaAtributos()[etiqueta]=valor;

//	this->registro += etiqueta;
//	this->registro += "=";
//	this->registro += valor;
//	this->registro += DELIMITADOR;
}

std::string Registro::getAtributo(std::string etiqueta){
	return this->getMapaAtributos()[etiqueta];
}

