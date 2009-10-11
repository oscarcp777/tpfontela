/*
 * EstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoBloques.h"

EstrategiaAlmacenamientoBloques::EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoBloques::~EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoBloques::guardar(Almacenamiento* donde){
	this->generarClaves(donde);
	Archivo* archivo=(Archivo*)donde;
	archivo->abrirArchivo(TEXTO);
	int i=1;
	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
	Componente* componente;

	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		componente = (Componente*)*iter;
		archivo->guardar(generarRegistro(componente));
		iter++;
		i++;
	}

	archivo->cerrarArchivo();

}


void EstrategiaAlmacenamientoBloques::agregarComponente(Componente* componente){

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }
std::string EstrategiaAlmacenamientoBloques::generarRegistro(Componente* componente){

	return "hola";
}
