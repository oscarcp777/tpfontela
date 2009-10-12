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
    std::string generarRegistro(Componente* componente);
    void agregarComponente(Almacenamiento* donde, Componente* componente);
    std::string getMetaData(Componente* componente);

};

#endif /* ESTRATEGIAALMACENAMIENTOREGISTROS_H_ */
