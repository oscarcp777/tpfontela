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


}
void Archivo::abrir(){

	if(this->getTipoArchivo().compare(TEXTO)==0){
		//intenta abrir el archivo en modo lectura - escritura
		this->archivo.open(this->getPath().c_str(),ios::out|ios::in);

		  if (this->archivo.is_open()){
			  cout<<"Existe Metadata";
			  this->metaData = this->leerMetadata();
		  }
		  else
		  {
			  cout<<"No Existe Metadata";
		    //si no hubo éxito en la apertura...
		    //limpia los flags de control de estado del archivo
			  this->archivo.clear();

		    //crea el archivo
			  this->archivo.open(this->getPath().c_str(),ios::out);
			  this->archivo.close();

		    //reabre el archivo para lectura - escritura
			  this->archivo.open(this->getPath().c_str(),ios::out|ios::in);

		    if (!this->archivo.is_open())
		      // si no se pudo crear el archivo arroja una excepción/
		      throw std::ios_base::failure("El archivo no pudo ser abierto");
		  }


	}
	if(this->getTipoArchivo().compare(BINARIO)==0){
		  /* abre el archivo en modo lectura - escritura binario*/
		  this->archivo.open(this->getPath().c_str(),
		                                ios::in |ios::out |ios::binary);

		  /* determina si tuvo éxito la apertura del archivo */
		  if (this->archivo.is_open()) {
			  cout<<"Existe Metadata";
			  this->metaData = this->leerMetadata();
		  }else{
			  cout<<"No Existe Metadata";
		    /* limpia los flags de control de estado del archivo */
		    this->archivo.clear();

		    /* crea el archivo */
		    this->archivo.open(this->getPath().c_str(),
		                                  ios::out | ios::binary);
		    this->archivo.close();

		    /* reabre el archivo para lectura - escritura binario */
		    this->archivo.open(this->getPath().c_str(),
		                                  ios::in|ios::out|ios::binary);

		    /* verifica que haya podido crear el archivo */
		    if (! this->archivo.is_open())

		      /* arroja una excepción */
		      throw string("El archivo no pudo ser abierto");
		  }


	}

}
void Archivo::cerrar(){
	this->archivo.close();

}

std::string Archivo::leerMetadata(){
	unsigned short metaDataSize;
	std::string datos = "";

	this->archivo.read((char*)&metaDataSize,sizeof(metaDataSize));
	this->metadataSize = metaDataSize;

	char* buffer = new char[metaDataSize];
	this->leer(buffer,this->metadataSize);
	datos = buffer;
	delete buffer;

	std::cout<<"Metadata: " << datos <<endl;
	return buffer;
}

void Archivo::escribirMetadata(std::string metadata){
	unsigned short metaDataSize;
	std::stringstream flujo;
	int tamanio = metadata.length();

	this->metadataSize = tamanio;
	metaDataSize = tamanio;
	this->guardar((char*)&metaDataSize,sizeof(metaDataSize));

	//flujo<< tamanio;
	this->metaData = /*flujo.str() + DELIMITADOR +*/ metadata;
	this->guardar(this->metaData.c_str(),this->metaData.length());

}

void Archivo::guardar(std::string registro){
	/* verifica que el archivo esta abierto */
	if (this->archivo.is_open()) {
		this->irAlFinal();
		//intenta escribir la cadena en el archivo
		this->archivo << registro;

		if (archivo.fail())
			// si se produjo un error, arroja una excepción
			throw std::ios_base::failure("No se pudo escribir correctamente la cadena");
	} else {
		/* arroja una excepción porque el archivo no está abierto */
		throw string("El archivo no esta abierto");
	}

}
void Archivo::guardar(const char* registro,int tamanioRegistro){

	/* verifica que el archivo esté abierto */
	if (this->archivo.is_open()) {
		this->irAlFinal();
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

void Archivo::leer(std::string& datos){

  /* verifica que el archivo esté abierto */
  if (this->archivo.is_open()) {

    /* lee del archivo una linea */
   std::getline(this->archivo,datos);

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

}
std::string Archivo::toString(){
	return "Archivo";
}




/**
 * Posiciona el cursor al comienzo del archivo
 */
void Archivo::irAlPrincipio() {
	this->archivo.tellg();
	this->archivo.clear();
	this->archivo.seekg(0);
	this->archivo.seekp(0);
	this->archivo.tellg();
}

/**
 * Posiciona el cursor al final del archivo
 */
void Archivo::irAlFinal() {
	this->archivo.tellg();
	this->archivo.clear();
	this->archivo.seekg(0, ios::end);
	this->archivo.seekp(0, ios::end);
	this->archivo.tellg();
}
/*----------------------------------------------------------------------------*/
long int Archivo::posicion(int tamanioRegistro) {

  long int pos = 0;

  /* verifica que el archivo esté abierto */
  if (this->archivo.is_open())

    /* calcula el número de registro según la posición del byte actual */
    pos = this->archivo.tellg() / tamanioRegistro;

  else
    /* arroja una excepción porque el archivo no está abierto */
    throw string("El archivo no está abierto");

  return pos;
}
/*----------------------------------------------------------------------------*/
void Archivo::posicionarse(long int posicion,int tamanioRegistro) {

  /* verifica que el archivo esté abierto */
  if (this->archivo.is_open()) {

    /* mueve la posición actual según sea el tamano del registro */
	  this->archivo.seekg(posicion * tamanioRegistro,ios_base::beg);

    /* chequea si se ha producido un error */
    if (this->archivo.fail())
      /* arroja una excepción ante la imposibilidad de leer un reg */
      throw string("No se pudo posicionar correctamente el registro");
  }
  else
    /* arroja una excepción porque el archivo no está abierto */
    throw string("El archivo no está abierto");
}
