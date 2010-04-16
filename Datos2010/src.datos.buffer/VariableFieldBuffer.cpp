/*
 * VariableFieldBuffer.cpp
 *
 *  Created on: 10/04/2010
 *      Author: Santiago
 */

#include "VariableFieldBuffer.h"

VariableFieldBuffer::VariableFieldBuffer(int maxBytes) :FixedLengthBuffer(maxBytes){
init();
}

VariableFieldBuffer::~VariableFieldBuffer() {
}


void VariableFieldBuffer::clear(){
	FixedLengthBuffer::clear();
}
int VariableFieldBuffer::pack(const void* field, int size){
	short len;// longitud de la cadena para ser embalado
	if(size>=0)len=size;
	else len=sizeof((char*)field);
	int start =this->nextByte;
	this->nextByte+=(len+sizeof(len));
	if(this->nextByte>this->maxBytes){return -1;}

	memcpy(&(this->buffer[start]),&len,sizeof(len));
	memcpy(&this->buffer[start+sizeof(len)],field,len);
//	this->bufferSize=this->nextByte;
	return len;
}
int VariableFieldBuffer::unPack(void* field,  int maxBytes){

	short len;// longitud de la cadena para ser embalado
	if(this->nextByte>=this->bufferSize)return -1;// no hay mas campos
	int start =this->nextByte;

	memcpy(&len,&buffer[start],sizeof(len));
	if(maxBytes!=-1&&len>maxBytes)return -1;//campo demasiado largo
	this->nextByte+=len+sizeof(len);
	if(this->nextByte>this->bufferSize)return -1;
	memcpy(field,&buffer[start+sizeof(len)],len);
	if(maxBytes>len||maxBytes==-1)
		((char*)field)[len]=0;//cero terminacion de la cadena
	return len;
}
void VariableFieldBuffer::print(){

}

int VariableFieldBuffer::init(){
	this->initialized=1;
	clear();
	return 1;
}
