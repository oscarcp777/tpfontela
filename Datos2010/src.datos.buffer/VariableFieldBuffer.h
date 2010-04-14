/*
 * VariableFieldBuffer.h
 *
 *  Created on: 10/04/2010
 *      Author: Santiago
 */

#ifndef VARIABLEFIELDBUFFER_H_
#define VARIABLEFIELDBUFFER_H_

#include "FixedLengthBuffer.h"

class VariableFieldBuffer :public FixedLengthBuffer {
public:
	VariableFieldBuffer(int maxBytes=1000);
	virtual ~VariableFieldBuffer();


	/**
	 * limpia los campos de buffer
	 */
	void clear();
	/**
	 *setea el valor al siguiente campo del buffer
	 *si el size =-1 uso strlen(str) en la longitudes de la etiqueta
	 *@return retorna la cantidad de bytes del enpaquetado si -1 si hay error
	 */
	int pack(const void* field,  int size=-1);
	/**
	 *extrae el valor al siguiente campo del buffer
	 *return reotrna el numero de bytes extraidos
	 */
	int unPack(void* field,  int maxBytes=-1);
	void print() ;
	int init();
};

#endif /* VARIABLEFIELDBUFFER_H_ */
