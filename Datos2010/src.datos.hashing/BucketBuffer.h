/*
 * BucketBuffer.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUCKETBUFFER_H_
#define BUCKETBUFFER_H_


class Bucket;

class BucketBuffer {
public:
	BucketBuffer(int keySize, int maxKeys);
	virtual ~BucketBuffer();
	int pack(const Bucket& bucket);
	int unPack(Bucket& bucket);
private:
	int keySize;
	int maxKeys;

	friend class Bucket;
};

#endif /* BUCKETBUFFER_H_ */
