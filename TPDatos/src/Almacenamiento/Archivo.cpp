/*
 * Archivo.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Archivo.h"
#include "../utils/Define.h"
using namespace std;
Archivo::Archivo() {
	// TODO Auto-generated constructor stub

}
void Archivo::abrirArchivo(std::string tipoArchivo){
	cout << "PATH:" << this->getPath() << endl;
	if(tipoArchivo.compare(TEXTO)==0){
		this->archivo.open(this->getPath().c_str(),fstream::in | fstream::out);
		if (!archivo.is_open()){
			this->archivo.clear();

			//crea el archivo
			this->archivo.open(this->getPath().c_str(), std::fstream::out);
			this->archivo.close();


			//reabre el archivo para lectura - escritura

			this->archivo.open(this->getPath().c_str(), std::fstream::in | std::fstream::out);


		}
	}
	if(tipoArchivo.compare(BINARIO)==0){
		/* abre el archivo en modo lectura - escritura binario*/
		this->archivo.open(this->getPath().c_str(),  ios::in |ios::out |ios::binary);
		/* determina si tuvo éxito la apertura del archivo */
		if (!this->archivo.is_open()) {

			/* limpia los flags de control de estado del archivo */
			this->archivo.clear();

			/* crea el archivo */
			this->archivo.open(this->getPath().c_str(),ios::out | ios::binary);
			this->archivo.close();

			/* reabre el archivo para lectura - escritura binario */
			this->archivo.open(this->getPath().c_str(),ios::in|ios::out|ios::binary);


		}
	}

}
void Archivo::cerrarArchivo(){
	this->archivo.close();

}
void Archivo::guardar(std::string registro){
	/* verifica que el archivo esté abierto */
	if (this->archivo.is_open()) {

		//intenta escribir la cadena en el archivo
		this->archivo << registro;

		if (archivo.fail())
			// si se produjo un error, arroja una excepción
			throw std::ios_base::failure("No se pudo escribir correctamente la cadena");
	} else {
		/* arroja una excepción porque el archivo no está abierto */
		throw string("El archivo no está abierto");
	}

}
void Archivo::guardar(const char* registro,int tamanioRegistro){

	/* verifica que el archivo esté abierto */
	if (this->archivo.is_open()) {

		/* escribe el registro en el archivo */
		this->archivo.write(static_cast<const char*>(registro),	tamanioRegistro);

		/* chequea si se ha producido un error */
		if (  this->archivo.fail())
			/* arroja una excepción ante la imposibilidad de escribir el reg */
			throw string("No se pudo escribir correctamente el registro");
	}
	else {
		/* arroja una excepción porque el archivo no está abierto */
		throw string("El archivo no está abierto");
	}


}

bool Archivo::fin() {

  /* para comprobar el fin lee un char del buffer, sin retirarlo y lo
     compara con el fin de archivo */
  bool esEof = (this->archivo.peek() == char_traits<char>::eof());

  if (esEof)
    /* si llegó al fin del archivo limpia los flags */
    this->archivo.clear();

  return esEof;
}


void Archivo::leer(void* datos, int tamanio) {

  /* verifica que el archivo esté abierto */
  if (this->archivo.is_open()) {

    /* lee del archivo un registro */
    this->archivo.read(static_cast<char*>(datos),tamanio);

    /* chequea si se ha producido un error */
    if (this->archivo.fail())
      /* arroja una excepción ante la imposibilidad de leer un reg */
      throw string("No se pudo leer correctamente el registro");
  }
  else {
    /* arroja una excepción porque el archivo no está abierto */
    throw string("El archivo no está abierto");
  }
}
Archivo::~Archivo() {
	// TODO Auto-generated destructor stub
}
std::string Archivo::toString(){
	return "Archivo";
}
