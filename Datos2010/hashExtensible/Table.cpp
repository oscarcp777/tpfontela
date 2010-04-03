/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"
#include "Cube.h"
#include "CubeBuffer.h"
#include "../src.datos.buffer/BufferFile.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>


const int maxKeySize = 12;
//using namespace std;

Table::Table(int maxCubeKeys) {
	this->depth = 0;//depth of Table
	this->numCells = 1;// number of entries 2^depth
	this->cubeAddr = new int[this->numCells]; //array of Cube addresses
	this->maxCubeKeys = maxCubeKeys;
	this->tableBuffer = new LengthFieldBuffer();
	this->tableFile = new BufferFile(*tableBuffer);
	this->currentCube = new Cube(*this, maxCubeKeys);
	this->theCubeBuffer = new CubeBuffer(maxKeySize, maxCubeKeys);
	this->cubeFile = new BufferFile(*theCubeBuffer );
	this->printCube = new Cube(*this, maxCubeKeys);

}

Table::~Table() {
	this->close();
}

int Table::open(string name){
	int result = 0;
	result = this->tableFile->open(name+EXT_DIR, ios::in|ios::out);
	if(!result) return 0;
	result = this->tableFile->read();
	if(result==-1) return 0;
	result = this->unPack();
	if(result == -1) return 0;
	result = this->cubeFile->open(name+EXT_BKT, ios::in|ios::out);
	return result;
}

int Table::create(string name){
	//create the two files, clear the Table, create a single Cube and add it to the Table and the Cube file
	int result = 0;
	result = this->tableFile->create(name+EXT_DIR,ios::out);
	if(!result) return 0;
	result = this->cubeFile->create(name+EXT_BKT,ios::out);
	if(!result) return 0;
	//store the empty currenCube in the CubeFile and add to Table
	cubeAddr[0] = this->storeCube(currentCube);
	//storeCube  hace un appends del Cube en el archivo de Cubes
	//y devuele su address, la cual se guarda en el directorio
	return result;
}

int Table::close(){
	//write the Table and close. error occurs on buffer overflow
	int result;
	result = this->pack();
	if(result == -1) return 0;
	this->tableFile->reWind();
	result = tableFile->write();
	if(result == -1) return 0;
	return  this->tableFile->close() && this->cubeFile->close();
}


int Table::insert(char* key, int recAddr){
 int found = search(key);
 if(found == -1){
	 return currentCube->insert(key,recAddr);
 }

 return 0; //key already exist
}

int Table::remove(char* key){
	//remove the key and return its recaddr
	int cubeAddr = this->find(key);
	this->loadCube(this->currentCube, cubeAddr);
	return this->currentCube->remove(key);
}
int Table::search(char* key){
	//return recAddr for key, also put current Cube into variable
	int recAddr = this->find(key);
	this->loadCube(currentCube,recAddr);
	return currentCube->search(key);
}

int Table::doubleSize(){
	//double the size of the Table
	int newSize = this->numCells*2;
	int* newCubeAddr = new int[newSize];
	for(int i=0; i<this->numCells; i++){
		newCubeAddr[2*i] = this->cubeAddr[i];
		newCubeAddr[2*i+1] = this->cubeAddr[i];
	}
	delete this->cubeAddr;
	this->cubeAddr = newCubeAddr;
	this->depth++;
	this->numCells = newSize;
	return 1;
}

int Table::collapse(){
	//if colapse is possible, reduce size by half
	if(this->depth == 0) return 0; //only one Cube
	//else look for buddies that are different, if found return
	for(int i=0; i<this->numCells; i+=2)
		if(this->cubeAddr[i] != this->cubeAddr[i+1]) return 0;

	int newSize = this->numCells/2;
	int* newCubeAddr = new int[newSize];
	for(int j=0; j<newSize; j++)
		newCubeAddr[j] = this->cubeAddr[j*2];
	delete this->cubeAddr;
	this->cubeAddr = newCubeAddr;
	this->depth--;
	this->numCells = newSize;
	return 1;
}

int Table::insertCube(int cubeAddr, int first, int last){
	//change cells to refer to this Cube
	for(int i= first; i<=last; i++)
		this->cubeAddr[i] = cubeAddr;
	return 1;
}

int Table::removeCube(int cubeIndex, int cubeDepth){
	//set all cells for this Cube to its buddy Cube
	int fillBits = this->depth - cubeDepth;//number of bits to fill
	int buddyIndex = cubeIndex^ (1<<(fillBits-1));
	//flip low bit
	int newCubeAddr = this->cubeAddr[buddyIndex];
	int lowIndex = cubeIndex >> fillBits << fillBits;
	//zero low bits
	int highIndex = lowIndex + (1<<fillBits) -1;
	//set low bits to 1
	for(int i= lowIndex; i <= highIndex; i++)
		this->cubeAddr[i] = newCubeAddr;
	return 0;
}

int Table::find(char* key){
	//return CubeAddr for key
	return this->cubeAddr[makeAddress((int)key,this->depth)];
}

int  Table::pack() const{
	//pack the buffer and return the number of bytes packed
	int result,packsize;
	this->tableBuffer->clear();
	//std::cout<<" this->depth: "<<this->depth<<std::endl;
	//std::cout<<" this->numCells: "<<this->numCells<<std::endl;
	packsize = this->tableBuffer->pack(&this->depth, sizeof(int));
	if(packsize == -1) return -1;
	for(int i=0; i<this->numCells; i++){
		//std::cout<<" i en el for de pack(): "<<i<<std::endl;
		//std::cout<<" this->cubeAddr[i]: "<<this->cubeAddr[i]<<std::endl;
		result = this->tableBuffer->pack(&this->cubeAddr[i],sizeof(int));
		if(result == -1) return -1;
		packsize += result;
	}
	return packsize;
}
int Table::unPack(){
	int result;
	result = this->tableBuffer->unPack(&this->depth, sizeof(int));
	if(result == -1) return -1;
	this->numCells = 1 << this->depth;
	std::cout<<" en unPack this->depth: "<<this->depth<<std::endl;
	std::cout<<" en unPack this->numCells: "<<this->numCells<<std::endl;
	if(this->cubeAddr != 0) delete this->cubeAddr;
	this->cubeAddr = new int[this->numCells];
	for(int i = 0; i<this->numCells; i++){
		result = this->tableBuffer->unPack(&this->cubeAddr[i], sizeof(int));
		if(result == -1) return -1;
	}
	return 0;
}

int Table::storeCube(Cube* cube){
	//update or append the Cube to the Cube file
	int result;
	result = this->theCubeBuffer->pack(*cube);
	if(result == -1) return -1;
	int addr = cube->cubeAddr;
	if(addr != 0) return this->cubeFile->write(addr);
	addr = this->cubeFile->append();
	//cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2En stroeCube su addr es: "<<addr<<endl;
	cube->cubeAddr = addr;
	return addr;
}

int Table::loadCube(Cube* cube, int cubeAddr){
	//read the Cube from file, and set CubeAddr field
	int result;
	result = this->cubeFile->read(cubeAddr);
	if(result == -1) return 0;
	result = this->theCubeBuffer->unPack(*cube);
	if(result == -1) return 0;
	cube->cubeAddr = cubeAddr;
	return 1;
}

void Table::print(){
	std::cout<<"Table depth: "<<this->depth<<"  size: "<<this->numCells<<std::endl;
	for(int i=0; i<this->numCells; i++){
		std::cout<<"Cube: "<<(void*)i<<"  addr: "<<this->cubeAddr[i]<<std::endl;
		this->loadCube(this->printCube, this->cubeAddr[i]);
		this->printCube->print();
	}
	std::cout<<"end Table**************************************************"<<endl;

}
int Table::getDepth(){
	return this->depth;
}
