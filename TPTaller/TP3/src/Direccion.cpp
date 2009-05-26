/*
 * Direccion.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
const double PI=3.14159265;

#include "Direccion.h"

Direccion::Direccion() {
	fi = 0;

}

Direccion::~Direccion() {
	// TODO Auto-generated destructor stub
}


float Direccion::getFi(){
	return fi;
}

void Direccion::setFi(float fi)
{
	this->fi = fi;
}
