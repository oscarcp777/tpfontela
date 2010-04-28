/*
 * FixedLengthBuffer.cpp
 *
 *  Created on: 01/04/2010
 *      Author: richy
 */

#include "FixedLengthBuffer.h"

FixedLengthBuffer::FixedLengthBuffer(const FixedLengthBuffer & buffer):IOBuffer(buffer) {
	this->init(buffer.bufferSize);

}

FixedLengthBuffer::FixedLengthBuffer(int recordSize):IOBuffer(recordSize){
	this->init(recordSize);
}
FixedLengthBuffer::~FixedLengthBuffer() {
	// TODO Auto-generated destructor stub
}
void FixedLengthBuffer::clear(){
	IOBuffer::clear();
	memset(this->buffer,0,this->bufferSize);
	this->buffer[0]=0;
	this->packing = 1; //TRUE
}
int FixedLengthBuffer::read(istream& stream){
	int recAddr = stream.tellg();
	stream.clear();
	this->clear();
	this->packing = 0; //FALSE
	stream.read(this->buffer, this->bufferSize);
	if(!stream.good()){
		stream.clear();
		return recAddr;
	}
	return recAddr;
}
int FixedLengthBuffer::write(ostream& stream) const{
		int recAddr = stream.tellp();
		stream.write(this->buffer, this->bufferSize);
		if(!stream.good()) return -1;
		return recAddr;
}

void FixedLengthBuffer::print(){
	IOBuffer::print();
	std::cout<<" Fixed ";
}

int FixedLengthBuffer::sizeOfBuffer() const{
	return this->bufferSize;
}

int FixedLengthBuffer::init(int recordSize){
	this->clear();
	this->bufferSize = recordSize;
	return 1;
}

int FixedLengthBuffer::changeRecordSize(int recordSize){
	this->bufferSize = recordSize;
	return 1;
}
