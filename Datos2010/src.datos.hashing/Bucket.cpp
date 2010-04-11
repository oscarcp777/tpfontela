/*
 * Bucket.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Bucket.h"
#include "Directory.h"




Bucket::Bucket(Directory & dir, int maxKeys):TextIndex(maxKeys), dir(dir) {

	this->bucketAddr = 0;
	this->depth = 0;

}
int Bucket::find(const char* key){
	for(int i=0; i <numKeys; i++)
		if(strcmp(keys[i], key)) return i; //key found
		else if(strcmp(keys[i],key)>0) return -1;//not found
	return -1;//not found
}
int Bucket::insert(char* key, int recAddr){

	if (numKeys < maxKeys){
		int result = TextIndex::insert(key,recAddr);
		dir.storeBucket(this);
		return result;

	}
	else{
		//si no tiene espacio se genera mas espacio, se hace un "split"
		split();
		return dir.insert(key,recAddr);

	}


}

int Bucket::remove(char* key){
	//remover key y devolver su recAddr
	int result = TextIndex::remove(key);
	if(!result) return 0; //key not in bucket
	this->tryCombine(); //attempt to combine with buddy
	dir.storeBucket(this);
	return 1;
}
Bucket* Bucket::split(){
	int newStart, newEnd;
	if(depth == dir.depth)// no hay espacio para hacer split de este bucket
		dir.doubleSize();
	Bucket* newBucket = new Bucket(dir, maxKeys);
	dir.storeBucket(newBucket); //PORQUE esta linea???
	newRange(newStart,newEnd);
	dir.insertBucket(newBucket->bucketAddr,newStart,newEnd);
	depth++;
	newBucket->depth = depth;
	redistribute(*newBucket);
	dir.storeBucket(this);
	dir.storeBucket(newBucket);
	return newBucket;
}

int Bucket::findBuddy(){
	//find the directory address of the bucket that is paired whit this
	if(dir.depth == 0) return -1; //no buddy, empty directory
			//unless bucket depth == directory depth, there is no sinlge bucket to pait with
	if(depth < dir.depth) return -1;
	int sharedAddress = Hash::makeAddress(keys[0], depth);
	//address of any key
	return sharedAddress ^ 1; //exclusive or with low bit

}

int Bucket::tryCombine(){
	int result;
	int buddyIndex = findBuddy();
	if(buddyIndex == -1) return 0; //no combination posible
	//load buddy bucket into memory
	int buddyAddr = dir.bucketAddr[buddyIndex];
	Bucket* buddyBucket = new Bucket(dir, maxKeys);
	dir.loadBucket(buddyBucket, buddyAddr);
	//if the sum of the sizes of the buckets is too big, return
	if(numKeys + buddyBucket->numKeys > maxKeys) return 0;
	combine(buddyBucket, buddyIndex);//collapse the 2 buckets
	result = dir.collapse();
	if(result) tryCombine(); //if collapse, may be able combine
	return 1;
}

int Bucket::combine(Bucket* buddy, int buddyIndex){
	//colapse this and buddy into a single bucket
	int result;
	//move keys from buddy to this
	for(int i=0; i < buddy->numKeys; i++){
	//insert the key of the budy into this
		result = insert(buddy->keys[i], buddy->recAddrs[i]);
		if(!result) return 0;
	}
	depth--;
	dir.removeBucket(buddyIndex,depth);
	return 1;

}
int Bucket::newRange(int & newStart, int & newEnd){
	//make a range for the new split bucket
	int sharedAddr = Hash::makeAddress(keys[0],depth);
	int bitsToFill = dir.depth - (depth+1);
	newStart = (sharedAddr << 1) | 1;
	newEnd = newStart;
	for(int j=0; j<bitsToFill; j++){
		newStart = newStart << 1;
		newEnd = (newEnd << 1) | 1;

	}
	return 1;
}

int Bucket::redistribute(Bucket & newBucket){
	//check each key in this bucket
	for(int i= numKeys -1; i>=0; i--){
		int bucketAddr = dir.find(keys[i]);//look up the bucket
		if(bucketAddr != this->bucketAddr){//key belongs in the new bucket
			newBucket.TextIndex::insert(keys[i], recAddrs[i]);
			TextIndex::remove(keys[i]);//delete key from this bucket

		}
	}
	return 1;
}
void Bucket::print(){
	std::cout<<"Bucket depth: "<<depth<<std::endl;
	std::cout<<"max keys: "<<maxKeys<<std::endl;
	std::cout<<"num keys: "<<numKeys<<std::endl;
	for(int i = 0; i<numKeys; i++)
		std::cout<<"\tKey["<<i<<"]"<<keys[i]<<" recAddr "<<recAddrs[i]<<std::endl;

}

Bucket::~Bucket() {
	// TODO Auto-generated destructor stub
}
