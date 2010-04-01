/*
 * IOBuffer.h
 *
 *  Created on: 27/03/2010
 *      Author: oscar
 */

#ifndef IOBUFFER_H_
#define IOBUFFER_H_

#include "../src.datos.utils/Object.h"

class IOBuffer: public Object {
	//an abstract base class for file buffers
public:
	IOBuffer(int maxBytes = 1000);
	IOBuffer & operator = (const IOBuffer &);
	virtual void clear();//clear fields from buffer
	virtual int pack(const void* field, int size=-1) = 0;//set the value of the next field of the buffer
	virtual int unPack(void* field, int maxBytes = -1) = 0; //extract the value of the next field of the buffer
	virtual void print();
	int init(int maxByte);
	//the read and write methods return the address of the record sequential read and write operations
	virtual int read(istream &) = 0; //read a buffer from the stream
	virtual int write(ostream &) const = 0;//write a buffer to the stream
	//these are the direct access read and write operations
	virtual int dRead(istream &, int recRef); //read specified record
	virtual int dWrite(ostream&, int recRef);//write specified record
	//these header operations return the size of the header
	virtual int readHeader(istream &);
	virtual int writeHeader(ostream &) const;

protected:
	int initialized; //true if buffer is initializes
	char* buffer; //character array to hold field values
	int bufferSize; //sum of the sizes of packed fields
	int maxBytes; //maximum number of characters in the buffer
	int nextByte; //index of next byte to be packed/unpacked
	int packing; //true if in packing mode, false if unpacking

	IOBuffer();
	virtual ~IOBuffer();
};

#endif /* IOBUFFER_H_ */
