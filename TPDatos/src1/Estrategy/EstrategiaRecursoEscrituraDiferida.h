/*
 * EstrategiaRecursoEscrituraDiferida.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIARECURSOESCRITURADIFERIDA_H_
#define ESTRATEGIARECURSOESCRITURADIFERIDA_H_

#include "EstrategiaRecurso.h"

class EstrategiaRecursoEscrituraDiferida: public EstrategiaRecurso {
public:
	EstrategiaRecursoEscrituraDiferida();
	virtual ~EstrategiaRecursoEscrituraDiferida();
	std::string toString();
	int escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento);

};

#endif /* ESTRATEGIARECURSOESCRITURADIFERIDA_H_ */
