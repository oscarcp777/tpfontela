/*
 * BucketBuffer.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "BucketBuffer.h"
#include "Bucket.h"

BucketBuffer::BucketBuffer(int keySize, int maxKeys) {
	// TODO Auto-generated constructor stub
	this->keySize = keySize;
	this->maxKeys = maxKeys;
}

BucketBuffer::~BucketBuffer() {
	// TODO Auto-generated destructor stub
}

int BucketBuffer::pack(const Bucket& bucket){
	return 0;

}
int BucketBuffer::unPack(Bucket& bucket){
	return 0;

}
