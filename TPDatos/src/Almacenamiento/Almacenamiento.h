/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ALMACENAMIENTO_H_
#define ALMACENAMIENTO_H_
#include "../Composite/Compuesto.h"
class Almacenamiento {
private:
	Compuesto* compuesto;
public:
	Almacenamiento();
	virtual ~Almacenamiento();
    Compuesto *getCompuesto();

    void setCompuesto(Compuesto *compuesto);
};

#endif /* ALMACENAMIENTO_H_ */
