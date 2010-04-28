/*
 * FixedFieldBuffer.h
 *
 *  Created on: 01/04/2010
 *      Author: richy
 */

#ifndef FIXEDFIELDBUFFER_H_
#define FIXEDFIELDBUFFER_H_
#include "FixedLengthBuffer.h"

class FixedFieldBuffer:public FixedLengthBuffer {
public:
	FixedFieldBuffer(int maxFields, int maxBytes = 1000);
	FixedFieldBuffer(int maxFields, int* fieldSize);
	FixedFieldBuffer(const FixedFieldBuffer & );
	virtual ~FixedFieldBuffer();
	FixedFieldBuffer & operator = (const FixedFieldBuffer & buffer);
	void clear();
	int addField(int fieldSize);//define the next field
	int pack(const void* field, int size = -1);//set the value of the next field of the bufer
	int unPack(void* field, int maxBytes = -1);//extract the value of the next field of the buffer
	void print();
	int numberOfFields() const;
	int init(int maxFields);
	int init(int numFields, int* fieldSize);

protected:
	int* fieldSize; //array to hold field sizes
	int maxFields; //maximum number of fields
	int numFields; //actual number of defined fields
	int nextField; //index of next field to be packed/unpacked

};

#endif /* FIXEDFIELDBUFFER_H_ */

