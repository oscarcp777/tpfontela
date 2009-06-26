/*
 * Direccion.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
#include "Direccion.h"
#include "Define.h"
#include <iostream>
Direccion::Direccion() {
	fi = PI/4;

}

Direccion::~Direccion() {
	 if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Direccion"<<std::endl;

}


double Direccion::getFi(){
	return fi;
}

void Direccion::setFi(double fi)
{
	this->fi = fi;
}
