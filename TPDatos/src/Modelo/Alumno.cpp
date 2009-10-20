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


void Alumno::serializarObjeto(){

	this->setAtributo("Nombre",this->nombre);

	std::stringstream flujo2;
	flujo2<<this->padron;
	this->setAtributo("Padron",flujo2.str());
}

void Alumno::hidratarObjeto(){
	this->nombre = this->getAtributo("Nombre");
	this->padron = atoi((this->getAtributo("Padron")).c_str());
}

std::string Alumno::getClaveObjeto(){
	std::string llave;
	llave.append("Nombre");
	llave.append("Padron");
	return llave;
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
