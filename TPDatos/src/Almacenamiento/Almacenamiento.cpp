/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"
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
std::string Almacenamiento::getNombreArchivo()
    {
        return nombreArchivo;
    }

    std::string Almacenamiento::getRuta()
    {
        return ruta;
    }

    void Almacenamiento::setNombreArchivo(std::string nombreArchivo)
    {
        this->nombreArchivo = nombreArchivo;
    }

    void Almacenamiento::setRuta(std::string ruta)
    {
        this->ruta = ruta;
    }

Almacenamiento::Almacenamiento() {
	this->compuesto= new Compuesto();

}
void Almacenamiento::agregarComponente(Componente* componente){
		this->compuesto->agregarComponente(componente);

}
Almacenamiento::~Almacenamiento() {
	// TODO Auto-generated destructor stub
}
Compuesto* Almacenamiento::getCompuesto()
   {
       return compuesto;
   }



std::string Almacenamiento::toString(){
	return "Almacenamiento";
}
