/*
 * TextIndex.cpp
 *
 *  Created on: 02/04/2010
 *      Author: richy
 */

#include "TextIndex.h"


TextIndex::TextIndex(int maxKeys, int unique):numKeys(0),keys(0),recAddrs(0) {
	this->init(maxKeys,unique);
}

TextIndex::~TextIndex() {
	delete keys;
	delete recAddrs;
}
int TextIndex::insert(const char* key, int recAddr){
	int i;
	int index= this->find(key);
	if(this->unique && index>=0) return 0; //key already in
	if(this->numKeys == this->maxKeys) return 0; //no room for another key
	for(i = this->numKeys-1; i>=0; i--){
		if(strcmp(key, this->keys[i])>0) break; //insert into i+1
		this->keys[i+1]= this->keys[i];
		this->recAddrs[i+1] = this->recAddrs[i];
	}
	this->keys[i+1] = strdup(key);
	this->recAddrs[i+1] = recAddr;
	this->numKeys++;
	return 1;
}

int TextIndex::remove(const char* key){
	int index = this->find(key);
	if(index < 0) return 0; //key not in index
	for(int i=index; i<this->numKeys; i++){
		this->keys[i] = this->keys[i+1];
		this->recAddrs[i] = this->recAddrs[i+1];
	}
	this->numKeys--;

	return 1;
}
int TextIndex::search(const char* key)const{
	int index= this->find(key);
	if(index < 0) return index;
	return this->recAddrs[index];
}
void TextIndex::print(){
	cout<<"Text index max keys "<<this->maxKeys<<" num keys "<<this->numKeys<<endl;
	for(int i = 0; i<this->numKeys; i++)
		cout<<" \t key["<<i<<"] ="<<this->keys[i]<<" recAddr "<<this->recAddrs[i]<<endl;
}
int TextIndex::find(const char* key)const{
	for(int i=0; i<this->numKeys; i++){
		if(strcmp(this->keys[i],key)==0) return i;//key found
		else if(strcmp(this->keys[i],key) > 0) return -1;//not found
	}
	return -1;//not found

}
int TextIndex::init(int maxkeys, int unique){
	this->unique = unique !=0;
	if(maxkeys <= 0){
		this->maxKeys = 0;
		return 0;
	}
	this->maxKeys = maxkeys;
	this->keys = new char *[maxkeys];
	this->recAddrs = new int[maxkeys];
	return 1;
}
