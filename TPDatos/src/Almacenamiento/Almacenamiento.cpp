/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"
Almacenamiento::Almacenamiento() {
	this->compuesto= new Compuesto();
	this->metaData = "";
	this->metadataSize = -1;

}
 std::string Almacenamiento::getClass(){
	 return "Almacenamiento";
 }
std::string Almacenamiento::getTipoArchivo()
{
	return tipoArchivo;
}

void Almacenamiento::setTipoArchivo(std::string tipoArchivo)
{
	this->tipoArchivo = tipoArchivo;
}
int Almacenamiento::getTamanio()
{


	return tamanio;
}

void Almacenamiento::setTamanio(int tamanio)
{
	this->tamanio = tamanio;
}


void Almacenamiento::setNombreArchivo(std::string nombreArchivo)
{
	this->nombreArchivo = nombreArchivo;
}

void Almacenamiento::setRuta(std::string ruta)
{
	this->ruta = ruta;
}


void Almacenamiento::agregarComponente(Componente* componente){
	std::cout<<"lllego 3"<<this->toString()<<std::endl;
	this->compuesto->agregarComponente(componente);

}
Almacenamiento::~Almacenamiento() {
	delete this->compuesto;
}
Compuesto* Almacenamiento::getCompuesto()
{
	return compuesto;
}

int Almacenamiento::getExisteMetaData()
{
	if (this->metadataSize == -1)
		return 0;
	else
		return 1;
}


std::string Almacenamiento::leerMetadata(){
	return "nada";
}

void Almacenamiento::escribirMetadata(std::string metadata){
	this->metaData = metadata;

}

std::string Almacenamiento::toString(){
	return "Almacenamiento";
}
