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
	int altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices);
	int bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, vector<EstrategiaIndice*> indices);
	void buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
				list<Componente*> &resultadoDeLABusqueda,
				Componente* componente,
				vector<Almacenamiento*> almacenamientos,
				vector<EstrategiaIndice*> indices,
				string claves);
	int actualizarComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices);

};

#endif /* ESTRATEGIARECURSOUNALMACENAMIENTO_H_ */
