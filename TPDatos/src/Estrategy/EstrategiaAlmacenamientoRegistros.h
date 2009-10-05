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
};

#endif /* ESTRATEGIAALMACENAMIENTOREGISTROS_H_ */
