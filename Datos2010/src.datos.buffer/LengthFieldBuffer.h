/*
 * LengthFieldBuffer.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef LENGTHFIELDBUFFER_H_
#define LENGTHFIELDBUFFER_H_
#include "VariableLengthBuffer.h"
#include <stdio.h>
#include <string.h>
class LengthFieldBuffer: public VariableLengthBuffer {
public:
	/**
	 * constructor con el tamanio maximo del buffer
	 */
	LengthFieldBuffer(int maxBytes=1000);
	/**
	 * constructor cons campos de tamanio especifico
	 */
	LengthFieldBuffer(const LengthFieldBuffer & buffer):VariableLengthBuffer(buffer){}
	virtual ~LengthFieldBuffer();
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

#endif /* LENGTHFIELDBUFFER_H_ */
