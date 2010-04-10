/*
 * Cube.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Cube.h"




Cube::Cube( INT_UNSIGNED sizeOfDispersion){
	this->sizeOfDispersion=sizeOfDispersion;
	this->sizeCube=SIZE_CUBE;
}
Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

int Cube::writeCube(BinaryFile *fileCube, int offsetCube)
{

 return 1;
}



bool Cube::hasSpace(int size){
	// el tamanio del registro mas el espacio minimo necesario que debe de tener el cubo
	//tiene que ser menor que el tamanio libre
	INT_UNSIGNED minimumSpace=size+PORCENT_FREE_CUBE*SIZE_CUBE;
	return(this->sizeFree>minimumSpace);
}



int Cube::readCube(BinaryFile *fileCube, int offsetCube)
{
	 return 1;
}



int Cube::deleteRecord(Record *record)
{
	 return 1;
}



int Cube::addRecord(Record *record)
{
	 return 1;
}



Record *Cube::searchRecord(Record *record)
{
	 return new Record();
}
int Cube::print(TextFile* output){
return 1;
}

