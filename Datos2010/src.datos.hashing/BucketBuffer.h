/*
 * BucketBuffer.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUCKETBUFFER_H_
#define BUCKETBUFFER_H_
#include "../src.datos.buffer/TextIndexBuffer.h"

class Bucket;

class BucketBuffer: public TextIndexBuffer{
public:
	BucketBuffer(int keySize, int maxKeys);
	virtual ~BucketBuffer();
	int pack(const Bucket& bucket);
	int unPack(Bucket& bucket);

	friend class Bucket;
};

#endif /* BUCKETBUFFER_H_ */
