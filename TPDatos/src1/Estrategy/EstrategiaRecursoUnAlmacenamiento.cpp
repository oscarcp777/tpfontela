/*
 * EstrategiaRecursoUnAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoUnAlmacenamiento.h"

int EstrategiaRecursoUnAlmacenamiento::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	almacenamiento->abrir();
	int pos = estrategiaAlmacenamiento->altaComponente(almacenamiento, componente);
	almacenamiento->cerrar();
	return pos;
}
int EstrategiaRecursoUnAlmacenamiento::bajaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	almacenamiento->abrir();
	estrategiaAlmacenamiento->quitarComponente(almacenamiento, componente);
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

void EstrategiaRecursoUnAlmacenamiento::busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave){
		Almacenamiento* almacenamiento=   almacenamientos.at(0);
		componente->setTamanio(almacenamiento->getTamanio());
		almacenamiento->abrir();
		estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente, almacenamiento, clave);
		almacenamiento->cerrar();
}
