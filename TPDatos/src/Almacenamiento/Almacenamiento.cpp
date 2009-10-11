/*
 * Almacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Almacenamiento.h"


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

Almacenamiento::Almacenamiento(Compuesto* comp) {
   this->compuesto=comp;
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

   void Almacenamiento::setCompuesto(Compuesto *compuesto)
   {
       this->compuesto = compuesto;
   }
   std::string Almacenamiento::toString(){
   	return "Almacenamiento";
   }
