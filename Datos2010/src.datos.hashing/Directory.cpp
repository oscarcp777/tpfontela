/*
 * Directory.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Directory.h"
#include "Bucket.h"
#include "BucketBuffer.h"
#include "../src.datos.buffer/BufferFile.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>


const int maxKeySize = 12;
//using namespace std;

Directory::Directory(int maxBucketKeys) {
	this->depth = 0;//depth of directory
	this->numCells = 1;// number of entries 2^depth
	this->bucketAddr = new int[this->numCells]; //array of bucket addresses
	this->maxBucketKeys = maxBucketKeys;
	this->directoryBuffer = new LengthFieldBuffer();
	this->directoryFile = new BufferFile(*directoryBuffer);
	this->currentBucket = new Bucket(*this, maxBucketKeys);
	this->theBucketBuffer = new BucketBuffer(maxKeySize, maxBucketKeys);
	this->bucketFile = new BufferFile(*theBucketBuffer );
	this->printBucket = new Bucket(*this, maxBucketKeys);

}

Directory::~Directory() {
	this->close();
}

void makeNames(char* name, char*& dirName, char*& bktName){
	//crea los nombres del archivo directory y del archivo de buckets
	string  directoryName;
	string bucketName;

	directoryName = name;
	directoryName+= ".dir";
	dirName = (char*)directoryName.c_str();

	bucketName = name;
	bucketName+= ".bkt";
	bktName = (char*)bucketName.c_str();
}

int Directory::open(string name){
	int result = 0;
//	char* directoryName;
//	char* bucketName;
//	makeNames(name, directoryName, bucketName);
	result = this->directoryFile->open(name+".dir", ios::in|ios::out);
	if(!result) return 0;
	result = this->directoryFile->read();
	if(result==-1) return 0;
	result = this->unPack();
	if(result == -1) return 0;
	result = this->bucketFile->open(name+".bkt", ios::in|ios::out);
	return result;
}

int Directory::create(string name){
	//create the two files, clear the directory, create a single bucket and add it to the directory and the bucket file
	int result = 0;
//	char* directoryName;
//	char* bucketName;
//	makeNames(name,directoryName,bucketName);
	result = this->directoryFile->create(name+".dir",ios::out);
	if(!result) return 0;
	result = this->bucketFile->create(name+".bkt",ios::out);
	if(!result) return 0;
	//store the empty currenBucket in the bucketFile and add to directory
	bucketAddr[0] = this->storeBucket(currentBucket);
	//storeBucket  hace un appends del bucket en el archivo de buckets
	//y devuele su address, la cual se guarda en el directorio
	return result;
}

int Directory::close(){
	//write the directory and close. error occurs on buffer overflow
	int result;
	result = this->pack();
	if(result == -1) return 0;
	this->directoryFile->reWind();
	result = directoryFile->write();
	if(result == -1) return 0;
	return  this->directoryFile->close() && this->bucketFile->close();
}


int Directory::insert(char* key, int recAddr){
 int found = search(key);
 if(found == -1){
	 return currentBucket->insert(key,recAddr);
 }

 return 0; //key already exist
}

int Directory::remove(char* key){
	//remove the key and return its recaddr
	int bucketAddr = this->find(key);
	this->loadBucket(this->currentBucket, bucketAddr);
	return this->currentBucket->remove(key);
}
int Directory::search(char* key){
	//return recAddr for key, also put current bucket into variable
	int recAddr = this->find(key);
	this->loadBucket(currentBucket,recAddr);
	return currentBucket->search(key);
}

int Directory::doubleSize(){
	//double the size of the directory
	int newSize = this->numCells*2;
	int* newBucketAddr = new int[newSize];
	for(int i=0; i<this->numCells; i++){
		newBucketAddr[2*i] = this->bucketAddr[i];
		newBucketAddr[2*i+1] = this->bucketAddr[i];
	}
	delete this->bucketAddr;
	this->bucketAddr = newBucketAddr;
	this->depth++;
	this->numCells = newSize;
	return 1;
}

int Directory::collapse(){
	//if colapse is possible, reduce size by half
	if(this->depth == 0) return 0; //only one bucket
	//else look for buddies that are different, if found return
	for(int i=0; i<this->numCells; i+=2)
		if(this->bucketAddr[i] != this->bucketAddr[i+1]) return 0;

	int newSize = this->numCells/2;
	int* newBucketAddr = new int[newSize];
	for(int j=0; j<newSize; j++)
		newBucketAddr[j] = this->bucketAddr[j*2];
	delete this->bucketAddr;
	this->bucketAddr = newBucketAddr;
	this->depth--;
	this->numCells = newSize;
	return 1;
}

int Directory::insertBucket(int bucketAddr, int first, int last){
	//change cells to refer to this bucket
	for(int i= first; i<=last; i++)
		this->bucketAddr[i] = bucketAddr;
	return 1;
}

int Directory::removeBucket(int bucketIndex, int bucketDepth){
	//set all cells for this bucket to its buddy bucket
	int fillBits = this->depth - bucketDepth;//number of bits to fill
	int buddyIndex = bucketIndex^ (1<<(fillBits-1));
	//flip low bit
	int newBucketAddr = this->bucketAddr[buddyIndex];
	int lowIndex = bucketIndex >> fillBits << fillBits;
	//zero low bits
	int highIndex = lowIndex + (1<<fillBits) -1;
	//set low bits to 1
	for(int i= lowIndex; i <= highIndex; i++)
		this->bucketAddr[i] = newBucketAddr;
	return 0;
}

int Directory::find(char* key){
	//return bucketAddr for key
	return this->bucketAddr[Hash::makeAddress(key,this->depth)];
}

int  Directory::pack() const{
	//pack the buffer and return the number of bytes packed
	int result,packsize;
	this->directoryBuffer->clear();
	//std::cout<<" this->depth: "<<this->depth<<std::endl;
	//std::cout<<" this->numCells: "<<this->numCells<<std::endl;
	packsize = this->directoryBuffer->pack(&this->depth, sizeof(int));
	if(packsize == -1) return -1;
	for(int i=0; i<this->numCells; i++){
		//std::cout<<" i en el for de pack(): "<<i<<std::endl;
		//std::cout<<" this->bucketAddr[i]: "<<this->bucketAddr[i]<<std::endl;
		result = this->directoryBuffer->pack(&this->bucketAddr[i],sizeof(int));
		if(result == -1) return -1;
		packsize += result;
	}
	return packsize;
}
int Directory::unPack(){
	int result;
	result = this->directoryBuffer->unPack(&this->depth, sizeof(int));
	if(result == -1) return -1;
	this->numCells = 1 << this->depth;
	std::cout<<" en unPack this->depth: "<<this->depth<<std::endl;
	std::cout<<" en unPack this->numCells: "<<this->numCells<<std::endl;
	if(this->bucketAddr != 0) delete this->bucketAddr;
	this->bucketAddr = new int[this->numCells];
	for(int i = 0; i<this->numCells; i++){
		result = this->directoryBuffer->unPack(&this->bucketAddr[i], sizeof(int));
		if(result == -1) return -1;
	}
	return 0;
}

int Directory::storeBucket(Bucket* bucket){
	//update or append the bucket to the bucket file
	int result;
	result = this->theBucketBuffer->pack(*bucket);
	if(result == -1) return -1;
	int addr = bucket->bucketAddr;
	if(addr != 0) return this->bucketFile->write(addr);
	addr = this->bucketFile->append();
	//cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2En stroeBucket su addr es: "<<addr<<endl;
	bucket->bucketAddr = addr;
	return addr;
}

int Directory::loadBucket(Bucket* bucket, int bucketAddr){
	//read the bucket from file, and set bucketAddr field
	int result;
	result = this->bucketFile->read(bucketAddr);
	if(result == -1) return 0;
	result = this->theBucketBuffer->unPack(*bucket);
	if(result == -1) return 0;
	bucket->bucketAddr = bucketAddr;
	return 1;
}

void Directory::print(){
	std::cout<<"Directory depth: "<<this->depth<<"  size: "<<this->numCells<<std::endl;
	for(int i=0; i<this->numCells; i++){
		std::cout<<"bucket: "<<(void*)i<<"  addr: "<<this->bucketAddr[i]<<std::endl;
		this->loadBucket(this->printBucket, this->bucketAddr[i]);
		this->printBucket->print();
	}
	std::cout<<"end directory**************************************************"<<endl;

}
int Directory::getDepth(){
	return this->depth;
}
