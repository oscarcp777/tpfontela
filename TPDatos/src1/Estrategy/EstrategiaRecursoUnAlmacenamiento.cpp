/*
 * EstrategiaRecursoUnAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoUnAlmacenamiento.h"


int EstrategiaRecursoUnAlmacenamiento::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	string clave=componente->getClave();
	almacenamiento->abrir();
	int pos = estrategiaAlmacenamiento->altaComponente(almacenamiento, componente);
	almacenamiento->cerrar();
	estrategiaIndice->abrir();
	estrategiaIndice->insertar((char*)clave.c_str(),pos);
	estrategiaIndice->cerrar();
	return pos;
}
int EstrategiaRecursoUnAlmacenamiento::bajaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, vector<EstrategiaIndice*> indices){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	estrategiaIndice->abrir();
	int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
	estrategiaIndice->cerrar();
	almacenamiento->abrir();
	estrategiaAlmacenamiento->quitarComponente(almacenamiento, componente, pos);
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
void EstrategiaRecursoUnAlmacenamiento::buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
		list<Componente*> &resultadoDeLABusqueda,
		Componente* componente,
		vector<Almacenamiento*> almacenamientos,
		vector<EstrategiaIndice*> indices,
		string claves){
	vector<string> vec;
	StringUtils::Tokenize(claves,vec," ");
	string clave=StringUtils::getValorTag(estrategiaAlmacenamiento->getMetadata()->getClavePrimaria(),vec);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	//this->estrategiaRecurso->busquedaSecuencial(this->estrategiaAlmacenamiento,resultadoDeLABusqueda,componente, this->almacenamientos, clave);
	estrategiaIndice->abrir();
	cout<<" clave "<<clave<<endl;
	int aux = estrategiaIndice->buscar((char*)clave.c_str());
	estrategiaIndice->cerrar();
	cout<<" registro encontrado posicion :"<<aux<<endl;
}
void EstrategiaRecursoUnAlmacenamiento::busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	componente->setTamanio(almacenamiento->getTamanio());
	almacenamiento->abrir();
	estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente, almacenamiento, clave);
	almacenamiento->cerrar();
}
