/*
 * FabricaDeRecursosDeAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "FabricaDeRecursosDeAlmacenamiento.h"

FabricaDeRecursosDeAlmacenamiento::FabricaDeRecursosDeAlmacenamiento() {
	// TODO Auto-generated constructor stub

}


void FabricaDeRecursosDeAlmacenamiento::RecursoDeAlmacenamientoEnArchivo(std::string nombreArchivo, std::string eAlmacenamiento /*"texto","registros","bloques"*/,Componente* componente){
	if (eAlmacenamiento.compare("texto")==0){
		new RecursoDeAlmacenamiento(componente, new EstrategiaRecursoUnAlmacenamiento(), new EstrategiaAlmacenamientoTexto(), new Archivo(/*nombreArchivo, componente*/) );

	}

}

FabricaDeRecursosDeAlmacenamiento::~FabricaDeRecursosDeAlmacenamiento() {
	// TODO Auto-generated destructor stub
}
