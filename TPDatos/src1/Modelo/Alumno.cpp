/*
 * Alumno.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Alumno.h"
#include "stdlib.h"

Alumno::Alumno(double dni, std::string nombre, int padron,int n1,int n2, int n3) {
	// TODO Auto-generated constructor stub
	this->dni = dni;
	this->nombre = nombre;
	this->padron = padron;


}
Alumno::Alumno() {

}

int Alumno::getPadron() const
{
	return padron;
}

void Alumno::setPadron(int padron)
{
	this->padron = padron;
}

int Alumno::getDni() const
{
	return dni;
}

void Alumno::setDni(int dni)
{
	this->dni = dni;
}

std::string Alumno::getNombre() const
{
	return nombre;
}

void Alumno::setNombre(std::string nombre)
{
	this->nombre = nombre;
}


void Alumno::serializarBinario(){

	this->setAtributo("Nombre",this->nombre.c_str(),this->nombre.length());
	this->setAtributo("Padron",&this->padron,sizeof(this->padron));
	this->setAtributo("DNI",&this->dni,sizeof(this->dni));

}

void Alumno::hidratarBinario(){
	this->clear();
	char aux[20];
	memset(aux,0,20);
	this->getAtributo(aux);
	this->nombre = aux;
	this->getAtributo(&this->padron,sizeof(this->padron));
	this->getAtributo(&this->dni,sizeof(this->dni));

}

std::string Alumno::getClaveObjeto(){
	std::string llave;
	llave.append("Nombre");
	llave.append("Padron");
	return llave;
}



Alumno::~Alumno() {
	// TODO Auto-generated destructor stub
}