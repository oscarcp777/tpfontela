/*
 * Buffer.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Almacenamiento.h"
#include <stdio.h>


class Buffer: public Almacenamiento {
public:
	Buffer();
	virtual ~Buffer();
	std::string toString();
	std::string getClass();
	void abrir();
	void cerrar();
	void irAlPrincipio();
	bool fin();
	void crear();
	void guardar(std::string registro);
	void guardar(char* buffer, int pos = -1);
	void leer(char* buffer, int pos);


private:
	char* datos;
	int posicionActual;
	int posicionActualLectura;
	int cantElementos;
};

#endif /* BUFFER_H_ */
