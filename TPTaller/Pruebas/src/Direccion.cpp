/*
 * Direccion.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
#include "Direccion.h"
#include "Define.h"
Direccion::Direccion() {
	fi =PI/4;

}

Direccion::~Direccion() {
	// TODO Auto-generated destructor stub
}


double Direccion::getFi(){
	return fi;
}

void Direccion::setFi(double fi)
{
	this->fi = fi;
}
