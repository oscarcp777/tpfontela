/*
 * Registro.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Registro.h"


Registro::Registro(int tamanio):Componente(tamanio) {


}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}




void Registro::setAtributo(std::string etiqueta, std::string valor){
	this->mapaAtributos[etiqueta]=valor;

}

std::string Registro::getAtributo(std::string etiqueta){
	return this->mapaAtributos[etiqueta];
}

std::string Registro::getDatosRegistro() const
{
	return datosRegistro;
}

void Registro::setDatosRegistro(std::string datosRegistro)
{
	this->datosRegistro = datosRegistro;
}

