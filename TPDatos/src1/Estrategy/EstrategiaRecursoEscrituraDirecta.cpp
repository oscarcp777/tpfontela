/*
 * EstrategiaRecursoEscrituraDirecta.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoEscrituraDirecta.h"

EstrategiaRecursoEscrituraDirecta::EstrategiaRecursoEscrituraDirecta() {
	// TODO Auto-generated constructor stub

}

EstrategiaRecursoEscrituraDirecta::~EstrategiaRecursoEscrituraDirecta() {
	// TODO Auto-generated destructor stub
}
int EstrategiaRecursoEscrituraDirecta::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente){

	// guardo en el archivo
	Almacenamiento* archivo=   almacenamientos.at(ALMACENAMIENTO_ARCHIVO);
	archivo->abrir();
	estrategiaAlmacenamiento->altaComponente(archivo, componente);
	archivo->cerrar();
	//guardo en el buffer
	estrategiaAlmacenamiento->altaComponente(almacenamientos.at(ALMACENAMIENTO_BUFFER), componente);
	return 0;
}
std::string EstrategiaRecursoEscrituraDirecta::toString(){
	return "EstrategiaRecursoEscrituraDirecta";
}