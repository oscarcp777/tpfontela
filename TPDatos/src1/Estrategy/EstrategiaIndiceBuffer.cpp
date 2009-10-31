/*
 * EstrategiaIndiceBuffer.cpp
 *
 *  Created on: 31/10/2009
 *      Author: oscar
 */

#include "EstrategiaIndiceBuffer.h"

EstrategiaIndiceBuffer::EstrategiaIndiceBuffer() {
}

EstrategiaIndiceBuffer::~EstrategiaIndiceBuffer() {
}
int EstrategiaIndiceBuffer::abrir(){
	return 1;
}

int EstrategiaIndiceBuffer::crear(char* nombre, char* ruta){
	return 1;
}

int EstrategiaIndiceBuffer::cerrar(){
	this->indiceClavesBuffer.clear();
    return 1;
}

int EstrategiaIndiceBuffer::insertar(char* key, int dir){
	this->indiceClavesBuffer[key]=dir;
	return 1;
}

int EstrategiaIndiceBuffer::remover(char* key, int dir){
	this->indiceClavesBuffer.erase(key);
	return 1;
}

int EstrategiaIndiceBuffer::buscar(char* key, int dir){
	return this->indiceClavesBuffer[key];
}
