/*
 * LengthFieldBuffer.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "LengthFieldBuffer.h"


LengthFieldBuffer::LengthFieldBuffer(int maxBytes):VariableLengthBuffer(maxBytes) {
	init();
}

LengthFieldBuffer::~LengthFieldBuffer() {
	VariableLengthBuffer::clear();
}
void LengthFieldBuffer::clear(){

}
int LengthFieldBuffer::pack(const void* field, int size){
	char str1[]="Sample string";
		  char str2[40];
		  char str3[40];
		  memcpy (str2,str1,strlen(str1)+1);
		  memcpy (str3,"copy successful",16);
	short len;// longitud de la cadena para ser embalado
	if(size>=0)len=size;
	else len=strlen((char*)field);
	int start =this->nextByte;
	this->nextByte+=(len+sizeof(len));
	if(this->nextByte>this->maxBytes){return -1;}

	memcpy(&(this->buffer[start]),&len,sizeof(len));
	memcpy(&this->buffer[start+sizeof(len)],&len,sizeof(len));
	this->bufferSize=this->nextByte;
	return len;
}
int LengthFieldBuffer::unPack(void* field,  int maxBytes){

	short len;// longitud de la cadena para ser embalado
	if(this->nextByte>this->maxBytes)return -1;// no hay mas campos
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
void LengthFieldBuffer::print(){

}
int LengthFieldBuffer::init(){
   this->initialized=1;
   clear();
   return 1;
}










