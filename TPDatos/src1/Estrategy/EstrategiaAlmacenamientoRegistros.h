/*
 * EstrategiaAlmacenamientoRegistros.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOREGISTROS_H_
#define ESTRATEGIAALMACENAMIENTOREGISTROS_H_

#include "EstrategiaAlmacenamiento.h"

class EstrategiaAlmacenamientoRegistros: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoRegistros();
	virtual ~EstrategiaAlmacenamientoRegistros();
    int altaComponente(Almacenamiento* donde, Componente* componente);
    void quitarComponente(Almacenamiento* donde, Componente* componente, int pos);
    void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
    void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
};

#endif /* ESTRATEGIAALMACENAMIENTOREGISTROS_H_ */
