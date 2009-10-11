/*
 * Alumno.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Alumno.h"

Alumno::Alumno(double dni, std::string nombre, int padron):Registro(10) {
	// TODO Auto-generated constructor stub
	this->dni = dni;
	this->nombre = nombre;
	this->padron = padron;

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


void Alumno::serializar(){
	this->setAtributo("Nombre",this->nombre);


}

void Alumno::hidratar(){
	this->nombre = this->getAtributo("Nombre");
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
