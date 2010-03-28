/*
 * Directory.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Directory.h"
#include "Bucket.h"
#include "BucketBuffer.h"
#include <stdio.h>
#include <fstream>
#include <sstream>

const int maxKeySize = 12;
using namespace std;

Directory::Directory(int maxBucketKeys) {
	this->depth = 0;//depth of directory
	this->numCells = 1;// number of entries 2^depth
	this->bucketAddr = new int[this->numCells]; //array of bucket addresses
	this->maxBucketKeys = maxBucketKeys;
	this->directoryBuffer = new LengthFieldBuffer();//TODO
	this->directoryFile = new BufferFile(/* *directoryBuffer */);//TODO
	this->currentBucket = new Bucket(*this, maxBucketKeys);
	this->theBucketBuffer = new BucketBuffer(maxKeySize, maxBucketKeys);
	this->bucketFile = new BufferFile(/* *theBucketBuffer */);
	this->printBucket = new Bucket(*this, maxBucketKeys);

}

Directory::~Directory() {
	this->close();
}

void makeNames(char* name, char*& dirName, char*& bktName){
	//TODO nose el nombre de la libreria ostrstream :P
//	ostrstream directoryName;
//	directoryName<<name<<".dir"<<ends;
//	dirName = strdup(directoryName.str());
//	ostrstream bucketName;
//	bucketName<<name<<".bkt"<<ends;
//	bktName = strdup(bucketName.str());

}

int Directory::open(char* name){
	int result = 0;
	char* directoryName;
	char* bucketName;
	makeNames(name, directoryName, bucketName);
	result = this->directoryFile->open(directoryName, ios::in|ios::out);// TODO falta hacer la clase fileBuffer
	if(!result) return 0;
	result = this->directoryFile->read();//TODO falta hacer la clase fileBuffer
	if(result==-1) return 0;
	result = this->unPack();
	if(result == -1) return 0;
	result = this->bucketFile->open(bucketName, ios::in|ios::out);//TODO falta hacer la clase fileBuffer
	return result;
}

int Directory::create(char* name){
	//create the two files, clear the directory, create a single bucket and add it to the directory and the bucket file
	int result = 0;
	char* directoryName;
	char* bucketName;
	makeNames(name,directoryName,bucketName);
	result = this->directoryFile->create(directoryName,ios::in|ios::out);//TODO falta hacer la clase fileBuffer
	if(!result) return 0;
	result = this->bucketFile->create(bucketName, ios::in|ios::out);//TODO falta hacer la clase fileBuffer
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
	this->directoryFile->reWind();//TODO falta hacer la clase fileBuffer
	result = directoryFile->write();
	if(result == -1) return 0;
	return this->directoryFile->close() && this->bucketFile->close();
}


int Directory::insert(char* key, int recAddr){
 int found = search(key);
 if(found == -1) return currentBucket->instert(key,recAddr);
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
	return recAddr;//TODO yo digo que es recAddr //pero el libro dice: currentBucket->search(key) pero no existe ese metodo para Bucket
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
	for(int j=0; j<newSize; j+=2)
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
}

int Directory::find(char* key){
	return 0;
}

int Directory::storeBucket(Bucket* bucket){
	return 0;
}

int Directory::loadBucket(Bucket* bucket, int bucketAddr){
	return 0;
}

void Directory::print(){

}
int  Directory::pack() const{
	return 0;
}
int Directory::unPack(){
	return 0;
}
