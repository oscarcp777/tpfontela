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
	this->buffer= new Buffer(SIZE_CUBE);
	this->numberOfRecords=0;
}
Cube::~Cube() {
	delete this->buffer;
	list<Record*>::iterator iterRecord;
		Record* record;
		for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){
			record=*iterRecord;
				delete record;
		}
}
int Cube::getDiskPosition(){
   return this->offsetCube*this->sizeCube;
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
	list<Record*>::iterator iterRecord;
	Record* record;

	for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){

		record=*iterRecord;
		int size=record->getSizeRecord();
		int key=record->getKey();
		this->buffer->packField(&(size),sizeof(record->getSizeRecord()));
		this->buffer->packField(&key,sizeof(record->getSizeRecord()));
		this->buffer->packField(record->getData(),sizeof(record->getData()));

	}
    fileCube->write(this->buffer->getData(),sizeof(record->getSizeRecord()),this->getDiskPosition());
	return TRUE;
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



int Cube::readCube(BinaryFile *fileCube)
{

	return 1;
}

int Cube::addRecord(Record *record)
{
	int diferentSize=0;
	Record* recordFound=this->search(record->getKey());
	if(recordFound==NULL){// si no lo encontro me fijo si hay espacio para el
		if(this->hasSpace(record->getSizeRecord())){
			this->records.push_back(record);
			return TRUE;
		}else{
			return FALSE;
		}
	}else{// si lo encontro lo actualizo
		if(record->getSizeRecord()>recordFound->getSizeRecord()){
			diferentSize=record->getSizeRecord()-recordFound->getSizeRecord();
			if(!this->hasSpace(diferentSize))
				return FALSE;
		}
		recordFound->setData(record->getData());
		delete record;


	}

	return TRUE;
}
int Cube::remove(int key){
	list<Record*>::iterator iterRecord;
	int found=FALSE;
	Record* record;
	int max=this->records.size();
	for (int var = 0; var <= max; ++var) {
		record = *iterRecord;
		if(key==record->getKey()){
			found=TRUE;
			delete record;
			this->records.erase(iterRecord);
			break;
		}
		iterRecord++;
	}
	return found;

}

Record *Cube::search(int key)
{
	list<Record*>::iterator iterRecord;
	Record* record;
	for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){
		record=*iterRecord;
		if(key==record->getKey())
			return record;
	}
	return NULL;
}


