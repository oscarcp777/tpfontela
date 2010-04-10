/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"


Table::Table() {
	this->fileCubes = new BinaryFile();
	this->fileCubesFree = new BinaryFile();
	this->fileTable = new BinaryFile();
}

Table::~Table() {
	delete this->fileCubes;
	delete this->fileCubesFree;
	delete this->fileTable;
}
int Table::createFiles(string fileName){
	this->fileCubes->create(fileName+EXT_CUBE);
	this->fileCubesFree->create(fileName+EXT_FREE_CUBE);
	this->fileTable->create(fileName+EXT_TABLE);
	return 0;
}
int Table::openFiles(string fileName){
	this->fileCubes->open(fileName+EXT_CUBE);
	this->fileCubesFree->open(fileName+EXT_FREE_CUBE);
	this->fileTable->open(fileName+EXT_TABLE);
	return 0;
}

int Table::hash(int key){
  return (key % this->sizeTable);
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
					this->element[i] = newCube->getOffsetCube();
				}
				for(int j = index; j>=0; j-=newCube->getSizeOfDispersion()){
					this->element[j] = newCube->getOffsetCube();
				}

			}
			//redistribuir y guardar los cubos en disco
			this->currentCube->redistribute(newCube);
			this->currentCube->writeCube(this->fileCubes);
			newCube->writeCube(fileCubes);
			//TODO delete newCube
			//TODO delete this->currentCube
		}

	}
	else//no pudo cargar el cubo
		return -1;

	return 1;
}

int Table::loadCube(int offset){
	int res = this->currentCube->readCube(fileCubes,offset);
	return res;
}

Record *Table::search(int key)
{
	int index = this->hash(key);
	int offset = this->element[index];
	int result = this->loadCube(offset);
	if(result)
		return this->currentCube->search(key);
	else
		return NULL;
}
int Table::remove(int key){
	int index = this->hash(key);
	int offset = this->element[index];
	int result = this->loadCube(offset);
	if(result){

		this->currentCube->remove(key);
		if(this->currentCube->getNumberOfRecords() == 0){//si queda vacio
			int indexUp = index - (this->currentCube->getSizeOfDispersion()/2);
			int indexDown = index + (this->currentCube->getSizeOfDispersion()/2);
			//comparo los indices dedsde el indice donde estaba (td/2) hacia arriba y hacia abajo
			//si NO son iguales no puedo borrar el cubo por lo que queda vacio
			if( this->element[indexUp] == this->element[indexDown]){
				//TODO borrar el cubo y marcarlo como vacio como lo hago?? PENSAR
				//this->currentCube->remove(); y poner en el archivo como bloque libre??
				this->element[index] = this->element[indexUp];
				this->loadCube(this->element[index]);

				for(unsigned int i = index; i<this->sizeTable; i+=this->currentCube->getSizeOfDispersion()){
					this->element[i] = this->currentCube->getOffsetCube();
				}
				for(int j = index; j>=0; j-=this->currentCube->getSizeOfDispersion()){
					this->element[j] = this->currentCube->getOffsetCube();
				}
				int sizeDisp = this->currentCube->getSizeOfDispersion();
				this->currentCube->setSizeOfDispersion(sizeDisp/2);
				//guardo el cubo con su nuevo numero de dispersion
				this->currentCube->writeCube(this->fileCubes);

				if(isTableDuplicate() == 1){//comparo las dos mitades de la tabla
					 //truncandola a la mitad porque son iguales
					collapse();

				}
			}
		}
	}
	else
		return -1;

	return 1;
}
int Table::isTableDuplicate(){
	int num = this->element.size()/2;
	for(int i=0; i<num; i++){
		if(this->element[i] != this->element[num+i])
			return 0;
	}
	return 1;
}
void Table::collapse(){
	this->element.resize(this->element.size()/2);
}
void Table::print(fstream *output)
{

}

int Table::deleteCube(INT_UNSIGNED offsetCube){
	return 1;
}

int Table::readTable(fstream *fileTable)
{
	return 1;
}


int Table::writeTable(fstream *fileTable)
{
	return 1;
}



