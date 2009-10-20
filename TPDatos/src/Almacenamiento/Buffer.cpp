/*
 *
 * Buffer.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Buffer.h"


Buffer::Buffer():Almacenamiento() {
	datos = new char[TAM_BUFFER];
	memset(datos,0,sizeof(char)*TAM_BUFFER);
	posicionActual = 0;
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
	delete(this->datos);
}
std::string Buffer::toString(){
	std::string buffer = datos;
	return buffer;
}
std::string Buffer::getClass(){
	return "Buffer";
}
void Buffer::abrir(){
	posicionActual = 0;
}

void Buffer::irAlPrincipio(){
	posicionActual = 0;
}

std::string Buffer::leerMetadata(){
	return "nada";
}

void Buffer::escribirMetadata(std::string metadata){
	this->metaData = metadata;

}

void Buffer::guardar(std::string registro){
	std::string temp = this->datos;
	//verifico que lo que voy a escribir entre en el espacio que queda de buffer
	if((int)registro.length() <= TAM_BUFFER - (int)temp.length()){
		temp+= registro;
		memcpy(this->datos,temp.c_str(),temp.length());
		//this->posicionActual=temp.length();
	}
	else {
		/* arroja una excepción porque el registro no entra */
		throw std::string("El registro no entra en el buffer");
	}

}

void Buffer::guardar(const char* registro,int tamanioRegistro){
	std::string temp = this->datos;
	std::string aux = registro;

		//verifico que lo que voy a escribir entre en el espacio que queda de buffer
		if(tamanioRegistro <= TAM_BUFFER - (int)temp.length()){
			while((int)aux.length() < tamanioRegistro){
				aux+= " ";
			}
			temp+= aux;
			memcpy(this->datos,temp.c_str(),temp.length());
		}
		else {
			/* arroja una excepción porque el registro no entra */
			throw std::string("El registro no entra en el buffer");
		}
}

std::string Buffer::leer(){

	std::string aux = this->datos;
	std::string aux2 = "";
	std::string caracter = "\n";
	std::string vacio = "";
	int posBarraN = aux.find_first_of(caracter.c_str(),this->posicionActual);
//	std::cout<<"pos actual: "<< this->posicionActual<<std::endl;
//	std::cout<<"posBarraN: "<< posBarraN<<std::endl;
//	std::cout<<"aux.length(): "<< aux.length()<<std::endl;
	aux2 = aux.substr(this->posicionActual,posBarraN);
	this->posicionActual+= aux2.length();

	return aux2;

}

void Buffer::leer(void* datos, int tamanio){
	//std::cout<<"pos actual: "<< this->posicionActual<<std::endl;
	std::string aux = this->datos;

	if(this->posicionActual+tamanio <= TAM_BUFFER){
		memcpy(datos, (void*)aux.substr(this->posicionActual,this->posicionActual+tamanio).c_str(), tamanio);
		this->posicionActual += tamanio;
	}
	else{
		memcpy(datos, (void*)aux.substr(this->posicionActual,aux.length()).c_str(), aux.length()-this->posicionActual);
		this->posicionActual += tamanio;
	}
}

bool Buffer::fin() {

  bool fin = false;
  std::string aux = this->datos;

  if(this->posicionActual == (int)aux.length())
	  fin = true;

  return fin;
}

void Buffer::cerrar(){
	this->posicionActual = 0;
}
