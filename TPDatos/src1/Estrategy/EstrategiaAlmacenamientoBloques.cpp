/*
 * EstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoBloques.h"
#include "stdlib.h"
using namespace std;
EstrategiaAlmacenamientoBloques::EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoBloques::~EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoBloques::guardar(Almacenamiento* donde){
//	int i=1;
//	std::list<Componente*>::iterator iteraBloques;
//	Bloque* bloque;
//	std::string metaData;
//
//	iteraBloques = donde->getCompuesto()->iteratorListaDeComponetes();
//	if(donde->getExisteMetaData() == 0){
//		metaData = this->generarMetadata((Componente*)*((Bloque*)*iteraBloques)->iteratorListaDeComponetes());
//		donde->escribirMetadata(metaData);
//	}
//
//	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
//		bloque = (Bloque*)*iteraBloques;
//		donde->guardar(bloque->getDatosRegistro().c_str(),bloque->getTamanio());
//		iteraBloques++;
//		i++;
//	}



}


void EstrategiaAlmacenamientoBloques::altaComponente(Almacenamiento* donde, Componente* componente){
//	Bloque* bloque = NULL;
//	int i=0;
//
//	std::string registro = generarRegistro(componente);
//	componente->setDatosRegistro(registro);
//	int cargado = 0;
//
//	if(donde->getCompuesto()->getCantidadDeElelmentos() == 0){
//		bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
//		donde->getCompuesto()->agregarComponente(bloque);
//	}
//	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
//
//
//	while(cargado == 0){
//		i++;
//		bloque = (Bloque*)*iter;
//		int length=(int)registro.length();
//		//componente->setId(bloque->getCantidadDeElelmentos()+1);
//		if(bloque->getTamanio()-bloque->getPosicionActual()>length){
//			bloque->agregarComponente(componente);
//			bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
//			cargado = 1;
//		}else{
//			if(i<donde->getCompuesto()->getCantidadDeElelmentos())
//				iter++;
//			else{
//				bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
//				donde->getCompuesto()->agregarComponente(bloque);
//				bloque->agregarComponente(componente);
//				bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
//				cargado = 1;
//			}
//
//		}
//	}

}

void EstrategiaAlmacenamientoBloques::quitarComponente(Almacenamiento* donde, Componente* componente){

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }

//std::string EstrategiaAlmacenamientoBloques::generarRegistro(Componente* componente){
//
//		  std::stringstream flujo;
//		  std::string aux="";
//		  std::string registro="";
//		  aux = EstrategiaAlmacenamiento::generarRegistro(componente);
//		  flujo<< aux.length();
//		  registro += flujo.str()+DELIMITADOR+ aux;
//		  return registro;
//}


void EstrategiaAlmacenamientoBloques::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){

	// Creo buffer de tamanio length.
//	char* buffer = new char[donde->getTamanio() + 1];
//	int tam = 0;
//	int cantCaracteresLeidos=0;
//	int i = 0;
//	int posDelimitador=0;
//	int dif = 0;
//    std::string datos="";
//    std::string valor="" ;
//    std::string auxString="";
//    std::string metaData="";
//    bool encontrado = false;
//    int k= 0;
//
//    vector<string> tokens;
//    vector<string> tags;
//	vector<string>::iterator the_iterator;
//	donde->irAlPrincipio();
//
//	metaData = donde->leerMetadata();
//	std::cout<<"metaData "<<metaData<<std::endl;
//	StringUtils::Tokenize(metaData,tags,DELIMITADOR);
//	while(!donde->fin()  && !encontrado ){
//		i=0;
//		cantCaracteresLeidos=0;
//		donde->leer(buffer,donde->getTamanio());
//		//std::cout<<"buffer: "<<buffer<<std::endl;
//		datos="";
//		datos=buffer;
//		std::cout<<"DATOS del bloque: "<<datos<<std::endl;
//
//		auxString = datos;
//		while(cantCaracteresLeidos != (int)datos.length() && !encontrado){
//			k=0;
//			tokens.clear();
//			posDelimitador = datos.find_first_of(DELIMITADOR,cantCaracteresLeidos);
//			auxString = datos.substr(cantCaracteresLeidos,cantCaracteresLeidos+posDelimitador);
//
//			dif = posDelimitador - cantCaracteresLeidos;
//			cantCaracteresLeidos+= dif+1;
//			tam = atoi(auxString.c_str());
//
//			auxString="";
//			auxString = datos.substr(posDelimitador +1,tam);
//
//			cantCaracteresLeidos+= tam;
//			//std::cout<<"string: "<<auxString<<std::endl;
//			StringUtils::Tokenize(auxString,tokens,DELIMITADOR);
//			the_iterator = tokens.begin();
//			while( the_iterator != tokens.end() ) {
//				valor = *the_iterator;
//				++the_iterator;
//				//cout<<"tag: "<<tags.at(k);
//				//cout<<"  dato: "<<valor<<endl;
//				componente->cargarAtributo(tags.at(k),valor);
//
//				if(valor.compare(clave) == 0)
//					encontrado = true;
//
//				k++;
//			}
//			if(encontrado)
//				componente->hidratar();
//
//		}
//	}
//	// Libero el buffer
//	delete[] buffer;

}
