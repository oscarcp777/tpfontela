/*
 * RecursosAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include "Almacenamiento.h"
#include "../Estrategy/EstrategiaRecurso.h"
#include "../Estrategy/EstrategiaAlmacenamiento.h"
#include "../Estrategy/EstrategiaIndice.h"
#include "../Composite/Componente.h"

#ifndef RECURSOSALMACENAMIENTO_H_
#define RECURSOSALMACENAMIENTO_H_

class RecursoDeAlmacenamiento {
public:
	RecursoDeAlmacenamiento(Componente* componente, EstrategiaRecurso* eRecurso, EstrategiaAlmacenamiento* eAlmacenamiento, Almacenamiento* almacenamiento );
	virtual ~RecursoDeAlmacenamiento();

private:
	Almacenamiento* almacenamiento;
	EstrategiaAlmacenamiento* eAlmacenamiento;
	EstrategiaRecurso* eRecurso;
	EstrategiaIndice* eIndice;


};

#endif /* RECURSOSALMACENAMIENTO_H_ */
