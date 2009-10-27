/*
 * Nodo.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "Nodo.h"

Nodo::Nodo(){

}

Nodo::Nodo(byte buffer[], int bloque, int nivel,int tamanioBuffer){

	setBuffer(buffer,tamanioBuffer);

	this->bloque = bloque;
	this->nivel = nivel;

}

int Nodo::getNivel() {
	return nivel;
}

int Nodo::getBloque() {
	return bloque;
}

byte* Nodo::getBuffer() {
	return buffer;
}

void Nodo::setBloque(int bloque) {
	this->bloque = bloque;
}

int Nodo::getTamanioBuffer(){
	return tamanioBuffer;
}

void Nodo::setBuffer(byte buffer[],int tamanioBuffer) {

	int i;

	delete(this->buffer);

	this->buffer = new byte[tamanioBuffer];

	for(i=0;i<tamanioBuffer;i++){
		this->buffer[i]=buffer[i];
	}

	this->tamanioBuffer = tamanioBuffer;
}

void Nodo::setNivel(int nivel) {
	this->nivel = nivel;
}

Nodo::~Nodo(){
	delete(this->buffer);
}
