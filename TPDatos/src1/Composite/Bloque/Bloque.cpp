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
	//cout<<"this->getCantidadDeElelmentos() "<<this->getCantidadDeElelmentos()<<endl;
	while (i<this->getCantidadDeElelmentos()){
		componente = (Componente*)*iteraRegistros;

		//cout<<"componente->getBuffer() : "<<componente->getBuffer()<<endl;
		len = componente->getTamanioBuffer();

		int start = this->nextByte;
		this->nextByte += sizeof(int) + 1;
		//agrego al buffer del bloque el tamanio del registro
		memcpy(&this->buffer[start],&len,sizeof(int));
		this->buffer[start + sizeof(int)] = Define::DELIMITADOR1;

		//copio el buffer del registro en el bloque
		start = this->nextByte;
		this->nextByte += len+1 ;
		//cout<< "Empieza a grabar el registro en: "<<start<<endl;
		memcpy(&this->buffer[start],componente->getBuffer(),len);
		//this->buffer[start + len] = Define::DELIMITADOR1;

		iteraRegistros++;
		i++;
	}
//
//	this->tamanioBuffer = this->nextByte;
//	cout<<"El buffer contiene: ";
//	for (int i = 0; i < this->tamanioBuffer; i++)
//		cout<<this->buffer[i];

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
	//int j = 1;
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
			cout<<"Encontro delimitador en posicion: "<< len+start<<endl;
			//cout<<"Agrego "<<j<<" registro a la lista del bloque"<<endl;
			this->nextByte += len +1;
			//cout<<"start "<<start<<endl;
			//cout<<"len "<<len<<endl;
			memcpy(&tamanioRegistro,&this->buffer[start],len);
			buffer = new char[tamanioRegistro];
			//cout<<"Tamaño registro "<<tamanioRegistro<<endl;
			//cout<<"Next byte 1:  "<<nextByte<<endl;
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
	this->nextByte = 0;
}

Componente* Bloque::obtenerNuevaInstancia(){
	return NULL;
}
int Bloque::compareTo(std::string clave,int num){
	return -1;
}
