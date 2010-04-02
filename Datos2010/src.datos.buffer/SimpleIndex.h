/*
 * SimpleIndex.h
 *
 *  Created on: 02/04/2010
 *      Author: oscar
 */

#ifndef SIMPLEINDEX_H_
#define SIMPLEINDEX_H_
#include <iostream>
template <class keyType>
class SimpleIndex {
protected:
	int maxKeys;
	int numKeys;
	keyType* keys;
	int* recAddrs;
	int find(const keyType key ,const int recAddr=-1,const int exact=1)const;
	int init(const int maxKeys,const int unique);
	int unique;

public:
	SimpleIndex(int maxKeys=100,int unique=1);
	~SimpleIndex();
	void clear();
	int insert(const keyType key,int recAddr);
	int remove(const keyType key,const int recAddr=-1);
	int search(const keyType key,const int recAddr=-1,const int exact=1)const;
	void print();
	int getNumKeys()const {
		return this->numKeys;
	}

};

#endif /* SIMPLEINDEX_H_ */
template <class keyType>
SimpleIndex<keyType>::SimpleIndex(int maxKeys,int unique):
numKeys(0),keys(0),recAddrs(0){
	init(maxKeys,unique);
}
template <class keyType>
SimpleIndex<keyType>::~SimpleIndex(){
	delete keys;
	delete recAddrs;
}
template <class keyType>
void SimpleIndex<keyType>::clear(){
	this->numKeys=0;
}
template <class keyType>
int SimpleIndex<keyType>::insert(const keyType key,int recAddr){
	int i;
	int index=find(key);
	if(this->unique&& index>=0)return 0;
	if(this->numKeys==this->maxKeys)return 0;
	for (i = this->numKeys-1; i>=0; i--) {
		if(key>this->keys[i])break;
		this->keys[i+1]=this->keys[i];
		this->recAddrs[i+1]=this->recAddrs[i];

	}
	this->keys[i+1]=key;
	this->recAddrs[i+1]=recAddr;
	this->numKeys++;
	return 1;



}

template <class keyType>
int SimpleIndex<keyType>::remove(const keyType key,int recAddr){

	int index=find(key);
	if(index< 0)return 0;

	for (int i = index; i<this->numKeys; i++) {

		this->keys[i]=this->keys[i+1];
		this->recAddrs[i]=this->recAddrs[i+1];

	}

	this->numKeys--;
	return 1;



}
template <class keyType>
int SimpleIndex<keyType>::search(const keyType key,int recAddr,	int exact)const{

	int index=find(key,recAddr,exact);
	if(index< 0)return index;
	return this->recAddrs[index];

}


template <class keyType>
void SimpleIndex<keyType>::print(){
	std::cout<<"maximo de claves "<<this->maxKeys<<" numero de keys :"<<this->numKeys<std::endl;
	for (int var = 0;  var < this->numKeys;  var++) {
		std::cout<<"\t tkey [ "<<var<<" ] "<<this->keys[var]<< " recaddr"
				<<this->recAddrs[var]<<std::endl;


	}


}
template <class keyType>
int SimpleIndex<keyType>::find(const keyType key,int recAddr,	int exact)const{

	for (int var = 0; var < this->numKeys; ++var) {
		if(this->keys[var]<key)continue;
		if(this->keys[var]==key){
			if(recAddr<0)return var;
			else if(recAddr==this->recAddrs[var])return var;
			else return -1;
		}
		if(!exact) return var;
	}
   if(exact==1)return -1;
   else return this->numKeys-1;

}

template <class keyType>
int SimpleIndex<keyType>::init(const int maxKeys,const int unique){

	this->unique=unique!=0;
	if(maxKeys<=0){
      this->maxKeys=0;
      return 0;
	}
this->maxKeys=maxKeys;
this->keys= new keyType[maxKeys];
this->recAddrs= new int[maxKeys];
return 1;
}






