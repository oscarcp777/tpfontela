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
	int altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente);
	int bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, int pos);
	void busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave);

};

#endif /* ESTRATEGIARECURSOESCRITURADIFERIDA_H_ */
