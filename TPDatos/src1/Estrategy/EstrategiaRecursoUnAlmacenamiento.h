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
	void busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave);
};

#endif /* ESTRATEGIARECURSOUNALMACENAMIENTO_H_ */
