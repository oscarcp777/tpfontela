/*
 * Alumno.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Alumno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Alumno::Alumno(double dni, std::string nombre, int padron,int n1,int n2, int n3) {
	// TODO Auto-generated constructor stub
	this->dni = dni;
	this->nombre = nombre;
	this->padron = padron;


}
Alumno::Alumno() {

}

int Alumno::getPadron()
{
	return padron;
}

void Alumno::setPadron(int padron)
{
	this->padron = padron;
}

int Alumno::getDni()
{
	return dni;
}

void Alumno::setDni(int dni)
{
	this->dni = dni;
}

std::string Alumno::getNombre(){
	return nombre;
}

void Alumno::setNombre(std::string nombre)
{
	this->nombre = nombre;
}
void Alumno::Init(){
	Registro::Init();
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

void Alumno::serializarTexto(){

	this->setAtributo("Nombre",this->nombre.c_str());
	std::stringstream flujo2;
	std::stringstream flujo;
	flujo2<<this->padron;
	this->setAtributo("Padron",(flujo2.str()).c_str());

	flujo<<this->dni;
	this->setAtributo("DNI",(flujo.str()).c_str());
}

void Alumno::hidratarTexto(){
	this->clear();
	char aux1[20];
	memset(aux1,0,20);
	this->getAtributo(aux1);
	this->nombre = aux1;

	char aux2[10];
	memset(aux2,0,10);
	this->getAtributo(aux2);
	this->padron = atoi(aux2);

	char aux3[20];
	memset(aux3,0,20);
	this->getAtributo(aux3);
	this->dni = atof(aux3);

}

Registro* Alumno::obtenerNuevaInstancia(){
	return new Alumno();
}

std::string Alumno::getClaveObjeto(){
	std::stringstream flujo;
	flujo<<this->padron;
	return flujo.str();;
}
int Alumno::compareTo(std::string clave, int num){
	int valor = -1;
	int aux = 0;

	switch(num){
	case 0:
			valor = this->nombre.compare(clave.c_str());
			break;
	case 1:
			aux = atoi(clave.c_str());
			if(this->padron == aux)
				valor = 0;
			break;

	case 2:
			aux = atof(clave.c_str());
			if(this->dni == aux)
				valor = 0;
			break;


	}
	return valor;
}


Alumno::~Alumno() {
	// TODO Auto-generated destructor stub
}
