/*
 * Directory.h
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_


#include "../src.datos.utils/Object.h"
#include "LengthFieldBuffer.h"
#include "BufferFile.h"

class Bucket;
class BucketBuffer;

class Directory {
public:
	Directory(int maxBucketKeys = -1);
	virtual ~Directory();
	int open(char* name);
	int create(char* name);
	int close();
	int insert(char* key, int recAddr);
	int remove(char* key);
	int search(char* key);// return recAddr for key
	void print();
protected:
	int depth;
	int numCells; //number of entries, = 2*depth
	int* bucketAddr; //array of bucket addresses
	int doubleSize();//double the size of the directory
	int collapse(); //collapse, halve the size
	int insertBucket(int bucketAddr, int first, int last);
	int removeBucket(int bucketIndex, int bucketDepth);
	int find(char* key); //return bucketAddr for key
	int storeBucket(Bucket* bucket); //update or append bucket from file
	int loadBucket(Bucket* bucket, int bucketAddr);//load bucket from file
	int maxBucketKeys;
	BufferFile* directoryFile;
	LengthFieldBuffer* directoryBuffer;
	BucketBuffer* theBucketBuffer;
	BufferFile* bucketFile;
	int pack() const;
	int unPack();
	Bucket* printBucket;
	Bucket* currentBucket;

	friend class Bucket;
};

#endif /* DIRECTORY_H_ */
