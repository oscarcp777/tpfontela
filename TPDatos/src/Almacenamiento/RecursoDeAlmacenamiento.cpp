/*
 * RecursosAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "RecursoDeAlmacenamiento.h"
#include "../Estrategy/EstrategiaRecursoUnAlmacenamiento.h"

RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(Componente* componente, EstrategiaRecurso* eRecurso, EstrategiaAlmacenamiento* eAlmacenamiento, Almacenamiento* alm  ) {
	// TODO Auto-generated constructor stub
	this->almacenamiento = alm;
	this->estrategiaAlmacenamiento = eAlmacenamiento;
	this->estrategiaRecurso = eRecurso;

}
RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(EstrategiaAlmacenamiento* eAlmacenamiento, Almacenamiento* almacenamiento ){
	this->almacenamiento = almacenamiento;
	this->estrategiaAlmacenamiento = eAlmacenamiento;
	this->estrategiaRecurso = new EstrategiaRecursoUnAlmacenamiento();
}

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() {
	delete this->almacenamiento;
	delete this->estrategiaAlmacenamiento ;
	delete this->estrategiaRecurso ;
	//delete this->estrategiaIndice;
}

int RecursoDeAlmacenamiento::leerArchivo(std::string ruta,std::string nombreArchivo){
	this->almacenamiento->setNombreArchivo(nombreArchivo);
	this->almacenamiento->setRuta(ruta);
	return 0;
}

int RecursoDeAlmacenamiento::escribirArchivo(std::string ruta,std::string nombreArchivo){
	this->almacenamiento->setNombreArchivo(nombreArchivo);
	this->almacenamiento->setRuta(ruta);
	this->almacenamiento->abrir();
	this->estrategiaAlmacenamiento->guardar(this->almacenamiento);
	this->almacenamiento->cerrar();
	return 0;
}

int RecursoDeAlmacenamiento::cargarComponente(Componente* componente){
	componente->setTamanio(this->almacenamiento->getTamanio());
	this->estrategiaAlmacenamiento->agregarComponente(this->almacenamiento, componente);
	return 0;
}


//void RecursoDeAlmacenamiento::crearArchivo(){
//	this->estrategiaAlmacenamiento->guardar(this->almacenamiento);
//}


void RecursoDeAlmacenamiento::busquedaSecuencial(Componente* componente, std::string clave){
	this->almacenamiento->abrir();
	this->estrategiaAlmacenamiento->busquedaSecuencial(componente, this->almacenamiento, clave);
	this->almacenamiento->cerrar();
}

std::string RecursoDeAlmacenamiento::toString(){
	std::string almacenamiento="null";
	std::string estrategiaAlmacenamiento="null";
	std::string estrategiaRecurso="null";
	if( this->almacenamiento!=NULL) almacenamiento= this->almacenamiento->toString();
	if(this->estrategiaAlmacenamiento!=NULL)  estrategiaAlmacenamiento=this->estrategiaAlmacenamiento->toString();
	if(this->estrategiaRecurso!=NULL)  estrategiaRecurso=this->estrategiaRecurso->toString();
	std::string devolver="Objetos que contiene el RecursoDeAlmacenamiento \n"+
	almacenamiento+"\n"+
	estrategiaAlmacenamiento+"\n"+
	estrategiaRecurso+"\n";
	return devolver;
}
