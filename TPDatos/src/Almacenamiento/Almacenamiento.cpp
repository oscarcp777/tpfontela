/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"

Almacenamiento::Almacenamiento() {
	// TODO Auto-generated constructor stub

}

Almacenamiento::~Almacenamiento() {
	// TODO Auto-generated destructor stub
}
Compuesto* Almacenamiento::getCompuesto() const
   {
       return compuesto;
   }

   void Almacenamiento::setCompuesto(Compuesto *compuesto)
   {
       this->compuesto = compuesto;
   }
