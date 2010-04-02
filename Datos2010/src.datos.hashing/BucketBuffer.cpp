/*
 * BucketBuffer.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "BucketBuffer.h"
#include "Bucket.h"

BucketBuffer::BucketBuffer(int keySize, int maxKeys):TextIndexBuffer(keySize,maxKeys,1,sizeof(int)) {
	this->addField(sizeof(int));
}

BucketBuffer::~BucketBuffer() {
	// TODO Auto-generated destructor stub
}

int BucketBuffer::pack(const Bucket& bucket){
	int result;
	result = TextIndexBuffer::pack(bucket);
	if(result == -1) return -1;
	return FixedFieldBuffer::pack(&bucket.depth);


}
int BucketBuffer::unPack(Bucket& bucket){
	int result;
	result = TextIndexBuffer::unPack(bucket);
	if(result == -1) return -1;
	return FixedFieldBuffer::unPack(&bucket.depth);
}
