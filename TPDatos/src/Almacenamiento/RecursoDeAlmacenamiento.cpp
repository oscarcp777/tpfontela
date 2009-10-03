/*
 * RecursosAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "RecursoDeAlmacenamiento.h"

RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(Componente* componente, EstrategiaRecurso* eRecurso, EstrategiaAlmacenamiento* eAlmacenamiento, Almacenamiento* alm  ) {
	// TODO Auto-generated constructor stub
		this->almacenamiento = alm;
		this->eAlmacenamiento = eAlmacenamiento;
		this->eRecurso = eRecurso;
		//this->eIndice = ?�;

}

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() {
	// TODO Auto-generated destructor stub
}
