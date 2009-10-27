/*
 * Elemento.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "Elemento.h"

Elemento::Elemento(){

}

Elemento::Elemento(int hijoIzq, int hijoDer, string clave) {

	this->hijoIzq = hijoIzq;
	this->hijoDer = hijoDer;
	this->clave = clave;

}

string Elemento::getClave(){
	return clave;
}

int Elemento::getHijoIzq() {
	return hijoIzq;
}

int Elemento::getHijoDer() {
	return hijoDer;
}

void Elemento::setClave(string clave) {
	this->clave = clave;
}

void Elemento::setHijoDer(int hijoDer) {
	this->hijoDer = hijoDer;
}

void Elemento::setHijoIzq(int hijoIzq) {
	this->hijoIzq = hijoIzq;
}
