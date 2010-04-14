/*
 * Cube.cpp
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Cube.h"




Cube::Cube( int sizeOfDispersion, int offset){
	this->offsetCube = offset;
	this->sizeOfDispersion=sizeOfDispersion;
	this->sizeCube=SIZE_CUBE;
	this->numberOfRecords = 0;
	/*EL TAMANIO LIBRE DEL BLOQUE ES LO QUE QUEDA DE LO RESERVO PARA LA METADATA
	 * Y EL PORCENTAJE DE ESPACIO LIBRE QUE GUARDO DE RESGUARDO PARA FUTURAS
	 * MODIFICACIONES DE LO REGISTROS
	 */
	int minumumSpaceFree=PORCENT_FREE_CUBE*this->sizeCube;
	this->sizeFree =this->sizeCube- (minumumSpaceFree+SIZE_METADATA);
	this->buffer= new Buffer(SIZE_CUBE);

}
Cube::~Cube() {
	delete this->buffer;
	list<Record*>::iterator iterRecord;
	Record* record;
	for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){
		record=*iterRecord;
		delete record;
	}
	this->records.clear();
}
int Cube::clear(){
	this->buffer->clear();
	list<Record*>::iterator iterRecord;
	Record* record;
	for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){
		record=*iterRecord;
		delete record;
	}
	this->records.clear();

	return TRUE;
}
int Cube::getDiskPosition(){
	return this->offsetCube*this->sizeCube;
}
int Cube::loadMetadata(){
	this->buffer->unPackField(&this->sizeFree,sizeof(this->sizeFree));
	this->buffer->unPackField(&this->numberOfRecords,sizeof(this->numberOfRecords));
	this->buffer->unPackField(&this->sizeOfDispersion,sizeof(this->sizeOfDispersion));
	return 1;
}
int Cube::writeMetadata(){
	this->buffer->clear();
	this->numberOfRecords=this->records.size();
	this->buffer->packField(&this->sizeFree,sizeof(this->sizeFree));
	this->buffer->packField(&this->numberOfRecords,sizeof(this->numberOfRecords));
	this->buffer->packField(&this->sizeOfDispersion,sizeof(this->sizeOfDispersion));
	return 1;
}
int Cube::writeCube(BinaryFile *fileCube)
{

	//cargo la metadata en el buffer para despues escribirla
	this->writeMetadata();
	list<Record*>::iterator iterRecord;
	Record* record;

	for (iterRecord=this->records.begin(); iterRecord!=this->records.end(); iterRecord++){

		record=*iterRecord;
		int size=record->getSizeDataRecord();
		int key=record->getKey();
		//cout<<"en WRITE CUBE size a pack "<<size<<endl;
		this->buffer->packField(&(size),sizeof(size));
		this->buffer->packField(&key,sizeof(key));
		//cout<<"en WRITE CUBE record->getData() "<<record->getData()<<endl;
		this->buffer->packField(record->getData(),size);

	}
	fileCube->write(this->buffer->getData(),this->sizeCube,this->getDiskPosition());
	fileCube->flush();
	return TRUE;
}
int Cube::addRecordList(Record* record){
  this->records.push_back(record);
  this->sizeFree=this->sizeFree-record->getSizeRecord();
  return TRUE;
}

int Cube::eraseRecordList(list<Record*>::iterator iterRecord,Record* record ){
	this->records.erase(iterRecord);
	this->sizeFree=this->sizeFree+record->getSizeRecord();
	return TRUE;
}

int Cube::reallocate(vector<int> offsetCubes,Record* newRecord,Cube* newCube,int sizeTable){
	list<Record*>::iterator iterRecord = this->records.begin();
		Record* record;
		this->records.push_back(newRecord);//agrego el nuevo registro que produjo el desborde asi lo distribuye
		int max=this->records.size();
		for (int var = 0; var < max; var++) {
			record = *iterRecord;
			if(this->offsetCube != offsetCubes[Hash::hashMod(record->getKey(),sizeTable)]){
				newCube->addRecordList(record);
				this->sizeFree = this->sizeFree+record->getSizeRecord();
				this->records.erase(iterRecord);
				iterRecord--;
			}
			iterRecord++;
		}

	return 1;
}


bool Cube::hasSpace(int size){
	return(this->sizeFree >= size);
}



int Cube::loadCube(BinaryFile *fileCube, int offsetCube){
	this->clear();
	this->setOffsetCube(offsetCube);
	fileCube->read(this->buffer->getData(),this->sizeCube,this->getDiskPosition());
	this->loadMetadata();
	Record* record;
	int size=0;
	int key=0;
	for (int var = 0; var < this->numberOfRecords; var++) {
		record=new Record();
		record->clear();
		this->buffer->unPackField(&(size),sizeof(size));
		this->buffer->unPackField(&key,sizeof(key));
		//*########################################
		 /* TODO NECESITO QUE SEA EL DOBLE DE SIZE SINO SE FUMA PORQUE C++ AGREGA UN /0 QUE COME ESPACIO
		  * PODRIA SER UN POCO MAS GRANDE QUE SIZE Y NO EL DOBLE PERO DEJA EL DOBLE QUE NO MOLESTA
		  */
		char* data=new char[size*2];
		memset(data,0,size*2);
		this->buffer->unPackField(data,size);
		record->setKey(key);
		record->setData(data);
		this->records.push_back(record);
	}

	return 1;
}

int Cube::addRecord(Record *record)
{
	int diferentSize=0;
	Record* recordFound=this->search(record->getKey());
	if(recordFound==NULL){
			this->records.push_back(record);
			this->sizeFree=this->sizeFree-record->getSizeRecord();
			return TRUE;

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
	list<Record*>::iterator iterRecord=this->records.begin();
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
		if(key==record->getKey()){
			cout<<"encontrado en cubo offset: "<<this->offsetCube<<endl;
			return record;
		}
	}
	return NULL;
}


