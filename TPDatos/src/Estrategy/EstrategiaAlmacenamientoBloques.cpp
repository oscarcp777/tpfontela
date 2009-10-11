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
	//this->generarClaves(donde);
	Archivo* archivo=(Archivo*)donde;
	archivo->abrirArchivo(TEXTO);
	int i=1;

	std::list<Componente*>::iterator iteraBloques = donde->getCompuesto()->iteratorListaDeComponetes();

	Bloque* bloque;


	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		bloque = (Bloque*)*iteraBloques;
		//archivo->guardar(bloque->getDatosRegistro().c_str(),bloque->getTamanio());
		archivo->guardar(bloque->getDatosRegistro());
		iteraBloques++;
		i++;
	}

	archivo->cerrarArchivo();

}


void EstrategiaAlmacenamientoBloques::agregarComponente(Almacenamiento* donde, Componente* componente){
	Bloque* bloque = NULL;
	int i=1;

	componente->serializar();
	std::string registro = generarRegistro(componente);
	componente->setDatosRegistro(registro);


	if(donde->getCompuesto()->getCantidadDeElelmentos() == 0){
		bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
		donde->getCompuesto()->agregarComponente(bloque);
	}
	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();

	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		bloque = (Bloque*)*iter;
		componente->setId(bloque->getCantidadDeElelmentos()+1);
         int length=(int)registro.length();
		if(bloque->getTamanio()-bloque->getPosicionActual()>length){
			bloque->agregarComponente(componente);
			bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
		}
		else{
			bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
			donde->getCompuesto()->agregarComponente(bloque);
			bloque->agregarComponente(componente);
		}
		i++;
	}

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }

std::string EstrategiaAlmacenamientoBloques::generarRegistro(Componente* componente){

		  std::stringstream flujo;
		  std::string aux="";
		  std::string registro="";
		  std::map<std::string,std::string>::iterator it;

		  for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){

	           aux+= it->second + DELIMITADOR;
		  }

		  flujo<< aux.length();
		  registro += flujo.str()+DELIMITADOR+ aux;

		return registro;
}
