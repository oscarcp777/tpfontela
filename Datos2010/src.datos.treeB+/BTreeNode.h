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
	BTreeNode(int maxKeys, int unique = 1):SimpleIndex<keyType>(maxKeys+1, unique) { init(); }

	~BTreeNode() { }

	int  insert(const keyType key, int recAddr){
		int result;
		result = SimpleIndex<keyType>::insert(key, recAddr);
		if (!result) return 0; //fallo insercion
		if (this->numKeys >= this->maxKeys) return -1; //overflow nodo
		return -1;
	}

	int  remove(const keyType key, int dir){
		int result;
		result = SimpleIndex<keyType>::remove(key, recAddr);
		if (!result) return 0; //fallo remover
		if (this->numKeys < this->minKeys) return -1; //underflow nodo
		return 0;
	}

	int search(const keyType key,const int recAddr = -1, const int exact = 1)const{
		return SimpleIndex<keyType>::search(key, recAddr, exact);
	}

	int  largestKey(){ 	   //retorna el valor de la clave mayor
		if (this->numKeys > 0)
			return this->keys[this->numKeys-1];
		else return this->keys[0];

	}

	int  split(BTreeNode* newNode){ 		//mover al nuevo nodo

		if (this->numKeys < this->maxKeys) return 0; // chequea si hay suficiente num de claves
		int midpt = (this->numKeys + 1)/2; //encuentra la primer clave a ser movida al nuevo nodo
		int numNewKeys = this->numKeys - midpt;
		//chequea que el numero de claves para el nuevo nodo este ok
		if (numNewKeys > newNode->maxBKeys || numNewKeys < newNode->minKeys)
			return 0;

		//mueve las claves y direcciones desde aca al nuevo nodo
		for(int i = midpt; i < this->numKeys; i++){
			newNode->keys[i-midpt] = this->keys[i];
			newNode->recAddrs[i-midpt] = this->recAddrs[i];
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
		}
		//ajustar numero de claves
		this->numKeys += fromNode->numKeys;

		return 1;
	}

	int  updateKey(keyType oldKey, keyType newKey, int recAddr = -1){

		int recaddr = this->search(oldKey,recAddr);
		if (recaddr < 0) return 0; 		// clave y direccion no encontradas
		this->remove(oldKey,recAddr);
		this->insert(newKey,recaddr);
		return 1;
	}

	int  pack(IOBuffer& buffer) const{
		int result;
		buffer.clear();
		result = buffer.pack(&this->numKeys);
		for (int i = 0; i<this->numKeys; i++){
			result = result && buffer.pack(&this->keys[i]);
			result = result && buffer.pack(&this->recAddrs[i]);
		}
		return result;
	}

	int  unpack(IOBuffer& buffer){
		int result;
		result = buffer.unPack(&this->numKeys);
		for (int i = 0; i<this->numKeys; i++){
			result = result && buffer.unPack(&this->keys[i]);
			result = result && buffer.unPack(&this->recAddrs[i]);
		}
		return result;
	}

	void  print(ostream &) const{
		SimpleIndex<keyType>::print(cout);
	}

	//Inicializa buffer para el nodo
	static int initBuffer(FixedFieldBuffer & buffer, int maxKeys, int keySize = sizeof(keyType)){
		buffer.addField(sizeof(int));
		for (int i = 0; i < maxKeys; i++){
			buffer.addField(keySize);
			buffer.addField(sizeof(int));
		}
		return 1;

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
		return nextNode;
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


protected:
	int nextNode;   		//direccion del siguiente nodo en el mismo nivel
	int recAddr;			//direccion de este nodo en el archivo del arbol
	int minKeys;		 	//minimo numero de claves en un nodo
	int maxBKeys;			//maximo number de claves en un nodo
	void clear(){ this->numKeys = 0; recAddr = -1; }

	int  init(){
		this->nextNode = -1;
		this->recAddr = -1;
		this->maxBKeys = this->maxKeys-1;
		this->minKeys = this->maxBKeys / 2;
		return 1;
	}

//	#ifndef BPLUSTREE_H_
//		friend class BPlusTree<keyType>;
//	#endif
};




#endif /* BTREENODE_H_ */
