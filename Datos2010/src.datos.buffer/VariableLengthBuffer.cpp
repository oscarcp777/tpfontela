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


const char* headerStr="Variable";
const int headerSize=strlen(headerStr);

int VariableLengthBuffer::readHeader(istream& stream){
  char str[headerSize+1];
  int result;
  //lee la cabezera del iobuffer
  result=IOBuffer::readHeader(stream);
  if(!result)return 0;
  stream.read(str,headerSize);
  if(!stream.good())return 0;
  if(strncmp(str,headerStr,headerSize)!=0) return 0;

  return stream.tellg();
}

int VariableLengthBuffer::writeHeader(ostream & stream) const{

  int result;
  //lee la cabezera del iobuffer
  result=IOBuffer::writeHeader(stream);
  if(!result)return 0;
  stream.write(headerStr,headerSize);
  if(!stream.good())return 0;
  return stream.tellp();
}

void VariableLengthBuffer::print(){

}
int VariableLengthBuffer::init(){
clear(); return 1;
}





















