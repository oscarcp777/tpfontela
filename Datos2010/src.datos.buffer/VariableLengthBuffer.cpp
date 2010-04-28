/*
 * VariableLengthBuffer.cpp
 *
 *  Created on: 01/04/2010
 *      Author: oscar
 */

#include "VariableLengthBuffer.h"

VariableLengthBuffer::VariableLengthBuffer(int maxBytes):
IOBuffer(maxBytes){
init();
}

VariableLengthBuffer::~VariableLengthBuffer() {
}
void VariableLengthBuffer::clear(){
  IOBuffer::clear();
}
int VariableLengthBuffer::read(istream& stream){
   if(stream.eof())return -1;
   int recaddr= stream.tellg();
   clear();
   unsigned short bufferSize;
   stream.read((char*)&bufferSize,sizeof(bufferSize));
   if(!stream.good()){
	   stream.clear(); return -1;
   }
   this->bufferSize=bufferSize;

   if(this->bufferSize>this->maxBytes)return -1; // buffer overflow
   stream.read(this->buffer,this->bufferSize);
   if(!stream.good()){
   	   stream.clear(); return -1;
      }
   return recaddr;

}
int VariableLengthBuffer::write(ostream& stream)const{

	 int recaddr=stream.tellp();
	 unsigned short bufferSize;
	 bufferSize=this->bufferSize;
	 stream.write((char*)&bufferSize,sizeof(bufferSize));
	 if(!stream)return -1;
	 stream.write(this->buffer,this->bufferSize);
	 if(!stream.good())
	   	  return -1;

	 return recaddr;
}

void VariableLengthBuffer::print(){
}

int VariableLengthBuffer::init(){
clear(); return 1;
}





















