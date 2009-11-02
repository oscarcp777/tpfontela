/*
 * NodeBSharp.cpp
 *
 *  Created on: 27/10/2009
 *      Author: richy
 */

#include "NodeBSharp.h"

NodeBSharp::NodeBSharp(int maxKeys, int tamanioLlave):numKeys(0),keys(0),direcciones(0) {
	// TODO Auto-generated constructor stub
	//this->clear();
	this->tamanioLlave = tamanioLlave;
	this->maxKeys = maxKeys+1;
	this->init();
	this->keys = new char*[this->maxKeys];
	this->direcciones = new int[this->maxKeys];
	for(int i=0;i<this->maxKeys;i++){
		this->keys[i]=new char(this->tamanioLlave);
	}
}

NodeBSharp::~NodeBSharp() {
	// TODO Auto-generated destructor stub
	delete keys;
	delete direcciones;
}

//Protected metods---------------

int NodeBSharp::init(){
	this->nodoSiguiente = -1;
	this->dir = -1;
	this->maxBKeys = this->maxKeys-1;
	this->minKeys = this->maxBKeys / 2;
	return 1;
}

int NodeBSharp::encontrar(char* key, int dir, int exacto){
	for(int i = 0; i < this->numKeys; i++){
		//if(this->getKeys()[i] < key ) continue; // no encontrado aun
		if(strcmp(this->getKeys()[i],key)<0) continue; // no encontrado aun
		if (strcmp(this->keys[i],key)==0){ //exact match
		//if (this->keys[i] == key){ //exact match
			if (dir < 0) return i;
			else if (dir == this->direcciones[i]) return i;
				 else return -1;
		}
		//no hay coincidencia exacta match: keys[i-1]<key<Keys[i]
		if (!exacto)//inexacta coincidencia con key
			return i;
		return -1;
	}
	//key > todas las key en el indice
	if (exacto == 1) return -1; //no exacto
	else return this->numKeys-1;

}

//-------------------

int NodeBSharp::insert(char* key, int dir){
	int i;
	int indice = this->encontrar(key);
	if(indice>=0) return 0; //key ya esta en arbol
	if (this->numKeys == this->maxKeys) return 0; //sin lugar para mas keys

	for(i = this->numKeys-1; i>=0; i--){
		//if (key > this->keys[i]) break; //insertar en ubicacion i+1
		if (strcmp(key,this->keys[i])>0) break; //insertar en ubicacion i+1
		this->keys[i+1] = this->keys[i];
		this->direcciones[i+1] = this->direcciones[i];
	}
	keys[i+1]=new char(this->tamanioLlave);
	memset(keys[i+1],0,this->tamanioLlave);
	memcpy(this->keys[i+1],key,strlen(key));
	//this->keys[i+1] = strdup(key);
	this->direcciones[i+1] = dir;
	this->numKeys++;

	if(this->numKeys >= this->maxKeys) return -1; //overflow de nodo

	return 1;
}

int NodeBSharp::remover(char* key, int dir){
	int indice = this->encontrar(key,dir);
	if (indice < 0 ) return 0; //no esta en el indice la key
	for (int i = indice; i < this->numKeys; i++){
		this->keys[i] = this->keys[i+1];
		this->direcciones[i] = this->direcciones[i+1];
	}
	this->numKeys--;

	if (this->numKeys < this->minKeys) return -1; //underflow del nodo
	return 1;
}

char* NodeBSharp::claveMayor(){ 	    			//retorna el valor de la clave mayor
	if (this->numKeys > 0) return this->keys[this->numKeys-1];
	else return this->keys[0];

}

int NodeBSharp::split(NodeBSharp* nuevoNodo){ 		//mover al nuevo nodo

	if (this->numKeys < this->maxKeys) return 0; // chequea si hay suficiente num de keys
	int midpt = (this->numKeys + 1)/2; //encontrar la 1er key a ser movida al nuevo nodo
	int numNuevaKey = this->numKeys - midpt;
	//chequea que el numero de keys para el nuevo nodo este ok
	if (numNuevaKey > nuevoNodo->maxBKeys || numNuevaKey < nuevoNodo->minKeys)
		return 0;

	//mueve las keys y direcciones desde aca al nuevo nodo
	for(int i = midpt; i < this->numKeys; i++){
		nuevoNodo->keys[i-midpt] = this->keys[i];
		nuevoNodo->direcciones[i-midpt] = this->direcciones[i];
	}
	//setea el numero de keys en los 2 nodos
	nuevoNodo->numKeys = numNuevaKey;
	this->numKeys = midpt;
	return 1;
}

int NodeBSharp::merge(NodeBSharp* desdeNodo){		//mueve desde el nodo

	if (this->numKeys + desdeNodo->numKeys > this->maxKeys-1) return 0;
	//mueve keys y direcciones desde desdeNodo a aca
	for(int i = 0; i < desdeNodo->numKeys; i++){
		this->keys[this->numKeys+i] = desdeNodo->keys[i];
		this->direcciones[this->numKeys+i] = desdeNodo->direcciones[i];
	}
	//ajustar numero de keys
	this->numKeys += desdeNodo->numKeys;

	return 1;
}

int NodeBSharp::actualizarKey(char* viejaKey, char* nuevaKey, int dir){

	int direccion = this->buscar(viejaKey,dir);
	this->remover(viejaKey,direccion);
	this->insert(nuevaKey,direccion);
	return 1;
}

int NodeBSharp::serializar(char* buffer){
	int nextByte = 0;
	memcpy(&buffer[nextByte],&this->numKeys,sizeof(int));
	nextByte+=sizeof(int);
	memcpy(&buffer[nextByte],&this->nodoSiguiente,sizeof(int));
	nextByte+=sizeof(int);
	for (int i = 0; i<this->numKeys; i++){
		//char aux[10];
		//memcpy(aux,this->keys[i],strlen(this->keys[i]));

		memcpy(&buffer[nextByte],this->keys[i],this->tamanioLlave);
		nextByte+=this->tamanioLlave;
		memcpy(&buffer[nextByte],&this->direcciones[i],sizeof(this->direcciones[i]));
		nextByte+=sizeof(this->direcciones[i]);
	}

	return 1;
}

int NodeBSharp::hidratar(char* buffer){
	int nextByte = 0;
	memcpy(&this->numKeys,&buffer[nextByte],sizeof(int));
	nextByte+=sizeof(int);
	memcpy(&this->nodoSiguiente,&buffer[nextByte],sizeof(int));
	nextByte+=sizeof(int);
	for (int i = 0; i<this->numKeys; i++){
		//keys[i]=new char(this->tamanioLlave);
		memset(keys[i],0,this->tamanioLlave);
		memcpy(this->keys[i],&buffer[nextByte],this->tamanioLlave);
		nextByte+=this->tamanioLlave;
		memcpy(&this->direcciones[i],&buffer[nextByte],sizeof(int));
		nextByte+=sizeof(this->direcciones[i]);
	}

	return 1;
}

int NodeBSharp::buscar(char* key, int dir, int exacto){

	int indice = this->encontrar(key,dir,exacto);
	if (indice < 0) return indice;
	return this->direcciones[indice];

}


void NodeBSharp::imprimir(ostream & stream){

	stream 	<<" Numero de keys en Nodo = "<<this->numKeys<< endl;
	for(int i = 0; i<this->numKeys; i++){
		stream << "\tKey["<<i<<"] "<<this->keys[i] << " direccion "<<this->direcciones[i]<<endl;
	}
	stream<<"\t\tApunta a direccion: "<<this->nodoSiguiente<<endl;
}

void NodeBSharp::modificarDireccion(char* key,int dir){
	for(int i = 0; i < this->numKeys; i++){
			if (strcmp(this->keys[i],key)==0){ //exact match
				this->direcciones[i]=dir;
			}

		}
}


