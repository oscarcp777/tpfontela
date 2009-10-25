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
	//memset(datos,0,sizeof(char)*TAM_BUFFER);
	posicionActual = 0;
	posicionActualLectura = 0;
	cantElementos = 0;
}
void Buffer::crear(){

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
	//posicionActual = 0;
}

void Buffer::irAlPrincipio(){
	posicionActual = 0;
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

void Buffer::guardar(char* buffer, int pos){

	//cout<<"Posicion actual buffer: "<<this->posicionActual<<endl;
	cout<<"Registro a guardar: "<<buffer<<endl;
	if(pos < 0){
		//verifico que lo que voy a escribir entre en el espacio que queda de buffer
		if(this->getTamanio() <= TAM_BUFFER - this->posicionActual){

			memcpy(&this->datos[this->posicionActual],buffer,this->getTamanio());
			this->posicionActual+=this->getTamanio();

			this->cantElementos++;
//			cout<<"Posicion actual buffer: "<<this->posicionActual<<endl;
//			for(int i = 0 ; i< strlen(buffer) ; i++){
//				cout<<i<<": "<<this->datos[i];
//
//			}
//			cout<<"Desde posicion actual : "<<this->posicionActual<<endl;
//			for(int i = this->posicionActual ; i< this->posicionActual+strlen(buffer) ; i++){
//							cout<<i<<": "<<this->datos[i];
//
//						}
//			this->posicionActual+=this->getTamanio();

		}
		else {
			throw std::string("El registro no entra en el buffer");
		}
	}else{
		memcpy(&this->datos[pos],buffer,this->getTamanio());
		this->cantElementos++;
	}


}


void Buffer::leer(char* buffer, int pos){

	if(pos+this->getTamanio() <= TAM_BUFFER){
		memcpy(buffer,&this->datos[pos],this->getTamanio());
		this->posicionActualLectura = pos + this->getTamanio();
	}

}


bool Buffer::fin() {

  bool fin = false;

  if(this->posicionActualLectura == this->getTamanio()*cantElementos)
	  fin = true;

  return fin;
}

void Buffer::cerrar(){
}
