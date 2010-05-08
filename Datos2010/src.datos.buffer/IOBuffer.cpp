/*
 * IOBuffer.cpp
 *
 *  Created on: 27/03/2010
 *      Author: oscar
 */

#include "IOBuffer.h"

IOBuffer::IOBuffer(int maxBytes) {
	this->init(maxBytes);

}

IOBuffer::~IOBuffer() {

	delete []this->buffer;
}

IOBuffer & IOBuffer::operator = (const IOBuffer & buffer){
	if(this->maxBytes < buffer.bufferSize) return *this; //fails
	this->initialized = buffer.initialized;
	this->bufferSize = buffer.bufferSize;
	memcpy(this->buffer, buffer.buffer, buffer.bufferSize);
	this->nextByte = buffer.nextByte;
	this->packing = buffer.packing;
	return *this;
}
	void IOBuffer::clear(){
		this->nextByte = 0;
		this->packing = 1; //true
	}
	void IOBuffer::print(){
		std::cout<<"maxBytes: "<<this->maxBytes<<" BufferSize "<<this->bufferSize;
	}

	int IOBuffer::init(int maxBytes){
		this->initialized = 0;//false
		if(maxBytes < 0) maxBytes = 0;
		this->maxBytes = maxBytes;
		this->buffer = new char[this->maxBytes];
		this->bufferSize = 0;
		this->clear();
		return 1;
	}

	int IOBuffer::dRead(istream & stream, int recRef){
		stream.seekg(recRef, ios::beg);
		if(stream.tellg() != recRef) return -1;
		return this->read(stream);

	}

	int IOBuffer::dWrite(ostream& stream, int recRef){
		stream.seekp(recRef, ios::beg);
		if(stream.tellp() != recRef) return -1;
		return this->write(stream);
	}

