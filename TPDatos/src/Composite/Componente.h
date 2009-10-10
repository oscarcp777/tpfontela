/*
 * Componente.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef COMPONENTE_H_
#define COMPONENTE_H_
#include <iostream>

#include "../Object/Object.h"
class Componente :public Object {

private:
	int tamanio;

public:

   virtual	void serializar()const=0;
	virtual void hidratar()const=0;
	Componente(int tamanio);
    Componente();
	virtual ~Componente();

    int getTamanio();

    void setTamanio(int tamanio);

};

#endif /* COMPONENTE_H_ */
