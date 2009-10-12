/*
 * Buffer.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Almacenamiento.h"


class Buffer: public Almacenamiento {
public:
	Buffer();
	virtual ~Buffer();
	std::string toString();

	void guardar(std::string registro);
	void guardar(const char* registro,int tamanioRegistro);
	std::string leer ();
	void leer(void* datos, int tamanio);
};

#endif /* BUFFER_H_ */
