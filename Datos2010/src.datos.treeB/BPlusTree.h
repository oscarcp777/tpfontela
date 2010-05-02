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
#include "../src.datos.storage/FreeBlockController.h"
#include "../src.datos.storage/TextFile.h"
#include "BTreeNode.h"

using namespace std;
const int MAX_HEIGHT = 5;

template <class keyType>
class BPlusTree{

public:

	BPlusTree(int blockSize, int keySize = sizeof(keyType), int unique = 1)
	:buffer(blockSize),
	 bTreeFile(this->buffer),
	 root(blockSize,keySize) {

		this->output=new TextFile();
		this->freeBlocks = new FreeBlockController(blockSize);
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
		delete this->nodes;
		delete this->freeBlocks;
		delete this->output;
	}

	/**
	 * Abre un BTree existente, valida que tamaño del bloque seteado sea el correcto de lo contrario lanza
	 * una excepcion
	 */
	int  open(string name, ios_base::openmode mode){
		int result = this->bTreeFile.open(name,mode);
		if (!result) return result;
		//Lee profundidad y valida blockSize
		result = this->readMetadata();
		if (!result) return result;
		if (this->height > 1)
			this->root.setIsLeaf(false);
		//Carga raiz
		result = this->bTreeFile.read(this->root);
		this->root.setRecAddr(result);
		this->freeBlocks->open(name, mode);
		return 1;
	}

	int create(string name, ios_base::openmode mode){
		int result = this->bTreeFile.create(name, mode);
		if (!result) return result;
		//Escribe profundidad
		result = this->writeMetadata();
		if (result == -1) return 0;
		//Agrega nodo raiz
		result = this->bTreeFile.write(this->root);
		this->root.setRecAddr(result);
		this->freeBlocks->create(name, mode);
		return result != -1;
	}

	int  close(){

		int result = this->bTreeFile.BufferFile::reWind();
		result = this->writeMetadata();
		if (result == -1) return 0;
//		result = this->bTreeFile.write(this->root);
//		if (result == -1) return 0;
		this->freeBlocks->close();
		return this->bTreeFile.close();
	}

	int  insert(const keyType key, const char* data){
		int result; int level = this->height -1;
		int newLargest = 0;
		keyType prevKey, largestKey;
		BNode* thisNode, *newNode, * parentNode;
		thisNode = this->findLeaf(key);
		if (thisNode->getNumKeys()!=0)
			if(key > thisNode->largestKey())
			{newLargest = 1; prevKey = thisNode->largestKey();}
		/*
		 * En result se encuentra lo que retorna el metodo insert del nodo.
		 * Si result es -1 entonces se produjo un overflow del
		 * nodo. Si result es 0, no se pudo realizar la inserccion.
		 * Y finalmente si result es 1 se realizo la inserccion
		 * en forma correcta.
		 */
		result = thisNode->insert(key,data);
		/*
		 * Esto nose bien que hace pero si la inserccion fue
		 * fallida no tendira que hacer esto.
		 */
		if (newLargest && (result != 0))
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
		/*
		 * Chequeo el resultado de result para no acceder a
		 * disco innecesariamente.
		 */
		if(result != 0){
			this->store(thisNode);
		}

		if (level >= 0){
			if(result == 0){
				return 0;
			}
			return 1; //insertar completado
		}
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
		this->store(&root);
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

	void  print(string fileName){


		this->output->open(fileName);
		this->freeBlocks->print(this->output->getStream());
		ostream& aux = this->output->getStream();

		aux <<"\nArbol B de profundidad " <<this->height<<" es "<<endl;
		this->root.print(aux);
		if (this->height >1)
			for(int i = 0; i<this->root.getNumKeys();i++){
				this->print(aux, this->root.getRecAddrs()[i], 2);
			}
		aux << "end of Arbol B"<<endl;
		this->output->close();
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
		this->nodeSecuentSet = &this->root;
		keyType* keysRoot = this->nodeSecuentSet->getKeys();

		if (this->nodeSecuentSet->getNumKeys() == 0){

			return NULL;
		}else{

			int key = keysRoot[0];
			/*
			 * Si el nodo es hoja, obtenemos el primer elemento de este nodo, que
			 * es tambien el primer dato del arbol. Sino es hoja tenemos que recorrer
			 * el arbol hasta encontrar el primer elemento.
			 */
			if(this->nodeSecuentSet->getIsLeaf()){

				this->nodeSecuentSet = findLeaf(key);
				/*
				 * Verifica si en el nodo hoja tiene solo una clave, si es asi
				 * la siguiente clave tiene que ser -1 al igual que el siguiente
				 * nodo y se tiene que setear el atributo endSecuentSet.
				 */

				if(this->nodeSecuentSet->getNumKeys()==1){

					this->nextKey = this->nodeSecuentSet->getKeys()[1];
					this->nextNode = -1;
					this->endSecuentSet = true;
				}else{
					this->nextKey = this->nodeSecuentSet->getKeys()[1];
					this->nextNode = this->nodeSecuentSet->getNextNode();
					this->endSecuentSet = false;
				}

				return this->nodeSecuentSet->getData()[0];

			}else{

				int recaddr, level;
				/*
				 * Recorro el arbol, sino esta el nodo en el arbol se carga en
				 * memoria.
				 */
				for(level = 1; level < this->height; level++){

					recaddr = this->nodes[level-1]->getRecAddrs()[this->nodes[level-1]->search(key,-1,0)];
					if (this->nodes[level] == NULL || this->nodes[level]->getRecAddr() != recaddr)
						this->nodes[level] = this->fetch(recaddr,level+1);

					if (this->nodes[level]->getIsLeaf()){
						break;
					}else{
						key = this->nodes[level]->getKeys()[0];
					}
				}
				this->nodeSecuentSet = this->nodes[level];
				if(this->nodeSecuentSet->getNumKeys()==1){

					this->nextKey = this->nodeSecuentSet->getKeys()[1];
					this->nextNode = -1;
					this->endSecuentSet = true;
				}else{
					this->nextKey = this->nodeSecuentSet->getKeys()[1];
					this->nextNode = this->nodeSecuentSet->getNextNode();
					this->endSecuentSet = false;
				}
				return this->nodeSecuentSet->getData()[0];
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
			/*
			 * Aca tendria q usar el nodo cargano en memoria
			 * this->nodes[level] ...
			 */
			char* dataReturn;
			int index = this->nodeSecuentSet->search(this->nextKey);

			if((index < (this->nodeSecuentSet->getNumKeys() - 1)) && (index!=-1)){

				dataReturn = this->nodeSecuentSet->getData()[index];
				this->nextKey = this->nodeSecuentSet->getKeys()[index + 1];
				this->nextNode = this->nodeSecuentSet->getNextNode();
			}else{

				dataReturn = this->nodeSecuentSet->getData()[index];
				if(this->nextNode != -1){

					BNode* nextNode = fetch(this->nextNode,this->height);
					this->nodeSecuentSet = nextNode;
					//chequear cuando retorna NULL
					if(this->nodeSecuentSet != NULL){

						this->nextKey = this->nodeSecuentSet->getKeys()[0];
						this->nextNode = this->nodeSecuentSet->getNextNode();
					}else{

						this->endSecuentSet = true;
					}

					//como fetch instancia una BNodo lo tengo que
					//deetear aca es posible que se cuelgue memoria.
					//delete nextNode;
				}else{

					this->endSecuentSet = true;
				}
							}
			return dataReturn;

		}else{

			return NULL;
		}
		return NULL;
	}
	/*
	 * Flag que determina el final del sucuent set.
	 * Antes de invocar este metodo, se tiene que invoca el
	 * getFirstElementSecuentSet ...
	 */
	bool getEndSecuentSet(){

		return this->endSecuentSet;
	}

	/*void updateFreeSpaceDataAddNode(BTreeNode<keyType>* nodo,keyType key,char*data){
		int sizeRemoveFreeSpace;

		if(nodo->getIsLeaf()){
			//string data = search(key,-1);
			sizeRemoveFreeSpace = strlen(data)+sizeof(short)+nodo->getKeySize();
		}else
			sizeRemoveFreeSpace = nodo->getKeySize();

		nodo->setFreeSpace(nodo->getFreeSpace()-sizeRemoveFreeSpace);
	}*/

	/*void updateFreeSpaceRemoveDataNode(BTreeNode<keyType>* nodo,keyType key){

		int sizeAddFreeSpace;

		if(nodo->getIsLeaf()){
			string data = search(key,-1);
			sizeAddFreeSpace = data.length()+sizeof(short)+nodo->getKeySize();
		}else
			sizeAddFreeSpace = nodo->getKeySize();

		nodo->setFreeSpace(nodo->getFreeSpace()+sizeAddFreeSpace);
	}*/

	/* METODOS PARA LA BAJA DEL ARBOL */

	int actualizarIndexSet(keyType keyVieja, keyType keyNueva,bool escribirNodo){

		BNode* nodo;
		int nivel;

		nivel=this->height-2;

		if(nivel>=0){
			do{
				nodo=this->nodes[nivel];
				nodo->updateKey(keyVieja,keyNueva);
				this->store(nodo);

				if(nodo->largestKey()==keyNueva)
				nivel--;
				else
					break;

			}while(nivel>=0);
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

		this->findLeaf(nodoInterno->largestKey());

		this->height--;

		this->writeMetadata();

		return 0;
	}

//	int underflowNodoInterno(BTreeNode<keyType>* nodo,keyType key, int nivel){
//
//	}

	int underflowRootNodeInterno(BTreeNode<keyType>* nodoPadre,BTreeNode<keyType>* nodo,keyType key){
//			if((nodoPadre->search(key)!=-1) && ((!nodoPadre->getIsLeaf() && ((nodoPadre->getNumKeys()-1)<nodoPadre->getMinKeys(blockSize)))
//					|| (nodoPadre->getIsLeaf() && nodoPadre->caseDataRemove(tamanioDato(key,nodoPadre),blockSize)==-1))){
//				if((this->height-2 == 0)&&((nodoPadre->getNumKeys()-1)==1)) //si solo tengo 2 niveles y el padre tiene 1 sola clave, subo todo a la raiz
//					resolverUnderflowNodoInterno(NULL,nodoPadre,nodo,key);
//				else
//					resolverUnderflowNodoInterno(this->nodes[this->height-3],nodoPadre,nodo,key);
//
//			}
			return 1;
	}

	int eliminarIndexSet(keyType key, BTreeNode<keyType>* nodoPadre,int nivelArbol){

			 //CASO 1: Si el nodo interno nodoPadre tiene mas claves que el minimo y la key (clave) no es la clave mas grande en el nodoPadre
			 //		   simplemente borrar key de nodoPadre
		if((nodoPadre->getNumKeys()-1)>1){
			if(((nodoPadre->getNumKeys()-1)>nodoPadre->getMinKeys(blockSize) || nivelArbol==0) && key!=nodoPadre->largestKey()){
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				this->store(nodoPadre);

			}/*CASO 2: Si el nodo interno nodoPadre tiene mas claves que el minimo numero de claves y la clave key es la mas grande en nodoPadre, borrar la clave key y modificar el indice de
			           mayor nivel que direcciona a la nueva clave mas grande en nodoPadre.
			  */
			else if(((nodoPadre->getNumKeys()-1)>nodoPadre->getMinKeys(blockSize) || nivelArbol==0) && nodoPadre->largestKey()==key){
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				actualizarIndexSet(key,nodoPadre->largestKey(),true);
				this->store(nodoPadre);

			}else{

			    /*CASO 3: Si el nodo padre tiene exactamente el minimo numero de claves y uno de los vecinos del nodo padre tiene pocas claves (cantidad de claves minima), mergear
		          		  nodo padre con este vecino y eliminar una clave desde el nodo padre. */

				/* CASO 4: Si el nodo padre tiene exactamente el minimo numero de claves y uno de los vecinos del nodo padre tiene muchas claves (cantidad mayor que la cantidad minima de claves),
						   redistribuir moviendo algunas claves desde un vecino hacia n, y modificar el indice mas alto para direccionar la nueva clave mayor en los nodos afectados.
				 */
				underflow(key,nodoPadre,nivelArbol-1);
			}
		}else{ //resolver underflow raiz para 1 clave (subir todo a la raiz)
			nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
			return -2;
		}

		return 1;
	}

	int tamanioDato(keyType key,BTreeNode<keyType>* nodo){
		int sizeKey=nodo->getKeySize();

		if(nodo->getIsLeaf()){
			int index=nodo->search(key);
			int tamanio=(sizeKey + sizeof(short) +strlen(nodo->getData()[index]));
			return tamanio;
		}

		return sizeKey;
	}

	/**
	 * Obtiene en nodoVecino al nodoHoja dando prioridad al vecino con cantidad de claves minimas para realizar la concatenacion de este nodo con el nodoHoja
	 * donde se produjo el underflow.
	 * En caso de que ambos nodos supere la cantidad de claves minimas retornara por default el nodo de la izquierda para redistribuir las claves
	 * con el nodoHoja donde se produjo el underflow.
	 *
	 * Pasandole al metodo nodeLeft con 1 estoy exigiendole a este metodo que me retorne el nodoVecinoIzquierdo.
	 * Pasandole al metodo nodeLeft con un valor distinto de 1 estoy exigiendole a este metodo que me retorne el nodoVecinoDerecho.
	 */

	BTreeNode<keyType>* obtenerNodoVecino(int* valNode,BTreeNode <keyType>* nodoPadre, keyType key,int nivel, int nodeLeft){
		int direccionNodoVecino;
		BNode* nodoVecino =NULL;
		*valNode=0;

		int indiceClave=nodoPadre->search(key);

		if(((indiceClave-1)>=0)&&(indiceClave+1<nodoPadre->getNumKeys())){ //Si puede obtener cualquiera de los dos nodos vecinos, obtengo el que yo quiero obtener
			if(nodeLeft==1)												   //sino entro al else y obtengo el nodoVecino que pueda obtener.
				direccionNodoVecino = nodoPadre->getRecAddrs()[indiceClave-1];
			else
					direccionNodoVecino = nodoPadre->getRecAddrs()[indiceClave+1];

			nodoVecino = this->fetch(direccionNodoVecino,nivel);

			*valNode= 1;

		}else if((indiceClave-1)>=0){ //obtengo el nodoVecino izquierdo
			direccionNodoVecino = nodoPadre->getRecAddrs()[indiceClave-1];
			nodoVecino = this->fetch(direccionNodoVecino,nivel);

			if(nodeLeft==1)
				*valNode= 2; //significa que lo pudo obtener, pero si le pide el nodoVecinoDerecho no lo va a poder obtener
			else
				*valNode= -1; //significa que no pudo obtener el nodo derecho, solo el izquierdo

		}else if(indiceClave+1<nodoPadre->getNumKeys()){ //obtengo el nodoVecino derecho
			direccionNodoVecino = nodoPadre->getRecAddrs()[indiceClave+1];
			nodoVecino = this->fetch(direccionNodoVecino,nivel);

			if(nodeLeft!=1)
				*valNode= 2; //significa que lo pudo obtener, pero si le pide el nodoVecinoIzquierdo no lo va a poder obtener
			else
				*valNode= -1; //significa que no pudo obtener el nodo izquierdo, solo el derecho

		}


		return nodoVecino;

	}


	void resolverUnderflowRaiz(BTreeNode <keyType>* nodoPadre,keyType key){
		BNode* nodoHoja;
		bool keyRemovida=false;
		int numKeys=nodoPadre->getNumKeys();
		BNode * newNode = new BNode(this->blockSize,this->keySize);
        keyType* vecKeysRemove = new keyType[newNode->getMaxKeys()];
        int posKeyRemove=0;
        int index;
		newNode->setIsLeaf(1);

		for(int i=0;i<numKeys;i++){
			nodoHoja=fetch(nodoPadre->getRecAddrs()[i],this->height);

			if(!keyRemovida){
				index=nodoHoja->search(key);
				if(nodoHoja->largestKey()==key){
					vecKeysRemove[posKeyRemove]=key;
					posKeyRemove++;
					keyRemovida=true;
				}
				nodoHoja->remove(key,nodoHoja->getRecAddrs()[index]);
			}else{
				vecKeysRemove[posKeyRemove]=nodoHoja->largestKey();
				posKeyRemove++;
			}

			newNode->merge(nodoHoja);
		}

			for(int i=0;i<=posKeyRemove;i++){
				keyType keyRemove=vecKeysRemove[i];
				nodoPadre->remove(keyRemove,nodoPadre->getRecAddrs()[nodoPadre->search(keyRemove)]);
			}

			nodoPadre->setIsLeaf(1);
			nodoPadre->merge(newNode);
			nodoPadre->setRecAddr(-1);
			nodoPadre->setNextNode(-1);

			store(nodoPadre);

			this->height--;

			this->writeMetadata();

			//delete newNode;  VER SE ESTA COLGANDO MEMORIA MALL
			delete[] vecKeysRemove;

	}

	/**
	 * En caso de que no se pueda hacer una redistribucion de nodos ni una concatenacion habra que balancear el arbol a un nivel anterior
	 * viendo el nodo interno (nodo padre) de la key a eliminar del nodo hoja, si tiene un nodo vecino con el cual se pueda redistribuir claves y/o
	 * realizar concatenacion, balanceando el arbol.
	 */


	int resolverUnderflowNodoInterno(BTreeNode <keyType>* nodoAbuelo, BTreeNode <keyType>* nodoPadre, BTreeNode <keyType>* nodoHoja, keyType key){

		if(nodoAbuelo==NULL){
			BNode* nodo = this->findLeaf(key);
			if(nodo!=nodoPadre)
				resolverUnderflowRaiz(nodoPadre,key);
			else{
				nodoPadre->remove(key,nodoPadre->getRecAddrs()[nodoPadre->search(key,-1)]);
				this->store(nodoPadre);
			}

			return 1;
		}

	/*	BNode* nodoVecino;
		BNode* nodoVecinoAux;

		if(nodoAbuelo==NULL){
			BNode* nodo = this->findLeaf(key);
			if(nodo!=nodoPadre)
			resolverUnderflowRaiz(nodoPadre,key);
			else{
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

			if(nodoHoja->getTamanioOcupado(blockSize)<nodoHoja->getMinFreeSpace(blockSize)){//el nodoVecinoAux se mergeo la hoja
				search(nodoVecinoAux->largestKey());
				nodoPadre=this->nodes[this->height-2];
				concatenarNodos(key,nodoPadre,nodoVecinoAux,nodoVecino,false);
			}else //el nodoHoja se mergeo con el nodoVecinoAux
				concatenarNodos(key,nodoPadre,nodoHoja,nodoVecino,false);

		return 1;*/
		return 0;
	}


	int concatenarNodos(keyType key,BTreeNode <keyType>* nodoPadre,BTreeNode <keyType>* nodo, BTreeNode <keyType>* nodoVecino){
		int ret_removeIndex=1;
		BNode* nodeMergeFather;

			if((key==nodoPadre->largestKey())&&((nodoVecino->getFreeSpace())>=(blockSize-(nodo->getFreeSpace()+tamanioDato(key,nodo))))){
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);

				if(nodo->getNumKeys()!=0){
				nodoPadre->updateAddr(key,nodoPadre->getRecAddrs()[nodoPadre->getNumKeys()-2]);
				ret_removeIndex=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-2);
				this->actualizarIndexSet(key,nodo->largestKey(),true);
				}else
					ret_removeIndex=eliminarIndexSet(key,nodoPadre,this->height-2);

				nodoVecino->merge(nodo);
				nodoVecino->setNextNode(nodo->getNextNode());
				freeBlocks->add(nodo->getRecAddr()); //al concatenar marco como libre el nodo hoja
				nodeMergeFather=nodoVecino;
			}else if(key==nodo->largestKey()){

				if((key<nodoVecino->getKeys()[0])&&((nodo->getFreeSpace()+tamanioDato(key,nodo))>=(blockSize-nodoVecino->getFreeSpace()))){
					nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
					//ret_removeIndex=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-2);
					//nodoPadre->updateKey(key,nodoVecino->largestKey());
					ret_removeIndex=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-2);
					actualizarIndexSet(key,nodoVecino->largestKey(),true);
					nodo->merge(nodoVecino);
					nodo->setNextNode(nodoVecino->getNextNode());
					freeBlocks->add(nodoVecino->getRecAddr()); //al concatenar marco como libre el nodo vecino
					nodeMergeFather=nodo;
				}else if((nodoVecino->getFreeSpace())>=(blockSize-(nodo->getFreeSpace()+tamanioDato(key,nodo)))){
					nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
					nodoPadre->updateKey(nodoVecino->largestKey(),nodo->largestKey());
					ret_removeIndex=eliminarIndexSet(key,nodoPadre,this->height-2);
					nodoVecino->merge(nodo);
					nodoVecino->setNextNode(nodo->getNextNode());
					freeBlocks->add(nodo->getRecAddr()); //al concatenar marco como libre el nodo hoja
					nodeMergeFather=nodoVecino;
				}else
					return -1;

				this->store(nodoPadre);
			}else{

				if((key<nodoVecino->getKeys()[0]) &&
				   ((nodo->getFreeSpace()+tamanioDato(key,nodo))>=(blockSize-nodoVecino->getFreeSpace()))){
					nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
					ret_removeIndex=eliminarIndexSet(nodoVecino->largestKey(),nodoPadre,this->height-2); //elimino porque el merge borra y inserta poniendo largestKey
					nodoPadre->updateKey(nodo->largestKey(),nodoVecino->largestKey());
					nodo->merge(nodoVecino);
					nodo->setNextNode(nodoVecino->getNextNode());
					freeBlocks->add(nodoVecino->getRecAddr()); //al concatenar marco como libre el nodo vecino
					nodeMergeFather=nodo;
				}else if(nodoVecino->getFreeSpace()>=blockSize-(nodo->getFreeSpace()+tamanioDato(key,nodo))){
					nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
					ret_removeIndex=eliminarIndexSet(nodo->largestKey(),nodoPadre,this->height-2);
					actualizarIndexSet(nodoVecino->largestKey(),nodo->largestKey(),true);
					//nodoPadre->updateKey(nodoVecino->getKeys()[nodoVecino->getNumKeys()-2],nodoVecino->largestKey());
					nodoVecino->merge(nodo);
					nodoVecino->setNextNode(nodo->getNextNode());
					freeBlocks->add(nodo->getRecAddr()); //al concatenar marco como libre el nodo hoja
					nodeMergeFather=nodoVecino;
				}else
					return -1;

				if(ret_removeIndex!=-2)
				this->store(nodoPadre);
			}

			this->store(nodoVecino);
			this->store(nodo);

			if(ret_removeIndex==-2){
				nodoPadre->remove(nodoPadre->getKeys()[0],nodoPadre->getRecAddrs()[0]);
				nodoPadre->setIsLeaf(1);
				nodoPadre->merge(nodeMergeFather);
				nodoPadre->setFreeSpace(nodoVecino->getFreeSpace());
				nodoPadre->setRecAddr(-1);
				nodoPadre->setNextNode(-1);
				freeBlocks->add(nodeMergeFather->getRecAddr()); //al concatenar marco como libre el nodo que se mergeo con el padre
				store(nodoPadre);
				this->height--;
				this->writeMetadata();
			}

		return 1;
	}


	int redistribuirClaves(keyType key,BTreeNode <keyType>* nodoPadre,BTreeNode <keyType>* nodo, BTreeNode <keyType>* nodoVecino){

			int sizeDataUnderflow=0;

			if(nodoVecino->getIsLeaf())
				sizeDataUnderflow=nodoVecino->getMinFreeSpace(blockSize);
			else
				sizeDataUnderflow=nodoVecino->getMinKeys(blockSize);

		    if(key==nodoPadre->largestKey()
		       && ((nodoVecino->getIsLeaf() && (nodoVecino->getFreeSpace()+tamanioDato(nodoVecino->largestKey(),nodoVecino))<=sizeDataUnderflow)
				|| (!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-1)>=sizeDataUnderflow))){ //la clave a eliminar esta en el padre y es la mayor, por lo que forma parte del index set
				actualizarIndexSet(key,nodo->getKeys()[nodo->getNumKeys()-2],true);
				nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
				if(nodo->getIsLeaf())
				nodo->insert(nodoVecino->largestKey(),nodoVecino->getData()[nodoVecino->getNumKeys()-1],nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);
				else
					nodo->insert(nodoVecino->largestKey(),NULL,nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);

				nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
				nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
			}else if(key==nodo->largestKey()){ //la clave a eliminar esta en el padre pero no es la mayor, por lo que no forma parte del index set

				if(key<nodoVecino->getKeys()[0] && 	((nodoVecino->getIsLeaf() && (nodoVecino->getFreeSpace()+tamanioDato(nodoVecino->getKeys()[0],nodoVecino))<=sizeDataUnderflow)
						|| (!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-1)>=sizeDataUnderflow))){ //paso la primer clave del nodoVecino
					if(nodo->getIsLeaf())
					nodo->updateKeyAndData(key,nodoVecino->getKeys()[0],nodoVecino->getData()[0]);
					else{
						nodo->updateKey(key,nodoVecino->getKeys()[0]);
						nodo->updateAddr(nodoVecino->getKeys()[0],nodoVecino->getRecAddrs()[0]);
					}

					nodoPadre->updateKey(key,nodoVecino->getKeys()[0]);
					nodoVecino->remove(nodoVecino->getKeys()[0],nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->getKeys()[0],-1)]);
				}else if(((nodoVecino->getIsLeaf() && (nodoVecino->getFreeSpace()+tamanioDato(nodoVecino->largestKey(),nodoVecino))<=sizeDataUnderflow)
									|| (!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-1)>=sizeDataUnderflow))){
					if(nodo->getIsLeaf())
					nodo->updateKeyAndData(key,nodoVecino->largestKey(),nodoVecino->getData()[nodoVecino->getNumKeys()-1]);
					else
						nodo->updateKey(key,nodoVecino->largestKey());

					nodoPadre->updateKey(key,nodo->largestKey());
					nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
					nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
				}

			}else{

				bool isNotUnderflowNodeSibling = false;

				if(nodo->largestKey()<nodoVecino->getKeys()[0]){
					isNotUnderflowNodeSibling= (nodoVecino->getIsLeaf() && (nodoVecino->getFreeSpace()+tamanioDato(nodoVecino->getKeys()[0],nodoVecino))<=sizeDataUnderflow)
											   || (!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-1)>=sizeDataUnderflow);
				}else{
					isNotUnderflowNodeSibling= (nodoVecino->getIsLeaf() && (nodoVecino->getFreeSpace()+tamanioDato(nodoVecino->largestKey(),nodoVecino))<=sizeDataUnderflow)
											   || (!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-1)>=sizeDataUnderflow);
				}

					if(isNotUnderflowNodeSibling){ //la clave a eliminar no esta en el padre
					nodo->remove(key,nodo->getRecAddrs()[nodo->search(key,-1)]);
					if(nodo->largestKey()<nodoVecino->getKeys()[0]){ //paso la primer clave del nodoVecino
						if(nodo->getIsLeaf())
							nodo->insert(nodoVecino->getKeys()[0],nodoVecino->getData()[0],nodoVecino->getRecAddrs()[0]);
						else
							nodo->insert(nodoVecino->getKeys()[0],NULL,nodoVecino->getRecAddrs()[0]);

						nodoPadre->updateKey(nodo->getKeys()[nodo->getNumKeys()-2],nodoVecino->getKeys()[0]);
						nodoVecino->remove(nodoVecino->getKeys()[0],nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->getKeys()[0],-1)]);
					}else{
						if(nodo->getIsLeaf())
							nodo->insert(nodoVecino->largestKey(),nodoVecino->getData()[nodoVecino->getNumKeys()-1],nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);
						else
							nodo->insert(nodoVecino->largestKey(),NULL,nodoVecino->getRecAddrs()[nodoVecino->getNumKeys()-1]);

						nodoPadre->updateKey(nodoVecino->largestKey(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
						nodoVecino->remove(nodoVecino->largestKey(),nodoVecino->getRecAddrs()[nodoVecino->search(nodoVecino->largestKey(),-1)]);
					}
				}else
					return -2; //deja al nodo vecino en underflow, probar redistribuir con el otro nodo vecino si es posible
			}

			this->store(nodo);
			this->store(nodoPadre);
			this->store(nodoVecino);

			if((nodo->getIsLeaf() && nodo->getFreeSpace()<=nodo->getMinFreeSpace(blockSize))
				|| (!nodo->getIsLeaf() && nodo->getNumKeys()>=nodo->getMinKeys(blockSize)))
				return 1; //quedo fuera de underflow
		return -1;
	}

	keyType obtenerClaveComparacion(keyType key,BTreeNode <keyType>* nodoVecino){
		if(nodoVecino->getKeys()[0]>key) //nodoVecino derecho
				return nodoVecino->getKeys()[0];

		return nodoVecino->largestKey(); //nodoVecino izquierdo
	}

	int pasarDatosYclavesSinRemover(BTreeNode<keyType>* nodoOrigen, BTreeNode<keyType>* nodoDestino){
		bool next=true;
		keyType key;
		int indice;
		int sizeOfData=0;
		keyType largestKey;
		bool isLargestKeyRedistribuida=false;

		do{
		key = obtenerClaveComparacion(nodoDestino->largestKey(),nodoOrigen);
		indice=nodoOrigen->search(key);
		sizeOfData+=tamanioDato(key,nodoOrigen);

		bool isUnderflowNodoOrigen=((nodoOrigen->getIsLeaf() && ((nodoOrigen->getFreeSpace()+sizeOfData)>nodoOrigen->getMinFreeSpace(blockSize)))
			|| (!nodoOrigen->getIsLeaf() && ((nodoOrigen->getNumKeys()-1)<nodoOrigen->getMinKeys(blockSize))));

		if(isUnderflowNodoOrigen)
			break;

		if(nodoOrigen->largestKey()==key && !isLargestKeyRedistribuida){
			isLargestKeyRedistribuida=true;
			largestKey = key;
		}

		if(nodoOrigen->getIsLeaf())
		nodoDestino->insert(key,nodoOrigen->getData()[indice]);
		else
			nodoDestino->insert(key,NULL);

		nodoOrigen->remove(key,indice);
		//this->store(nodoOrigen);

		if((nodoDestino->getIsLeaf() && nodoDestino->getFreeSpace()<=nodoDestino->getMinFreeSpace(blockSize)) ||
		   (!nodoDestino->getIsLeaf() && nodoDestino->getNumKeys()>=nodoDestino->getMinKeys(blockSize))) //si quedo fuera de underflow no sigo en el while
			next=false;
		}while(next);

		if(isLargestKeyRedistribuida)
			actualizarIndexSet(largestKey,nodoOrigen->largestKey(),true);

		this->store(nodoOrigen);
		this->store(nodoDestino);

		return 1;
	}

	int concatenarDatosYclavesSinRemover(BTreeNode<keyType>* nodoOrigen, BTreeNode<keyType>* nodoDestino){
		if(nodoOrigen->largestKey()>nodoDestino->largestKey()){ //nodoOrigen a derecha y nodoDestino a izquierda
			nodoDestino->setNextNode(nodoOrigen->getNextNode());
			nodoDestino->merge(nodoOrigen);
			store(nodoDestino);
		}else{
			nodoOrigen->setNextNode(nodoDestino->getNextNode());
			nodoOrigen->merge(nodoDestino);
			store(nodoOrigen);
		}
		return 1;
	}

	int isContinueUnderflow(BTreeNode<keyType>* nodo,keyType keyRemove,BTreeNode<keyType>* nodoVecino,int sizeData){

		if(nodoVecino->getIsLeaf() && (nodoVecino->caseDataRemove(sizeData,blockSize)<0))
			return -2; //significa que el nodo vecino si se redistribuye esta clave quedara en underflow
		else if(!nodoVecino->getIsLeaf() && (nodoVecino->getNumKeys()-((sizeData)/(nodo->getKeySize())))<nodoVecino->getMinKeys(blockSize))
			return -2; //significa que el nodo vecino si se redistribuye esta clave quedara en underflow

		if(((nodo->getIsLeaf()) && (((nodo->getFreeSpace()+tamanioDato(keyRemove,nodo))-sizeData)<0)) ||
		   ((!nodo->getIsLeaf()) && ((nodo->getNumKeys()+((sizeData/*-tamanioDato(keyRemove,nodo)*/)/(nodo->getKeySize()))+nodo->getNumKeys()-1)>nodo->getMaxKeys())))
			return -2; //el ultimo dato hace que quede en overflow el nodo

		if(nodo->getIsLeaf()){
			if(((nodo->getFreeSpace()+tamanioDato(keyRemove,nodo))-sizeData)<=nodo->getMinFreeSpace(blockSize))
				return 1; //se fue del underflow
			else
				return -1; //sigue en underflow
		}else{
			if(((sizeData/*-tamanioDato(keyRemove,nodo)*/)/(nodo->getKeySize())+nodo->getNumKeys()-1)>=nodo->getMinKeys(blockSize))
				return 1; //se fue del underflow
			else
				return -1; //sigue en underflow
		}

		return 0;

	}

	/*
	 * 	Metodo que me dice si puede redistribuir las claves recursivamente
		en caso de que me devuelva true se llamara al metodo redistribuirClavesRecursivoUnderflow
		caso contrario no se llamara a este metodo y se evaluara si se puede hacer la concatenacion
		con alguno de los nodos vecinos
		en caso de no poder porque los hace quedar en overflow quedar� dicho nodo en underflow
		eliminando la clave que produce dicho underflow.

		Este metodo me retornara 1 si se puede redistribuir las keys de manera de no dejar en underflow el nodo
		Me devolvera 2 si se puede redistribuir las keys con los dos nodos vecinos de manera de no dejar en underflow
		ambos nodos.
		Caso contrario me retornara -1 y tendre que ver si se puede concatenar con uno de los nodos vecinos.

		El index-set se compara distinto, igual que en un b. Hacer solo esto para los nodos hoja.
		En el momento de que se elimina una clave que sea la mayor en el nodo hoja o sea que este en el nodo interno
		ahi tendre que balancear el index-set verificando de que no haya underflow en los nodos internos de esa rama.

	 */

	int isHasRedistribuirKeysRecursive(keyType key,BTreeNode<keyType>* nodo,int nivelPadre, int nivelNodo){

		BNode* nodoVecino;
		BNode* nodoPadre = this->nodes[nivelPadre];
		int valNodeSibling=0;
		nodoVecino=obtenerNodoVecino(&valNodeSibling,nodoPadre,nodo->largestKey(),nivelNodo,0); //obtengo el nodoVecino derecho
		int sizeData=0;
		int ret_valUnderflow;
		int pos_i=-1;
		bool continueRedistribucion=true;

		if(valNodeSibling==-1 || valNodeSibling==2){
			continueRedistribucion=false;
		}

		for(int i=0;i<nodoVecino->getNumKeys();i++){

			sizeData+=tamanioDato(nodoVecino->getKeys()[i],nodoVecino);
			ret_valUnderflow=isContinueUnderflow(nodo,key,nodoVecino,sizeData);
			if(ret_valUnderflow!=-1){ //si no continua en underflow, (overflow, underflow del nodo vecino, o haber solucionado el underflow)
				pos_i=i;
				break;
			}

		}

		if(ret_valUnderflow==1)
			return 1; //se puede redistribuir con un nodo vecino

		if(ret_valUnderflow==-2 && continueRedistribucion){ //significa que la ultima clave para redistribuir hizo quedar en overflow el nodo, o en underflow el nodo vecino, y como posiblemente se puede redistribuir tambien con el otro nodo, lo evaluo
			sizeData-=tamanioDato(nodoVecino->getKeys()[pos_i],nodoVecino);
			if(valNodeSibling==1){ //significa que puedo obtener el nodoVecino izquierdo y ver si puedo redistribuir con este nodo tambien sin quedar en overflow
				nodoVecino=obtenerNodoVecino(&valNodeSibling,nodoPadre,nodo->largestKey(),nivelNodo,1); //cambia la referencia del nodoVecino

				for(int i=(nodoVecino->getNumKeys()-1);i>=0;i--){

					sizeData+=tamanioDato(nodoVecino->getKeys()[i],nodoVecino);
					ret_valUnderflow=isContinueUnderflow(nodo,key,nodoVecino,sizeData);
					if(ret_valUnderflow!=-1){
						break;
					}
				}
			}
		}else
			return -1; //no se puede redistribuir con ningun nodo vecino

		if(ret_valUnderflow==1)
			return 2; //se puede redistribuir con dos nodos vecinos

		return -1; //no se puede redistribuir con ningun nodo vecino.

	}

	int redistribuirSinEliminarClaves(BTreeNode<keyType>* nodo,BTreeNode<keyType>* nodoVecino, BTreeNode<keyType>* otroNodoVecino,int caso){

		if(caso==1 || caso==2) //nodoVecino derecho, y se pasan las claves de este nodo al nodo afectado (nodo)
		  pasarDatosYclavesSinRemover(nodoVecino,nodo);
		else if(caso==3){
			pasarDatosYclavesSinRemover(nodoVecino,nodo);
			pasarDatosYclavesSinRemover(otroNodoVecino,nodo);
		}
		return 1;

	}

	int redistribuirClavesRecursivoUnderflow(BTreeNode<keyType>* nodoPadre, BTreeNode<keyType>* nodo, keyType key,int nivelPadre,int redistribucionClaves){
			BNode* nodoVecino;
			int ret_val=0;
			nodoVecino=obtenerNodoVecino(&ret_val,nodoPadre,nodo->largestKey(),nivelPadre+2,0); //intento obtener el nodo derecho
			int caso=0;
			int ret_ini;
			bool redistribuyo=false;

			//hay que hacer que cuando se redistribuye una clave con eliminacion y queda en underflow, intento redistribuir con el otro nodo
			//vecino con eliminacion de clave. Luego

			ret_ini=redistribuirClaves(key,nodoPadre,nodo,nodoVecino); //hago la primera redistribucion con eliminacion de la clave del nodo

			if(ret_ini==-2){//no puedo redistribuir con el nodoVecino anterior pues me deja dicho nodoVecino en underflow
				nodoVecino=obtenerNodoVecino(&ret_val,nodoPadre,nodo->largestKey(),nivelPadre+2,1);
				ret_ini=redistribuirClaves(key,nodoPadre,nodo,nodoVecino);
			}

			if(redistribucionClaves==1 && ret_val==2 && ret_ini==-1){ //redistribuir con el nodoDerecho
				caso=1;
				redistribuirSinEliminarClaves(nodo,nodoVecino,NULL,caso);
				redistribuyo=true;
			}else if(redistribucionClaves==1 && ret_val==-1 && ret_ini==-1){ //redistribuir con el nodoIzquierdo
				caso=2;
				redistribuirSinEliminarClaves(nodo,nodoVecino,NULL,caso);
				redistribuyo=true;
			}else if(ret_ini==-1){ //redistribuir con ambos nodos
				caso=3;
				int otroVal=0;
				BNode* otroNodoVecino;
				otroNodoVecino=obtenerNodoVecino(&otroVal,nodoPadre,nodo->largestKey(),nivelPadre+2,1);
				redistribuirSinEliminarClaves(nodo,nodoVecino,otroNodoVecino,caso);
				redistribuyo=true;
			}

			if (!redistribuyo && ret_ini==-1)
				return -1;


		return 1;
	}

	int underflow(keyType key,BTreeNode<keyType>* nodo,int nivelPadre){

		BNode* nodoPadre=NULL;

		int indiceClave;
		int redistribucionClaves;
//		int retUnderflowRootNodeInterno;


		nodoPadre=this->nodes[nivelPadre];
		indiceClave=nodoPadre->search(key,-1); //si la encuentra el indice clave me dara la posicion de la clave en el array de claves del nodoPadre.

		if(indiceClave<0) //la clave a eliminar no esta en el padre "no forma parte del index set"
			indiceClave=nodoPadre->search(nodo->largestKey()); //busca el indice de la clave mayor en el padre

		//retUnderflowRootNodeInterno=underflowRootNodeInterno(nodoPadre,nodo,key);

		redistribucionClaves=isHasRedistribuirKeysRecursive(key,nodo,nivelPadre,nivelPadre+2);

		if(redistribucionClaves!=-1) //si no era caso de underflow en la raiz o nodo interno y se puede redistribuir
			redistribuirClavesRecursivoUnderflow(nodoPadre,nodo,key,nivelPadre,redistribucionClaves);
		else{ //si no era caso de underflow en la raiz o nodo interno, concateno
			int ret_concatenacion;
			int val_node=0;
			BNode* nodoVecino;
			nodoVecino=obtenerNodoVecino(&val_node,nodoPadre,nodo->largestKey(),nivelPadre+2,0);

			//if(val_node!=1)//significa que solo puede obtener un solo nodoVecino (el derecho o izquierdo, no es necesario saberlo aqui)
				ret_concatenacion=concatenarNodos(key,nodoPadre,nodo,nodoVecino);

			//else{ //veo si puedo concatenar con el otro nodo vecino

//				ret_concatenacion=concatenarNodos(key,nodoPadre,nodo,nodoVecino);

				if(ret_concatenacion==-1){
					BNode* otroVecino=obtenerNodoVecino(&val_node,nodoPadre,nodo->largestKey(),nivelPadre+2,1); //obtenego el nodo vecino izquierdo
					ret_concatenacion=concatenarNodos(key,nodoPadre,nodo,otroVecino);
				}

			//}

			return ret_concatenacion;

		}

		return 1;

	}

	int simpleRemove(BTreeNode<keyType>*nodoHoja,keyType key,int dir,bool removeWithUnderflow){
		/*CASO 1: Si el nodo hoja n tiene mas claves que el minimo y k (clave) no es la clave mas grande en n, simplemente borrar k de n*/
		if(((nodoHoja->caseDataRemove(tamanioDato(key,nodoHoja),blockSize)>=0 || removeWithUnderflow) && key!=nodoHoja->largestKey())||(this->height==1)){
			//updateFreeSpaceRemoveDataNode(nodoHoja,key);
			nodoHoja->remove(key,dir);

			this->store(nodoHoja);
			return 1;
		}/*CASO 2: Si el nodo hoja n tiene mas que el minimo numero de claves y la clave k es la mas grande en n, borrar la clave k y modificar el indice de
				           mayor nivel que direcciona a la nueva clave mas grande en n.
		 */
		else if(((nodoHoja->caseDataRemove(tamanioDato(key,nodoHoja),blockSize)>=0 || removeWithUnderflow) && key==nodoHoja->largestKey())||(this->height==1)){
			//updateFreeSpaceRemoveDataNode(nodoHoja,key);
			nodoHoja->remove(key,dir);
			actualizarIndexSet(key,nodoHoja->largestKey(),true);
			this->store(nodoHoja);
			return 1;
		}

		/*CASO 3 y 4: Si no salio por el caso 1 ni el caso 2, se produce un underflow con caso 3 o 4. */
		return -1;
	}

	int remover(keyType key){

		BNode* nodoHoja;
		int nivelPadreHoja;
		int ret_remove=1;
		bool removeWithUnderflow=false;

		nodoHoja=this->findLeaf(key);

		nivelPadreHoja=this->height-2;

		int index = nodoHoja->search(key);

		if(index==-1){
			return -1;
		}

		int dir = nodoHoja->getRecAddrs()[index];

		ret_remove=simpleRemove(nodoHoja,key,dir,removeWithUnderflow);

		if(ret_remove==-1)
		ret_remove=underflow(key,nodoHoja,nivelPadreHoja);

		if(ret_remove==-1){
			removeWithUnderflow=true;
			simpleRemove(nodoHoja,key,dir,removeWithUnderflow);
		}

		return ret_remove;
	}


	/* TERMINAN LOS METODOS PARA LA BAJA DEL ARBOL */

protected:
	typedef BTreeNode<keyType> BNode;
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
	BNode* nodeSecuentSet;
	BNode** nodes; 			//nodos disponibles

	FreeBlockController* freeBlocks;		//Manejador Bloques Libres
	TextFile* output;						//Archivo de texto donde se muestra el estado de la estructura


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
		BNode* newNode = new BNode(this->blockSize,this->keySize);
		int recAddr = freeBlocks->get();
		if (recAddr == -1)
			recAddr = this->bTreeFile.append(*newNode);
		else
			this->bTreeFile.write(*newNode,recAddr);
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

	/**
	 * Lee un buffer del tamaño de un bloque con la metadata del BTree, aquí se encuentra el tamaño
	 * del bloque utilizado en el archivo y la profundidad actual del árbol
	 */
	int readMetadata(){
		FixedFieldBuffer buffer(3,this->blockSize);
		buffer.addField(sizeof(int));
		buffer.addField(sizeof(int));
		buffer.addField(this->blockSize-(2*sizeof(int)));
		this->bTreeFile.BufferFile::readFromBuffer(buffer,0);
		int blockSizeAux;
		buffer.unPack(&blockSizeAux);
		buffer.unPack(&this->height);
		if (blockSizeAux != this->blockSize)
			throw string("BLOCK SIZE ERROR");
		return this->height != 0;
	}

	/**
	 * Escribe un buffer del tamaño de un bloque con la metadata del BTree, aquí se guarda el tamaño
	 * del bloque utilizado en el archivo y la profundidad actual del árbol
	 */
	int writeMetadata(){
		FixedFieldBuffer buffer(3,this->blockSize);
		buffer.addField(sizeof(int));
		buffer.addField(sizeof(int));
		buffer.addField(this->blockSize-(2*sizeof(int)));
		buffer.pack(&this->blockSize);
		buffer.pack(&this->height);
		return this->bTreeFile.BufferFile::writeFromBuffer(buffer,0);
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

};

#endif /* BPLUSTREE_H_ */
