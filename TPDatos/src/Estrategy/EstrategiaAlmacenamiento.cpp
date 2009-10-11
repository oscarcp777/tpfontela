/*
 * EstrategiaAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamiento.h"

EstrategiaAlmacenamiento::EstrategiaAlmacenamiento() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamiento::~EstrategiaAlmacenamiento() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamiento::generarClaves(Almacenamiento* donde){
	int i=1;
	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
	Componente* componente;
	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		componente = (Componente*)*iter;
		componente->serializar();
		iter++;
		i++;
	}

}



std::string EstrategiaAlmacenamiento::generarRegistro(Componente* componente){
  return "nada";
}

std::string EstrategiaAlmacenamiento::toString(){
   	return "EstrategiaAlmacenamiento";
   }
void EstrategiaAlmacenamiento::guardar(Almacenamiento* donde){

}
