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
void EstrategiaRecursoEscrituraDirecta::buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
			list<Componente*> &resultadoDeLABusqueda,
			Componente* componente,
			vector<Almacenamiento*> almacenamientos,
			vector<EstrategiaIndice*> indices,
			string claves)
{

}
int EstrategiaRecursoEscrituraDirecta::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	int i=0;

	for(i=0;i<2;i++){
		Almacenamiento* almacenamiento=   almacenamientos.at(i);
		EstrategiaIndice* estrategiaIndice=indices.at(i);
		string clave=componente->getClave();
		almacenamiento->abrir();
		int pos = estrategiaAlmacenamiento->altaComponente(almacenamiento, componente);
		almacenamiento->cerrar();
		estrategiaIndice->abrir();
		estrategiaIndice->insertar((char*)clave.c_str(),pos);
		estrategiaIndice->cerrar();
	}
	return 0;
}

int EstrategiaRecursoEscrituraDirecta::bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	int i=0;
	for(i=0;i<2;i++){
		Almacenamiento* almacenamiento=   almacenamientos.at(i);
		EstrategiaIndice* estrategiaIndice=indices.at(i);
		estrategiaIndice->abrir();
		int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
		estrategiaIndice->cerrar();
		almacenamiento->abrir();
		estrategiaAlmacenamiento->quitarComponente(almacenamiento, componente, pos);
		almacenamiento->cerrar();
	}
	return 0;
}
std::string EstrategiaRecursoEscrituraDirecta::toString(){
	return "EstrategiaRecursoEscrituraDirecta";
}

void EstrategiaRecursoEscrituraDirecta::busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave){
	Almacenamiento* buffer=   almacenamientos.at(ALMACENAMIENTO_BUFFER);
	componente->setTamanio(buffer->getTamanio());
	buffer->abrir();
	estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente, buffer, clave);
	buffer->cerrar();
}
