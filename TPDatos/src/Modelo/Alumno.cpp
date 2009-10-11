/*
 * Alumno.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Alumno.h"

Alumno::Alumno(double dni, std::string nombre, int padron,int n1,int n2, int n3):Registro(10) {
	// TODO Auto-generated constructor stub
	this->dni = dni;
	this->nombre = nombre;
	this->padron = padron;
	//this->nota= new Nota[3];
	this->nota[0]=new Nota(n1);
	this->nota[1]=new Nota(n2);
	this->nota[2]=new Nota(n3);

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

	//std::stringstream flujo;
	std::stringstream flujo2;
	//flujo<<this->dni;
	//this->setAtributo("DNI",flujo.str());

	flujo2<<this->padron;
	this->setAtributo("Padron",flujo2.str());
	//for (int i = 0;  i < 3;  i++) {
	//	this->nota[1]->serializar();
	//}


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
