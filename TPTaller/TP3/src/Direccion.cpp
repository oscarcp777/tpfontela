/*
 * Direccion.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
const double PI=3.14159265;

#include "Direccion.h"

Direccion::Direccion() {
	fi = PI/4;
	//fi = 0;

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
