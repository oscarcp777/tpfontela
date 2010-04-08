/*
 * RegistroClaveHash.cpp
 *
 *  Created on: 07/11/2009
 *      Author: santiago
 */

#include "RegistroClaveHash.h"

RegistroClaveHash::RegistroClaveHash() {
	// TODO Auto-generated constructor stub
}

string RegistroClaveHash::getClave(){
	return this->clave;
}

void RegistroClaveHash::setClave(string clave){
	this->clave = clave;
}

int RegistroClaveHash::getOffset(){
	return this->offset;
}

void RegistroClaveHash::setOffset(int offset){
	this->offset = offset;
}

RegistroClaveHash::~RegistroClaveHash() {
	// TODO Auto-generated destructor stub
}
