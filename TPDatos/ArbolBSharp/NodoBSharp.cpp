/*
 * NodoBMas.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */
#include "NodoBSharp.h"

NodoBSharp::NodoBSharp(){

}

// Costructor
NodoBSharp::NodoBSharp(unsigned char cantClavesPorNivel){
	cuentas = 0;

}

int NodoBSharp::getCuentas(){
	return this->cuentas;
}

void NodoBSharp::setCuentas(int cuentas){
	this->cuentas=cuentas;
}

void NodoBSharp::setRama(unsigned char posRama,NodoBSharp*rama){
	this->ramas[posRama]=rama;
}

void NodoBSharp::setNodoRegistro(unsigned char posClave,NodoRegistro*nodoRegistro){
	this->nodosRegistros[posClave]=nodoRegistro;
}

void NodoBSharp::setHoja(NodoBSharp* hoja){
	this->shojas=hoja;
}

NodoBSharp*NodoBSharp::getHoja(){
	return shojas;
}

NodoBSharp* NodoBSharp::getRama(unsigned char posRama){
	return this->ramas[posRama];
}

NodoRegistro* NodoBSharp::getNodoRegistro(unsigned char posClave){
	return this->nodosRegistros[posClave];
}
