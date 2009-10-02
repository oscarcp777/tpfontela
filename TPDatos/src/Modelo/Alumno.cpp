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

Clave* Alumno::serializarToolkit(){
	Clave* raiz = new Clave("Alumno");
	char nombreAtributo[30];
	raiz->setearAtributo("dni",itoa(this->dni,nombreAtributo,10));

	return raiz;
}

void Alumno::hidratarToolkit(Clave* clave){

}


/*public Element serializarJDOM() {
		Element raiz = new Element("Posicion");
		raiz.setAttribute("PosX", (new Integer(this.x).toString()));
		raiz.setAttribute("PosY", new Integer(this.y).toString());
		return raiz;
	}*/

Alumno::~Alumno() {
	// TODO Auto-generated destructor stub
}