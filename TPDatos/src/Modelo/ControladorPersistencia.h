/*
 * ControladorPersistencia.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */
#include "Alumno.h"
#include "Persistidor.h"


#ifndef CONTROLADORPERSISTENCIA_H_
#define CONTROLADORPERSISTENCIA_H_

class ControladorPersistencia {
public:
	ControladorPersistencia(Alumno* alumno);
	virtual ~ControladorPersistencia();
	void guardar();
	void recuperar();

private:
	Alumno* alumno;

};

#endif /* CONTROLADORPERSISTENCIA_H_ */
