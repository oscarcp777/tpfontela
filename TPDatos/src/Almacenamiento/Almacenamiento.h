/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ALMACENAMIENTO_H_
#define ALMACENAMIENTO_H_



#include "../Composite/Compuesto.h"
#include "../Composite/Componente.h"
#include "../Object/Object.h"
class Almacenamiento:public Object{
private:
	Compuesto* compuesto;
public:
	Almacenamiento(Componente* comp);
	virtual ~Almacenamiento();
    Compuesto *getCompuesto();
    std::string toString();
    void setCompuesto(Compuesto *compuesto);
};

#endif /* ALMACENAMIENTO_H_ */
