/*
 * EstrategiaAlmacenamientoTexto.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOTEXTO_H_
#define ESTRATEGIAALMACENAMIENTOTEXTO_H_
#include "EstrategiaAlmacenamiento.h"
#include <list>
#include <iterator>
class EstrategiaAlmacenamientoTexto: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoTexto();
	virtual ~EstrategiaAlmacenamientoTexto();
    void guardar(Almacenamiento* donde);
};

#endif /* ESTRATEGIAALMACENAMIENTOTEXTO_H_ */
