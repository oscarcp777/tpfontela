/*
 * EstrategiaAlmacenamientoBloques.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOBLOQUES_H_
#define ESTRATEGIAALMACENAMIENTOBLOQUES_H_

#include "EstrategiaAlmacenamiento.h"

class EstrategiaAlmacenamientoBloques: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoBloques();
	virtual ~EstrategiaAlmacenamientoBloques();
	virtual void guardar(Almacenamiento* donde) const;
};

#endif /* ESTRATEGIAALMACENAMIENTOBLOQUES_H_ */
