/*
 * FixedFieldBuffer.cpp
 *
 *  Created on: 01/04/2010
 *      Author: richy
 */

#include "FixedFieldBuffer.h"

FixedFieldBuffer::FixedFieldBuffer(int maxFields, int maxBytes):FixedLengthBuffer(maxBytes){
	this->init(maxFields);
}

static int sumFieldSizes(int numFields, int*fieldSize){
	int sum = 0;
	for(int i=0; i<numFields; i++)
		sum +=fieldSize[i];
	return sum;
}

FixedFieldBuffer & FixedFieldBuffer:: operator = (const FixedFieldBuffer & buffer){
	//si la cantidad de campos no es la mimsa o los tamaños no son los mismos no se copia
	if(this->numFields != buffer.numFields) return *this;
	for(int i=0; i<this->numFields; i++)
		if(this->fieldSize[i] != buffer.fieldSize[i]) return *this;
	this->nextField = buffer.nextField;
	FixedFieldBuffer::operator = (buffer);
	return *this;

}
FixedFieldBuffer::FixedFieldBuffer(int maxFields, int* fieldSize):FixedLengthBuffer(sumFieldSizes(maxFields,fieldSize)){
	this->init(maxFields,fieldSize);
}

int FixedFieldBuffer::numberOfFields() const{
	return this->numFields;
}

void FixedFieldBuffer::clear(){
	FixedLengthBuffer::clear();
	this->nextField = 0;
	this->buffer[0] = 0;
	this->packing = 1; //TRUE;
}

int FixedFieldBuffer::addField(int fieldSize){
	this->initialized = 1; //TRUE
	if(this->numFields == this->maxFields) return 0; //FALSE
	if(this->bufferSize + fieldSize > this->maxBytes) return 0; //FALSE
	this->fieldSize[this->numFields] = fieldSize;
	this->numFields++;
	this->bufferSize += fieldSize;
	return 1;//TRUE
}

static const char* headerStr = "Field";
static const int headerStrSize = strlen(headerStr);

int FixedFieldBuffer::readHeader(istream & stream){
	char* str = new char[headerStrSize+1];
	int numFields;
	int* fieldSize;
	int result;
	result = FixedLengthBuffer::readHeader(stream);
	if(result < 0) return -1;

	stream.read(str,headerStrSize);
	if(!stream.good()) return -1;
	if(strncmp(str,headerStr,headerStrSize) != 0) return 0;

	stream.read((char*)&numFields, sizeof(numFields));
	if(!stream.good())return -1;
	fieldSize = new int[numFields];

	for(int i=0; i <numFields; i++)
		stream.read((char*)&fieldSize[i], sizeof(fieldSize[i]));

	if(this->initialized){
		if(numFields != this->numFields) return -1;
		for(int j=0; j<numFields; j++)
			if(fieldSize[j] != this->fieldSize[j]) return -1;
		return stream.tellg();
	}
	this->init(numFields,fieldSize);
	return stream.tellg();


}

int FixedFieldBuffer::writeHeader(ostream & stream) const{
	//a header consists of the
	//fixedLengthBufferHeader
	//fixed     5bytes
	//variable sized record of length fields
	//that describes the file records
	//header record size     2bytes
	//number of fields   4bytes
	//field sizes    4bytes per field
	int result;
	if(!this->initialized) return -1; //cannot write unitialized buffer
	result = FixedLengthBuffer::writeHeader(stream);
	if(!result) return -1;
	stream.write(headerStr,headerStrSize);
	if(!stream.good()) return -1;
	stream.write((char*)&this->numFields, sizeof(this->numFields));
	for(int i=0; i< this->numFields; i++){
		stream.write((char*)&this->fieldSize[i], sizeof(this->fieldSize[i]));
	}
	if(!stream.good()) return -1;
	return stream.tellp();
}

int FixedFieldBuffer::pack(const void* field, int size){
	if(this->nextField == this->numFields || !this->packing)
		return -1; //buffer is full or not packing mode
	int start = this->nextByte; //first byte to be pack
	int packSize = this->fieldSize[nextField]; //number bytes to be packed
	if(size != -1 && packSize != size) return -1;
	memcpy(&this->buffer[start], field, packSize);
	this->nextByte += packSize;
	this->nextField++;
	if(this->nextField == this->numFields){
		this->packing = -1;
		this->nextField = this->nextByte = 0;
	}
	return packSize;

}

int FixedFieldBuffer::unPack(void* field, int maxBytes){
	this->packing = 0; //FALSE
	if(this->nextField == this->numFields) //buffer is full
		return -1;
	int start = this->nextByte; //first byte to be unpacked
	int packSize = this->fieldSize[this->nextField];
	memcpy(field,&this->buffer[start],packSize);
	this->nextByte += packSize;
	this->nextField++;
	if(this->nextField == this->numFields) this->clear(); //all fields unpacked
	return packSize;

}

void FixedFieldBuffer::print(){
	FixedLengthBuffer::print();
	cout<<endl;
	cout<<" \t max fields "<<this->maxFields<< " and actual"<<this->numFields<<endl;
	for(int i=0; i<this->numFields; i++)
		cout<<"\t field "<<i<<" size "<<this->fieldSize[i]<<endl;
	this->buffer[this->bufferSize]=0;
	cout<<" nextByte "<<this->nextByte<<endl;
	cout<<" buffer '"<<this->buffer<<"'"<<endl;
}

int FixedFieldBuffer::init(int maxFields){
	this->clear();
	if(maxFields <0) maxFields=0;
	this->maxFields = maxFields;
	this->fieldSize = new int[this->maxFields];
	this->bufferSize = 0;
	this->numFields = 0;
	return 1;
}

int FixedFieldBuffer::init(int numFields, int* fieldSize){
	//initialize
	this->initialized = 1; //TRUE
	this->init(numFields);

	//addd fields
	for(int j=0; j<this->numFields; j++)
		this->addField(fieldSize[j]);//EN EL LIBRO ESTA ASI PERO CREO QUE ESTA MAL this->addField(this->fieldSize[j]);

	return 1;
}
FixedFieldBuffer::FixedFieldBuffer(const FixedFieldBuffer & ){

}

FixedFieldBuffer::~FixedFieldBuffer(){

}





