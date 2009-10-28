/*
 * Registro.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Registro::Registro() {
	this->nextByte = 0;
	this->tamanioBuffer = 0;

}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}

void Registro::serializar(string tipo){
	this->setClave(this->getClaveObjeto());
	if (tipo.compare(BINARIO)==0)
		this->serializarBinario();
	if (tipo.compare(TEXTO) == 0)
		this->serializarTexto();
	//std::cout<< "Clave: " << this->clave <<std::endl;
}

void Registro::hidratar(string tipo){
	if (tipo.compare(BINARIO) == 0)
		this->hidratarBinario();
	if (tipo.compare(TEXTO) == 0)
		this->hidratarTexto();
}


int Registro::setAtributo(std::string etiqueta,const void* campo, int tamanio){
	this->estiquetas.push_back(etiqueta);
	short len;
	//cout<<"Tamanio: "<<tamanio<<endl;
	//cout<<"Delimitador: "<<delim<<endl;
	if (tamanio >= 0) len = tamanio;
	else len = strlen((char*)campo);

//	short aux = (short)strlen((char*)campo);
//	cout<<"Len: "<<len<<endl;
//	cout<<"Aux: "<<aux<<endl;
//	if (len > (short)strlen((char*)campo)){
//		cout<<"Campo muy chico!!"<<endl;
//		return -1;
//	}
	if (len > this->getTamanio()){
		//cout <<  "El registro no entra en la estructura establecida" << endl;
		return -1;
	}
	int start = this->nextByte;
	this->nextByte += len + 1;
	//if (NextByte > MaxBytes) return -1
	memcpy(&this->buffer[start],campo,len);
	this->buffer[start + len] = Define::DELIMITADOR1;
	this->tamanioBuffer = this->nextByte;

	return len;


}

int Registro::getAtributo(void* campo, int tamanio){

	int len = -1;
	//cout<<"nextByte EN Registro::getAtributo: "<<this->nextByte<<endl;
	int start = this->nextByte;
	for (int i = start; i < this->tamanioBuffer; i++){
		if (this->buffer[i] == Define::DELIMITADOR1){
			len = i - start;
			break;
		}
	}
	if (len == -1){
		cout << "No encontro delimitador"<<endl;
		return -1;
	}
	this->nextByte += len +1;
	if (this->nextByte > this->tamanioBuffer) return -1;
	memcpy(campo,&this->buffer[start],len);
//	if (tamanio > len || tamanio == -1){
//		((char*)campo)[len] = 0;
//	}
	return len;
}

//Para que funcionen pruebas unitarias
void Registro::Init(){
	this->buffer = new char[500];  //setea el tamanio maximo del buffer de registro
}

void Registro::clear(){
	this->nextByte = 0;
}



