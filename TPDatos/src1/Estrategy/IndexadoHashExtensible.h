/*
 * IndexadoHashExtensible.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef INDEXADOHASHEXTENSIBLE_H_
#define INDEXADOHASHEXTENSIBLE_H_

#include "EstrategiaIndice.h"

class IndexadoHashExtensible: public EstrategiaIndice {
public:
	IndexadoHashExtensible();
	virtual ~IndexadoHashExtensible();
	int abrir();
	int crear(char* nombre, char* ruta);
	int cerrar();
	int insertar(char* key, int dir);
	int remover(char* key, int dir=-1);
	int buscar(char* key, int dir=-1);
};

#endif /* INDEXADOHASHEXTENSIBLE_H_ */
