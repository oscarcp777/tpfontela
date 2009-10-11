/*
 * EstrategiaAlmacenamientoTexto.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoTexto.h"

EstrategiaAlmacenamientoTexto::EstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoTexto::~EstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoTexto::guardar(Almacenamiento* donde){
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



std::string EstrategiaAlmacenamientoTexto::toString(){
   	return "EstrategiaAlmacenamientoTexto";
   }
