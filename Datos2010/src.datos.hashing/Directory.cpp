/*
 * Directory.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Directory.h"
#include "Bucket.h"
#include "BucketBuffer.h"

const int maxKeySize = 12;

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


int Directory::doubleSize(){
	return 0;
}

int Directory::collapse(){
	return 0;
}
int Directory::insertBucket(int bucketAddr, int first, int last){
	return 0;
}

int Directory::removeBucket(int bucketIndex, int depth){
	return 0;
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

int Directory::open(char* name){
	return 0;
}

int Directory::create(char* name){
	return 0;
}

int Directory::close(){
	return 0;
}

int Directory::insert(char* key, int recAddr){
	return 0;
}

int Directory::remove(char* key){
	return 0;
}

int Directory::search(char* key){// return recAddr for key
	return 0;
}

void Directory::print(){

}
