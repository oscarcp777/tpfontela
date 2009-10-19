/*
 * EstrategiaRecursoUnAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoUnAlmacenamiento.h"

int EstrategiaRecursoUnAlmacenamiento::escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento){
	// guardo en el archivo
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	if(almacenamiento->getClass().compare("Archivo")==0){
		almacenamiento->abrir();
		estrategiaAlmacenamiento->guardar(almacenamiento);
		almacenamiento->cerrar();
	}
	//guardo en el buffer
	if(almacenamiento->toString().compare("Buffer")==0)
		estrategiaAlmacenamiento->guardar( almacenamiento);
	return 0;
	return 0;
}
EstrategiaRecursoUnAlmacenamiento::EstrategiaRecursoUnAlmacenamiento() {

}

EstrategiaRecursoUnAlmacenamiento::~EstrategiaRecursoUnAlmacenamiento() {
	// TODO Auto-generated destructor stub
}
std::string EstrategiaRecursoUnAlmacenamiento::toString(){
	return "EstrategiaRecursoUnAlmacenamiento";
}
