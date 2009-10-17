/*
 * Nodo.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */
#include "NodoRegistro.h"

NodoRegistro::NodoRegistro()
{
	claveRegistro=-1;
	posicionRegistro=-1;
}

NodoRegistro::NodoRegistro(int claveRegistro,long posicionRegistro)
{
	this->claveRegistro=claveRegistro;
	this->posicionRegistro=posicionRegistro;

}

int NodoRegistro::getClaveRegistro(){
	return this->claveRegistro;
}

long NodoRegistro::getPosicionRegistro(){
	return this->posicionRegistro;
}

void NodoRegistro::setClaveRegistro(int claveRegistro){
	this->claveRegistro=claveRegistro;
}
void NodoRegistro::setPosicionRegistro(long posicionRegistro){
	this->posicionRegistro = posicionRegistro;
}

NodoRegistro::~NodoRegistro()
{

}
