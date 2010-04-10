/*
 * Cube.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Cube.h"




Cube::Cube( INT_UNSIGNED sizeOfDispersion, INT_UNSIGNED offset){
	this->offsetCube = offset;
	this->sizeOfDispersion=sizeOfDispersion;
	this->sizeCube=SIZE_CUBE;
	this->sizeFree = SIZE_CUBE;
}
Cube::~Cube() {
	// TODO Auto-generated destructor stub
}
int Cube::loadMetadata(){
    this->buffer->clear();
    this->buffer->packField(&this->sizeFree,sizeof(this->sizeFree));
    this->buffer->packField(&this->numberOfRecords,sizeof(this->numberOfRecords));
    this->buffer->packField(&this->sizeOfDispersion,sizeof(this->sizeOfDispersion));
    return 1;
}
int Cube::writeCube(BinaryFile *fileCube)
{

	//cargo la metadata en el buffer para despues escribirla
    this->loadMetadata();

 return 1;
}

int Cube::redistribute(Cube* newCube){
	return 1;
}


bool Cube::hasSpace(int size){
	// el tamanio del registro mas el espacio minimo necesario que debe de tener el cubo
	//tiene que ser menor que el tamanio libre
	INT_UNSIGNED minimumSpace=size+PORCENT_FREE_CUBE*SIZE_CUBE;
	return(this->sizeFree > minimumSpace);
}



int Cube::readCube(BinaryFile *fileCube, int offsetCube)
{
	 return 1;
}

int Cube::addRecord(Record *record)
{
	 return 1;
}
int Cube::remove(int key){
	return 1;
}

Record *Cube::search(int key)
{
	//TODO buscar clave "key" y devolver un record
	 return new Record();
}


