/*
 * Cube.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Cube.h"




Cube::Cube( INT_UNSIGNED sizeOfDispersion){
	this->sizeOfDispersion=sizeOfDispersion;
}
Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

int Cube::writeCube(fstream *fileCube, int offsetCube)
{
 return 1;
}



bool Cube::hasSpace(int size)
{
	 return 1;
}



int Cube::readCube(fstream *fileCube, int offsetCube)
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


