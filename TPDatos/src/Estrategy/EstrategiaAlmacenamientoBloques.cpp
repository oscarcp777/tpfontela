/*
 * EstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoBloques.h"
using namespace std;
EstrategiaAlmacenamientoBloques::EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoBloques::~EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoBloques::guardar(Almacenamiento* donde){
	int i=1;
	std::list<Componente*>::iterator iteraBloques;
	Bloque* bloque;
	std::string metaData;
	Archivo* archivo=(Archivo*)donde;
	archivo->abrirArchivo();
	iteraBloques = donde->getCompuesto()->iteratorListaDeComponetes();
	if(archivo->getExisteMetaData() == 1){
	metaData = this->getMetaData((Componente*)*((Bloque*)*iteraBloques)->iteratorListaDeComponetes());
	archivo->guardar(metaData.c_str(),donde->getTamanio());
	archivo->setExisteMetaData(0);
	}
   archivo->irAlFinal();
	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		bloque = (Bloque*)*iteraBloques;
		archivo->guardar(bloque->getDatosRegistro().c_str(),bloque->getTamanio());

		iteraBloques++;
		i++;
	}

	archivo->cerrarArchivo();

}


void EstrategiaAlmacenamientoBloques::agregarComponente(Almacenamiento* donde, Componente* componente){
	Bloque* bloque = NULL;
	int i=0;

	std::string registro = generarRegistro(componente);
	componente->setDatosRegistro(registro);
	int cargado = 0;

	if(donde->getCompuesto()->getCantidadDeElelmentos() == 0){
		bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
		donde->getCompuesto()->agregarComponente(bloque);
	}
	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();


	while(cargado == 0){
		i++;
		bloque = (Bloque*)*iter;
		int length=(int)registro.length();
		//componente->setId(bloque->getCantidadDeElelmentos()+1);
		if(bloque->getTamanio()-bloque->getPosicionActual()>length){
			bloque->agregarComponente(componente);
			bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
			cargado = 1;
		}else{
			if(i<donde->getCompuesto()->getCantidadDeElelmentos())
				iter++;
			else{
				bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
				donde->getCompuesto()->agregarComponente(bloque);
				bloque->agregarComponente(componente);
				bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
				cargado = 1;
			}

		}
	}

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }

std::string EstrategiaAlmacenamientoBloques::generarRegistro(Componente* componente){

		  std::stringstream flujo;
		  std::string aux="";
		  std::string registro="";
		  aux = EstrategiaAlmacenamiento::generarRegistro(componente);
		  flujo<< aux.length();
		  registro += flujo.str()+DELIMITADOR+ aux;
		  return registro;
}

std::string EstrategiaAlmacenamientoBloques::getMetaData(Componente* componente){
	 std::stringstream flujo;
	 std::string metaData="";
	 std::string aux="";
	 std::map<std::string,std::string>::iterator it;

	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){

		 aux+= it->first + DELIMITADOR;
	 }
	 flujo<< aux.length();
	 metaData+= flujo.str()+DELIMITADOR+aux;
	 return metaData;
}

void EstrategiaAlmacenamientoBloques::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){


	/*#########################################################################################################################*/
	/*#################    MALDITO RICHY SE TE MORIA NO POR LO QUE HABIA TOCADO YO SINO POR QUE EL STACK DE LA MEMORIA ESTATICA */
	/*#################    SE LLENABA  PARA ESO CREE UN BUFFER CON EL TAMANIO DEL BLOQUE Y ANDA JOYA AHI QUE HACERLO ASI EN TODO
	 *                              JAJAJAJAJAAJ!!                                                                                 ##*/
	/*#########################################################################################################################*/



	// Creo buffer de tamanio length.
	char* buffer = new char[donde->getTamanio() + 1];
    std::string datos;
    std::string valor ;
    vector<string> tokens;
	Archivo* archivo=(Archivo*)donde;
	 vector<string>::iterator the_iterator;
	archivo->abrirArchivo();
	archivo->irAlPrincipio();
	while(!archivo->fin()){
		archivo->leer(buffer,donde->getTamanio());
		datos=buffer;
		std::cout<<"DATOS del bloque: "<<datos<<std::endl;
		StringUtils::Tokenize(datos,tokens,"|");
			   	the_iterator = tokens.begin();
			   	while( the_iterator != tokens.end() ) {
			   		valor = *the_iterator;
			   		++the_iterator;
			     cout<<"dato del campo :"<<valor<<endl;
			   	}
	}
	// Libero el buffer
	delete[] buffer;
	archivo->cerrarArchivo();

}
