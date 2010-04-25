/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockList.h"

FreeBlockList::FreeBlockList(int blockSize)
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
}

FreeBlockList::~FreeBlockList() {
}


int FreeBlockList::open(string name, ios_base::openmode mode){

		int result = this->bTreeFile.open(name.append(".libres"),mode);
		if (!result) return result;
//		//Leo profundidad
//		result = this->readHeight();
//		if (!result) return result;
//		if (this->height > 1)
//					this->root.setIsLeaf(false);
//		//Carga raiz
//		this->bTreeFile.read(this->root);

		return 1;
	}

	int FreeBlockList::create(string name, ios_base::openmode mode){

		int result = this->bTreeFile.create(name.append(".libres"), mode);
		if (!result) return result;
//		//Escribo profundidad
//		result = this->writeHeight();
//		if (!result) return result;
//		//Agrega nodo raiz
//		result = this->bTreeFile.write(this->root);
//		this->root.setRecAddr(result);
		return result != -1;
	}

	int FreeBlockList::close(){

		int result = this->bTreeFile.BufferFile::reWind();
		if (!result) return result;
//		//Escribo profundidad
//		result = this->writeHeight();
//		if (!result) return result;
//		result = this->bTreeFile.write(this->root);
//		if (result == -1) return 0;
////		for (int i = this->height -1 ; i >= 0; i--) {
////			if (this->nodes[i] != NULL)
////				delete this->nodes[i];
////		}
//		delete this->nodes;
		return this->bTreeFile.close();
	}


void FreeBlockList::add(int blockId){

	this->freeBlocks.push_back(blockId);
	this->nBlocks++;
	if (2*this->maxFields -2 < this->freeBlocks.size() ){
		int dirBlock = (this->nBlocks/this->maxFields)*this->blockSize + this->blockSize;
		this->writeSimpleBlock(dirBlock);
	}
	this->pack();
	this->bTreeFile.write(0);

}

int FreeBlockList::get(){

	if (this->nBlocks == 0){
		return -1;
	}

	if (this->freeBlocks.empty()){
		int dirBlock = (this->nBlocks/this->maxFields)*this->blockSize + this->blockSize;
		this->readSimpleBlock(dirBlock);
	}


	this->nBlocks--;
	int addr = this->freeBlocks.back();
	this->freeBlocks.pop_back();
	this->pack();
	this->bTreeFile.write();
	return addr;

}

int FreeBlockList::pack(){
	int result;
	unsigned int i;
	buffer.clear();
//	cout << "BEGIN PACK"<<endl;
//	cout << "Bloques totales: " << nBlocks << endl;
	result = buffer.pack(&this->nBlocks);
	for (i = 0; i<this->freeBlocks.size(); i++){
//		int aux = this->freeBlocks[i];
//		int size = this->freeBlocks.size();
//		cout << "Aux: " << aux << " Size: " << this->freeBlocks.size() << endl;
		result = result && buffer.pack(&(this->freeBlocks[i]));
	}
//	cout << "END PACK"<<endl;
	return result;
}

int FreeBlockList::unpack(){
	int result;
	unsigned int i;
	result = buffer.unPack(&this->nBlocks);
	for (i = 0; i<this->freeBlocks.size(); i++){
		int auxElement;
		result = result && buffer.unPack(&auxElement);
		this->freeBlocks.push_back(auxElement);
	}
	return result;
}

int FreeBlockList::writeSimpleBlock(int addr){
	unsigned int i;
	simpleBuffer.clear();
	for (i = 0; i < this->maxFields; i++) {
		int aux = this->freeBlocks.back();
		cout <<"Moviendo a bloque: " << aux << endl;
		this->simpleBuffer.pack(&(aux));
		this->freeBlocks.pop_back();
		cout << " Size: " << this->freeBlocks.size() << endl;
	}
	return this->bTreeFile.writeFromBuffer(simpleBuffer,addr);
}

int FreeBlockList::readSimpleBlock(int addr){
	unsigned int i;
	simpleBuffer.clear();
	this->bTreeFile.readFromBuffer(simpleBuffer,addr);
	int auxElement;
	for (i = 0; i < this->maxFields; i++) {
		auxElement = 0;
		this->simpleBuffer.unPack(&auxElement);
		cout <<"Sacando de bloque: " << auxElement << endl;
		this->freeBlocks.push_back(auxElement);
	}
	return 1;
}
