/*
 * Componente.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Componente.h"



Componente::Componente() {
	// TODO Auto-generated constructor stub
	this->tamanio = 999;
	this->posicionActual = 0;

}

Componente::~Componente() {

}

int Componente::getTamanio(){
    return this->tamanio;
}

void Componente::setTamanio(int tamanio)
{
    this->tamanio = tamanio;
    this->buffer = new char[tamanio];
    memset(this->buffer,0,tamanio);
}


std::string Componente::getClave() const
{
	return clave;
}

void Componente::setClave(std::string clave)
{
	this->clave = clave;
}

int Componente::getPosicionActual() const
{
	return posicionActual;
}

void Componente::setPosicionActual(int posicionActual)
{
	this->posicionActual = posicionActual;
}

int Componente::getId() const
{
	return id;
}

void Componente::setId(int id)
{
	this->id = id;
}


char *Componente::getBuffer() const
{
	return buffer;
}

void Componente::setBuffer(char *buffer)
{
	memcpy(&this->buffer[0],buffer,sizeof(char)*this->getTamanio());
	this->nextByte = 0;
	this->tamanioBuffer = this->tamanio;
}

int Componente::getTamanioBuffer() const
{
	return tamanioBuffer;
}

void Componente::setTamanioBuffer(int tamanioBuffer)
{
	this->tamanioBuffer = tamanioBuffer;
}
string Componente::getNombreAtributos(){
	vector<string>::iterator the_iterator;
	string nombreAtributos="";
	     	string valor ="";
	     	the_iterator = this->estiquetas.begin();
	     	while( the_iterator !=  this->estiquetas.end() ) {
	     		valor = *the_iterator;
	     		nombreAtributos=nombreAtributos+valor+DELIMITADOR;
	     		++the_iterator;
	     	}

	     	return nombreAtributos;
}
