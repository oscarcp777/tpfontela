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
	int altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente);
};

#endif /* ESTRATEGIARECURSOESCRITURADIRECTA_H_ */
