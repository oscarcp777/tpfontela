/*
 * EstrategiaRecurso.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIARECURSO_H_
#define ESTRATEGIARECURSO_H_
#include "../Object/Object.h"
#include "../Almacenamiento/Almacenamiento.h"
#include "../Estrategy/EstrategiaAlmacenamiento.h"

class EstrategiaRecurso :public Object{
public:
	EstrategiaRecurso();
	virtual ~EstrategiaRecurso();
	std::string toString();
	virtual int altaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente)=0;
	virtual int bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, int pos)=0;
	virtual void busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave) =0;
};

#endif /* ESTRATEGIARECURSO_H_ */
