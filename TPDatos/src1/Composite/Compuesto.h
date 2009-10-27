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
protected:
	std::list<Componente*> listaDeComponetes;
public:
	Compuesto();
	virtual ~Compuesto();
	std::string toString();
	std::list<Componente*>::iterator iteratorListaDeComponetes();
    int getCantidadDeElelmentos();
   void agregarComponente(Componente* componente);
   void removerComponente(Componente* componente);
};

#endif /* COMPUESTO_H_ */
