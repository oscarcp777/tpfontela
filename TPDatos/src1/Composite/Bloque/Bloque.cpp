/*
 * Bloque.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Bloque.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Bloque::Bloque(int tamanio) {

	// TODO Auto-generated constructor stub
	this->setTamanio(tamanio);
	this->nextByte = 0;
	this->tamanioBuffer = 0;
	 this->buffer = new char[tamanio];
	    memset(this->buffer,0,tamanio);


}

Bloque::~Bloque() {

}


void Bloque::serializar(string tipo){
	std::list<Componente*>::iterator iteraRegistros = this->iteratorListaDeComponetes();
	int i=0;
	int len;
	Componente* componente;


	//ir al ultimo registro agregado
	while (i<this->getCantidadDeElelmentos()){
		componente = (Componente*)*iteraRegistros;
		iteraRegistros++;
		i++;
	}
	cout<<"componente->getBuffer(): "<<componente->getBuffer()<<endl;
	len = componente->getTamanioBuffer();

	int start = this->nextByte;
	this->nextByte += sizeof(int) + 1;
	//agrego al buffer del bloque el tamanio del registro
	memcpy(&this->buffer[start],&len,sizeof(int));
	this->buffer[start + sizeof(int)] = Define::DELIMITADOR1;

	//copio el buffer del registro en el bloque
	start = this->nextByte;
	this->nextByte += len ;
	memcpy(&this->buffer[start],componente->getBuffer(),len);
	//this->buffer[start + len] = Define::DELIMITADOR1;


	this->tamanioBuffer = this->nextByte;
	cout<<"El buffer contiene: ";
	for (int i = 0; i < this->tamanioBuffer; i++)
		cout<<this->buffer[i];

}

void Bloque::hidratar(string tipo){
	std::list<Componente*>::iterator iteraRegistros = this->iteratorListaDeComponetes();
	int i=0;
	int tamanioRegistro;
	bool encontroDelimitador = false;
	char* buffer;
	Componente* componente;
	std::string datosBuffer = "";
	std::string auxString = "";
	//ir al ultimo registro  agregado EN REALIDAD TIENE UN SOLO ELEMENTO ASIQUE ES LO MISMO QUE OBTENER EL ULTIMO
	while (i<this->getCantidadDeElelmentos()){
		componente = (Componente*)*iteraRegistros;
		iteraRegistros++;
		i++;
	}
	this->listaDeComponetes.remove(componente);

	while(this->nextByte < this->getTamanio()){
		encontroDelimitador = false;
		int len = -1;
		int start = this->nextByte;
		for (int i = start; i < this->getTamanio(); i++){
			if (this->buffer[i] == Define::DELIMITADOR1){
				len = i - start;
				encontroDelimitador = true;
				break;
			}
		}
		if(encontroDelimitador){
			this->nextByte += len +1;
			memcpy(&tamanioRegistro,&this->buffer[start],len);
			buffer = new char[tamanioRegistro];
			start = this->nextByte;
			componente = componente->obtenerNuevaInstancia();
			componente->setTamanio(tamanioRegistro);
			memcpy(buffer,&this->buffer[start],tamanioRegistro);

			componente->setBuffer(buffer);
			componente->hidratar(BINARIO);
			this->agregarComponente(componente);
			this->nextByte += tamanioRegistro +1;
			delete buffer;
		}
		else
			this->nextByte = this->getTamanio();
	}
//	while (cantCaracteresLeidos < (int)strlen(this->buffer) ){
//		std::cout<<"DATOS del bloque: "<<datosBuffer<<std::endl;
//
//			//obtengo la posicion del delimitador
//			posDelimitador = datosBuffer.find_first_of(DELIMITADOR,cantCaracteresLeidos);
//
//			cout<<"posDelimitador: "<<posDelimitador<<endl;
//			//obtengo el string hasta el delimitador (seria el numero de caracteres que tengo que leer despues)
//			auxString = datosBuffer.substr(cantCaracteresLeidos,cantCaracteresLeidos+posDelimitador);
//			std::cout<<"auxString: "<<auxString<<std::endl;
//			//lei cantidad de caracteres hasta el delimitador
//			cantCaracteresLeidos += auxString.length()+1;
//			//dejo guardado en datos buffer a partir de uno mas del pipe en adelante
//			datosBuffer = datosBuffer.substr(posDelimitador+1);
//			std::cout<<"datosBuffer: "<<datosBuffer<<std::endl;
//			//tamanio tiene el numerito de caracteres que ocupa el registro
//			tamanio = atoi(auxString.c_str());
//			//obtengo los datos del registro
//			auxString ="";
//			auxString = datosBuffer.substr(0, tamanio);
//			std::cout<<"auxString: "<<auxString<<std::endl;
//			// lei tamanio de cantidad de caracteres
//			cantCaracteresLeidos += tamanio;
//			//dejo guardado en datos buffer a partir de uno mas del pipe en adelante
//			datosBuffer = datosBuffer.substr(tamanio+1);
//			std::cout<<"datosBuffer: "<<datosBuffer<<std::endl;


//			donde->leer(bufferAux, pos);
//			componente->setBuffer(bufferAux);
//			componente->hidratar(BINARIO);
//
//			if (componente->compareTo(clave,0) == 0){
//				resultadoDeLABusqueda.push_back(componente);
//				componente = componente->obtenerNuevaInstancia();
//				componente->setTamanio(donde->getTamanio());
//			}
//		}
}

Componente* Bloque::obtenerNuevaInstancia(){
	return NULL;
}
int Bloque::compareTo(std::string clave,int num){
	return -1;
}
