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
		//this->data = new char*[this->maxKeys];
		this->data = new char*[this->maxKeys];
		for (int i = 0; i < this->maxKeys; i++) {
			this->data[i]=NULL;
		}
		init(maxSize);
	 }

	~BTreeNode() {
		int i;
		for (i = 0; i < this->numKeys; ++i) {
			delete this->data[i];
		}
		delete this->data;
	}

	int  insert(const keyType key, const char* data, int recAddr = -1){
		int result;


		result = SimpleIndex<keyType>::insert(key, recAddr);
		if (result == -1) return 0; //fallo insercion
		if (this->isLeaf){
			string dataAux = data;
			int i;
			cout << dataAux.length() <<endl;
			char* dat = new char[dataAux.length()];
			memcpy(dat,data,dataAux.length());
			for (i = this->numKeys-1; i>=result; i--) {
				this->data[i+1]=this->data[i];
			}
			this->data[result] = dat;
			this->freeSpace -= (dataAux.length()+sizeof(short));  //key + short tamaño key
			this->freeSpace -= this->keySize;
			if (this->freeSpace <= 0)
				return -1;

		}else
			if (this->numKeys >= this->maxKeys) return -1; //overflow nodo
		return 1;
	}

	int  remove(const keyType key, int dir){
		int result;
		result = SimpleIndex<keyType>::remove(key, recAddr);
		if (!result) return 0; //fallo remover
		if (this->numKeys < this->minKeys) return -1; //underflow nodo
		return 0;
	}

	int search(const keyType key,const int recAddr = -1, const int exact = 1)const{
		//devuelve la posicion de la key en el vector
		return SimpleIndex<keyType>::find(key,recAddr,exact);
		//return SimpleIndex<keyType>::search(key, recAddr, exact);
	}

	keyType  largestKey(){ 	   //retorna el valor de la clave mayor
		if (this->numKeys > 0)
			return this->keys[this->numKeys-1];
		else return this->keys[0];

	}

	int  split(BTreeNode* newNode){ 		//mover al nuevo nodo

//		if (this->numKeys < this->maxKeys) return 0; // chequea si hay suficiente num de claves
		int midpt = (this->numKeys + 1)/2; //encuentra la primer clave a ser movida al nuevo nodo
		int numNewKeys = this->numKeys - midpt;
		//chequea que el numero de claves para el nuevo nodo este ok
//		if (numNewKeys > newNode->maxBKeys || numNewKeys < newNode->minKeys)
//			return 0;

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
				fromNode->data[this->numKeys+i] = this->data[i];
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

	int  pack(IOBuffer& buffer) const{
		int result;
		buffer.clear();
		result = buffer.pack(&this->numKeys);
		if (this->isLeaf){
			result = buffer.pack(&this->nextNode);
			result = buffer.pack(&this->freeSpace);
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.pack(&this->keys[i],sizeof(keyType));
//				int size = strlen(this->data[i]);
//				cout<<size<<endl;
				result = result && buffer.pack(this->data[i],strlen(this->data[i]));
			}
		}else{
			for (int i = 0; i<this->numKeys; i++){
				result = result && buffer.pack(&this->keys[i],sizeof(keyType));
				result = result && buffer.pack(&this->recAddrs[i]);
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
				this->data[i] = new char[len];
				memset(this->data[i],0,len);
				memcpy(this->data[i],auxData,len);
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

	void  print(ostream &) const{
		cout 	<<" Numero de keys en Nodo = "<<this->numKeys<< endl;
		for(int i = 0; i<this->numKeys; i++){
			if (isLeaf)
				cout << "\tKey["<<i<<"] "<<this->keys[i] << " dato "<<this->data[i]<<endl;
			else
				cout << "\tKey["<<i<<"] "<<this->keys[i] << " dir "<<this->recAddrs[i]<<endl;
		}
		if (isLeaf){
			cout<<"\t\tEspacio libre: "<<this->freeSpace<<endl;
			cout<<"\t\tApunta a direccion: "<<this->nextNode<<endl;

		}

	}

	//Inicializa buffer para el nodo
//	static int initBuffer(FixedFieldBuffer & buffer, int maxKeys, int keySize = sizeof(keyType)){
//		buffer.addField(sizeof(int));
//		buffer.addField(sizeof(int));
//		for (int i = 0; i < maxKeys; i++){
//			buffer.addField(keySize);
//			buffer.addField(sizeof(int));
//		}
//		return 1;
//
//	}

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
	}


protected:
	int nextNode;   		//direccion del siguiente nodo en el mismo nivel
	int recAddr;			//direccion de este nodo en el archivo del arbol
	int minKeys;		 	//minimo numero de claves en un nodo
	int maxBKeys;			//maximo number de claves en un nodo


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
		this->minKeys = this->maxBKeys / 2;

		//tamaño del bloque ocupado con datos de metadata del bloque, se resta al freeSpace en este init
		//tamaño n.keys + n.keys + tamaño espacio libre + espacio libre + tamaño nod.sig. + nod.sig
		int blockMetadataSize = sizeof(short)*3 + sizeof(int)*3 ;
		//tamaño clave + clave
		this->keySize = sizeof(short)+sizeof(keyType);
		// 0,7 del bloque ocupado - metadata bloque
		this->freeSpace = maxSize*0.7 - blockMetadataSize;
		//los nodos se inician como hojas
		this->isLeaf = 1;

		return 1;
	}

//	#ifndef BPLUSTREE_H_
//		friend class BPlusTree<keyType>;
//	#endif
};




#endif /* BTREENODE_H_ */
