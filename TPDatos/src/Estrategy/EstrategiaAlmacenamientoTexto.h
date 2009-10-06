/*
 * EstrategiaAlmacenamientoTexto.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOTEXTO_H_
#define ESTRATEGIAALMACENAMIENTOTEXTO_H_
#include "EstrategiaAlmacenamiento.h"

class EstrategiaAlmacenamientoTexto: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoTexto();
	virtual ~EstrategiaAlmacenamientoTexto();
	virtual void guardar(Almacenamiento* donde) const;
};

#endif /* ESTRATEGIAALMACENAMIENTOTEXTO_H_ */
