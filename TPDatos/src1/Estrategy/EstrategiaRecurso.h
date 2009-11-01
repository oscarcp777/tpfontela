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
#include "../Estrategy/EstrategiaIndice.h"
using namespace std;
class EstrategiaRecurso :public Object{
public:
	EstrategiaRecurso();
	virtual ~EstrategiaRecurso();
	std::string toString();
	virtual int altaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices)=0;
	virtual int bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices)=0;
	virtual void buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
			list<Componente*> &resultadoDeLABusqueda,
			Componente* componente,
			vector<Almacenamiento*> almacenamientos,
			vector<EstrategiaIndice*> indices,
			string claves)=0;
	virtual void busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave) =0;
};

#endif /* ESTRATEGIARECURSO_H_ */
