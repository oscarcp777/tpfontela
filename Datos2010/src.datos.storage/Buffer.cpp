/*
 *
 * Buffer.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Buffer.h"


Buffer::Buffer():Storage() {
//	datos = new char[TAM_BUFFER];
	//memset(datos,0,sizeof(char)*TAM_BUFFER);
	posicionActual = 0;
	posicionActualLectura = 0;
	cantElementos = 0;
	cantLineas = 0;
	cantlineasLeidas = 0;
	texto = 0;
	binario = 0;
}
void Buffer::create(){

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
void Buffer::open(){
	//posicionActual = 0;
}

void Buffer::irAlPrincipio(){
	posicionActual = 0;
}


int Buffer::write(std::string registro, int pos){

	int dir = -1;
	if(this->texto == 0)
		this->texto = true;

	if(pos<0){
		//si pos<0 copio al final del bufer
		//verifico que lo que voy a escribir entre en el espacio que queda de buffer
		string temp = this->datos;

		if((int)registro.length() <= TAM_BUFFER - (int)temp.length()){
			temp+= registro+"\n";
			dir = strlen(this->datos);
			memcpy(this->datos,temp.c_str(),temp.length());
			this->cantLineas++;
			//this->posicionActual=temp.length();
		}
		else /* arroja una excepción porque el registro no entra */
			throw std::string("El registro no entra en el buffer");

	}
	else{
		registro+= "\n";
		memcpy(&this->datos[pos],registro.c_str(),registro.length());
		dir = pos;
		this->cantLineas++;

	}
	return dir;
}

int Buffer::write(char* buffer, int pos){

	if(this->binario == 0)
		this->binario = true;

	if(pos < 0){

		//verifico que lo que voy a escribir entre en el espacio que queda de buffer
		if(this->size <= TAM_BUFFER - this->posicionActual){
			int dir = this->posicionActual;
			memcpy(&this->datos[this->posicionActual],buffer,this->size);
			this->posicionActual+=this->size;

			this->cantElementos++;
			return dir;
		}
		else {
			throw std::string("El registro no entra en el buffer");
		}
	}else{
		memcpy(&this->datos[pos],buffer,this->size);
		this->cantElementos++;
		return pos;
	}


}

void Buffer::read(std::string& datos, int pos){
	if(pos>=0){
		this->posicionActual = pos;
		std::string aux = this->datos;
		std::string aux2 = "";
		std::string caracter = "\n";
		std::string vacio = "";
		int posBarraN = aux.find_first_of(caracter.c_str(),this->posicionActual+1);

		aux2 = aux.substr(this->posicionActual,posBarraN-this->posicionActual);
		this->posicionActual+= aux2.length()+1;
		//en la siguiente linea borro el ultimo caracter, que es el \n (para no devolverlo)
		datos= aux2.replace(aux2.length(),1,vacio.c_str());
		this->cantlineasLeidas++;
	}
	else
		cout<<"posicion incorrecta para leer buffer, pos:"<<pos<<endl;
}

void Buffer::read(char* buffer, int pos){

	if(pos+this->size <= TAM_BUFFER){
		memcpy(buffer,&this->datos[pos],this->size);
		this->posicionActualLectura = pos + this->size;
	}

}


bool Buffer::fin() {

  bool fin = false;
  if(this->binario == true){
	  if(this->posicionActualLectura == this->size*cantElementos)
		  fin = true;
  }
  else if(this->texto == true){
	  if(this->cantlineasLeidas == this->cantLineas)
		  fin = true;

  }

  return fin;
}

void Buffer::close(){
}
