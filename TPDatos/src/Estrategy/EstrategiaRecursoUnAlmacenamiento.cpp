/*
 * EstrategiaRecursoUnAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoUnAlmacenamiento.h"

int EstrategiaRecursoUnAlmacenamiento::escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	almacenamiento->abrir();
	estrategiaAlmacenamiento->guardar(almacenamiento);
	almacenamiento->cerrar();
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
