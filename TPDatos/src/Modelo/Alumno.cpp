/*
 * Alumno.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Alumno.h"

Alumno::Alumno() {
	// TODO Auto-generated constructor stub

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

Clave* Dato::serializarToolkit(){
	return new Clave();
}

void Dato::hidratarToolkit(Clave* clave){

}


Alumno::~Alumno() {
	// TODO Auto-generated destructor stub
}
