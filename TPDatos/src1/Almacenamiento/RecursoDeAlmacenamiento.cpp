/*
 * RecursosAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "RecursoDeAlmacenamiento.h"
#include "../Estrategy/EstrategiaRecursoUnAlmacenamiento.h"


RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,Almacenamiento* archivo,Almacenamiento* buffer,   EstrategiaRecurso* estrategiaRecurso,EstrategiaIndice* estrategiaIndice ){
	// TODO Auto-generated constructor stub

	if(archivo!=NULL)
		this->almacenamientos.push_back(archivo);
	if(buffer!=NULL)
		this->almacenamientos.push_back(buffer);
	this->estrategiaAlmacenamiento = estrategiaAlmacenamiento;
	this->estrategiaRecurso = estrategiaRecurso;
	this->estrategiaIndice=estrategiaIndice;
}
RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(){

}

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() {

	vector<Almacenamiento*>::iterator the_iterator;
	the_iterator =  this->almacenamientos.begin();
	while( the_iterator != this->almacenamientos.end() ) {
		delete *the_iterator;
		++the_iterator;
	}

	delete this->estrategiaAlmacenamiento ;
	delete this->estrategiaRecurso ;
	delete this->estrategiaIndice ;
}


int RecursoDeAlmacenamiento::alta(Componente* componente){

	componente->setTamanio(this->almacenamientos.at(0)->getTamanio());
	int dir = this->estrategiaRecurso->altaComponente(this->almacenamientos,this->estrategiaAlmacenamiento, componente);
	this->estrategiaIndice->abrir();
	this->estrategiaIndice->insertar((char*)componente->getClave().c_str(),dir);
	this->estrategiaIndice->cerrar();
	return 0;
}
int RecursoDeAlmacenamiento::baja(Componente* componente){
	componente->setTamanio(this->almacenamientos.at(0)->getTamanio());
	this->estrategiaRecurso->bajaComponente(this->almacenamientos,this->estrategiaAlmacenamiento, componente);
	return 0;
}
int RecursoDeAlmacenamiento::modificion(Componente* componente){
	return 0;
}
int RecursoDeAlmacenamiento::buscar(list<Componente*> &resultadoDeLABusqueda,Componente* componente,std::string clave){
	//this->estrategiaRecurso->busquedaSecuencial(this->estrategiaAlmacenamiento,resultadoDeLABusqueda,componente, this->almacenamientos, clave);
	this->estrategiaIndice->abrir();
	int aux = this->estrategiaIndice->buscar((char*)componente->getClave().c_str());
	this->estrategiaIndice->cerrar();
	return aux;
}
void RecursoDeAlmacenamiento::busquedaSecuencial(Componente* componente, std::string clave){

//	Almacenamiento* almacenamiento=   almacenamientos.at(0);
//	componente->setTamanio(almacenamiento->getTamanio());
//	almacenamiento->abrir();
//	this->estrategiaAlmacenamiento->busquedaSecuencial(componente, almacenamiento, clave);
//	almacenamiento->cerrar();
}

std::string RecursoDeAlmacenamiento::toString(){
	std::string almacenamiento="null";
	std::string estrategiaAlmacenamiento="null";
	std::string estrategiaRecurso="null";
	if( this-> almacenamientos.at(0)!=NULL) almacenamiento= almacenamientos.at(0)->toString();
	if(this->estrategiaAlmacenamiento!=NULL)  estrategiaAlmacenamiento=this->estrategiaAlmacenamiento->toString();
	if(this->estrategiaRecurso!=NULL)  estrategiaRecurso=this->estrategiaRecurso->toString();
	std::string devolver="Objetos que contiene el RecursoDeAlmacenamiento \n"+
			almacenamiento+"\n"+
			estrategiaAlmacenamiento+"\n"+
			estrategiaRecurso+"\n";
	return devolver;
}
void RecursoDeAlmacenamiento::cerrar(){
  this->estrategiaAlmacenamiento->getMetadata()->actualizarMetadata(this->almacenamientos.at(0)->getTipoArchivo());
}
