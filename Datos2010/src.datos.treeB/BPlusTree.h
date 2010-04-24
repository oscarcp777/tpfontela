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
		if(index != -1){

			return nodoHoja->getData()[index];
		}else{

			return NULL;
		}
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

		if (node->getNumKeys() == 0){

			return NULL;
		}else{

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
				if(node!=NULL){

					return node->getData()[0];
				}else{

					return NULL;
				}

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

	void updateFreeSpaceRemoveDataNode(BTreeNode<keyType>* nodo,keyType key){

		int sizeAddFreeSpace;

		if(nodo->getIsLeaf()){
			string data = search(key,-1);
			sizeAddFreeSpace = data.length()+sizeof(short);
		}else
			sizeAddFreeSpace = sizeof(short);

		nodo->setFreeSpace(nodo->getFreeSpace()+sizeAddFreeSpace);
	}

	/* METODOS PARA LA BAJA DEL ARBOL */

	int actualizarIndexSet(keyType keyVieja, keyType keyNueva,bool escribirNodo){

		BNode* nodo;
		int nivel;

		nivel=this->height-2;

		while(nivel>=0){

			nodo=this->nodes[nivel];
			nodo->updateKey(keyVieja,keyNueva);
			this->store(nodo);

			if(nodo->largestKey()==keyVieja)
				nivel--;

		}

		return 1;
	}


	int bajarUnNivel(int nivelInferiorNodo){

		BNode* nodoNivelInferior = this->nodes[nivelInferiorNodo];
		BNode* nodoInterno;
		int numKeys=nodoNivelInferior->getNumKeys();
		int numKeysNodoInterno=0;
		int* direccionesAux = new int[nodoNivelInferior->getNumKeys()];

		memcpy(direccionesAux,nodoNivelInferior->getRecAddrs(),(nodoNivelInferior->getNumKeys())*sizeof(int));

		for(int i=0;i<numKeys;i++){

			nodoInterno=this->fetch(direccionesAux[i],nivelInferiorNodo);
			numKeysNodoInterno=nodoInterno->getNumKeys();

			for(int j=0;j<numKeysNodoInterno;j++){

				if(j==numKeysNodoInterno-1){
					nodoNivelInferior->updateAddr(nodoInterno->largestKey(),nodoInterno->getRecAddrs()[j]);
				}else
					nodoNivelInferior->insert(nodoInterno->getKeys()[j],nodoInterno->getData()[j],nodoInterno->getRecAddrs()[j]);


			}

		}

		delete(direccionesAux);

		this->store(nodoNivelInferior);

		//nodoNivelInferior->serializar(this->buffer);

		this->findLeaf(nodoInterno->largestKey());

		this->height--;

		this->writeHeight();

		return 0;
	}

	int eliminarIndexSet(keyType key, BTreeNode<keyType>* nodoHoja,int nivelArbol,bool modificarDireccion,bool underflowNodoInterno){

		BNode* nodoPadre;

		nodoPadre=this->nodes[nivelArbol];

			/*CASO 1: Si el nodo hoja n tiene mas claves que el minimo y k (clave) no es la clave mas grande en n, simplemente borrar k de n*/
			if((nodoPadre->caseDataRemove(nodoPadre->getMinFreeSpace(blockSize),blockSize)>0) && key!=nodoPadre->largestKey()){
				if(modificarDireccion){
					nodoPadre->updateAddr(nodoHoja->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				}
				updateFreeSpaceRemoveDataNode(nodoPadre,key);
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				this->store(nodoPadre);

			}/*CASO 2: Si el nodo hoja n tiene mas que el minimo numero de claves y la clave k es la mas grande en n, borrar la clave k y modificar el indice de
			           mayor nivel que direcciona a la nueva clave mas grande en n.
			  */
			else if((nodoPadre->caseDataRemove(nodoPadre->getMinFreeSpace(blockSize),blockSize)>0) && nodoPadre->largestKey()==0){
				if(modificarDireccion){
					nodoPadre->updateAddr(nodoHoja->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				}
				updateFreeSpaceRemoveDataNode(nodoPadre,key);
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				actualizarIndexSet(key,nodoPadre->largestKey(),true);
				this->store(nodoPadre);

			}/*CASO 3 y 4: Si no salio por el caso 1 ni el caso 2, se produce un underflow con caso 3 o 4. */
			else{

				if(nodoPadre->caseDataRemove(nodoPadre->getMinFreeSpace(blockSize),blockSize)==0 && underflowNodoInterno){
					bajarUnNivel(nivelArbol);

					return -1; //underflow en nodo interno, se baja un nivel. Reduccion del orden del arbol
				}

				underflow(nodoPadre,key);
			}

		return 1;
	}


	/**
	 * Obtiene en nodoVecino al nodoHoja dando prioridad al vecino con cantidad de claves minimas para realizar la concatenacion de este nodo con el nodoHoja
	 * donde se produjo el underflow.
	 * En caso de que ambos nodos supere la cantidad de claves minimas retornara por default el nodo de la izquierda para redistribuir las claves
	 * con el nodoHoja donde se produjo el underflow.
	 */

	BTreeNode <keyType>* obtenerNodoVecino(BTreeNode <keyType>* nodoHoja, BTreeNode <keyType>* nodoPadreHoja, int indiceClave,int nivel,bool underflowNodoInterno){
		int direccionNodoHojaVecino;
		//char* claveAreemplazar;

		BNode* nodoHojaVecino;
		BNode* nodoHojaVecinoAux;

		if((indiceClave-1)>=0){
			direccionNodoHojaVecino = nodoPadreHoja->getRecAddrs()[indiceClave-1];
			//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave-1];
		}else if(indiceClave+1<nodoPadreHoja->getNumKeys()){
			direccionNodoHojaVecino = nodoPadreHoja->getRecAddrs()[indiceClave+1];
			//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave+1];
		}

		nodoHojaVecino = this->fetch(direccionNodoHojaVecino,nivel);

		//Retornara el nodoHojaVecino de la izquierda para hacer concatenacion en caso de que este en underflow el nodo interno o
		//redistribucion en caso de estar en underflow un nodo hoja
		if((nodoHojaVecino->caseDataRemove(nodoHojaVecino->getMinFreeSpace(blockSize),blockSize)>0) || (nodoHojaVecino->caseDataRemove(nodoHojaVecino->getMinFreeSpace(blockSize),blockSize)==0 && underflowNodoInterno))
			return nodoHojaVecino;
		else if(indiceClave+1<nodoPadreHoja->getNumKeys()){ //Retornara el nodoHojaVecino de la derecha
			direccionNodoHojaVecino = nodoPadreHoja->getRecAddrs()[indiceClave+1];
					//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave+1];
					nodoHojaVecinoAux = this->fetch(direccionNodoHojaVecino,nivel);
					if((nodoHojaVecinoAux->caseDataRemove(nodoHojaVecinoAux->getMinFreeSpace(blockSize),blockSize)>0) || (nodoHojaVecinoAux->caseDataRemove(nodoHojaVecinoAux->getMinFreeSpace(blockSize),blockSize)==0 && underflowNodoInterno))
						return nodoHojaVecinoAux;
		}

		return nodoHojaVecino; //sino retorno por default el nodoHojaVecino de la izquierda
	}


	void resolverUnderflowRaiz(BTreeNode <keyType>* nodoPadre,keyType key){
		BNode* nodoHoja;
		bool keyRemovida;
		int numKeys=nodoPadre->getNumKeys();

		for(int i=0;i<numKeys;i++){
			nodoHoja=fetch(nodoPadre->getRecAddrs()[i],1);

			if(nodoHoja->largestKey()==key)
				keyRemovida=true;

			updateFreeSpaceRemoveDataNode(nodoHoja,nodoHoja->largestKey());
			nodoHoja->remove(nodoHoja->largestKey(),nodoHoja->getRecAddrs()[nodoHoja->search(nodoHoja->largestKey(),-1)]);
			nodoPadre->merge(nodoHoja);
			store(nodoHoja);
		}


		if(!keyRemovida){
			updateFreeSpaceRemoveDataNode(nodoPadre,key);
			nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
		}
			nodoPadre->setRecAddr(-1);
			nodoPadre->setNextNode(-1);

			store(nodoPadre);

		 //   nodoPadre->serializar(this->buffer);

			this->height--;

			writeHeight();

	}

	/**
	 * En caso de que no se pueda hacer una redistribucion de nodos ni una concatenacion habra que balancear el arbol a un nivel anterior
	 * viendo el nodo interno (nodo padre) de la key a eliminar del nodo hoja, si tiene un nodo vecino con el cual se pueda redistribuir claves y/o
	 * realizar concatenacion, balanceando el arbol.
	 */


	int resolverUnderflowNodoInterno(BTreeNode <keyType>* nodoAbuelo, BTreeNode <keyType>* nodoPadre, BTreeNode <keyType>* nodoHoja, keyType key){

		BNode* nodoVecino;
		BNode* nodoVecinoAux;

		if(nodoAbuelo==NULL){
			BNode* nodo = this->findLeaf(key);
			if(nodo!=nodoPadre)
			resolverUnderflowRaiz(nodoPadre,key);
			else{
				updateFreeSpaceRemoveDataNode(nodoPadre,key);
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				this->store(nodoPadre);
			}

			return 1;
		}

		nodoVecino = obtenerNodoVecino(nodoPadre,nodoAbuelo,nodoAbuelo->search(nodoPadre->largestKey()),this->height,true);


			int indiceClave=nodoPadre->search(key);
			if(indiceClave<0)
				indiceClave=nodoPadre->search(nodoHoja->largestKey());
			nodoVecinoAux=obtenerNodoVecino(nodoHoja,nodoPadre,indiceClave,this->height,true);
			search(nodoHoja->largestKey()); //para actualizar la profundidad
			nodoPadre=this->nodes[this->height-2];
			concatenarNodos(key,nodoPadre,nodoHoja,nodoVecinoAux,true);

			if(nodoHoja->caseDataRemove(nodoHoja->getMinFreeSpace(blockSize),blockSize)<0){//el nodoVecinoAux se mergeo la hoja
				search(nodoVecinoAux->largestKey());
				nodoPadre=this->nodes[this->height-2];
				concatenarNodos(key,nodoPadre,nodoVecinoAux,nodoVecino,false);
			}else //el nodoHoja se mergeo con el nodoVecinoAux
				concatenarNodos(key,nodoPadre,nodoHoja,nodoVecino,false);

		return 1;
	}


	int concatenarNodos(keyType key,BTreeNode <keyType>* nodoPadre,BTreeNode <keyType>* nodo, BTreeNode <keyType>* nodoVecino,bool hasNodeFeal){
		if(!hasNodeFeal){

			if(key>nodoVecino->largestKey()){ //la clave a eliminar es mayor que la clave mayor del nodoVecino (nodoVecino a la izquierda)
				int ret=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-3,true,true); //el nodoPadre es el nodoHoja (nodoInterno, seria nodoPadre con el abuelo "this->profundidad-3")
				//actualizarIndexSet(nodoVecino->claveMayor(),nodo->claveMayor(),false);
				//
				if(ret!=-1)
				nodoVecino->merge(nodoPadre);

			}else{ //la clave a eliminar es menor que la clave mayor del nodoVecino (nodoVecino a la derecha)
				int ret=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-3,true,true);

				if(ret!=-1)
				nodoPadre->merge(nodoVecino);
			}
			this->store(nodoVecino);
			this->store(nodo);

		}else{
			if(key==nodoPadre->largestKey()){
				updateFreeSpaceRemoveDataNode(nodo,key);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				nodoPadre->updateAddr(key,nodoPadre->getRecAddrs()[nodoPadre->getNumKeys()-2]);
				updateFreeSpaceRemoveDataNode(nodoPadre,nodoVecino->largestKey());
				nodoPadre->remove(nodoVecino->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(nodoVecino->largestKey(),-1)]);
				this->actualizarIndexSet(key,nodo->largestKey(),true);

				nodoVecino->merge(nodo);
				nodoVecino->setNextNode(nodo->getNextNode());
			}else if(key==nodo->largestKey()){
				updateFreeSpaceRemoveDataNode(nodo,key);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				if(key<nodoVecino->getKeys()[0]){
					updateFreeSpaceRemoveDataNode(nodoPadre,nodoVecino->largestKey());
					nodoPadre->remove(nodoVecino->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(nodoVecino->largestKey(),-1)]);
					nodoPadre->updateKey(key,nodoVecino->largestKey());
					nodo->merge(nodoVecino);
					nodo->setNextNode(nodoVecino->getNextNode());
				}else{
					nodoPadre->updateKey(nodoVecino->largestKey(),nodo->largestKey());
					updateFreeSpaceRemoveDataNode(nodoPadre,key);
					nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
					nodoVecino->merge(nodo);
					nodoVecino->setNextNode(nodo->getNextNode());
				}

				this->store(nodoPadre);
			}else{
				updateFreeSpaceRemoveDataNode(nodo,key);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				if(key<nodoVecino->getKeys()[0]){
					updateFreeSpaceRemoveDataNode(nodoPadre,nodoVecino->largestKey());
					nodoPadre->remove(nodoVecino->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(nodoVecino->largestKey(),-1)]);
					nodoPadre->updateKey(nodo->largestKey(),nodoVecino->largestKey());
					nodo->merge(nodoVecino);
					nodo->setNextNode(nodoVecino->getNextNode());
				}else{
					nodoVecino->merge(nodo);
					updateFreeSpaceRemoveDataNode(nodoPadre,nodoVecino->largestKey());
					nodoPadre->remove(nodoVecino->largestKey(),nodoPadre->getRecAddrs()[nodoPadre->search(nodoVecino->largestKey(),-1)]);
					nodoPadre->updateKey(nodoVecino->getKeys()[nodoVecino->getNumKeys()-2],nodoVecino->largestKey());
					nodoVecino->setNextNode(nodo->getNextNode());
				}

				this->store(nodoPadre);
			}

			this->store(nodoVecino);
			this->store(nodo);
		}
		return 1;
	}


	int redistribuirClaves(keyType key,BTreeNode <keyType>* nodoPadre,BTreeNode <keyType>* nodo, BTreeNode <keyType>* nodoVecino/*,bool hasNodeFeal*/){

		    if(key==nodoPadre->largestKey()){ //la clave a eliminar esta en el padre y es la mayor, por lo que forma parte del index set
				actualizarIndexSet(key,nodo->getKeys()[nodo->getNumKeys()-2],false);
				updateFreeSpaceRemoveDataNode(nodo,key);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				nodo->insert(nodoVecino->largestKey(),nodoVecino->getData()[nodoVecino->getNumKeys()-1],nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);
				nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
				updateFreeSpaceRemoveDataNode(nodoVecino,nodoVecino->largestKey());
				nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
			}else if(key==nodo->largestKey()){ //la clave a eliminar esta en el padre pero no es la mayor, por lo que no forma parte del index set

				if(key<nodoVecino->getKeys()[0]){ //paso la primer clave del nodoVecino
					nodo->updateKey(key,nodoVecino->getKeys()[0]);
					nodoPadre->updateKey(key,nodoVecino->getKeys()[0]);
					updateFreeSpaceRemoveDataNode(nodoVecino,nodoVecino->getKeys()[0]);
					nodoVecino->remove(nodoVecino->getKeys()[0],nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->getKeys()[0],-1)]);
				}else{
					nodo->updateKey(key,nodoVecino->largestKey());
					nodoPadre->updateKey(key,nodo->largestKey());
					nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
					updateFreeSpaceRemoveDataNode(nodoVecino,nodoVecino->largestKey());
					nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
				}

			}else{ //la clave a eliminar no esta en el padre
				updateFreeSpaceRemoveDataNode(nodo,key);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				if(nodo->largestKey()<nodoVecino->getKeys()[0]){ //paso la primer clave del nodoVecino
					nodo->insert(nodoVecino->getKeys()[0],nodo->getData()[0],nodoVecino->getRecAddrs()[0]);
					nodoPadre->updateKey(nodo->getKeys()[nodo->getNumKeys()-2],nodoVecino->getKeys()[0]);
					updateFreeSpaceRemoveDataNode(nodoVecino,nodoVecino->getKeys()[0]);
					nodoVecino->remove(nodoVecino->getKeys()[0],nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->getKeys()[0],-1)]);
				}else{
					nodo->insert(nodoVecino->largestKey(),nodoVecino->getData()[nodoVecino->getNumKeys()-1],nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);
					nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
					updateFreeSpaceRemoveDataNode(nodoVecino,nodoVecino->largestKey());
					nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
				}
			}

			this->store(nodo);
			this->store(nodoPadre);
			this->store(nodoVecino);

		return 1;
	}


	int underflow(BTreeNode<keyType>* nodo,keyType key){

		BNode* nodoVecino;
		BNode* nodoPadre;
		int indiceClave;

		nodoPadre=this->nodes[this->height-2];
		indiceClave=nodoPadre->search(key,-1); //si la encuentra el indice clave me dara la posicion de la clave en el array de claves del nodoPadre.

		if(indiceClave<0) //la clave a eliminar no esta en el padre "no forma parte del index set"
			indiceClave=nodoPadre->search(nodo->largestKey(),-1); //busca el indice de la clave mayor en el padre

		nodoVecino=obtenerNodoVecino(nodo,nodoPadre,indiceClave,this->height,false);

		/*CASO 3: Si el nodo n tiene exactamente el minimo numero de claves y uno de los vecinos del nodo n tiene pocas claves (cantidad de claves minima), mergear
		          n con este vecino y eliminar una clave desde el nodo padre. */
		if((nodoVecino->caseDataRemove(nodoVecino->getMinFreeSpace(blockSize),blockSize)==0) && (nodo->caseDataRemove(nodo->getMinFreeSpace(blockSize),blockSize)==0)
			&& (nodoPadre->caseDataRemove(nodoPadre->getMinFreeSpace(blockSize),blockSize)>0))
			concatenarNodos(key,nodoPadre,nodo,nodoVecino,true);
		else if((nodoVecino->caseDataRemove(nodoVecino->getMinFreeSpace(blockSize),blockSize)==0) && (nodo->caseDataRemove(nodo->getMinFreeSpace(blockSize),blockSize)==0)
			&& (nodoPadre->caseDataRemove(nodoPadre->getMinFreeSpace(blockSize),blockSize)==0)){
			if(this->height-3 == -1)
			resolverUnderflowNodoInterno(NULL,nodoPadre,nodo,key);
			else
				resolverUnderflowNodoInterno(this->nodes[this->height-3],nodoPadre,nodo,key);
		}
		 /* CASO 4: Si el nodo n tiene exactamente el minimo numero de claves y uno de los vecinos de n tiene muchas claves (cantidad mayor que la cantidad minima de claves),
					redistribuir moviendo algunas claves desde un vecino hacia n, y modificar el indice mas alto para direccionar la nueva clave mayor en los nodos afectados.
		  */
		else if((nodoVecino->caseDataRemove(nodoVecino->getMinFreeSpace(blockSize),blockSize)>0) && (nodo->caseDataRemove(nodo->getMinFreeSpace(blockSize),blockSize)==0))
			redistribuirClaves(key,nodoPadre,nodo,nodoVecino);


		return 1;

	}


	int remover(keyType key, int dir){

		BNode* nodoHoja;
		int nivelArbol;

		nodoHoja=this->findLeaf(key);

		nivelArbol=this->height-2;

		/*CASO 1: Si el nodo hoja n tiene mas claves que el minimo y k (clave) no es la clave mas grande en n, simplemente borrar k de n*/
		if(((nodoHoja->caseDataRemove(nodoHoja->getMinFreeSpace(blockSize),blockSize)>0) && key!=nodoHoja->largestKey())||(this->height==1)){
			updateFreeSpaceRemoveDataNode(nodoHoja,key);
			nodoHoja->remove(key,dir);

			this->store(nodoHoja);
			return 1;
		}/*CASO 2: Si el nodo hoja n tiene mas que el minimo numero de claves y la clave k es la mas grande en n, borrar la clave k y modificar el indice de
		           mayor nivel que direcciona a la nueva clave mas grande en n.
		  */
		else if((nodoHoja->caseDataRemove(nodoHoja->getMinFreeSpace(blockSize),blockSize)>0) && key==nodoHoja->largestKey()){
			updateFreeSpaceRemoveDataNode(nodoHoja,key);
			nodoHoja->remove(key,dir);
			actualizarIndexSet(key,nodoHoja->largestKey(),true);
			this->store(nodoHoja);
			return 1;
		}/*CASO 3 y 4: Si no salio por el caso 1 ni el caso 2, se produce un underflow con caso 3 o 4. */

			underflow(nodoHoja,key);

			return 1;
	}


	/* TERMINAN LOS METODOS PARA LA BAJA DEL ARBOL */

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
