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

	void guardar(std::string registro);
	void guardar(const char* registro,int tamanioRegistro);
	std::string leer ();
	void leer(void* datos, int tamanio);
	bool fin();

private:
	char* datos;
	int posicionActual;
};

#endif /* BUFFER_H_ */
