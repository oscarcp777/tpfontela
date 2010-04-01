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

static const char* headerStr = "Fixed";
static const int headerStrSize = strlen(headerStr);

int FixedLengthBuffer::readHeader(istream& stream){
	char str[headerStrSize+1];
	int recordSize;
	int result;
	//read the IOBUffer header
	result = IOBuffer::readHeader(stream);
	if(result<0) return -1;
	//read the string "Fixed"
	stream.read(str, headerStrSize);
	if(!stream.good()) return -1;
	if(strncmp(str,headerStr,headerStrSize) != 0) return -1;
	stream.read((char*)&recordSize, sizeof(recordSize));
	if(this->initialized){//check for consistency
		if(recordSize != this->bufferSize) return -1;
	}
	else//else initialize the buffer from the header
		this->changeRecordSize(recordSize);  //TODO en el libro falta ese else, verificar si esta bien

	return stream.tellg();

}

int FixedLengthBuffer::writeHeader(ostream& stream){
	//write a buffer header to the beginning of the stream
	//a header consists of the
	//IOBUffer header
	//FIXED  5 bytes
	//record size 2 bytes
	int result;
	if(!this->initialized) return -1; //cannot write untialized buffer
	result = IOBuffer::writeHeader(stream);
	if(!result) return -1;
	stream.write(headerStr,headerStrSize);
	if(!stream.good()) return -1;
	stream.write((char*)&this->bufferSize, sizeof(this->bufferSize));
	if(!stream.good()) return -1;
	return stream.tellp();
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
