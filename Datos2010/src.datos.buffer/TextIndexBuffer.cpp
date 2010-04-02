/*
 * TextIndexBuffer.cpp
 *
 *  Created on: 02/04/2010
 *      Author: richy
 */

#include "TextIndexBuffer.h"

TextIndexBuffer::TextIndexBuffer(int keySize, int maxKeys, int extraFields, int extraSize):FixedFieldBuffer(1+2*maxKeys+extraFields,sizeof(int)+maxKeys*keySize+maxKeys*sizeof(int)+extraSize) {
	this->maxKeys = maxKeys;
	this->keySize = keySize;
	this->addField(sizeof(int));
	for(int i=0; i<maxKeys; i++){
		this->addField(this->keySize);
		this->addField(sizeof(int));

	}
	this->dummy = new char[keySize+1];

}

TextIndexBuffer::~TextIndexBuffer() {
	// TODO Auto-generated destructor stub
}
int TextIndexBuffer::pack(const Bucket& bucket){
	int result;
	this->clear();
	result = FixedFieldBuffer::pack(&bucket.numKeys);
	for(int i=0; i<bucket.numKeys; i++){
		result = result && FixedFieldBuffer::pack(bucket.keys[i]);
		result = result && FixedFieldBuffer::pack(&bucket.recAddrs[i]);
	}
	for(int j=0; j<bucket.maxKeys-bucket.numKeys; j++){
		result = result && FixedFieldBuffer::pack(this->dummy);
		result = result && FixedFieldBuffer::pack(this->dummy);
	}
	return result;
}
int TextIndexBuffer::unPack(Bucket& bucket){
	int result;
	result = FixedFieldBuffer::unPack(&bucket.numKeys);
	for(int i=0; i<bucket.numKeys; i++){
		bucket.keys[i] = new char[this->keySize];
		result = result && FixedFieldBuffer::unPack(bucket.keys[i]);
		result = result && FixedFieldBuffer::unPack(&bucket.recAddrs[i]);
		}
	for(int j=0; j<bucket.maxKeys-bucket.numKeys; j++){
			result = result && FixedFieldBuffer::unPack(this->dummy);
			result = result && FixedFieldBuffer::unPack(this->dummy);
		}
		return result;
}
void TextIndexBuffer::print(){
	cout<<"TextIndexBuffer: keySize "<<this->keySize<<" maxKeys "<<this->maxKeys<<endl;
	FixedFieldBuffer::print();
}
