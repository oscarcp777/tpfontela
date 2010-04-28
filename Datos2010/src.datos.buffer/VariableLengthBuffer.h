/*
 * VariableLengthBuffer.h
 *
 *  Created on: 01/04/2010
 *      Author: oscar
 */

#ifndef VARIABLELENGTHBUFFER_H_
#define VARIABLELENGTHBUFFER_H_

#include "IOBuffer.h"

class VariableLengthBuffer: public IOBuffer {
	/**
	 * clase abstracta diseñada para soportar registros de longitud variable
	 * y lo campos pueden ser de una variedad de tipos
	 */
public:
	VariableLengthBuffer(int maxBytes=1000);
	virtual ~VariableLengthBuffer();
	VariableLengthBuffer(const VariableLengthBuffer & buffer):
		IOBuffer(buffer){}
	/**
	 * limpia los campos del buffer
	 */
	void clear();
	//the read and write methods return the address of the record sequential read and write operations
	int read(istream &); //read a buffer from the stream
	int write(ostream &) const ;//write a buffer to the stream
	//these header operations return the size of the header
	int packFixLen(void*,int);
    int packDelimeted(void*,int);
    int packLenght(void*,int);
    void print() ;
    /**
     * return retorno el tamanio actual de buffer
     */
    int sizeOfBuffer()const;
   int init();



};


#endif /* VARIABLELENGTHBUFFER_H_ */
