/*
 *  BPlusTree.h
 *
 *  Created on: 02/04/2010
 *      Author: santiago
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../src.datos.utils/Object.h"
#include "../src.datos.buffer/RecordFile.h"
#include "../src.datos.buffer/FixedFieldBuffer.h"
#include "BTreeNode.h"

using namespace std;
const int MAX_HEIGHT = 5;
template <class keyType>
class BPlusTree{


public:

	BPlusTree(int order, int keySize = sizeof(keyType), int unique = 1)
	:buffer(1+2*order,sizeof(int)+order*keySize+order*sizeof(int)),
	 bTreeFile(this->buffer),
	 root(order) {
 		this->height = 1;
		this->order = order;
		this->poolSize = MAX_HEIGHT*2;
		this->nodes = new BNode * [poolSize];
		BNode::initBuffer(this->buffer,this->order);
		this->nodes[0] = &this->root;

	}

	~BPlusTree() {
		close();
		delete this->nodes;
	}


	int  open(string name, ios_base::openmode mode){

		int result = this->bTreeFile.open(name,mode);
		if (!result) return result;
		//Carga raiz
		this->bTreeFile.read(this->root);
		this->height = 1; // TODO encontrar profundidad en el archivo
		return 1;
	}

	int  create(string name, ios_base::openmode mode){

		int result = this->bTreeFile.create(name, mode);
		if (!result) return result;
		//Agrega nodo raiz
		result = this->bTreeFile.write(this->root);
		return result != -1;
	}

	int  close(){

		int result = this->bTreeFile.BufferFile::reWind();
		if (!result) return result;
		result = this->bTreeFile.write(this->root);
		if (result == -1) return 0;
		return this->bTreeFile.close();
	}

	int  insert(const keyType key, int recAddr){

		int result; int level = this->height -1;
		int newLargest = 0;
		keyType prevKey, largestKey;
		BNode* thisNode, *newNode, * parentNode;
		thisNode = this->findLeaf(key);
		//if(key > nodoActual->claveMayor())
		//TODO fijarse de cambiar largestKey en vez de int a keyType
		if (thisNode->getNumKeys()!=0)
			if(key > thisNode->largestKey())
			{newLargest = 1; prevKey = thisNode->largestKey();}

		result = thisNode->insert(key,recAddr);

		if (newLargest)
			for (int i = 0; i<this->height-1;i++){
				this->nodes[i]->updateKey(prevKey,key);
				if (i>0) this->store(this->nodes[i]);
			}

		while (result == -1){ //si hay overflow y no esta en la raiz
			//recordar clave mayor
			largestKey = thisNode->largestKey();
			//splitear el nodo
			newNode = this->newNode();
			thisNode->split(newNode);

			if(newNode->getRecAddr()!=thisNode->getNextNode())
				newNode->setNextNode(thisNode->getNextNode());
			thisNode->setNextNode(newNode->getRecAddr());

			this->store(thisNode);
			this->store(newNode);

			level--; //ir al nivel del padre
			if (level < 0) break;
			//hacer nuevoNodo padre del nodoActual
			parentNode = this->nodes[level];
			result = parentNode->updateKey(largestKey,thisNode->largestKey());
			result = parentNode->insert(newNode->largestKey(),newNode->getRecAddr());

			thisNode = parentNode;
		}

			this->store(thisNode);
			if (level >= 0) return 1; //insertar completado
			//sino hay que splitear la raiz
			int newAddr =  this->bTreeFile.append(this->root);
			//poner anterior raiz en archivo
			//insertar 2 claves en la nueva raiz
			this->root.getKeys()[0]= thisNode->largestKey();
			this->root.getRecAddrs()[0]=newAddr;
			this->root.getKeys()[1]= newNode->largestKey();
			this->root.getRecAddrs()[1]=newNode->getRecAddr();
			this->root.setNumKeys(2);
			this->height++;
			return 1;
	}

	int  remove(const keyType key, int dir){
		this->modificar(key,-1);
		return 1;
	}

	int  search(const keyType key, int dir){
		BNode* nodoHoja;
		nodoHoja = findLeaf(key);
		return nodoHoja->search(key,dir);
		return 1;
	}

	void  print(ostream & stream){

		stream <<"Arbol B de profundidad " <<this->height<<" es "<<endl;
		this->root.print(stream);
		if (this->height >1)
			for(int i = 0; i<this->root.getNumKeys();i++){
				this->print(stream, this->root.getRecAddrs()[i], 2);
			}
		stream << "end of Arbol B"<<endl;

	}

	void  print(ostream & stream, int dirNodo, int nivel){

		BNode* nodoActual = this->fetch(dirNodo);
		stream << "\nNodo en nivel "<<nivel<<" direccion " << dirNodo<< " ";
		nodoActual->print(stream);
		if (this->height > nivel){
			nivel++;
			for(int i = 0; i < nodoActual->getNumKeys(); i++){
				this->print(stream, nodoActual->getRecAddrs()[i], nivel);
			}
			stream << "final del nivel "<<nivel <<endl;
		}


	}


protected:
	typedef BTreeNode<keyType> BNode;
	FixedFieldBuffer buffer;
	RecordFile<BNode> bTreeFile;
	BNode root;				//raiz
	int height;				//profundidad arbol
	int order;
	int poolSize;			//cantidad de nodos
	int metadataSize;
	BNode** nodes; 			//nodos disponibles


	BTreeNode<keyType>*  findLeaf(const keyType key){  //FindLeaf

		int recaddr, level;
		for(level = 1; level < this->height; level++){
			recaddr = this->nodes[level-1]->search(key,-1,0);
			this->nodes[level] = this->fetch(recaddr);
		}
		return this->nodes[level-1];
	}

	BTreeNode<keyType>*  newNode(){
		//crea un nuevo nodo y lo inserta en el arbol y setea su direccion
		BNode* newNode = new BNode(this->order);
		int recAddr = this->bTreeFile.append(*newNode);
		newNode->setRecAddr(recAddr);
		return newNode;
	}

	BTreeNode<keyType>*  fetch(int recAddr){ 		//Fetch
		//carga este nodo desde el archivo en un nuevo nodo
		BNode* newNode = new BNode(this->order);
		int result = this->bTreeFile.read(*newNode,recAddr);
		if (result == -1) return NULL;
		newNode->setRecAddr(result);
		return newNode;
	}

	int  store(BNode* node){ //Store

		return this->bTreeFile.write(*node,node->getRecAddr());
	}

};

#endif /* BPLUSTREE_H_ */
