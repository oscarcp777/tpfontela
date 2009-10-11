/*
 * Archivo.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Archivo.h"
#include "../utils/Define.h"
using namespace std;
Archivo::Archivo(Compuesto* comp):Almacenamiento(comp) {
	// TODO Auto-generated constructor stub

}
void Archivo::abrirArchivo(std::string tipoArchivo){
	if(tipoArchivo.compare(TEXTO)==0)
		 this->archivo.open(this->getPath().c_str(),fstream::in | fstream::out);
	if(tipoArchivo.compare(BINARIO)==0)
		this->archivo.open(this->getPath().c_str(),  ios::in |ios::out |ios::binary);
	if (!archivo.is_open()){
		      // si no se pudo crear el archivo arroja una excepción/
		      throw std::ios_base::failure("El archivo no pudo ser abierto");
		  }
}
  void Archivo::cerrarArchivo(){
	  this->archivo.close();

  }
void Archivo::guardar(std::string contenido){
		  this->archivo.write(contenido.c_str(),contenido.length());


}
Archivo::~Archivo() {
	// TODO Auto-generated destructor stub
}
std::string Archivo::toString(){
	return "Archivo";
}
