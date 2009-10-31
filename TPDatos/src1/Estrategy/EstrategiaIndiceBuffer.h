/*
 * EstrategiaIndiceBuffer.h
 *
 *  Created on: 31/10/2009
 *      Author: oscar
 */

#ifndef ESTRATEGIAINDICEBUFFER_H_
#define ESTRATEGIAINDICEBUFFER_H_

#include "EstrategiaIndice.h"
#include <map>
class EstrategiaIndiceBuffer: public EstrategiaIndice {
private:
        map<char*,int> indiceClavesBuffer;
public:
	EstrategiaIndiceBuffer();
	virtual ~EstrategiaIndiceBuffer();
     int abrir();
	 int crear(char* nombre, char* ruta);
	 int cerrar();
	 int insertar(char* key, int dir);
	 int remover(char* key, int dir=-1);
	 int buscar(char* key, int dir=-1);

};

#endif /* ESTRATEGIAINDICEBUFFER_H_ */
