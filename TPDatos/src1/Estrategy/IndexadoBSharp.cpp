/*
 * IndexadoBSharp.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "IndexadoBSharp.h"
const int PROF_MAXIMA = 5;

IndexadoBSharp::IndexadoBSharp(int orden, int tamanioLlave) :raiz(orden, tamanioLlave) {

	this->orden = orden;

	this->tamanioRegistro = sizeof(int)+sizeof(int)+this->orden*tamanioLlave+this->orden*sizeof(int);
	this->tamanioLlave = tamanioLlave;
	this->archivoIndice = new Archivo();
	this->archivoIndice->setTamanio(this->tamanioRegistro);

	//el buffer se compone por: int-llave-int
	this->buffer = new char[this->tamanioRegistro];

	this->tamanioMetadata = 0;
	this->profundidad = 1;
	this->cantidadNodos = PROF_MAXIMA*2;
	this->nodos = new NodeBSharp*[this->cantidadNodos];
	this->nodos[0] = &this->raiz;

}

IndexadoBSharp::~IndexadoBSharp() {

	cerrar();
	delete this->nodos;
}

//Protected metods--------------

NodeBSharp* IndexadoBSharp::buscarHoja(char* key){  //FindLeaf

	int dir, nivel;
	for(nivel = 1; nivel < this->profundidad; nivel++){
		dir = this->nodos[nivel-1]->buscar(key,-1,0);
		this->nodos[nivel] = this->leerNodo(dir);
	}
	return this->nodos[nivel-1];
}

NodeBSharp* IndexadoBSharp::nuevoNodo(){
	//crea un nuevo nodo y lo inserta en el arbol y setea su direccion
	NodeBSharp* nuevoNodo = new NodeBSharp(this->orden,this->tamanioLlave);
	nuevoNodo->serializar(this->buffer);
	int dir = this->archivoIndice->guardar(this->buffer);
	nuevoNodo->setDir(dir);
	return nuevoNodo;
}

NodeBSharp* IndexadoBSharp::leerNodo(int dir){ 		//Fetch
	NodeBSharp* nuevoNodo = new NodeBSharp(this->orden,this->tamanioLlave);
	memset(this->buffer,0,this->tamanioRegistro);
	this->archivoIndice->leer(this->buffer,dir);
	nuevoNodo->hidratar(this->buffer);
	nuevoNodo->setDir(dir);
	return nuevoNodo;
}

int IndexadoBSharp::escribirNodo(NodeBSharp* nodo){ //Store

	nodo->serializar(this->buffer);
	return this->archivoIndice->guardar(this->buffer,nodo->getDir());
}

int IndexadoBSharp::escribirProfundidad(char* buffer){
	int aux = this->archivoIndice->getTamanio();
	this->archivoIndice->setTamanio(sizeof(int));
	memcpy(&buffer[0], &this->profundidad,sizeof(int));
	this->archivoIndice->guardar(buffer,0);
	this->archivoIndice->setTamanio(aux);
	return sizeof(int);
}

int IndexadoBSharp::leerProfundidad(char* buffer){
	int aux = this->archivoIndice->getTamanio();
	this->archivoIndice->setTamanio(sizeof(int));
	this->archivoIndice->leer(buffer,0);
	memcpy(&this->profundidad,&buffer[0],sizeof(int));
	this->archivoIndice->setTamanio(aux);
	return sizeof(int);
}

//---------------------------

int IndexadoBSharp::abrir(){

	this->archivoIndice->abrir();
	this->tamanioMetadata = this->leerProfundidad(this->buffer);
	memset(this->buffer,0,this->tamanioRegistro);
	this->archivoIndice->leer(this->buffer,this->tamanioMetadata);
	this->raiz.hidratar(this->buffer);
	//this->profundidad = 1;
	this->raiz.setDir(this->tamanioMetadata);
	return 1;
}

int IndexadoBSharp::crear(char* nombre, char* ruta){
	this->archivoIndice->setNombreArchivo(nombre);
	this->archivoIndice->setRuta(ruta);
	this->archivoIndice->crear();
	this->archivoIndice->abrir();
	this->tamanioMetadata = this->escribirProfundidad(this->buffer);
	this->raiz.serializar(this->buffer);
	this->archivoIndice->guardar(buffer,this->tamanioMetadata);
	this->archivoIndice->cerrar();
	this->raiz.setDir(this->tamanioMetadata);
	return 1;
}

int IndexadoBSharp::cerrar(){

	this->archivoIndice->irAlPrincipio();
	this->tamanioMetadata = this->escribirProfundidad(this->buffer);
	this->raiz.serializar(this->buffer);
	this->archivoIndice->guardar(buffer,this->tamanioMetadata);
	this->archivoIndice->cerrar();
	return 1;
}

int IndexadoBSharp::insertar(char* key, int dir){

	int resultado; int nivel = this->profundidad -1;
	int nuevoTamanio = 0;
	char* claveAnterior, *claveMayor;
	NodeBSharp* nodoActual, *nuevoNodo, * nodoPadre;
	nodoActual = this->buscarHoja(key);
	//cout<<"clave mayor nodo: "<< nodoActual->claveMayor()<<endl;
	//if(key > nodoActual->claveMayor())
	if (nodoActual->getNumKeys()!=0)
		if(strcmp(key,nodoActual->claveMayor())>0)
			{nuevoTamanio = 1; claveAnterior = nodoActual->claveMayor();}

	resultado = nodoActual->insert(key,dir);

	if (nuevoTamanio)
		for (int i = 0; i<this->profundidad-1;i++){
			this->nodos[i]->actualizarKey(claveAnterior,key);
			if (i>0) this->escribirNodo(this->nodos[i]);
		}

	while (resultado == -1){ //si hay overflow y no esta en la raiz


		//recordar claveMayor
		claveMayor = nodoActual->claveMayor();
		//splitear el nodo
		nuevoNodo = this->nuevoNodo();
		nodoActual->split(nuevoNodo);

		if(nuevoNodo->getDir()!=nodoActual->getNodoSiguiente())
			nuevoNodo->setNodoSiguiente(nodoActual->getNodoSiguiente());
		nodoActual->setNodoSiguiente(nuevoNodo->getDir());

		this->escribirNodo(nodoActual);
		this->escribirNodo(nuevoNodo);

		nivel--; //ir al nivel del padre
		if (nivel < 0) break;
		//hacer nuevoNodo padre del nodoActual
		nodoPadre = this->nodos[nivel];
		resultado = nodoPadre->actualizarKey(claveMayor,nodoActual->claveMayor());
		resultado = nodoPadre->insert(nuevoNodo->claveMayor(),nuevoNodo->getDir());


		nodoActual = nodoPadre;
	}

	this->escribirNodo(nodoActual);
	if (nivel >= 0) return 1; //insertar completado
	//sino hay que splitear la raiz


	this->raiz.serializar(this->buffer);
	int nuevaDir =  this->archivoIndice->guardar(this->buffer);
	//poner anterior raiz en archivo
	//insertar 2 keys en la nueva raiz
	this->raiz.getKeys()[0]= nodoActual->claveMayor();
	this->raiz.getDirecciones()[0]=nuevaDir;
	this->raiz.getKeys()[1]= nuevoNodo->claveMayor();
	this->raiz.getDirecciones()[1]=nuevoNodo->getDir();
	this->raiz.setNumKeys(2);
	this->profundidad++;
	return 1;
}




int IndexadoBSharp::remover(char* key, int dir){
	return 1;
}

int IndexadoBSharp::buscar(char* key, int dir){
	NodeBSharp* nodoHoja;
	nodoHoja = buscarHoja(key);
	return nodoHoja->buscar(key,dir);
	return 1;
}

void IndexadoBSharp::imprimir(ostream & stream){

	stream <<"Arbol B de profundidad " <<this->profundidad<<" es "<<endl;
	cout<<"Dir Raiz: "<<this->raiz.getDir()<<endl;
	this->raiz.imprimir(stream);
	if (this->profundidad >1)
		for(int i = 0; i<this->raiz.getNumKeys();i++){
			this->imprimir(stream, this->raiz.getDirecciones()[i], 2);
		}
	stream << "end of Arbol B"<<endl;

}

void IndexadoBSharp::imprimir(ostream & stream, int dirNodo, int nivel){

	NodeBSharp* nodoActual = this->leerNodo(dirNodo);
	stream << "\nNodo en nivel "<<nivel<<" direccion " << dirNodo<< " ";
	nodoActual->imprimir(stream);
	if (this->profundidad > nivel){
		nivel++;
		for(int i = 0; i < nodoActual->getNumKeys(); i++){
			this->imprimir(stream, nodoActual->getDirecciones()[i], nivel);
		}
		stream << "final del nivel "<<nivel <<endl;
	}


}
