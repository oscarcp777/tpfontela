/*
 * Bucket.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "../src.datos.utils/Object.h"
#include "Hash.h"

const int defaultMaxKeys = 100;

class Directory;

class Bucket {

public:
	Bucket(Directory & dir, int maxKeys = defaultMaxKeys);
	virtual ~Bucket();
protected:
	int instert(char* key, int recAddr);
	int remove(char* key);
	Bucket* split();
	int newRange(int & newStart, int & newEnd);
	int redistribute(Bucket & newBucket);
	int find(const char* key);
	int findBuddy();
	int tryCombine();
	int combine(Bucket* buddy, int buddyIndex);
	void print();
	int depth;
	Directory  &dir;
	int bucketAddr;
	int maxKeys;
	int numKeys;
	char** keys;
	int unique; //si es true, cada key tiene que ser unica
	int* recAddrs;

	friend class Directory;
	friend class BucketBuffer;
	friend class TextIndexBuffer;
};

#endif /* BUCKET_H_ */
