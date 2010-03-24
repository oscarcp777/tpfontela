/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Storage.h"
using namespace std;
Storage::Storage() {


}
int Storage::getCantidadRegistrosEnMemoria()
   {
       return cantidadRegistrosEnMemoria;
   }

   void Storage::setCantidadRegistrosEnMemoria(int cantidadRegistrosEnMemoria)
   {
       this->cantidadRegistrosEnMemoria = cantidadRegistrosEnMemoria;
   }
string Storage::getClavePrimaria()
    {
        return clavePrimaria;
    }

    void Storage::setClavePrimaria(string clavePrimaria)
    {
        this->clavePrimaria = clavePrimaria;
    }

string Storage::getClass(){
	 return "Almacenamiento";
 }
std::string Storage::getTipoArchivo()
{
	return tipoArchivo;
}

void Storage::setTipoArchivo(std::string tipoArchivo)
{
	this->tipoArchivo = tipoArchivo;
}
int Storage::getTamanio()
{


	return tamanio;
}

void Storage::setTamanio(int tamanio)
{
	this->tamanio = tamanio;
}

std::string Storage::getPath(){
	return this->ruta+this->nombreArchivo;
}

void Storage::setNombreArchivo(std::string nombreArchivo)
{
	this->nombreArchivo = nombreArchivo;
}

void Storage::setRuta(std::string ruta)
{
	this->ruta = ruta;
}



Storage::~Storage() {

}




std::string Storage::toString(){
	return "Storage";
}
