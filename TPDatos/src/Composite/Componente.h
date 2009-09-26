/*
 * Componente.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef COMPONENTE_H_
#define COMPONENTE_H_


class Componente{

private:
	int tamanio;

public:
	Componente(int tamanio);

	virtual ~Componente();

    int getTamanio();

    void setTamanio(int tamanio);

};

#endif /* COMPONENTE_H_ */
