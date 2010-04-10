/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"


Table::Table() {


}

Table::~Table() {
}

int Table::hash(int key){
  return (key % this->sizeTable);
}

int Table::readTable(fstream *fileTable)
{
	return 1;
}



int Table::duplicateTable()
{
	for(unsigned int i= 0 ; i< this->sizeTable; i++ ){
		this->element[i+this->sizeTable] = this->element[i];
	}
	this->sizeTable = this->sizeTable*2;

	return 1;
}

int Table::insert(Record* record){
	int index = this->hash(record->getKey());
	int offset = this->element[index];
	int result = this->loadCube(offset);
	int add;
	if(result == 1){//si pudo cargar el cubo
		add =this->currentCube->addRecord(record);
		if(add != 1){//si no agrego es porque no hay lugar

			Cube* newCube;
			if(this->currentCube->getSizeOfDispersion() == this->sizeTable){
				//tamaño sispersion = tamaño tabla
				this->duplicateTable();
				this->currentCube->setSizeOfDispersion(this->sizeTable);
				this->countsCubes++;
				newCube = new Cube(this->sizeTable,this->countsCubes);
				this->element[index] = this->countsCubes;

			}
			else{//tamaño sispersion <> tamaño tabla
				unsigned int dispersionSize = this->currentCube->getSizeOfDispersion();
				this->currentCube->setSizeOfDispersion(dispersionSize*2);
				this->countsCubes++;
				newCube = new Cube(dispersionSize*2,this->countsCubes);
				for(unsigned int i = index; i<this->sizeTable; i+=newCube->getSizeOfDispersion()){
					this->element[i] = this->countsCubes;
				}
				for(int j = index; j>=0; j-=newCube->getSizeOfDispersion()){
					this->element[j] = this->countsCubes;
				}

			}
			//redistribuir y guardar los cubos en disco
			this->currentCube->redistribute(newCube);
			this->currentCube->writeCube(this->fileCubes);
			newCube->writeCube(fileCubes);
		}

	}
	else//no pudo cargar el cubo
		return -1;

	return 1;
}

int Table::redispersableCubes(INT_UNSIGNED offsetCube)
{
	return 1;
}



Record *Table::search(int key)
{
	return new Record(0,0);
}

void Table::print(fstream *output)
{

}



int Table::writeTable(fstream *fileTable)
{
	return 1;
}





Cube *Table::getNewCube(fstream *fileCubes)
{
	return new Cube(0,0);
}
int Table::loadCube(int offset){
	int res = this->currentCube->readCube(fileCubes,offset);
	return res;
}


Cube *Table::getCurrentCube(INT_UNSIGNED offsetCube,fstream* fileCubo)
{
	return new Cube(0,0);
}

int Table::deleteCube(INT_UNSIGNED offsetCube)
{
	return 1;
}

