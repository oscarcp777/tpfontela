/*
 * ControladorPersistencia.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "ControladorPersistencia.h"


ControladorPersistencia::ControladorPersistencia(Alumno* alumno) {
	// TODO Auto-generated constructor stub
	this->alumno = alumno;
}

void ControladorPersistencia::guardar(){
	Persistidor::guardar("alumno.txt", this->alumno);
}

void ControladorPersistencia::recuperar(){
	Persistidor::recuperar("alumno.txt", this->alumno);
}


ControladorPersistencia::~ControladorPersistencia() {
	// TODO Auto-generated destructor stub
}
