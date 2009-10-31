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
    void guardar(Almacenamiento* donde);

    int altaComponente(Almacenamiento* donde, Componente* componente);
    void quitarComponente(Almacenamiento* donde, Componente* componente, int pos);
    void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave);

};

#endif /* ESTRATEGIAALMACENAMIENTOREGISTROS_H_ */
