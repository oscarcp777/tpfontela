/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"

Almacenamiento::Almacenamiento(Compuesto* comp) {
   this->compuesto=comp;
}

Almacenamiento::~Almacenamiento() {
	// TODO Auto-generated destructor stub
}
Compuesto* Almacenamiento::getCompuesto()
   {
       return compuesto;
   }

   void Almacenamiento::setCompuesto(Compuesto *compuesto)
   {
       this->compuesto = compuesto;
   }
   std::string Almacenamiento::toString(){
   	return "Almacenamiento";
   }
