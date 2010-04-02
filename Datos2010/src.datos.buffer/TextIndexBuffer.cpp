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
int TextIndexBuffer::pack(const TextIndex& index){
	int result;
	this->clear();
	result = FixedFieldBuffer::pack(&index.numKeys);
	for(int i=0; i<index.numKeys; i++){
		result = result && FixedFieldBuffer::pack(index.keys[i]);
		result = result && FixedFieldBuffer::pack(&index.recAddrs[i]);
	}
	for(int j=0; j<index.maxKeys-index.numKeys; j++){
		result = result && FixedFieldBuffer::pack(this->dummy);
		result = result && FixedFieldBuffer::pack(this->dummy);
	}
	return result;
}
int TextIndexBuffer::unPack(TextIndex& index){
	int result;
	result = FixedFieldBuffer::unPack(&index.numKeys);
	for(int i=0; i<index.numKeys; i++){
		index.keys[i] = new char[this->keySize];
		result = result && FixedFieldBuffer::unPack(index.keys[i]);
		result = result && FixedFieldBuffer::unPack(&index.recAddrs[i]);
		}
	for(int j=0; j<index.maxKeys-index.numKeys; j++){
			result = result && FixedFieldBuffer::unPack(this->dummy);
			result = result && FixedFieldBuffer::unPack(this->dummy);
		}
		return result;
}
void TextIndexBuffer::print(){
	cout<<"TextIndexBuffer: keySize "<<this->keySize<<" maxKeys "<<this->maxKeys<<endl;
	FixedFieldBuffer::print();
}
