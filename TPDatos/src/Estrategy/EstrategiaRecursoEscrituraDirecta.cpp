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
int EstrategiaRecursoEscrituraDirecta::escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento){

	// guardo en el archivo
	Almacenamiento* archivo=   almacenamientos.at(ALMACENAMIENTO_ARCHIVO);
	archivo->abrir();
	estrategiaAlmacenamiento->guardar(archivo);
	archivo->cerrar();
	//guardo en el buffer
	estrategiaAlmacenamiento->guardar( almacenamientos.at(ALMACENAMIENTO_BUFFER));
	return 0;
}
std::string EstrategiaRecursoEscrituraDirecta::toString(){
	return "EstrategiaRecursoEscrituraDirecta";
}
