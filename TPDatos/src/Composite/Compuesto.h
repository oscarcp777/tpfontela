/*
 * Compuesto.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef COMPUESTO_H_
#define COMPUESTO_H_
#include <list>
#include "../Object/Object.h"
#include "Componente.h"
class Compuesto: public Object {
private:
	std::list<Componente*> listaDeComponetes;
public:
	Compuesto();
	virtual ~Compuesto();
	std::list<Componente*>::iterator iteratorListaDeComponetes();
    int getCantidadDeElelmentos();
   void agregarComponente(Componente* componente);

};

#endif /* COMPUESTO_H_ */
