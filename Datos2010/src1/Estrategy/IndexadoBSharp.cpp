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

	int resultado; int nivel = this->profundidad -1; //obtengo el ultimo nivel y voy al nivel anterior para estar en el nodo padre.
	int nuevoTamanio = 0;
	char* claveAnterior, *claveMayor;
	NodeBSharp* nodoActual, *nuevoNodo, * nodoPadre;
	nodoActual = this->buscarHoja(key);
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
	this->escribirProfundidad(this->buffer);
	//std::cout<<"NIVEL ARBOL:"<<this->profundidad;

	return 1;
}

int IndexadoBSharp::modificar(char* key, int dir){
	NodeBSharp* nodoActual;
	int valor;
	nodoActual = this->buscarHoja(key);
	nodoActual->modificarDireccion(key,dir);
	valor=nodoActual->remover(key,dir);
	this->escribirNodo(nodoActual);

	return valor;
}
/*
int IndexadoBSharp::colocarClaveOrdenadamente(char**keysNodo,int numKeys,char*keyAinsertar){

	char* primeraKey;

	primeraKey=new char(this->tamanioLlave);

		if(strcmp(keysNodo[numKeys-1],keyAinsertar)>0)
			keysNodo[numKeys+1]=keyAinsertar;
		else{
			for(int i=0;i<=numKeys;i++){
			memcpy(primeraKey,keysNodo[i],strlen(keysNodo[i]));
			keysNodo[i+1]=primeraKey;
			}
			keysNodo[0]=keyAinsertar;
		}

		return 1;
}
*/

int IndexadoBSharp::actualizarIndexSet(char* keyVieja, char* keyNueva,bool escribirNodo){

	NodeBSharp* nodo;
	int nivel;

	nivel=this->profundidad-2;

	while(nivel>=0){
		nodo=this->nodos[nivel];
		if(strcmp(nodo->claveMayor(),keyVieja)!=0){
			nodo->actualizarKey(keyVieja,keyNueva);
			this->escribirNodo(nodo);
			break;
		}else{
			nodo->actualizarKey(keyVieja,keyNueva);
			this->escribirNodo(nodo);
			nivel--;
		}
	}

	return 1;
}

int IndexadoBSharp::bajarUnNivel(int nivelInferiorNodo){
	NodeBSharp* nodoNivelInferior = this->nodos[nivelInferiorNodo];
	NodeBSharp* nodoInterno;
	int numKeys=nodoNivelInferior->getNumKeys();
	int numKeysNodoInterno=0;
	int* direccionesAux = new int[nodoNivelInferior->getNumKeys()];

	memcpy(direccionesAux,nodoNivelInferior->getDirecciones(),(nodoNivelInferior->getNumKeys())*sizeof(int));

	for(int i=0;i<numKeys;i++){

		nodoInterno=leerNodo(direccionesAux[i]);
		numKeysNodoInterno=nodoInterno->getNumKeys();

		for(int j=0;j<numKeysNodoInterno;j++){

			if(j==numKeysNodoInterno-1){
				nodoNivelInferior->modificarDireccion(nodoInterno->claveMayor(),nodoInterno->getDirecciones()[j]);
			}else
				nodoNivelInferior->insert(nodoInterno->getKeys()[j],nodoInterno->getDirecciones()[j]);


		}

	}

	delete(direccionesAux);

	this->escribirNodo(nodoNivelInferior);

	nodoNivelInferior->serializar(this->buffer);

	buscarHoja(nodoInterno->claveMayor());

	this->profundidad--;

	escribirProfundidad(this->buffer);

	return 0;
}




int IndexadoBSharp::eliminarIndexSet(char* key, NodeBSharp* nodoHoja,int nivelArbol,bool modificarDireccion,bool underflowNodoInterno){

	NodeBSharp* nodoPadre;

	nodoPadre=this->nodos[nivelArbol];


		/*CASO 1: Si el nodo hoja n tiene mas claves que el minimo y k (clave) no es la clave mas grande en n, simplemente borrar k de n*/
		if((nodoPadre->getNumKeys()>nodoPadre->getMinKeys()) && strcmp(key,nodoPadre->claveMayor())!=0){
			if(modificarDireccion){
				nodoPadre->modificarDireccion(nodoHoja->claveMayor(),nodoPadre->getDirecciones()[nodoPadre->buscar(key,-1,-2)]);
			}
			nodoPadre->remover(key);
			this->escribirNodo(nodoPadre);

		}/*CASO 2: Si el nodo hoja n tiene mas que el minimo numero de claves y la clave k es la mas grande en n, borrar la clave k y modificar el indice de
		           mayor nivel que direcciona a la nueva clave mas grande en n.
		  */
		else if((nodoPadre->getNumKeys()>nodoPadre->getMinKeys()) && strcmp(key,nodoPadre->claveMayor())==0){
			if(modificarDireccion){
				nodoPadre->modificarDireccion(nodoHoja->claveMayor(),nodoPadre->getDirecciones()[nodoPadre->buscar(key,-1,-2)]);
			}
			nodoPadre->remover(key);
			actualizarIndexSet(key,nodoPadre->claveMayor(),true);
			this->escribirNodo(nodoPadre);

		}/*CASO 3 y 4: Si no salio por el caso 1 ni el caso 2, se produce un underflow con caso 3 o 4. */
		else{

			if(nodoPadre->getNumKeys()==nodoPadre->getMinKeys() && underflowNodoInterno){
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
NodeBSharp* IndexadoBSharp::obtenerNodoVecino(NodeBSharp* nodoHoja, NodeBSharp* nodoPadreHoja, int indiceClave,bool underflowNodoInterno){
	int direccionNodoHojaVecino;
	//char* claveAreemplazar;

	NodeBSharp* nodoHojaVecino;
	NodeBSharp* nodoHojaVecinoAux;

	if((indiceClave-1)>=0){
		direccionNodoHojaVecino = nodoPadreHoja->getDirecciones()[indiceClave-1];
		//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave-1];
	}else if(indiceClave+1<nodoPadreHoja->getNumKeys()){
		direccionNodoHojaVecino = nodoPadreHoja->getDirecciones()[indiceClave+1];
		//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave+1];
	}

	nodoHojaVecino = this->leerNodo(direccionNodoHojaVecino);

	//Retornara el nodoHojaVecino de la izquierda para hacer concatenacion en caso de que este en underflow el nodo interno o
	//redistribucion en caso de estar en underflow un nodo hoja
	if((nodoHojaVecino->getNumKeys()>nodoHojaVecino->getMinKeys()) || (nodoHojaVecino->getNumKeys()==nodoHojaVecino->getMinKeys() && underflowNodoInterno))
		return nodoHojaVecino;
	else if(indiceClave+1<nodoPadreHoja->getNumKeys()){ //Retornara el nodoHojaVecino de la derecha
		direccionNodoHojaVecino = nodoPadreHoja->getDirecciones()[indiceClave+1];
				//claveAreemplazar = nodoPadreHoja->getKeys()[indiceClave+1];
				nodoHojaVecinoAux = this->leerNodo(direccionNodoHojaVecino);
				if((nodoHojaVecinoAux->getNumKeys()>nodoHojaVecinoAux->getMinKeys()) || (nodoHojaVecinoAux->getNumKeys()==nodoHojaVecinoAux->getMinKeys() && underflowNodoInterno))
					return nodoHojaVecinoAux;
	}

	return nodoHojaVecino; //sino retorno por default el nodoHojaVecino de la izquierda
}


void IndexadoBSharp::resolverUnderflowRaiz(NodeBSharp* nodoPadre,char* key){
	NodeBSharp* nodoHoja;
	bool keyRemovida;
	int numKeys=nodoPadre->getNumKeys();

	for(int i=0;i<numKeys;i++){
		nodoHoja=leerNodo(nodoPadre->getDirecciones()[i]);

		if(strcmp(nodoHoja->claveMayor(),key)==0)
			keyRemovida=true;

		nodoHoja->remover(nodoHoja->claveMayor());
		nodoPadre->merge(nodoHoja);
		escribirNodo(nodoHoja);
	}


	if(!keyRemovida)
		nodoPadre->remover(key);

		nodoPadre->setDir(-1);
		nodoPadre->setNodoSiguiente(-1);

		escribirNodo(nodoPadre);

	    nodoPadre->serializar(this->buffer);

		this->profundidad--;

		escribirProfundidad(this->buffer);

}

/**
 * En caso de que no se pueda hacer una redistribucion de nodos ni una concatenacion habra que balancear el arbol a un nivel anterior
 * viendo el nodo interno (nodo padre) de la key a eliminar del nodo hoja, si tiene un nodo vecino con el cual se pueda redistribuir claves y/o
 * realizar concatenacion, balanceando el arbol.
 */

int IndexadoBSharp::resolverUnderflowNodoInterno(NodeBSharp* nodoAbuelo, NodeBSharp* nodoPadre, NodeBSharp* nodoHoja, char* key){

	NodeBSharp* nodoVecino;
	NodeBSharp* nodoVecinoAux;
	/*NodeBSharp* nodoHojaAux;
	bool redistribuirClaves;
	int i;*/

	//redistribuirClaves=false;
	if(nodoAbuelo==NULL){
		NodeBSharp* nodo = buscarHoja(key);
		if(nodo!=nodoPadre)
		resolverUnderflowRaiz(nodoPadre,key);
		else{
			nodoPadre->remover(key);
			this->escribirNodo(nodoPadre);
		}

		return 1;
	}

	nodoVecino = obtenerNodoVecino(nodoPadre,nodoAbuelo,nodoAbuelo->buscar(nodoPadre->claveMayor(),-1,-2),true);

	/*
	for(i=(nodoVecino->getNumKeys()-1);i>=0;i--){
		nodoHojaAux=buscarHoja(nodoVecino->getKeys()[i]);
		if(nodoHojaAux->getNumKeys()>nodoHojaAux->getMinKeys()){
			redistribuirClaves=true;
			break;
		}
	}*/

	/*if(redistribuirClaves)
		this->redistribuirClaves(key,nodoPadre,nodoHoja,nodoVecino,false);
	else{*/
		int indiceClave=nodoPadre->buscar(key,-1,-2);
		if(indiceClave<0)
			indiceClave=nodoPadre->buscar(nodoHoja->claveMayor(),-1,-2);
		nodoVecinoAux=obtenerNodoVecino(nodoHoja,nodoPadre,indiceClave,true);
		buscarHoja(nodoHoja->claveMayor()); //para actualizar la profundidad
		nodoPadre=this->nodos[this->profundidad-2];
		concatenarNodos(key,nodoPadre,nodoHoja,nodoVecinoAux,true);
		if(nodoHoja->getNumKeys()<nodoHoja->getMinKeys()){//el nodoVecinoAux se mergeo la hoja
			buscarHoja(nodoVecinoAux->claveMayor());
			nodoPadre=this->nodos[this->profundidad-2];
			concatenarNodos(key,nodoPadre,nodoVecinoAux,nodoVecino,false);
		}else //el nodoHoja se mergeo con el nodoVecinoAux
			concatenarNodos(key,nodoPadre,nodoHoja,nodoVecino,false);
	//}

	return 1;
}

int IndexadoBSharp::concatenarNodos(char* key,NodeBSharp* nodoPadre,NodeBSharp* nodo, NodeBSharp* nodoVecino,bool hasNodeFeal){
	if(!hasNodeFeal){

		if(strcmp(key,nodoVecino->claveMayor())>0){ //la clave a eliminar es mayor que la clave mayor del nodoVecino (nodoVecino a la izquierda)
			int ret=eliminarIndexSet(nodoVecino->claveMayor(),nodoPadre,this->profundidad-3,true,true); //el nodoPadre es el nodoHoja (nodoInterno, seria nodoPadre con el abuelo "this->profundidad-3")
			//actualizarIndexSet(nodoVecino->claveMayor(),nodo->claveMayor(),false);
			//
			if(ret!=-1)
			nodoVecino->merge(nodoPadre);

		}else{ //la clave a eliminar es menor que la clave mayor del nodoVecino (nodoVecino a la derecha)
			int ret=eliminarIndexSet(nodoVecino->claveMayor(),nodoPadre,this->profundidad-3,true,true);

			if(ret!=-1)
			nodoPadre->merge(nodoVecino);
		}
		this->escribirNodo(nodoVecino);
		this->escribirNodo(nodo);

	}else{
		if(strcmp(key,nodoPadre->claveMayor())==0){
			nodo->remover(key);
			nodoPadre->modificarDireccion(key,nodoPadre->getDirecciones()[nodoPadre->getNumKeys()-2]);
			nodoPadre->remover(nodoVecino->claveMayor());
			//eliminarIndexSet(nodoVecino->claveMayor(),nodo,this->profundidad-2); //se cambio a nodoPadre->remover por este
			this->actualizarIndexSet(key,nodo->claveMayor(),true);

			nodoVecino->merge(nodo);
			nodoVecino->setNodoSiguiente(nodo->getNodoSiguiente());
		}else if(strcmp(key,nodo->claveMayor())==0){
			nodo->remover(key);
			if(strcmp(key,nodoVecino->getKeys()[0])<0){
				nodoPadre->remover(nodoVecino->claveMayor());
				//eliminarIndexSet(nodoVecino->claveMayor(),nodo,this->profundidad-2); //se cambio a nodoPadre->remover por este
				nodoPadre->actualizarKey(key,nodoVecino->claveMayor());
				nodo->merge(nodoVecino);
				nodo->setNodoSiguiente(nodoVecino->getNodoSiguiente());
			}else{
				nodoPadre->actualizarKey(nodoVecino->claveMayor(),nodo->claveMayor());
				nodoPadre->remover(key);
				//eliminarIndexSet(key,nodo,this->profundidad-2); //se cambio a nodoPadre->remover por este
				nodoVecino->merge(nodo);
				nodoVecino->setNodoSiguiente(nodo->getNodoSiguiente());
			}

			this->escribirNodo(nodoPadre);
		}else{
			nodo->remover(key);
			if(strcmp(key,nodoVecino->getKeys()[0])<0){
				nodoPadre->remover(nodoVecino->claveMayor());
				nodoPadre->actualizarKey(nodo->claveMayor(),nodoVecino->claveMayor());
				nodo->merge(nodoVecino);
				//eliminarIndexSet(nodoVecino->claveMayor(),nodo,this->profundidad-2); //se cambio a nodoPadre->remover por este
				nodo->setNodoSiguiente(nodoVecino->getNodoSiguiente());
			}else{
				nodoVecino->merge(nodo);
				nodoPadre->remover(nodoVecino->claveMayor());
				nodoPadre->actualizarKey(nodoVecino->getKeys()[nodoVecino->getNumKeys()-2],nodoVecino->claveMayor());
				//eliminarIndexSet(nodo->claveMayor(),nodo,this->profundidad-2); //se cambio a nodoPadre->remover por este
				nodoVecino->setNodoSiguiente(nodo->getNodoSiguiente());
			}

			this->escribirNodo(nodoPadre);
		}

		this->escribirNodo(nodoVecino);
		this->escribirNodo(nodo);
	}
	return 1;
}

/*
char* IndexadoBSharp::obtenerClaveRedistribucion(NodeBSharp* nodo,NodeBSharp* nodoPadre,char*keyABorrar){
	NodeBSharp* nodoHoja;
	char* key;

	if(strcmp(keyABorrar,nodo->claveMayor())>0){ //obtengo la clave mayor del nodo vecino para redistribuir
		nodoHoja=this->buscarHoja(nodo->claveMayor());
		key=(char*)malloc(strlen(nodoHoja->claveMayor())*sizeof(char));
		memcpy(key,nodoHoja->claveMayor(),strlen(nodoHoja->claveMayor())*sizeof(char));
		remover(nodoHoja->claveMayor(),nodoHoja->getDirecciones()[nodoHoja->getNumKeys()-1]);
	}else if(strcmp(keyABorrar,nodo->claveMayor())<0){ //obtengo la clave menor del nodo vecino para redistribuir
		nodoHoja=this->buscarHoja(nodo->getKeys()[0]);
		key=(char*)malloc(strlen(nodoHoja->getKeys()[0])*sizeof(char));
		memcpy(key,nodoHoja->getKeys()[0],strlen(nodoHoja->getKeys()[0])*sizeof(char));
		remover(nodoHoja->getKeys()[0],nodoHoja->getDirecciones()[0]);
	}



	return key;
}*/

int IndexadoBSharp::redistribuirClaves(char* key,NodeBSharp* nodoPadre,NodeBSharp* nodo, NodeBSharp* nodoVecino/*,bool hasNodeFeal*/){

	/*if(!hasNodeFeal){
		char* keyRedistribucion;
		keyRedistribucion=obtenerClaveRedistribucion(nodoVecino,nodoPadre,key);
		this->insertar(keyRedistribucion,-1);
		remover(key,-1);
	}else{*/

		if(strcmp(key,nodoPadre->claveMayor())==0){ //la clave a eliminar esta en el padre y es la mayor, por lo que forma parte del index set
			actualizarIndexSet(key,nodo->getKeys()[nodo->getNumKeys()-2],false);
			nodo->remover(key);
			nodo->insert(nodoVecino->claveMayor(),nodoVecino->getDirecciones()[nodoVecino->getNumKeys()-1]);
			nodoPadre->actualizarKey(nodoVecino->claveMayor(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
			nodoVecino->remover(nodoVecino->claveMayor());
		}else if(strcmp(key,nodo->claveMayor())==0){ //la clave a eliminar esta en el padre pero no es la mayor, por lo que no forma parte del index set
			if(strcmp(key,nodoVecino->getKeys()[0])<0){ //paso la primer clave del nodoVecino
				nodo->actualizarKey(key,nodoVecino->getKeys()[0]);
				nodoPadre->actualizarKey(key,nodoVecino->getKeys()[0]);
				nodoVecino->remover(nodoVecino->getKeys()[0]);
			}else{
				nodo->actualizarKey(key,nodoVecino->claveMayor());
				nodoPadre->actualizarKey(key,nodo->claveMayor());
				nodoPadre->actualizarKey(nodoVecino->claveMayor(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
				nodoVecino->remover(nodoVecino->claveMayor());
			}

		}else{ //la clave a eliminar no esta en el padre
			nodo->remover(key);
			if(strcmp(nodo->claveMayor(),nodoVecino->getKeys()[0])<0){ //paso la primer clave del nodoVecino
				nodo->insert(nodoVecino->getKeys()[0],nodoVecino->getDirecciones()[0]);
				nodoPadre->actualizarKey(nodo->getKeys()[nodo->getNumKeys()-2],nodoVecino->getKeys()[0]);
				nodoVecino->remover(nodoVecino->getKeys()[0]);
			}else{
				nodo->insert(nodoVecino->claveMayor(),nodoVecino->getDirecciones()[nodoVecino->getNumKeys()-1]);
				nodoPadre->actualizarKey(nodoVecino->claveMayor(),nodoVecino->getKeys()[nodoVecino->getNumKeys()-2]);
				nodoVecino->remover(nodoVecino->claveMayor());
			}
		}

		this->escribirNodo(nodo);
		this->escribirNodo(nodoPadre);
		this->escribirNodo(nodoVecino);
	//}
	return 1;
}

int IndexadoBSharp::underflow(NodeBSharp* nodo,char* key){

	NodeBSharp* nodoVecino;
	NodeBSharp* nodoPadre;
	int indiceClave;

	nodoPadre=this->nodos[this->profundidad-2];
	indiceClave=nodoPadre->buscar(key,-1,-2); //Con exacto==-2, si la encuentra el indice clave me dara la posicion de la clave en el array de claves del nodoPadre.

	if(indiceClave<0) //la clave a eliminar no esta en el padre "no forma parte del index set"
		indiceClave=nodoPadre->buscar(nodo->claveMayor(),-1,-2); //busca el indice de la clave mayor en el padre

	nodoVecino=obtenerNodoVecino(nodo,nodoPadre,indiceClave,false);

	/*CASO 3: Si el nodo n tiene exactamente el minimo numero de claves y uno de los vecinos del nodo n tiene pocas claves (cantidad de claves minima), mergear
	          n con este vecino y eliminar una clave desde el nodo padre. */
	if((nodoVecino->getNumKeys()==nodoVecino->getMinKeys()) && (nodo->getNumKeys()==nodo->getMinKeys())
		&& (nodoPadre->getNumKeys()>nodoPadre->getMinKeys()))
		concatenarNodos(key,nodoPadre,nodo,nodoVecino,true);
	else if((nodoVecino->getNumKeys()==nodoVecino->getMinKeys()) && (nodo->getNumKeys()==nodo->getMinKeys())
		&& (nodoPadre->getNumKeys()==nodoPadre->getMinKeys())){
		if(this->profundidad-3 == -1)
		resolverUnderflowNodoInterno(NULL,nodoPadre,nodo,key);
		else
			resolverUnderflowNodoInterno(this->nodos[this->profundidad-3],nodoPadre,nodo,key);
	}
	 /* CASO 4: Si el nodo n tiene exactamente el minimo numero de claves y uno de los vecinos de n tiene muchas claves (cantidad mayor que la cantidad minima de claves),
				redistribuir moviendo algunas claves desde un vecino hacia n, y modificar el indice mas alto para direccionar la nueva clave mayor en los nodos afectados.
	  */
	else if((nodoVecino->getNumKeys()>nodoVecino->getMinKeys()) && (nodo->getNumKeys()==nodo->getMinKeys()))
		redistribuirClaves(key,nodoPadre,nodo,nodoVecino);


	return 1;

}


int IndexadoBSharp::remover(char* key, int dir){

	NodeBSharp* nodoHoja;
	int nivelArbol;

	nodoHoja=this->buscarHoja(key);

	nivelArbol=this->profundidad-2;

	/*if(nivelArbol==1){ //solo tengo la raiz
		nodoHoja->remover(key,dir);
		this->escribirNodo(nodoHoja);
		return 1;
	}*/

	/*CASO 1: Si el nodo hoja n tiene mas claves que el minimo y k (clave) no es la clave mas grande en n, simplemente borrar k de n*/
	if(((nodoHoja->getNumKeys()>nodoHoja->getMinKeys()) && strcmp(key,nodoHoja->claveMayor())!=0)||(this->profundidad==1)){
		nodoHoja->remover(key,dir);
		this->escribirNodo(nodoHoja);
		return 1;
	}/*CASO 2: Si el nodo hoja n tiene mas que el minimo numero de claves y la clave k es la mas grande en n, borrar la clave k y modificar el indice de
	           mayor nivel que direcciona a la nueva clave mas grande en n.
	  */
	else if((nodoHoja->getNumKeys()>nodoHoja->getMinKeys()) && strcmp(key,nodoHoja->claveMayor())==0){
		nodoHoja->remover(key,dir);
		actualizarIndexSet(key,nodoHoja->claveMayor(),true);
		this->escribirNodo(nodoHoja);
		return 1;
	}/*CASO 3 y 4: Si no salio por el caso 1 ni el caso 2, se produce un underflow con caso 3 o 4. */

		underflow(nodoHoja,key);

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


void IndexadoBSharp::imprimirArbol(ostream & stream){
	for(int i=0;i<this->cantidadNodos;i++){
		NodeBSharp* nodo=this->nodos[i];
		stream<<"NODO "<<i<<endl;
		for(int j=0;i<nodo->getNumKeys();j++){
			stream<<"Clave "<<nodo->getKeys()[j]<<endl;
			stream<<"Direccion "<<nodo->getDirecciones()[j]<<endl;
		}
		stream<<endl;
		stream<<"PROXIMO NODO"<<endl;
	}
}
