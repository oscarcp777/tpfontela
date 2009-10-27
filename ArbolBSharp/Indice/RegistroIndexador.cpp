/*
 * RegistroIndexador.cpp
 *
 *  Created on: Oct 26, 2009
 *      Author: dan
 */

#include "RegistroIndexador.h"

RegistroIndexador::RegistroIndexador(){

}

string RegistroIndexador::getTermino(){
	return termino;
}

void RegistroIndexador::setTermino(string termino){
	this->termino=termino;
}

RegistroIndexador::~RegistroIndexador(){

}
