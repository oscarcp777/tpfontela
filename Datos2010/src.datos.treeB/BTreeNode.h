/*
 *  BTreeNode.h
 *
 *  Created on: 02/04/2010
 *      Author: santiago
 */

#ifndef BTREENODE_H_
#define BTREENODE_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../src.datos.buffer/IOBuffer.h"
#include "../src.datos.buffer/SimpleIndex.h"
#include "../src.datos.buffer/FixedFieldBuffer.h"
//#include "../src.datos.treeB+/BPlusTree.h"

using namespace std;

template <class keyType>

class BTreeNode : SimpleIndex <keyType> {

public:
	BTreeNode(int maxSize,int keySize, int unique = 1)
	//(Tamaño bloque - metadata bloque)/tamaño clave       //ver init
	:SimpleIndex<keyType>(((maxSize-sizeof(short) - sizeof(int))/(keySize+sizeof(short)+sizeof(int)+sizeof(short))), unique),
	 data(0)
	 {
		//el array de punteros se inicializa con un max. de posibles referencias
		//dado por el max. de claves posibles a insertar (es decir sin contar el
		//tamaño del dato)
		this->data = new char*[this->maxKeys];
		init(maxSize);
	 }

	~BTreeNode() {
		int i;
		for (i = 0; i < this->numKeys; i++) {
				if (this->data[i] != NULL){
					delete this->data[i];
					this->data[i]=NULL;
				}
		}
		delete this->data;
	}

	int  insert(const keyType key, const char* data, int recAddr = -1){

		int result;
		result = SimpleIndex<keyType>::insert(key, recAddr);
		if (result == -1) return 0; //fallo insercion
		if (this->isLeaf){
			string dataAux = data;
			int size = dataAux.length();
			/*
			 * Chequeo que el dato no supere un tamaño maximo.
			 * Si supera ese tamaño, retorna 0 y ese valor es
			 * considerado que la inserccion no se pudo realizar.
			 * Ademas de esto, tengo que eliminar la key que inserte en
			 * el SimpleIndex.
			 */
			if(size > (this->blockMaxSize*PORCENT_BLOCK_SIZE)){

				SimpleIndex<keyType>::remove(key,recAddr);
				return 0;
			}

			int i;
			for (i = this->numKeys-2; i>=result; i--) {
				if (this->data[i]!=NULL){
					this->data[i+1]=this->data[i];
				}
			}
			this->data[result] = new char[size+1];
			strcpy(this->data[result],data);

			this->freeSpace -= (dataAux.length()+sizeof(short));
			this->freeSpace -= this->keySize;
			if (this->freeSpace <= 0)
				return -1;

		}else{
			freeSpace-=this->keySize;
			if (this->numKeys >= this->maxKeys) return -1; //overflow nodo
		}
			return 1;
	}


	void updateAddr(keyType key,int dir){
		for(int i = 0; i < this->numKeys; i++){
				if (this->keys[i]==key){ //exact match
					this->recAddrs[i]=dir;
				}

			}
	}


	int remove(const keyType key, int dir){
		int result;
		int index=SimpleIndex<keyType>::find(key);
		result = SimpleIndex<keyType>::remove(key, recAddr);
		if (!result) return 0; //fallo remover
		if(this->isLeaf){
			string data=this->data[index];
			freeSpace+=(data.length()+sizeof(short));
			freeSpace+=this->keySize;
		for (int i = index; i<this->numKeys; i++) {
			if (this->data[i+1]!=NULL){
				this->data[i]=this->data[i+1];
			}
		}
		}else{
			freeSpace+=this->keySize;
		if (this->numKeys < this->minKeys) return -1; //underflow nodo
		}
		return 0;
	}

	int search(const keyType key,const int recAddr = -1, const int exact = 1)const{
		//devuelve la posicion de la key en el vector
		return SimpleIndex<keyType>::find(key,recAddr,exact);
		//return SimpleIndex<keyType>::search(key, recAddr, exact);
	}


	keyType largestKey(){ 	   //retorna el valor de la clave mayor
		if (this->numKeys > 0)
			return this->keys[this->numKeys-1];
		else return this->keys[0];

	}

	int  split(BTreeNode* newNode){ 		//mover al nuevo nodo

		int midpt = (this->numKeys + 1)/2; //encuentra la primer clave a ser movida al nuevo nodo
		int numNewKeys = this->numKeys - midpt;
		//mueve las claves y direcciones desde aca al nuevo nodo
		for(int i = midpt; i < this->numKeys; i++){
			newNode->keys[i-midpt] = this->keys[i];
			newNode->recAddrs[i-midpt] = this->recAddrs[i];
			if (isLeaf){
				newNode->data[i-midpt] = this->data[i];
				newNode->freeSpace -= (strlen(this->data[i])+sizeof(short));
				newNode->freeSpace -= this->keySize;
				this->freeSpace += (strlen(this->data[i])+sizeof(short));
				this->freeSpace += this->keySize;
				this->data[i] = NULL;
			}else{
				newNode->freeSpace += this->keySize;
			}
		}
		//setea el numero de claves en los 2 nodos
		newNode->numKeys = numNewKeys;
		this->numKeys = midpt;
		return 1;
	}

	int  merge(BTreeNode* fromNode){		//mueve desde el nodo

		//chequea si hay demasiadas claves
		if (this->numKeys + fromNode->numKeys > this->maxKeys-1) return 0;
		//mueve claves y direcciones desde fromNode a este nodo
		for(int i = 0; i < fromNode->numKeys; i++){
			this->keys[this->numKeys+i] = fromNode->keys[i];
			this->recAddrs[this->numKeys+i] = fromNode->recAddrs[i];
			if (isLeaf){
				 string dataAux=fromNode->data[i];
				 this->data[this->numKeys+i]=fromNode->data[i];
				 freeSpace-=(dataAux.length()+sizeof(short));
				 freeSpace-=this->keySize;
			}else{
				freeSpace-=this->keySize;
			}
		}
		//ajustar numero de claves
		this->numKeys += fromNode->numKeys;

		return 1;
	}

	int  updateKey(keyType oldKey, keyType newKey, int recAddr = -1){

//		int recaddr = this->search(oldKey,recAddr);
		int recaddr = this->recAddrs[this->search(oldKey,recAddr)];
		if (recaddr < 0) return 0; 		// clave y direccion no encontradas
		this->remove(oldKey,recAddr);
		this->insert(newKey,NULL,recaddr);
		return 1;
	}

	/*
	 * Lo mismo que hace updateKey con la diferencia que en lugar de hacer un insert con un dato nulo,
	 * lo hace con un nuevo dato.
	 */
	int updateKeyAndData(keyType oldKey, keyType newKey, char* newData, int recAddr=-1){
		int recaddr = this->recAddrs[this->search(oldKey,recAddr)];
		if (recaddr < 0) return 0; 		// clave y direccion no encontradas
		this->remove(oldKey,recAddr);
		this->insert(newKey,newData,recaddr);
		return 1;
	}

	int  pack(IOBuffer& buffer) const{
		int result;
		buffer.clear();
		result = buffer.pack(&this->numKeys,sizeof(int));
		if (this->isLeaf){
			result = buffer.pack(&this->nextNode,sizeof(int));
			result = buffer.pack(&this->freeSpace,sizeof(int));
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.pack(&this->keys[i],sizeof(keyType));
				result = result && buffer.pack(this->data[i],strlen(this->data[i]));
			}
		}else{
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.pack(&this->keys[i],sizeof(keyType));
				result = result && buffer.pack(&this->recAddrs[i],sizeof(int));
			}
		}


		return result;
	}

	int  unpack(IOBuffer& buffer){
		int result;
		int size=this->freeSpace;
		char auxData[size];
		memset(auxData,0,size);
		result = buffer.unPack(&this->numKeys,sizeof(int));
		if (this->isLeaf){
			result = buffer.unPack(&this->nextNode,sizeof(int));
			result = buffer.unPack(&this->freeSpace,sizeof(int));
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.unPack(&this->keys[i],sizeof(keyType));
				result = result && buffer.unPack(auxData);
				int len = strlen(auxData);
				this->data[i] = new char[len+1];
				memset(this->data[i],0,len);
				strcpy(this->data[i],(char*)auxData);
				memset(auxData,0,size);
			}
		}else{
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.unPack(&this->keys[i]);
				result = result && buffer.unPack(&this->recAddrs[i]);
			}
		}

		return result;
	}

	void  print(ostream & stream) const{
		stream 	<<" Numero de keys en Nodo = "<<this->numKeys<<" )"<<endl;
		for(int i = 0; i<this->numKeys; i++){
			if (isLeaf)
				stream << "\t ( Key["<<i<<"]  |"<<this->keys[i] << "| dato "<< this->data[i]<<" )"<<endl;
			else
				stream << "\t ( Key["<<i<<"] |"<<this->keys[i] << "|  dir "<<this->recAddrs[i]<<" )"<<endl;
		}
		if (isLeaf){
			stream<<"\t\tEspacio libre: "<<this->freeSpace<<endl;
			stream<<"\t\tApunta a direccion: "<<this->nextNode<<endl;
		}

	}

	int getMaxKeys(){
		return this->maxKeys;
	}

	int getRecAddr() const
	{
		return recAddr;
	}

	void setRecAddr(int recAddr)
	{
		this->recAddr = recAddr;
	}

	int getNextNode() const
	{
		return this->nextNode;
	}

	void setNextNode(int nextNode)
	{
		this->nextNode = nextNode;
	}

	keyType* getKeys() const
	{
		return this->keys;
	}

	void setKeys(keyType* keys)
	{
		this->keys = keys;
	}

	int* getRecAddrs() const
	{
		return this->recAddrs;
	}

	void setRecAddrs(int* recAddrs)
	{
		this->recAddrs = recAddrs;
	}

	int getNumKeys() const
	{
		return this->numKeys;
	}

	void setNumKeys(int numKeys)
	{
		this->numKeys = numKeys;
	}

	bool getIsLeaf()
	{
		return this->isLeaf;
	}

	void setIsLeaf(bool value)
	{
		this->isLeaf = value;
		if (value == false){

		}
	}

	int getFreeSpace(){
		return this->freeSpace;
	}

	void setFreeSpace(int freeSpace){
		this->freeSpace = freeSpace;
	}


	char** getData() const
	{
		return this->data;
	}
	
	/**
	 * El espacio minimo es el 20% del tama�o del bloque
	 */

	int getMinFreeSpace(int blockSize){
		return blockSize*0.5;
	}
/*
	int getBlockMaxSize(){
		return this->blockMaxSize;
	}*/
	/**
	 * Retorna el minimo numero de claves que puede haber en un nodo interno (no hoja)
	 */
	int getMinKeys(int blockSize){
//		int max_Keys=(blockSize)/(keySize);
//		int ret_minKeys=(max_Keys)/2;
		return ((this->getMaxKeys())/2);//ret_minKeys; TODO cuando se solucione el underflow del insert descomentar lo que esta comentado en getMinKeys de BTreeNode.h
	}

	int getTamanioOcupado(int blockSize){
		return (blockSize-freeSpace);
	}

	int getKeySize(){
		return this->keySize;
	}

	int caseDataRemove(int sizeDataRemove,int blockSize){
		if((sizeDataRemove+freeSpace)>(blockSize-getMinFreeSpace(blockSize))){
			return -1; //underflow
		}else if((sizeDataRemove+freeSpace)==(blockSize-getMinFreeSpace(blockSize))){
			return 0; //en el limite
		}else if((sizeDataRemove+freeSpace)>blockSize){
			return -2;
		}
		return 1; //ninguna de las anteriores
	}
	


protected:
	int nextNode;   		//direccion del siguiente nodo en el mismo nivel
	int recAddr;			//direccion de este nodo en el archivo del arbol
	int minKeys;		 	//minimo numero de claves en un nodo
	int maxBKeys;			//maximo number de claves en un nodo
    int blockMaxSize;

	//Variables agregadas para conversion
	//Determina si el nodo es hoja o no, para su manejo diferenciado
	bool isLeaf;
	//array de punteros a los datos ingresados
	char** data;
	//en nodos hojas es el espacio libre del bloque
	int freeSpace;
	//tamaño que ocupa guardar cada key(se va restando por cada insert al freeSpace)
	int keySize;




	void clear(){ this->numKeys = 0; recAddr = -1; }

	int  init(int maxSize){
		this->nextNode = -1;
		this->recAddr = -1;
		this->maxBKeys = this->maxKeys-1;
		this->minKeys = 2;

		//tamaño del bloque ocupado con datos de metadata del bloque, se resta al freeSpace en este init
		//tamaño n.keys + n.keys + tamaño espacio libre + espacio libre + tamaño nod.sig. + nod.sig
		int blockMetadataSize = sizeof(short)*3 + sizeof(int)*3 ;
		//tamaño clave + clave
		this->keySize = sizeof(short)+sizeof(keyType);
		//bloque ocupado - metadata bloque
		this->freeSpace = maxSize - blockMetadataSize;

		this->blockMaxSize = this->freeSpace; //lo que ocupa el bloque
		//los nodos se inician como hojas
		this->isLeaf = 1;

		for (int i = 0; i < this->maxKeys; i++) {
			this->data[i]=NULL;
		}

		return 1;
	}

#ifndef BPLUSTREE_H_
	template <class keyType>
	friend class BPlusTree <class keyType>;
#endif
};




#endif /* BTREENODE_H_ */
