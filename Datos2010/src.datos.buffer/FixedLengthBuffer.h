/*
 * FixedLengthBuffer.h
 *
 *  Created on: 01/04/2010
 *      Author: richy
 */

#ifndef FIXEDLENGTHBUFFER_H_
#define FIXEDLENGTHBUFFER_H_
#include "IOBuffer.h"

class FixedLengthBuffer: public IOBuffer{

public:
	FixedLengthBuffer(int recordSize = 1000);
	FixedLengthBuffer(const FixedLengthBuffer & buffer);//copy constructor
	virtual ~FixedLengthBuffer();
	void clear();
	int read(istream& stream);
	int write(ostream& stream) const;
	int readHeader(istream& stream);
	int writeHeader(ostream& stream)const;
	void print();
	int sizeOfBuffer() const;
protected:
	int init(int recordSize);
	int changeRecordSize(int recordSize);

};

#endif /* FIXEDLENGTHBUFFER_H_ */
