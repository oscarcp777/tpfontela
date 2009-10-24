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

}

Bloque::~Bloque() {
//Comente estas lineas porque se llama solo al destructor de Compuesto desde aca (por la herencia)
// y rompia cuando queria destruir, supongo destruye bien

//	int i=0;
//		std::list<Componente*>::iterator iter = this->listaDeComponetes.begin();
//				Componente* componente;
//
//				while(i<this->getCantidadDeElelmentos()){
//					componente = (Componente*)*iter;
//					delete componente;
//					iter++;
//					i++;
//				}
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

}
