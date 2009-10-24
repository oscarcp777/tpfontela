/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"
using namespace std;
Almacenamiento::Almacenamiento() {
	this->compuesto= new Compuesto();
	this->metaData = new Metadata();


}
int Almacenamiento::getCantidadRegistrosEnMemoria()
   {
       return cantidadRegistrosEnMemoria;
   }

   void Almacenamiento::setCantidadRegistrosEnMemoria(int cantidadRegistrosEnMemoria)
   {
       this->cantidadRegistrosEnMemoria = cantidadRegistrosEnMemoria;
   }
string Almacenamiento::getClavePrimaria()
    {
        return clavePrimaria;
    }

    void Almacenamiento::setClavePrimaria(string clavePrimaria)
    {
        this->clavePrimaria = clavePrimaria;
    }

string Almacenamiento::getClass(){
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

std::string Almacenamiento::getPath(){
	return this->ruta+this->nombreArchivo;
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
	if (this->metaData->getSize() == -1)
		return 0;
	else
		return 1;
}

std::string Almacenamiento::toString(){
	return "Almacenamiento";
}
Metadata* Almacenamiento::getMetadata(){
	return this->metaData;
}
