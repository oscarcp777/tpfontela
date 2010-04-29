/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockController.h"

/**
 *	Clase encargada de administrar las direcciones de bloques liberados por alguna estructura de almacenamiento
 *	de datos. Ésta clase mediante los métodos add y get, carga y recupera direcciones de bloques libres
 *	respectivamente.
 *	Su funcionamiento no es predecible, puede devolver los bloques en orden indeterminado según su estructura,
 *	si no tiene bloques libres para devolver devuelve -1.
 */
FreeBlockController::FreeBlockController(int blockSize)
	:buffer(2*(blockSize/sizeof(int)),2*blockSize),
	 simpleBuffer(blockSize/sizeof(int),blockSize),
	 bTreeFile(buffer){
	this->blockSize = blockSize;
	unsigned int i;
	this->maxFields = blockSize/sizeof(int);
	for (i = 0; i < (2*this->maxFields); i++) {
		this->buffer.addField(sizeof(int));
	}
	for (i = 0; i < this->maxFields; i++) {
		this->simpleBuffer.addField(sizeof(int));
	}
	this->nBlocks = 0;
	this->nBlocksDoubleBuffer = 0;
}

FreeBlockController::~FreeBlockController() {
}

/**
 * Llamar a este método con el mismo nombre y modo del archivo de datos usado, el archivo de bloques libres
 * tendra la extensión .free
 */
int FreeBlockController::open(string name, ios_base::openmode mode){

		int result = this->bTreeFile.open(name.append(".free"),mode);
		if (!result) return result;
		this->bTreeFile.read(0);
		this->unpack();
		return 1;
}

/**
 * Llamar a este método con el mismo nombre y modo del archivo de datos usado, el archivo de bloques libres
 * tendra la extensión .free
 */
int FreeBlockController::create(string name, ios_base::openmode mode){

	int result = this->bTreeFile.create(name.append(".free"), mode);
	if (!result) return result;
	return result != -1;
}

int FreeBlockController::close(){

	int result = this->bTreeFile.BufferFile::reWind();
	if (!result) return result;
	return this->bTreeFile.close();
}


void FreeBlockController::add(int blockId){

	this->freeBlocks.push_back(blockId);
	this->nBlocks++;
	this->nBlocksDoubleBuffer++;
	if (2*this->maxFields -2 < this->freeBlocks.size() ){
		int dirBlock = (this->nBlocks/this->maxFields)*this->blockSize + this->blockSize;
		this->writeSimpleBlock(dirBlock);
	}
	this->pack();
	this->bTreeFile.write(0);

}

int FreeBlockController::get(){

	if (this->nBlocks == 0){
		return -1;
	}

	if (this->freeBlocks.empty()){
		int dirBlock = (this->nBlocks/this->maxFields)*this->blockSize + this->blockSize;
		this->readSimpleBlock(dirBlock);
	}

	this->nBlocks--;
	this->nBlocksDoubleBuffer--;
	int addr = this->freeBlocks.back();
	this->freeBlocks.pop_back();
	this->pack();
	this->bTreeFile.write(0);
	return addr;

}

void FreeBlockController::print(){
	unsigned int i;
	for (i = 0; i < this->freeBlocks.size(); ++i) {
		cout<<"Elemento["<<i<<"]: "<<this->freeBlocks[i]<<endl;
	}
}

int FreeBlockController::getSize(){
	return this->nBlocks;
}

int FreeBlockController::pack(){
	int result;
	unsigned int i;
	buffer.clear();
	result = buffer.pack(&this->nBlocks);
	result = buffer.pack(&this->nBlocksDoubleBuffer);
	for (i = 0; i<this->freeBlocks.size(); i++){
		result = result && buffer.pack(&(this->freeBlocks[i]));
	}
	return result;
}

int FreeBlockController::unpack(){
	int result;
	int i;
	result = buffer.unPack(&this->nBlocks);
	result = buffer.unPack(&this->nBlocksDoubleBuffer);
	for (i = 0; i< this->nBlocksDoubleBuffer; i++){
		int auxElement;
		result = result && buffer.unPack(&auxElement);
		this->freeBlocks.push_back(auxElement);
	}
	return result;
}

int FreeBlockController::writeSimpleBlock(int addr){
	unsigned int i;
	simpleBuffer.clear();
	this->nBlocksDoubleBuffer-=this->maxFields;
	for (i = 0; i < this->maxFields; i++) {
		int aux = this->freeBlocks.back();
#ifdef DEBUG
		cout <<"Moviendo a bloque "<<addr/this->blockSize - 1<<": " << aux << endl;
#endif
		this->simpleBuffer.pack(&(aux));
		this->freeBlocks.pop_back();
	}	
	return this->bTreeFile.writeFromBuffer(simpleBuffer,addr);
}

int FreeBlockController::readSimpleBlock(int addr){
	unsigned int i;
	simpleBuffer.clear();
	this->nBlocksDoubleBuffer+=this->maxFields;
	this->bTreeFile.readFromBuffer(simpleBuffer,addr);
	int auxElement;
	for (i = 0; i < this->maxFields; i++) {
		auxElement = 0;
		this->simpleBuffer.unPack(&auxElement);
#ifdef DEBUG
		cout <<"Sacando de bloque "<< addr/this->blockSize - 1<<": " << auxElement << endl;
#endif
		this->freeBlocks.push_back(auxElement);
	}
	return 1;
}
