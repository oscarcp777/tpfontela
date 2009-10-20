/*
 * Registro.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Registro.h"


Registro::Registro() {


}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}

void Registro::serializar(){
	this->setClave(this->getClaveObjeto());
	this->serializarObjeto();
	std::cout<< "Clave: " << this->clave <<std::endl;
}

void Registro::hidratar(){
	this->hidratarObjeto();
}


void Registro::setAtributo(std::string etiqueta, std::string valor){
	this->mapaAtributos[etiqueta]=valor;

}

std::string Registro::getAtributo(std::string etiqueta){
	return this->mapaAtributos[etiqueta];
}

std::string Registro::getDatosRegistro()
{
	return datosRegistro;
}

void Registro::setDatosRegistro(std::string datosRegistro)
{
	this->datosRegistro = datosRegistro;
}

