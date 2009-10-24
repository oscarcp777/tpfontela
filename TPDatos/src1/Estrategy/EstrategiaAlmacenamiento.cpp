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



std::string EstrategiaAlmacenamiento::generarMetadata(Componente* componente){
//	 std::stringstream flujo;
	 std::string metaData="";
//	 std::string aux="";
//	 std::map<std::string,std::string>::iterator it;
//
//	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){
//
//		 aux+= it->first + DELIMITADOR;
//	 }
//	 flujo<< aux.length();
//	// metaData+= flujo.str()+DELIMITADOR+aux;
//	 metaData = aux;
	 return metaData;
}

std::string EstrategiaAlmacenamiento::toString(){
   	return "EstrategiaAlmacenamiento";
   }


