/*
 * TextFile.cpp
 *
 *  Created on: 25/03/2010
 *      Author: oscar
 */

#include "TextFile.h"

TextFile::TextFile() {
	// TODO Auto-generated constructor stub

}

TextFile::~TextFile() {
	// TODO Auto-generated destructor stub
}
void TextFile::create(string fileName){

}
void TextFile::open(string fileName){
	  //intenta abrir el archivo en modo lectura - escritura
	  this->file.open(fileName.c_str(), std::fstream::in | std::fstream::out);

	  if (!this->file.is_open()) {
	    //si no hubo éxito en la apertura...
	    //limpia los flags de control de estado del archivo
		  this->file.clear();

	    //crea el archivo
		  this->file.open(fileName.c_str(), std::fstream::out);
		  this->file.close();

	    //reabre el archivo para lectura - escritura
		  this->file.open(fileName.c_str(), std::fstream::in | std::fstream::out);

	    if (!this->file.is_open())
	      // si no se pudo crear el archivo arroja una excepción/
	      throw std::ios_base::failure("El archivo no pudo ser abierto");
	  }
	  if (!this->file.is_open())
	      // si no se pudo crear el archivo arroja una excepción/
	      throw std::ios_base::failure("El archivo no pudo ser abierto");
}
