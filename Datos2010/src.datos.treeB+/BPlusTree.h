/*
 *  BPlusTree.h
 *
 *  Created on: 02/04/2010
 *      Author: santiago
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include "../src.datos.utils/Object.h"
#include "../src.datos.buffer/RecordFile.h"
#include "../src.datos.buffer/VariableFieldBuffer.h"
#include "BTreeNode.h"

using namespace std;
const int MAX_HEIGHT = 5;

template <class keyType> class BPlusTree{

public:

	BPlusTree(int blockSize, int keySize = sizeof(keyType), int unique = 1)
	:buffer(blockSize),
	 bTreeFile(this->buffer),
	 root(blockSize,keySize) {
 		this->height = 1;
		this->blockSize = blockSize;
		this->nodes = new BNode * [MAX_HEIGHT];
		for (int i = 0; i < MAX_HEIGHT; i++) {
					this->nodes[i] = NULL;
		}
		this->keySize = keySize;
		this->nodes[0] = &this->root;

	}

	~BPlusTree() {
		close();

	}


	int  open(string name, ios_base::openmode mode){

		int result = this->bTreeFile.open(name,mode);
		if (!result) return result;
		//Leo profundidad
		result = this->readHeight();
		if (!result) return result;
		if (this->height > 1)
					this->root.setIsLeaf(false);
		//Carga raiz
		this->bTreeFile.read(this->root);

		return 1;
	}

	int  create(string name, ios_base::openmode mode){

		int result = this->bTreeFile.create(name, mode);
		if (!result) return result;
		//Escribo profundidad
		result = this->writeHeight();
		if (!result) return result;
		//Agrega nodo raiz
		result = this->bTreeFile.write(this->root);
		this->root.setRecAddr(result);
		return result != -1;
	}

	int  close(){

		int result = this->bTreeFile.BufferFile::reWind();
		if (!result) return result;
		//Escribo profundidad
		result = this->writeHeight();
		if (!result) return result;
		result = this->bTreeFile.write(this->root);
		if (result == -1) return 0;
//		for (int i = this->height -1 ; i >= 0; i--) {
//			if (this->nodes[i] != NULL)
//				delete this->nodes[i];
//		}
		delete this->nodes;
		return this->bTreeFile.close();
	}

	int  insert(const keyType key, const char* data){
		cout << "Insercion clave: " << key << endl;
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

		result = thisNode->insert(key,data);

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
			newNode->setIsLeaf(thisNode->getIsLeaf());
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
			parentNode->setIsLeaf(0);
			result = parentNode->updateKey(largestKey,thisNode->largestKey());
			result = parentNode->insert(newNode->largestKey(),NULL,newNode->getRecAddr());

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
			this->root.setIsLeaf(0);
			this->height++;
			delete newNode;
			return 1;
	}

	int  remove(const keyType key, int dir){
		this->modificar(key,-1);
		return 1;
	}

	char* search(const keyType key, int dir = -1){
		BNode* nodoHoja;
		nodoHoja = findLeaf(key);
		int index = nodoHoja->search(key,dir);
		return nodoHoja->getData()[index];
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

	void  print(ostream & stream, int dirNodo, int level){

		BNode* currentNode = this->fetch(dirNodo, level);
		stream << "\nNodo en nivel "<<level<<" direccion " << dirNodo<< " ";
		currentNode->print(stream);
		if (this->height > level){
			level++;
			for(int i = 0; i < currentNode->getNumKeys(); i++){
				this->print(stream, currentNode->getRecAddrs()[i], level);
			}
			stream << "final del nivel "<<level <<endl;
		}
		//delete currentNode;

	}
	/*
	 * Retorna el primer elemento del secuent set. Y posiciona un apuntador
	 * al siguente elemento del secuent set. Si el apuntador estaba apuntando
	 * a un elemento en particular, la llamada a este metodo setea este
	 * al siguiente del primer elemento.
	 */
	char* getFirstElementSecuentSet(){

		/*
		 * Obtengo el primer nodo del secuent set, luego
		 * obtengo el primer key del vector y asi por
		 * traer la hoja y sacar el dato.
		 */
		BNode* node;
		node = &this->root;
		keyType* keysRoot = this->root.getKeys();
		int key = keysRoot[0];

		if(node->getIsLeaf()){

			node = findLeaf(key);
			//Verifica si en el nodo hoja hay otra clave
			if(node->getNumKeys() > 0){

				this->nextKey = node->getKeys()[1];
				this->nextNode = node->getNextNode();
				this->endSecuentSet = false;
			}else{

				this->nextKey = -1;
				this->nextNode = -1;
				this->endSecuentSet = true;
			}
			return node->getData()[0];

		}else{
			int recaddr, level;
			for(level = 1; level < this->height; level++){
	//			recaddr = this->nodes[level-1]->search(key,-1,0);
				recaddr = this->nodes[level-1]->getRecAddrs()[this->nodes[level-1]->search(key,-1,0)];
				if (this->nodes[level] == NULL || this->nodes[level]->getRecAddr() != recaddr)
					this->nodes[level] = this->fetch(recaddr,level+1);
				/*
				 * Aca va los de si son hojas.
				 */

				if (this->nodes[level]->getIsLeaf())
					break;
				}
			this->nextKey = this->nodes[level]->getKeys()[1];
			this->nextNode = this->nodes[level]->getNextNode();
			this->endSecuentSet = false;

			return this->nodes[level]->getData()[0];
		}
	}
	/*
	 * Retorna el elemento actual del secuent set apuntado por el apuntador y
	 * setea este al siguiente elemento del secuent set. Si no existe el siguiente
	 * elemento, el apuntador toma un valor invalido.
	 */
	char* getNextElementSecuentSet(){

		if(!this->endSecuentSet){

			BNode* node;
			node = findLeaf(this->nextKey);
			int index = node->search(this->nextKey);
			int nextkey;

			if(index < (node->getNumKeys() - 1)){
				nextkey = index + 1;
				this->nextKey = node->getKeys()[nextkey];
				this->nextNode = node->getNextNode();
			}else{

				BNode* nextNode = fetch(this->nextNode,this->height);
				//chequear cuando retorna NULL
				if(nextNode != NULL){

					this->nextKey = nextNode->getKeys()[0];
					this->nextNode = nextNode->getNextNode();
				}else{

					this->endSecuentSet = true;
				}

				//como fetch instancia una BNodo lo tengo que
				//deetear
				delete nextNode;
			}
			return node->getData()[index];

		}else{

			return NULL;
		}
	}
	/*
	 * Flag que determina el final del sucuent set.
	 * Antes de invocar este metodo, se tiene que invoca el
	 * getFirstElementSecuentSet ...
	 */
	bool getEndSecuentSet(){

		return this->endSecuentSet;
	}

protected:
	typedef BTreeNode <keyType> BNode;
	VariableFieldBuffer buffer;
	RecordFile<BNode> bTreeFile;
	BNode root;				//raiz
	int height;				//profundidad arbol
	int blockSize;
	int keySize;
	int poolSize;			//cantidad de nodos
	int metadataSize;
	int nextKey;
	int nextNode;
	bool endSecuentSet;
	BNode** nodes; 			//nodos disponibles


	BTreeNode<keyType>*  findLeaf(const keyType key){  //FindLeaf

		int recaddr, level;
		for(level = 1; level < this->height; level++){
//			recaddr = this->nodes[level-1]->search(key,-1,0);
			recaddr = this->nodes[level-1]->getRecAddrs()[this->nodes[level-1]->search(key,-1,0)];
			if (this->nodes[level] == NULL || this->nodes[level]->getRecAddr() != recaddr)
				this->nodes[level] = this->fetch(recaddr,level+1);
			if (level + 1 == this->height)
				this->nodes[level]->setIsLeaf(1);
			else
				this->nodes[level]->setIsLeaf(0);
		}
		return this->nodes[level-1];
	}

	BTreeNode<keyType>*  newNode(){
		//crea un nuevo nodo y lo inserta en el arbol y setea su direccion
		//TODO agregar en metadata bloques libres y preguntar si hay para escribir un nodo ahi
		BNode* newNode = new BNode(this->blockSize,this->keySize);
		int recAddr = this->bTreeFile.append(*newNode);
		newNode->setRecAddr(recAddr);
		return newNode;
	}

	BTreeNode<keyType>*  fetch(int recAddr, int level){
		//carga este nodo desde el archivo en un nuevo nodo
		BNode* newNode = new BNode(this->blockSize,this->keySize);
		if (level == this->height)
			newNode->setIsLeaf(1);
		else
			newNode->setIsLeaf(0);
		int result = this->bTreeFile.read(*newNode,recAddr);
		if (result == -1) return NULL;
		newNode->setRecAddr(result);
		return newNode;
	}

	int  store(BNode* node){ //Store

		return this->bTreeFile.write(*node,node->getRecAddr());
	}

	int readHeight(){
		cout<<"Leo profundidad"<<endl;
		FixedFieldBuffer buffer(1,sizeof(int));
		buffer.addField(sizeof(int));
		this->bTreeFile.read(buffer);
		buffer.unPack(&this->height);
		return this->height != 0;
	}

	int writeHeight(){
		cout<<"Escribo profundidad"<<endl;
		FixedFieldBuffer buffer(1,sizeof(int));
		buffer.addField(sizeof(int));
		buffer.pack(&this->height);
		return this->bTreeFile.write(buffer);
	}

};

#endif /* BPLUSTREE_H_ */
