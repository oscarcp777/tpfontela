/*
 * EstrategiaRecursoUnAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIARECURSOUNALMACENAMIENTO_H_
#define ESTRATEGIARECURSOUNALMACENAMIENTO_H_

#include "EstrategiaRecurso.h"

class EstrategiaRecursoUnAlmacenamiento: public EstrategiaRecurso {
public:
	EstrategiaRecursoUnAlmacenamiento();
	virtual ~EstrategiaRecursoUnAlmacenamiento();
	std::string toString();
	int altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente);
};

#endif /* ESTRATEGIARECURSOUNALMACENAMIENTO_H_ */
