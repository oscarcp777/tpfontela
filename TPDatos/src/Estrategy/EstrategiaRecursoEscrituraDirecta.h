/*
 * EstrategiaRecursoEscrituraDirecta.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIARECURSOESCRITURADIRECTA_H_
#define ESTRATEGIARECURSOESCRITURADIRECTA_H_

#include "EstrategiaRecurso.h"

class EstrategiaRecursoEscrituraDirecta: public EstrategiaRecurso {
public:
	EstrategiaRecursoEscrituraDirecta();
	virtual ~EstrategiaRecursoEscrituraDirecta();
	std::string toString();
	int escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento);
};

#endif /* ESTRATEGIARECURSOESCRITURADIRECTA_H_ */
