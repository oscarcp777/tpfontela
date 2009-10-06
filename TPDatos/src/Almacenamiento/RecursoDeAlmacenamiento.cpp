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

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() {
	delete this->almacenamiento;
	delete this->estrategiaAlmacenamiento ;
	delete this->estrategiaRecurso ;
}
RecursoDeAlmacenamiento::RecursoDeAlmacenamiento() {
	            this->almacenamiento = NULL;
				this->estrategiaAlmacenamiento = NULL;
				this->estrategiaRecurso = new EstrategiaRecursoUnAlmacenamiento();
}

void RecursoDeAlmacenamiento::crearArchivo(){
			this->estrategiaAlmacenamiento->guardar(this->almacenamiento);
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
